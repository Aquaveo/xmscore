//------------------------------------------------------------------------------
/// \file
/// \brief Functions and macros for assertion and checking for errors.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmscore/misc/XmError.h>

// 3. Standard Library Headers
// 4. External Library Headers

// 5. Shared Headers

// 6. Non-shared Headers

#pragma warning(disable : 4127) // some tests use constant arguments to if() statements in macros

namespace xms
{
int XM0 = 0; ///< avoid warning
int XM1 = 1; ///< avoid warning

//------------------------------------------------------------------------------
/// \brief Stores whether we want XM_ASSERT to do something or not.
/// \return Reference to a bool.
//------------------------------------------------------------------------------
bool& xmAsserting()
{
  static bool m_asserting = true;
  return m_asserting;
} // xmAsserting

} // namespace xms

#ifdef CXX_TEST
///////////////////////////////////////////////////////////////////////////////
// TESTS
///////////////////////////////////////////////////////////////////////////////

#include <xmscore/misc/boost_defines.h>
#include <cxxtest/TestSuite.h>
#include <xmscore/misc/XmError.t.h>

namespace xms
{
namespace
{ // unnamed namespace

//------------------------------------------------------------------------------
/// \brief Use this class to do a scoped assert disable
//------------------------------------------------------------------------------
class XmAssertScopedDisable
{
  bool const m_initialValue;

public:
  XmAssertScopedDisable() // remember then disable
  : m_initialValue(xmAsserting())
  {
    xmAsserting() = false;
  };
  ~XmAssertScopedDisable() // restore
  {
    xmAsserting() = m_initialValue;
  };
}; // XmAssertDisable
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void iTest_XM_ENSURE_TRUE_VOID(bool a_assert)
{
  char* foo = new char[123];
  XM_ENSURE_TRUE_VOID(foo);           // should pass
  XM_ENSURE_TRUE_VOID_NO_ASSERT(foo); // should pass

  delete[] foo;
  foo = nullptr;
  if (a_assert)
  {
    XmAssertScopedDisable disable;
    XM_ENSURE_TRUE_VOID(foo); // should return
  }
  else
  {
    XM_ENSURE_TRUE_VOID_NO_ASSERT(foo); // should return
  }

  TS_FAIL("iTest_XM_ENSURE_TRUE_VOID"); // shouldn't get here
} // iTest_XM_ENSURE_TRUE_VOID

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void iTest_XM_ENSURE_TRUE_T(bool a_assert)
{
  try
  {
    char* foo = new char[123];
    XM_ENSURE_TRUE_T(foo, "1");           // should pass
    XM_ENSURE_TRUE_T_NO_ASSERT(foo, "1"); // should pass

    delete[] foo;
    foo = nullptr;
    if (a_assert)
    {
      XmAssertScopedDisable disable;
      XM_ENSURE_TRUE_T(foo, std::runtime_error("2")); // should throw
    }
    else
    {
      XM_ENSURE_TRUE_T_NO_ASSERT(foo, std::runtime_error("2")); // should throw
    }

    TS_FAIL("iTest_XM_ENSURE_TRUE_T"); // shouldn't get here
  }
  catch (std::runtime_error& e)
  {
    std::string s = e.what();
    TS_ASSERT_EQUALS(s, "2");
  }
} // iTest_XM_ENSURE_TRUE_T
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_ENSURE_TRUE_ptr(bool a_assert)
{
  char* foo = new char[123];
  XM_ENSURE_TRUE(foo, XR_FAILURE);           // should pass
  XM_ENSURE_TRUE_NO_ASSERT(foo, XR_FAILURE); // should pass

  delete[] foo;
  foo = nullptr;
  if (a_assert)
  {
    XmAssertScopedDisable disable;
    XM_ENSURE_TRUE(foo, XR_FAILURE); // should return
  }
  else
  {
    XM_ENSURE_TRUE_NO_ASSERT(foo, XR_FAILURE); // should pass
  }

  TS_FAIL("iTest_XM_ENSURE_TRUE_ptr"); // shouldn't get here
  return XR_FAILURE;
} // iTest_XM_ENSURE_TRUE_ptr
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_ENSURE_TRUE_boost_ptr(bool a_assert)
{
  BSHP<char> foo(new char(123));
  XM_ENSURE_TRUE(foo, XR_FAILURE);           // should pass
  XM_ENSURE_TRUE_NO_ASSERT(foo, XR_FAILURE); // should pass

  foo.reset();
  if (a_assert)
  {
    XmAssertScopedDisable disable;
    XM_ENSURE_TRUE(foo, XR_FAILURE); // should return
  }
  else
  {
    XM_ENSURE_TRUE_NO_ASSERT(foo, XR_FAILURE); // should pass
  }

  TS_FAIL("iTest_XM_ENSURE_TRUE_boost_ptr"); // shouldn't get here
  return XR_FAILURE;
} // iTest_XM_ENSURE_TRUE_boost_ptr
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void iTest_XM_ENSURE_SUCCESS_VOID(bool a_assert)
{
  xmresult foo = XR_SUCCESS;
  XM_ENSURE_SUCCESS_VOID(foo);           // should pass
  XM_ENSURE_SUCCESS_VOID_NO_ASSERT(foo); // should pass

  foo = XR_FAILURE;
  if (a_assert)
  {
    XmAssertScopedDisable disable;
    XM_ENSURE_SUCCESS_VOID(foo); // should return
  }
  else
  {
    XM_ENSURE_SUCCESS_VOID_NO_ASSERT(foo); // should pass
  }

  TS_FAIL("iTest_XM_ENSURE_SUCCESS_VOID"); // shouldn't get here
} // iTest_XM_ENSURE_SUCCESS_VOID
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_ENSURE_SUCCESS(bool a_assert)
{
  xmresult foo = XR_SUCCESS;
  XM_ENSURE_SUCCESS(foo, XR_FAILURE);           // should pass
  XM_ENSURE_SUCCESS_NO_ASSERT(foo, XR_FAILURE); // should pass

  foo = XR_FAILURE;
  if (a_assert)
  {
    XmAssertScopedDisable disable;
    XM_ENSURE_SUCCESS(foo, XR_FAILURE); // should return
  }
  else
  {
    XM_ENSURE_SUCCESS_NO_ASSERT(foo, XR_FAILURE); // should pass
  }

  TS_FAIL("iTest_XM_ENSURE_SUCCESS"); // shouldn't get here
  return XR_FAILURE;
} // iTest_XM_ENSURE_SUCCESS
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_ENSURE_SUCCESS_T(bool a_assert)
{
  try
  {
    xmresult foo = XR_SUCCESS;
    XM_ENSURE_SUCCESS_T(foo, XR_FAILURE);           // should pass
    XM_ENSURE_SUCCESS_T_NO_ASSERT(foo, XR_FAILURE); // should pass

    foo = XR_FAILURE;
    if (a_assert)
    {
      XmAssertScopedDisable disable;
      XM_ENSURE_SUCCESS_T(foo, XR_FAILURE); // should throw
    }
    else
    {
      XM_ENSURE_SUCCESS_T_NO_ASSERT(foo, XR_FAILURE); // should pass
    }

    TS_FAIL("iTest_XM_ENSURE_SUCCESS"); // shouldn't get here
  }
  catch (xmresult& e)
  {
    TS_ASSERT_EQUALS(e, XR_FAILURE);
    return XR_SUCCESS;
  }
  return XR_FAILURE;
} // iTest_XM_ENSURE_SUCCESS_T
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_RETURN_XMRESULT_bool(bool a)
{
  XM_RETURN_XMRESULT(a);
} // iTest_XM_RETURN_XMRESULT_bool
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_RETURN_XMRESULT_boost_ptr_true()
{
  BSHP<char> foo(new char(123));
  XM_RETURN_XMRESULT(foo);
} // iTest_XM_RETURN_XMRESULT_boost_ptr_true
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
xmresult iTest_XM_RETURN_XMRESULT_boost_ptr_false()
{
  BSHP<int> p;
  XM_RETURN_XMRESULT(p);
} // iTest_XM_RETURN_XMRESULT_boost_ptr_false

} // unnamed namespace

} // namespace xms

////////////////////////////////////////////////////////////////////////////////
/// \class XmErrorUnitTests
/// \brief Unit tests for XmError.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Tests for XmError.
//------------------------------------------------------------------------------
void XmErrorUnitTests::test1()
{
  // TS_FAIL("XmErrorUnitTests::test1");

  // XM_ENSURE_TRUE

  xms::iTest_XM_ENSURE_TRUE_VOID(false);
  xms::iTest_XM_ENSURE_TRUE_VOID(true);

  xms::xmresult rv = xms::iTest_XM_ENSURE_TRUE_ptr(false);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);
  rv = xms::iTest_XM_ENSURE_TRUE_ptr(true);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);

  rv = xms::iTest_XM_ENSURE_TRUE_boost_ptr(false);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);
  rv = xms::iTest_XM_ENSURE_TRUE_boost_ptr(true);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);

  // XM_ENSURE_SUCCESS

  xms::iTest_XM_ENSURE_SUCCESS_VOID(false);
  xms::iTest_XM_ENSURE_SUCCESS_VOID(true);

  rv = xms::iTest_XM_ENSURE_SUCCESS(false);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);
  rv = xms::iTest_XM_ENSURE_SUCCESS(true);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);

  xms::iTest_XM_ENSURE_SUCCESS_T(false);
  xms::iTest_XM_ENSURE_SUCCESS_T(true);

  // XM_RETURN_RESULT

  rv = xms::iTest_XM_RETURN_XMRESULT_bool(true);
  TS_ASSERT_EQUALS(rv, xms::XR_SUCCESS);

  rv = xms::iTest_XM_RETURN_XMRESULT_bool(false);
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);

  rv = xms::iTest_XM_RETURN_XMRESULT_boost_ptr_true();
  TS_ASSERT_EQUALS(rv, xms::XR_SUCCESS);

  rv = xms::iTest_XM_RETURN_XMRESULT_boost_ptr_false();
  TS_ASSERT_EQUALS(rv, xms::XR_FAILURE);

} // XmErrorUnitTests::test1
//------------------------------------------------------------------------------
/// \brief Tests for XM_ASSERT.
//------------------------------------------------------------------------------
void XmErrorUnitTests::test_XM_ASSERT()
{
  using namespace xms;
  // TS_FAIL("XmErrorUnitTests::test_XM_ASSERT");

  TS_ASSERT_EQUALS(xms::xmAsserting(), true); // this is the default
  // XM_ASSERT(false); // this should assert. It did when it was not commented

  XmAssertScopedDisable disable;
  XM_ASSERT(false); // now it should do nothing
} // XmErrorUnitTests::test_XM_ASSERT

#endif
