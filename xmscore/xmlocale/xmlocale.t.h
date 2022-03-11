#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------
#include <cxxtest/TestSuite.h>

/// \brief tests for translation
class LocaleUnitTests : public CxxTest::TestSuite
{
public:
  void setUp();
  void tearDown();

  void testMarkedUntranslated();
  void testMarkedTranslated();
  void testUnmarked();
  void testNullMarked();
}; // LocaleUnitTests
#endif
