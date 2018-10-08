#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#include <cxxtest/TestSuite.h>

/// tests for points classes
class PtUnitTests : public CxxTest::TestSuite
{
public:
  void testIt();
  void testStreams();
};
#endif
