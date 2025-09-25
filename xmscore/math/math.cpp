//------------------------------------------------------------------------------
/// \file
/// \ingroup math
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

#include <xmscore/math/math.h>

//----- Function definitions ---------------------------------------------------

#if CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// TESTS
////////////////////////////////////////////////////////////////////////////////

#include <xmscore/math/math.t.h>
#include <cmath> // sqrt
#include <xmscore/points/pt.h>
#include <xmscore/testing/TestTools.h>

////////////////////////////////////////////////////////////////////////////////
/// \class MathUnitTests
/// \brief Unit tests for xmscore math functions.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test xmscore math functions.
//------------------------------------------------------------------------------
void MathUnitTests::TestIt()
{
  // TS_FAIL("MathUnitTests::TestIt");

  // TS_ASSERT_EQUALS(0,1);
  TS_ASSERT_DELTA(xms::MagSquared(1, 2, 3, 4), 30.0, 0.001);
  TS_ASSERT_DELTA(xms::MagSquared(1, 2, 3), 14.0, 0.001);
  TS_ASSERT_DELTA(xms::MagSquared(1, 2), 5.0, 0.001);

  TS_ASSERT_DELTA(xms::Mag(1, 2, 3, 4), 5.4772, 0.001);
  TS_ASSERT_DELTA(xms::Mag(1, 2, 3), 3.7416, 0.001);
  TS_ASSERT_DELTA(xms::Mag(1, 2), 2.2360, 0.001);

  TS_ASSERT_EQUALS(xms::Clamp(5, 1, 8), 5);
  TS_ASSERT_EQUALS(xms::Clamp(5, 5, 8), 5);
  TS_ASSERT_EQUALS(xms::Clamp(5, 1, 5), 5);
  TS_ASSERT_EQUALS(xms::Clamp(5, 6, 8), 6);
  TS_ASSERT_EQUALS(xms::Clamp(5, 1, 2), 2);
  // TS_ASSERT_EQUALS(0,1);

  // EPS
  const double D = 1e-5;
  TS_ASSERT_EQUALS(xms::EQ_EPS(1.0, 1.0, D), true);
  TS_ASSERT_EQUALS(xms::EQ_EPS(1.12345, 1.12345, D), true);
  TS_ASSERT_EQUALS(xms::EQ_EPS(1.12345, 1.12346, D), true);
  TS_ASSERT_EQUALS(xms::EQ_EPS(1.12345, 1.12347, D), true);
  TS_ASSERT_EQUALS(xms::EQ_EPS(1.0, 2.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::EQ_EPS(1.0, 1.0, D), true);  // using integers
  TS_ASSERT_EQUALS(xms::EQ_EPS(2.0, 1.0, D), false); // using integers

  TS_ASSERT_EQUALS(xms::LT_EPS(1.0, 1.0, D), false);
  TS_ASSERT_EQUALS(xms::LT_EPS(1.12345, 1.12345, D), false);
  TS_ASSERT_EQUALS(xms::LT_EPS(1.12345, 1.12346, D), false);
  TS_ASSERT_EQUALS(xms::LT_EPS(1.12345, 1.12347, D), false);
  TS_ASSERT_EQUALS(xms::LT_EPS(1.0, 2.0, D), true);  // using integers
  TS_ASSERT_EQUALS(xms::LT_EPS(1.0, 1.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::LT_EPS(2.0, 1.0, D), false); // using integers

  TS_ASSERT_EQUALS(xms::GT_EPS(1.0, 1.0, D), false);
  TS_ASSERT_EQUALS(xms::GT_EPS(1.12345, 1.12345, D), false);
  TS_ASSERT_EQUALS(xms::GT_EPS(1.12345, 1.12346, D), false);
  TS_ASSERT_EQUALS(xms::GT_EPS(1.12345, 1.12347, D), false);
  TS_ASSERT_EQUALS(xms::GT_EPS(1.12347, 1.12345, D), false);
  TS_ASSERT_EQUALS(xms::GT_EPS(1.0, 2.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::GT_EPS(1.0, 1.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::GT_EPS(2.0, 1.0, D), true);  // using integers

  // TOL
  TS_ASSERT_EQUALS(xms::EQ_TOL(1.0, 1.0, D), true);
  TS_ASSERT_EQUALS(xms::EQ_TOL(1.12345, 1.12345, D), true);
  TS_ASSERT_EQUALS(xms::EQ_TOL(1.12345, 1.12346, D), true);
  TS_ASSERT_EQUALS(xms::EQ_TOL(1.12345, 1.12347, D), false);
  TS_ASSERT_EQUALS(xms::EQ_TOL(1.0, 2.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::EQ_TOL(1.0, 1.0, D), true);  // using integers
  TS_ASSERT_EQUALS(xms::EQ_TOL(2.0, 1.0, D), false); // using integers

  TS_ASSERT_EQUALS(xms::LT_TOL(1.0, 1.0, D), false);
  TS_ASSERT_EQUALS(xms::LT_TOL(1.12345, 1.12345, D), false);
  TS_ASSERT_EQUALS(xms::LT_TOL(1.12345, 1.12346, D), false);
  TS_ASSERT_EQUALS(xms::LT_TOL(1.12345, 1.12347, D), true);
  TS_ASSERT_EQUALS(xms::LT_TOL(1.0, 2.0, D), true);  // using integers
  TS_ASSERT_EQUALS(xms::LT_TOL(1.0, 1.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::LT_TOL(2.0, 1.0, D), false); // using integers

  TS_ASSERT_EQUALS(xms::GT_TOL(1.0, 1.0, D), false);
  TS_ASSERT_EQUALS(xms::GT_TOL(1.12345, 1.12345, D), false);
  TS_ASSERT_EQUALS(xms::GT_TOL(1.12345, 1.12346, D), false);
  TS_ASSERT_EQUALS(xms::GT_TOL(1.12345, 1.12347, D), false);
  TS_ASSERT_EQUALS(xms::GT_TOL(1.12347, 1.12345, D), true);
  TS_ASSERT_EQUALS(xms::GT_TOL(1.0, 2.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::GT_TOL(1.0, 1.0, D), false); // using integers
  TS_ASSERT_EQUALS(xms::GT_TOL(2.0, 1.0, D), true);  // using integers

} // MptTester::TestIt
#endif
