#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Routines for creating and writing to logs and stacking errors.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
// 1. Standard library headers

// 3. Standard Library Headers
#include <vector>

// 4. External Library Headers
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

// 5. Shared Headers
#include <xmscore/misc/Singleton.h>

// 6. Non-shared Headers

//----- Defines ----------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief Log message which can have a log type (Debug, Stackable, Gui).
/// \param[in] A: Message type (see `#xmlog::MessageTypeEnum`).
/// \param[in] B: Message to be logged. Gets converted to a std::string.
/// \see xmslog::LogLevelEnum
//------------------------------------------------------------------------------
#if _WIN32 || _WIN64 // WIN
// An odd ball string expansion requirement for the preprocessor
#define XM_UTIL2(line) UTIL##line
#define XM_UTIL(line) XM_UTIL2(line)
#define XM_LOG(A, B)                                      \
  ::xms::XmLog::Instance().Log(__FILE__, __LINE__, A, B); \
  \
static std::string XM_UTIL(__LINE__);                     \
  \
if(!XM_UTIL(__LINE__).size())                             \
  {                                                       \
    XM_UTIL(__LINE__) = xms::g_xmUtil;                    \
  \
}

namespace xms
{
//----------------------------------------------------------------------------
/// \brief Global string that instances of XM_LOG will copy from
//----------------------------------------------------------------------------
extern std::string g_xmUtil;
}
#else // NOT WIN
#define XM_LOG(A, B) ::xms::XmLog::Instance().Log(__FILE__, __LINE__, A, B);
#endif // NOT WIN

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

// Define Severity Levels

/// Severity                                      Details
/// -----------------------------------------------------
/// Info                            Informational message
/// Warning                  Non-critical warning message
/// Error                          Critical error message
/// Debug                   Details of internal operation

///
namespace xmlog
{
/// Log level for XM_LOG
enum MessageTypeEnum {
  info,    ///< Informational message for the user
  warning, ///< Warning message for the user
  error,   ///< Critical error message for the user
  debug    ///< Details of internal operation
};
/*
//----------------------------------------------------------------------------
/// \brief Get MessageTypeEnum as a string
//----------------------------------------------------------------------------
static std::string MessageTypeStr(MessageTypeEnum a_level) {
  if (a_level == info) return "INFO";
  if (a_level == warning) return "WARNING";
  if (a_level == error) return "ERROR";
  if (a_level == debug) return "DEBUG";
  return "";
} // MessageTypeStr
*/
}

namespace xms
{
/// Callback to return the name of the log file
typedef boost::function<std::string()> XmLogFilenameCallback;

/// Container type used to store log messages
typedef std::vector<std::pair<xmlog::MessageTypeEnum, std::string>> MessageStack;

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class XmLog
////////////////////////////////////////////////////////////////////////////////
class XmLog : public xms::Singleton<XmLog>
{
  /// Allow Singleton access to private members
  friend Singleton<XmLog>;

public:
  ~XmLog();
  void Log(const char* const a_file,
           int a_line,
           xmlog::MessageTypeEnum a_level,
           std::string a_message);
  int ErrCount();
  MessageStack GetAndClearStack();
  std::string GetAndClearStackStr();
  static XmLogFilenameCallback& LogFilenameCallback();
  static std::string LogFilename();

private:
  /// Constructor hidden and not implemented
  XmLog();
  struct Impl;
  /// Implementation pointer
  boost::scoped_ptr<Impl> m;
}; // class XmLog

//----- Global functions -------------------------------------------------------

} // namespace xms
