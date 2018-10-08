#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup xmscore_misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class StringUtilUnitTests : public CxxTest::TestSuite
{
public:
  void testExtendedASCII();
  void testImplodeExplode();
  void testSuIndexOfElem();
  void testSplit();
  void testMakeUnique();
  void testTrim();
  void testReplace();
  void testCountChar();
  void testNumAndSciNot();
  void testToUpper();
  void test_str2int();
  void testMisc();
  void testXmCommaNumpunct();
  void testSuSimplified();
  void testSuIcontains();
  void testSuVecContainsStr();
  void test_STRstd();
  void testPrec();
  void testSTR();
}; // StringUtilUnitTests

#endif
