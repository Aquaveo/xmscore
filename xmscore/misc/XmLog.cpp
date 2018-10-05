//------------------------------------------------------------------------------
/// \file
/// \brief Routines for creating and writing to logs and stacking errors.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
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
#include <boost/filesystem.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

// 5. Shared code headers
#ifdef CXX_TEST
#include <xmscore/testing/TestTools.h>
#endif

// 6. Non-shared code headers

//----- Namespace declaration --------------------------------------------------
namespace bfs = boost::filesystem;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;

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
/// Used for convenience to declare a global log object
BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(xms_global_log,
                                    boost::log::sources::severity_logger_mt<xmlog::MessageTypeEnum>)
{
  boost::log::sources::severity_logger_mt<xmlog::MessageTypeEnum> lg;
  // Configure the logger here
  lg.add_attribute("TimeStamp", boost::log::attributes::local_clock());
  lg.add_attribute("Process", boost::log::attributes::current_process_name());
  lg.add_attribute("Scope", boost::log::attributes::named_scope());
  return lg;
}
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", xmlog::MessageTypeEnum)
// BOOST_LOG_ATTRIBUTE_KEYWORD(file_name, "FileName", const char* const)
// BOOST_LOG_ATTRIBUTE_KEYWORD(line_num, "LineNumber", int)

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
  // Setup the formatter for file sinks
  boost::log::formatter file_fmt = expr::stream << "[" << severity << "]"
                                                << "["
                                                << expr::format_date_time<boost::posix_time::ptime>(
                                                     "TimeStamp", "%Y-%m-%d %H:%M:%S")
                                                << "]"
                                                << "[" << expr::attr<std::string>("Process") << ":"
                                                << expr::attr<std::string>("FileName") << ":"
                                                << expr::attr<int>("LineNumber") << "]"
                                                << ": " << expr::smessage;

  // Initialize sinks
  // Create a backend and attach a couple of streams to it
  boost::shared_ptr<sinks::text_ostream_backend> backend =
    boost::make_shared<sinks::text_ostream_backend>();
  // backend->add_stream(boost::shared_ptr< std::ostream >(&std::clog, boost::empty_deleter()));
  backend->add_stream(boost::shared_ptr<std::ostream>(new std::ofstream(XmLog::LogFilename())));

  // Enable auto-flushing after each log record written
  backend->auto_flush(true);

  // Wrap it into the frontend and register in the core.
  // The backend requires synchronization in the frontend.
  typedef sinks::synchronous_sink<sinks::text_ostream_backend> sink_t;
  boost::shared_ptr<sink_t> sink(new sink_t(backend));
  sink->set_formatter(file_fmt);
  boost::log::core::get()->add_sink(sink);

  // Add attributes
  boost::log::add_common_attributes();

  // Add Log to BugTracker
  std::string tmp = XmLog::LogFilename();
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

  if (a_level == xmlog::debug)
  {
    BOOST_LOG_SEV(xms_global_log::get(), a_level)
      << boost::log::add_value("FileName", a_file) << boost::log::add_value("LineNumber", a_line)
      << a_message;
  }
  else
  {
    m->m_stackedMessages.push_back(std::make_pair(a_level, a_message));
    BOOST_LOG_SEV(xms_global_log::get(), a_level)
      << boost::log::add_value("FileName", a_file) << boost::log::add_value("LineNumber", a_line)
      << a_message;
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
    if (fg_logPath.empty())
    {
      bfs::path p = bfs::temp_directory_path() / bfs::unique_path();
      fg_logPath = p.string() + "debug.log";
    }
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

  // BOOST_LOG_FUNCTION();
  // std::string s = BOOST_CURRENT_FUNCTION;
  // std::string s2 = s;
  // TS_ASSERT_EQUALS(s2, s);
}
#endif

#pragma warning(pop)
