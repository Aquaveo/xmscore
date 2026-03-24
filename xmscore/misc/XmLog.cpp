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
#include <fstream>
#include <sstream>

// 4. External library headers
#include <chrono>
#include <ctime>
#include <iomanip>
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
/// \brief Formatting Logic for Severity
/// \param strm: ostream
/// \param lvl: message type enum.
/// \return ostream.
//------------------------------------------------------------------------------
template <typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm,
                                                      xmlog::MessageTypeEnum lvl)
{
  static const char* const str[] = {"   info", "warning", "  error", "  debug"};
  if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
    strm << str[lvl];
  else
    strm << static_cast<int>(lvl);
  return strm;
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
  std::ostringstream ss;
  ss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
  return ss.str();
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
  /// Log file stream
  std::ofstream m_logFile;

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
    m->m_logFile.open(filename);
  }
} // XmLog::XmLog
//------------------------------------------------------------------------------
/// \brief destructor
//------------------------------------------------------------------------------
XmLog::~XmLog()
{
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
    if (m->m_logFile.is_open())
    {
      m->m_logFile << "[" << a_level << "]"
                   << "[" << iTimestamp() << "]"
                   << "[" << iProcessName() << ":" << a_file << ":" << a_line << "]"
                   << ": " << a_message << "\n";
      m->m_logFile.flush();
    }
  }
} // XmLog::Log
//------------------------------------------------------------------------------
/// \brief Returns the current count of the error stack
/// \return Current count of the error stack.
//------------------------------------------------------------------------------
int XmLog::ErrCount()
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
#endif

#pragma warning(pop)
