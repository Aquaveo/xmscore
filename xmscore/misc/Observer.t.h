#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

class ObserverIntermediateTests : public CxxTest::TestSuite
{
public:
#ifndef CXXTEST4
  virtual const CxxTest::TestGroup& group();
#endif
  void testTimeRemaining();
  void testMockObserver();
};
#endif
