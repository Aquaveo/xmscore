#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Functions and macros for assertion and checking for errors.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// 5. Shared Headers
#include <xmscore/misc/XmLog.h>

// 6. Non-shared Headers

//----- Functions --------------------------------------------------------------

namespace xms
{
bool& xmAsserting();
extern int XM0, XM1; // replacements for 0 and 1 which do not cause warning C4127: conditional
                     // expression is constant

////////////////////////////////////////////////////////////////////////////////
// Some code copied from Mozilla. Code is under Mozilla Public License, v. 2.0
// which can be obtained at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Like Mozilla's nsresult.
//------------------------------------------------------------------------------
enum xmresult { XR_SUCCESS = 0, XR_FAILURE = 1 };
//------------------------------------------------------------------------------
/// \brief Like Mozilla's NS_LIKELY in their Likely.h file
//------------------------------------------------------------------------------
#define XM_LIKELY(x) (!!(x))
#define XM_UNLIKELY(x) (!!(x)) ///< \brief Like Mozilla's NS_LIKELY in their Likely.h file
//------------------------------------------------------------------------------
/// \brief Like Mozilla's NS_FAILED in their nsError.h file
/// \param _xmresult result to test
/// \return integer 0 or 1
//------------------------------------------------------------------------------
inline unsigned int XM_FAILED_impl(xmresult _xmresult)
{
  // return static_cast<uint32_t>(_xmresult) & 0x80000000;
  return static_cast<unsigned int>(_xmresult) & 0x00000001;
}
#define XM_FAILED(_xmresult) ((bool)XM_UNLIKELY(XM_FAILED_impl(_xmresult)))   ///< macro
#define XM_SUCCEEDED(_xmresult) ((bool)XM_LIKELY(!XM_FAILED_impl(_xmresult))) ///< macro
//------------------------------------------------------------------------------
/// \brief Does a regular ASSERT if xmAsserting, otherwise does nothing.
//------------------------------------------------------------------------------
#ifdef _DEBUG
#define XM_ASSERT(x)        \
  \
{                        \
    if (xms::xmAsserting()) \
      assert(x);            \
  \
}
#else
#define XM_ASSERT(x) ((void)0)
#endif
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
///
/// Like Mozilla's NS_ENSURE_SUCCESS in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to xms::xmresult.
/// \param[in] ret: Value returned if x evaluates to xms::XR_FAILURE (any type).
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_5(x, ret, lvl, msg, ast)                            \
  do                                                                          \
  {                                                                           \
    xms::xmresult __rv = x; /* Don't evaluate |x| more than once */           \
    if (XM_FAILED(__rv))                                                      \
    {                                                                         \
      XM_LOG(lvl, msg);                                                       \
      if (ast)                                                                \
      {                                                                       \
        XM_ASSERT(!#x);                                                       \
      }                                                                       \
      return ret;                                                             \
    }                                                                         \
  } while (xms::XM0)
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
///
/// Like Mozilla's NS_ENSURE_SUCCESS in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to xms::xmresult.
/// \param[in] ret: Value returned if x evaluates to xms::XR_FAILURE (any type).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_3(x, ret, ast) \
  XM_ENSURE_SUCCESS_5(x, ret, xmlog::debug, N_("XM_ENSURE_SUCCESS(" #x ", " #ret ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS(...)                                                           \
  BOOST_PP_CAT(                                                                          \
    BOOST_PP_OVERLOAD(XM_ENSURE_SUCCESS_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to xms::XR_FAILURE and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_NO_ASSERT(...)                                                 \
  BOOST_PP_CAT(                                                                          \
    BOOST_PP_OVERLOAD(XM_ENSURE_SUCCESS_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
///
/// Like Mozilla's NS_ENSURE_SUCCESS in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to xms::xmresult.
/// \param[in] ret: Value returned if x evaluates to xms::XR_FAILURE (any type).
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_T_5(x, ret, lvl, msg, ast)                          \
  do                                                                          \
  {                                                                           \
    xms::xmresult __rv = x; /* Don't evaluate |x| more than once */           \
    if (XM_FAILED(__rv))                                                      \
    {                                                                         \
      XM_LOG(lvl, msg);                                                       \
      if (ast)                                                                \
      {                                                                       \
        XM_ASSERT(!#x);                                                       \
      }                                                                       \
      throw(ret);                                                             \
    }                                                                         \
  } while (xms::XM0)
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
///
/// Like Mozilla's NS_ENSURE_SUCCESS in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to xms::xmresult.
/// \param[in] ret: Value returned if x evaluates to xms::XR_FAILURE (any type).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_T_3(x, ret, ast) \
  XM_ENSURE_SUCCESS_T_5(x, ret, xmlog::debug, N_("XM_ENSURE_SUCCESS_T(" #x ", " #ret ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_T(...)                                                           \
  BOOST_PP_CAT(                                                                            \
    BOOST_PP_OVERLOAD(XM_ENSURE_SUCCESS_T_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to xms::XR_FAILURE and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_T_NO_ASSERT(...)                                                 \
  BOOST_PP_CAT(                                                                            \
    BOOST_PP_OVERLOAD(XM_ENSURE_SUCCESS_T_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
///
/// Like Mozilla's NS_ENSURE_SUCCESS_VOID in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to xms::xmresult.
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_VOID_4(x, lvl, msg, ast)                            \
  do                                                                          \
  {                                                                           \
    xms::xmresult __rv = x;                                                   \
    if (XM_FAILED(__rv))                                                      \
    {                                                                         \
      XM_LOG(lvl, msg);                                                       \
      if (ast)                                                                \
      {                                                                       \
        XM_ASSERT(!#x);                                                       \
      }                                                                       \
      return;                                                                 \
    }                                                                         \
  } while (xms::XM0)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
///
/// Like Mozilla's NS_ENSURE_SUCCESS_VOID in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to xms::xmresult.
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_VOID_2(x, ast) \
  XM_ENSURE_SUCCESS_VOID_4(x, xmlog::debug, N_("XM_ENSURE_SUCCESS_VOID(" #x ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to xms::XR_FAILURE, logs, and
///        optionally asserts.
/// \param ... Variable input
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_VOID(...)                                                           \
  BOOST_PP_CAT(                                                                               \
    BOOST_PP_OVERLOAD(XM_ENSURE_SUCCESS_VOID_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to xms::XR_FAILURE and logs.
/// \param ... Variable input
//------------------------------------------------------------------------------
#define XM_ENSURE_SUCCESS_VOID_NO_ASSERT(...)                                                 \
  BOOST_PP_CAT(                                                                               \
    BOOST_PP_OVERLOAD(XM_ENSURE_SUCCESS_VOID_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c false (any type).
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_5(x, ret, lvl, msg, ast)                               \
  do                                                                          \
  {                                                                           \
    if (XM_UNLIKELY(!(x)))                                                    \
    {                                                                         \
      XM_LOG(lvl, msg);                                                       \
      if (ast)                                                                \
      {                                                                       \
        XM_ASSERT(!#x);                                                       \
      }                                                                       \
      return ret;                                                             \
    }                                                                         \
  } while (xms::XM0)
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c false (any type).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_3(x, ret, ast) \
  XM_ENSURE_TRUE_5(x, ret, xmlog::debug, N_("XM_ENSURE_TRUE(" #x ", " #ret ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_2(x, ast) XM_ENSURE_TRUE_VOID_2(x, ast)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false, logs, and optionally
///        asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE(...)                                                                      \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(XM_ENSURE_TRUE_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
               BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_NO_ASSERT(...)                                                            \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(XM_ENSURE_TRUE_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
               BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Throws ret if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c false (any type).
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_T_5(x, ret, lvl, msg, ast)                               \
  do                                                                            \
  {                                                                             \
    if (XM_UNLIKELY(!(x)))                                                      \
    {                                                                           \
      XM_LOG(lvl, msg);                                                         \
      if (ast)                                                                  \
      {                                                                         \
        XM_ASSERT(!#x);                                                         \
      }                                                                         \
      throw(ret);                                                               \
    }                                                                           \
  } while (xms::XM0)
//------------------------------------------------------------------------------
/// \brief Throws ret if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c false (any type).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_T_3(x, ret, ast) \
  XM_ENSURE_TRUE_T_5(x, ret, xmlog::debug, N_("XM_ENSURE_TRUE_T(" #x ", " #ret ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Throws ret if \a x evaluates to \c false, logs, and optionally
///        asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_T(...)                                                                      \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(XM_ENSURE_TRUE_T_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
               BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Throws ret if \a x evaluates to \c false and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_T_NO_ASSERT(...)                                                            \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(XM_ENSURE_TRUE_T_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
               BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_VOID_4(x, lvl, msg, ast)                                 \
  do                                                                            \
  {                                                                             \
    if (XM_UNLIKELY(!(x)))                                                      \
    {                                                                           \
      XM_LOG(lvl, msg);                                                         \
      if (ast)                                                                  \
      {                                                                         \
        XM_ASSERT(!#x);                                                         \
      }                                                                         \
      return;                                                                   \
    }                                                                           \
  } while (xms::XM0)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_TRUE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_VOID_2(x, ast) \
  XM_ENSURE_TRUE_VOID_4(x, xmlog::debug, N_("XM_ENSURE_TRUE_VOID(" #x ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false, logs, and optionally
///        asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_VOID(...)                                                           \
  BOOST_PP_CAT(                                                                            \
    BOOST_PP_OVERLOAD(XM_ENSURE_TRUE_VOID_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c false and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_TRUE_VOID_NO_ASSERT(...)                                                 \
  BOOST_PP_CAT(                                                                            \
    BOOST_PP_OVERLOAD(XM_ENSURE_TRUE_VOID_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to \c true, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_FALSE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c true (any type).
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_5(x, ret, lvl, msg, ast) XM_ENSURE_TRUE_5(!(x), ret, lvl, msg, ast)
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to \c true, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_FALSE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c true (any type).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_3(x, ret, ast) \
  XM_ENSURE_FALSE_5(x, ret, xmlog::debug, N_("XM_ENSURE_FALSE(" #x ", " #ret ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to \c true, logs, and optionally
///        asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE(...)                                                                      \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(XM_ENSURE_FALSE_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
               BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns \a ret if \a x evaluates to \c true and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_NO_ASSERT(...)                                                            \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(XM_ENSURE_FALSE_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
               BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to \c true, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_FALSE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c true (any type).
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_T_5(x, ret, lvl, msg, ast) XM_ENSURE_TRUE_T(!(x), ret, lvl, msg, ast)
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to \c true, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_FALSE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ret: Value returned if x evaluates to \c true (any type).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_T_3(x, ret, ast) \
  XM_ENSURE_FALSE_T_5(x, ret, xmlog::debug, N_("XM_ENSURE_FALSE_T(" #x ", " #ret ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to \c true, logs, and optionally
///        asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_T(...)                                                           \
  BOOST_PP_CAT(                                                                          \
    BOOST_PP_OVERLOAD(XM_ENSURE_FALSE_T_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Throws \a ret if \a x evaluates to \c true and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_T_NO_ASSERT(...)                                                 \
  BOOST_PP_CAT(                                                                          \
    BOOST_PP_OVERLOAD(XM_ENSURE_FALSE_T_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c true, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_FALSE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] lvl: Log level xmlog::LogLevelEnum.
/// \param[in] msg: Log message (\c std::string).
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_VOID_4(x, lvl, msg, ast) XM_ENSURE_TRUE_VOID_4(!(x), lvl, msg, ast)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c true, logs, and optionally
///        asserts.
///
/// Like Mozilla's NS_ENSURE_FALSE in their nsDebug.h file.
/// \param[in] x:   Expression that evaluates to a bool \c true or \c false.
/// \param[in] ast: Asserts if true (\c bool).
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_VOID_2(x, ast) \
  XM_ENSURE_FALSE_VOID_4(x, xmlog::debug, N_("XM_ENSURE_FALSE_VOID(" #x ") failed"), ast)
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c true, logs, and optionally
///        asserts.
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_VOID(...)                                                           \
  BOOST_PP_CAT(                                                                             \
    BOOST_PP_OVERLOAD(XM_ENSURE_FALSE_VOID_, __VA_ARGS__, xms::XM1)(__VA_ARGS__, xms::XM1), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns (void) if \a x evaluates to \c true and logs.
//------------------------------------------------------------------------------
#define XM_ENSURE_FALSE_VOID_NO_ASSERT(...)                                                 \
  BOOST_PP_CAT(                                                                             \
    BOOST_PP_OVERLOAD(XM_ENSURE_FALSE_VOID_, __VA_ARGS__, xms::XM0)(__VA_ARGS__, xms::XM0), \
    BOOST_PP_EMPTY())
//------------------------------------------------------------------------------
/// \brief Returns XR_SUCCESS if cond == true, else XR_FAILURE. Useful to
///        convert a true/false return value into an xmresult return value.
/// \param[in] x: Expression to be evaluated (expression of any type).
//------------------------------------------------------------------------------
#define XM_RETURN_XMRESULT(x)                        \
  {                                                  \
    return (XM_LIKELY(x) ? XR_SUCCESS : XR_FAILURE); \
  }
} // namespace xms
