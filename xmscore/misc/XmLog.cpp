//------------------------------------------------------------------------------
/// \file
/// \brief Routines for creating and writing to logs and stacking errors.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#pragma warning(push)
#pragma warning(disable : 4100) // unreferenced formal parameter
#pragma warning(disable : 4103)
#pragma warning(disable : 4512) // assignment operator could not be generated
#pragma warning(disable : 4701) // potentially uninitialized local variable
#pragma warning(disable : 4244)

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/misc/XmLog.h>

// 3. Standard library headers
#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream>

// 4. External library headers
#include <chrono>
#include <mutex>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#if !defined(__EMSCRIPTEN__)
#include <boost/filesystem.hpp>
#endif

// 5. Shared code headers
#ifdef CXX_TEST
#include <xmscore/testing/TestTools.h>
#endif

// 6. Non-shared code headers

//----- Namespace declaration --------------------------------------------------
#if !defined(__EMSCRIPTEN__)
namespace bfs = boost::filesystem;
#endif

//----- Constants / Enumerations -----------------------------------------------

//----- Forward declarations ---------------------------------------------------

//----- Global variables -------------------------------------------------------
#if _WIN32 || _WIN64 // WIN
namespace xms
{
std::string g_xmUtil;
}
#endif

//----- Structs / Classes ------------------------------------------------------

namespace xmlog
{
//------------------------------------------------------------------------------
/// \brief Return severity level as a string.
/// \param lvl: message type enum.
/// \return severity string.
//------------------------------------------------------------------------------
static const char* iSeverityStr(xmlog::MessageTypeEnum lvl)
{
  static const char* const str[] = {"   info", "warning", "  error", "  debug"};
  if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
    return str[lvl];
  return "unknown";
}

} // namespace xmlog

namespace xms
{
//------------------------------------------------------------------------------
/// \brief Return the current process name.
//------------------------------------------------------------------------------
static std::string iProcessName()
{
#if defined(_WIN32) || defined(_WIN64)
  char buf[MAX_PATH];
  DWORD len = GetModuleFileNameA(NULL, buf, MAX_PATH);
  if (len > 0)
    return bfs::path(buf).filename().string();
  return "unknown";
#elif defined(__APPLE__)
  const char* name = getprogname();
  return name ? name : "unknown";
#else
  std::ifstream comm("/proc/self/comm");
  std::string name;
  if (comm && std::getline(comm, name))
    return name;
  return "unknown";
#endif
} // iProcessName
//------------------------------------------------------------------------------
/// \brief Return current local time as a formatted string.
//------------------------------------------------------------------------------
static std::string iTimestamp()
{
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  struct tm buf;
#if defined(_WIN32) || defined(_WIN64)
  localtime_s(&buf, &time);
#else
  localtime_r(&time, &buf);
#endif
  char timeBuf[32];
  std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &buf);
  return timeBuf;
} // iTimestamp

/// Callback to return the name of the log file
static XmLogFilenameCallback fg_logFilenameCallback;

////////////////////////////////////////////////////////////////////////////////
/// \class XmLog::Impl
/// \brief implementation of XmLog
////////////////////////////////////////////////////////////////////////////////
struct XmLog::Impl
{
  Impl()
  : m_firstRun(true)
  {
  }

  /// Stack of messages that can be shown at a later time
  MessageStack m_stackedMessages;
  /// Used to setup log file first time something is logged
  bool m_firstRun;
  /// Mutex for thread-safe file writes
  std::mutex m_mutex;
  /// Log file handle (using FILE* to avoid std::ostream locale issues in shared libraries)
  FILE* m_logFile = nullptr;

  void StackedErrToStream(std::ostream& a_os);
};

//----- Internal function prototypes -------------------------------------------

//----- Function definitions ---------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class XmLog
/// \brief
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief constructor
//------------------------------------------------------------------------------
XmLog::XmLog()
: Singleton()
, m(new Impl())
{
  std::string filename = XmLog::LogFilename();
  if (!filename.empty())
  {
    m->m_logFile = std::fopen(filename.c_str(), "a");
  }
} // XmLog::XmLog
//------------------------------------------------------------------------------
/// \brief destructor
//------------------------------------------------------------------------------
XmLog::~XmLog()
{
  if (m->m_logFile)
  {
    std::fclose(m->m_logFile);
    m->m_logFile = nullptr;
  }
}
//------------------------------------------------------------------------------
/// \brief    Logs
/// \param    a_file    Source file name
/// \param    a_line    line number in source file name
/// \param    a_level   Lowest Severity level of the logged item
/// \param    a_message Message to log
//------------------------------------------------------------------------------
void XmLog::Log(const char* const a_file,
                int a_line,
                xmlog::MessageTypeEnum a_level,
                std::string a_message)
{
  if (m->m_firstRun)
  {
    m->m_firstRun = false;
    // Make sure the log file is created
    XM_LOG(xmlog::debug, "Start Log");
  }

  if (a_level != xmlog::debug)
  {
    m->m_stackedMessages.push_back(std::make_pair(a_level, a_message));
  }

  {
    std::lock_guard<std::mutex> lock(m->m_mutex);
    if (m->m_logFile)
    {
      std::string ts = iTimestamp();
      std::string proc = iProcessName();
      std::fprintf(m->m_logFile, "[%s][%s][%s:%s:%d]: %s\n",
                   xmlog::iSeverityStr(a_level), ts.c_str(), proc.c_str(),
                   a_file, a_line, a_message.c_str());
      std::fflush(m->m_logFile);
    }
  }
} // XmLog::Log
//------------------------------------------------------------------------------
/// \brief Returns the current count of the error stack
/// \return Current count of the error stack.
//------------------------------------------------------------------------------
int XmLog::ErrCount() const
{
  return (int)m->m_stackedMessages.size();
} // XmLog::ErrCount
//------------------------------------------------------------------------------
/// \brief Clears the error stack and returns its contents as a string.
/// \return Contents of the error stack as a string.
//------------------------------------------------------------------------------
std::string XmLog::GetAndClearStackStr()
{
  std::stringstream ss;
  m->StackedErrToStream(ss);
  return ss.str();
} // XmLog::GetAndClearStackStr
//------------------------------------------------------------------------------
/// \brief Returns a copy of the error stack before clearing it
/// \return MessageStack.
//------------------------------------------------------------------------------
MessageStack XmLog::GetAndClearStack()
{
  MessageStack messages = m->m_stackedMessages;
  m->m_stackedMessages.clear();
  return messages;
} // XmLog::GetAndClearStack
//------------------------------------------------------------------------------
/// \brief Set the callback that returns the log filename.
///
/// Static because the XmLog constructor needs it, so we must set it BEFORE
/// we construct the XmLog singleton.
/// \return The callback.
//------------------------------------------------------------------------------
XmLogFilenameCallback& XmLog::LogFilenameCallback()
{
  return fg_logFilenameCallback;
} // XmLog::LogFilenameCallback
//------------------------------------------------------------------------------
/// \brief Return the name of the log file.
///
/// Static because the XmLog constructor needs it, so we must set
/// LogFilenameCallback BEFORE we construct the XmLog singleton.
/// \return The name of the log file.
//------------------------------------------------------------------------------
std::string XmLog::LogFilename()
{
  if (!LogFilenameCallback().empty())
  {
    return LogFilenameCallback()(); // Call the callback function
  }
  else
  {
    static std::string fg_logPath;
#if !defined(__EMSCRIPTEN__)
    if (fg_logPath.empty())
    {
      bfs::path p = bfs::temp_directory_path() / bfs::unique_path();
      fg_logPath = p.string() + "debug.log";
    }
#endif
    return fg_logPath;
  }
} // XmLog::LogFilename
//------------------------------------------------------------------------------
/// \brief Sends error stack to passed stream. Formats for dialog box
/// \param a_os: The stream.
//------------------------------------------------------------------------------
void XmLog::Impl::StackedErrToStream(std::ostream& a_os)
{
  if (m_stackedMessages.size() > 0)
  {
    for (auto it = m_stackedMessages.begin(); it != m_stackedMessages.end(); it++)
    {
      a_os << "---" << it->second << "\n"
           << "\n";
    }
    m_stackedMessages.clear();
  }
} // XmLog::StackedErrToStream

} // namespace xms

#ifdef CXX_TEST
///////////////////////////////////////////////////////////////////////////////
// TESTS
///////////////////////////////////////////////////////////////////////////////

#include <xmscore/misc/XmLog.t.h>

namespace xms
{ // unnamed namespace

//------------------------------------------------------------------------------
/// \brief Run debug log test.
//------------------------------------------------------------------------------
void iTest_XM_LOG_debug()
{
  XM_LOG(xmlog::debug, "Debug Log Test");

  std::ifstream t(XmLog::LogFilename());
  std::string str;

  t.seekg(0, std::ios::end);
  str.reserve((int)t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  TS_ASSERT(str.find("  debug]") != std::string::npos);
  TS_ASSERT(str.find("Start Log") != std::string::npos);
  TS_ASSERT(str.find("Debug Log Test") != std::string::npos);
}
//------------------------------------------------------------------------------
/// \brief Run stackable log test.
//------------------------------------------------------------------------------
void iTest_XM_LOG_stackable()
{
  XM_LOG(xmlog::info, "Stackable Log Test");

  std::ifstream t(XmLog::LogFilename());
  std::string str;

  t.seekg(0, std::ios::end);
  str.reserve((int)t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  TS_ASSERT(str.find("  debug]") != std::string::npos);
  TS_ASSERT(str.find("Start Log") != std::string::npos);
  TS_ASSERT(str.find("Stackable Log Test") != std::string::npos);
}
//------------------------------------------------------------------------------
/// \brief Run GUI log test.
//------------------------------------------------------------------------------
void iTest_XM_LOG_gui()
{
  XM_LOG(xmlog::error, "Test Log");
}

} // xms namespace

////////////////////////////////////////////////////////////////////////////////
/// \class XmLogUnitTests
/// \brief Tests for XmLog.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test XM_LOG.
//------------------------------------------------------------------------------
void XmLogUnitTests::testAll()
{
  // Uncomment these to test but then comment them out again because we don't
  // want them to run every time

  // xms::iTest_XM_LOG_debug();
  // xms::iTest_XM_LOG_stackable();
  // xms::iTest_XM_LOG_gui();
}
//------------------------------------------------------------------------------
/// \brief Exercises the XmLog::Log path end-to-end and the message-stack
///        accessors that previously had no direct test coverage.
///
/// We intentionally do not override the LogFilenameCallback or call
/// XmLog::Delete() here.  Singleton::LogFilename is consulted only once
/// (during XmLog construction), so changing the callback at runtime would
/// have no effect; and Singleton<T>::Delete() does not compile today
/// (its body calls Instance(true, boost::shared_ptr<T>()) but Instance's
/// second parameter is T*).  That defect is flagged for developer review.
//------------------------------------------------------------------------------
void XmLogUnitTests::testLogStackAndDiskOutput()
{
  // The singleton may or may not have been instantiated by an earlier test
  // (XM_ENSURE_TRUE etc. can log through XmLog).  Drain whatever is sitting
  // on the stack so our assertions below are deterministic.
  (void)xms::XmLog::Instance().GetAndClearStack();

  XM_LOG(xmlog::info, "info-coverage");
  XM_LOG(xmlog::warning, "warn-coverage");
  XM_LOG(xmlog::error, "err-coverage");
  XM_LOG(xmlog::debug, "debug-coverage"); // debug entries are NOT stacked

  // ErrCount reflects only the three stackable messages.
  TS_ASSERT_EQUALS(3, xms::XmLog::Instance().ErrCount());

  // GetAndClearStackStr formats the stack into a single string and empties it.
  std::string stack_str = xms::XmLog::Instance().GetAndClearStackStr();
  TS_ASSERT(stack_str.find("info-coverage") != std::string::npos);
  TS_ASSERT(stack_str.find("warn-coverage") != std::string::npos);
  TS_ASSERT(stack_str.find("err-coverage") != std::string::npos);
  TS_ASSERT_EQUALS(0, xms::XmLog::Instance().ErrCount());

  // GetAndClearStack returns a (now-empty) MessageStack -- exercises the
  // alternate accessor.
  XM_LOG(xmlog::info, "stack-accessor");
  xms::MessageStack drained = xms::XmLog::Instance().GetAndClearStack();
  TS_ASSERT_EQUALS(1u, drained.size());
  TS_ASSERT_EQUALS(xmlog::info, drained[0].first);
  TS_ASSERT_EQUALS(std::string("stack-accessor"), drained[0].second);

  // Read the resolved log file back and confirm at least one of our messages
  // made it through the on-disk path.  Timestamp and process-name vary, so
  // we look for the message body only.
  std::ifstream in(xms::XmLog::LogFilename());
  std::stringstream buf;
  buf << in.rdbuf();
  std::string contents = buf.str();
  TS_ASSERT(contents.find("info-coverage") != std::string::npos);

  // Drain the stack one final time to keep state tidy for downstream tests.
  (void)xms::XmLog::Instance().GetAndClearStack();
} // XmLogUnitTests::testLogStackAndDiskOutput
#endif

#pragma warning(pop)
