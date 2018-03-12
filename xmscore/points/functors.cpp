//------------------------------------------------------------------------------
/// \file
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

#include <xmscore/points/functors.h>

//----- Function definitions ---------------------------------------------------

#if CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// TESTS
////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <xmscore/points/functors.t.h>
#include <xmscore/testing/TestTools.h>

typedef std::set<xms::Pt3d, xms::ltPt3d> SET_WITH_LTPT3D; ///< meant for testing only

namespace // unnamed namespace
{
//------------------------------------------------------------------------------
/// \brief Used just to test passing a typedef'd type that uses a functor
//------------------------------------------------------------------------------
void iTestPassingMptFunctorTypes(SET_WITH_LTPT3D& a_set)
{
  SET_WITH_LTPT3D::iterator iter;
  iter = a_set.begin();
  iter = a_set.find(xms::Pt3d(0, 0, 0));
  TS_ASSERT_EQUALS(iter, a_set.end());
}
} // unnamed namespace
//------------------------------------------------------------------------------
/// \brief test functors
//------------------------------------------------------------------------------
void FunctorsUnitTests::TestIt()
{
  // Test xms::ltPt3d functor by itself
  {
    // Some points from lowest to highest
    xms::Pt3d pt1(0, 0, 0);
    xms::Pt3d pt2(0.0001, 0.0001, 0.0001);
    xms::Pt3d pt3(0.001, 0.001, 0.001);
    xms::Pt3d pt4(0.01, 0.01, 0.01);

    xms::ltPt3d functor1(0.0001, 0.0001);

    TS_ASSERT_EQUALS(functor1(pt1, pt2), false); // given our tol, these are =
    TS_ASSERT_EQUALS(functor1(pt1, pt3), true);
    TS_ASSERT_EQUALS(functor1(pt1, pt4), true);
    TS_ASSERT_EQUALS(functor1(pt2, pt1), false); // given our tol, these are =
    TS_ASSERT_EQUALS(functor1(pt2, pt3), true);
    TS_ASSERT_EQUALS(functor1(pt2, pt4), true);
    TS_ASSERT_EQUALS(functor1(pt3, pt1), false);
    TS_ASSERT_EQUALS(functor1(pt3, pt2), false);
    TS_ASSERT_EQUALS(functor1(pt3, pt4), true);
    TS_ASSERT_EQUALS(functor1(pt4, pt1), false);
    TS_ASSERT_EQUALS(functor1(pt4, pt2), false);
    TS_ASSERT_EQUALS(functor1(pt4, pt3), false);
  }

  // Test xms::ltPt3d_2D functor by itself
  {
    xms::Pt3d pt1(0, 0, 1);
    xms::Pt3d pt2(0, 0, 2);

    xms::ltPt3d_2D functor1(0.001);

    // Neither point should be less than the other because we don't compare z
    TS_ASSERT_EQUALS(functor1(pt1, pt2), false);
    TS_ASSERT_EQUALS(functor1(pt2, pt1), false);
  }

  // Test xms::ltPt2d functor by itself
  {
    xms::Pt2d pt1(0, 0);
    xms::Pt2d pt2(0.0001, 0.0001);
    xms::Pt2d pt3(0.001, 0.001);
    xms::Pt2d pt4(0.01, 0.01);

    xms::ltPt2d functor1(0.0001);

    TS_ASSERT_EQUALS(functor1(pt1, pt2), false); // given our tol, these are =
    TS_ASSERT_EQUALS(functor1(pt1, pt3), true);
    TS_ASSERT_EQUALS(functor1(pt1, pt4), true);
    TS_ASSERT_EQUALS(functor1(pt2, pt1), false); // given our tol, these are =
    TS_ASSERT_EQUALS(functor1(pt2, pt3), true);
    TS_ASSERT_EQUALS(functor1(pt2, pt4), true);
    TS_ASSERT_EQUALS(functor1(pt3, pt1), false);
    TS_ASSERT_EQUALS(functor1(pt3, pt2), false);
    TS_ASSERT_EQUALS(functor1(pt3, pt4), true);
    TS_ASSERT_EQUALS(functor1(pt4, pt1), false);
    TS_ASSERT_EQUALS(functor1(pt4, pt2), false);
    TS_ASSERT_EQUALS(functor1(pt4, pt3), false);
  }

  // Test the functor as part of a set
  {
    // Some points from lowest to highest
    xms::Pt3d pt1(0, 0, 0);
    xms::Pt3d pt2(0.0001, 0.0001, 0.0001);
    xms::Pt3d pt3(0.001, 0.001, 0.001);
    xms::Pt3d pt4(0.01, 0.01, 0.01);

    xms::ltPt3d functor1(0.0001, 0.0001);
    std::set<xms::Pt3d, xms::ltPt3d> set_pt3d(functor1);

    // Add the points in descending order
    set_pt3d.insert(pt4);
    set_pt3d.insert(pt3);
    set_pt3d.insert(pt2);
    set_pt3d.insert(pt1); // this one will be ignored given our tolerance

    TS_ASSERT_EQUALS(set_pt3d.size(), 3); // given our tol, pt1 and pt2 are =

    // Iterate through the set and see that they are in the right order
    // even though we put them in in the wrong order
    std::set<xms::Pt3d, xms::ltPt3d>::iterator iter;
    iter = set_pt3d.begin();
    TS_ASSERT_EQUALS(*iter, pt2);
    ++iter;
    TS_ASSERT_EQUALS(*iter, pt3);
    ++iter;
    TS_ASSERT_EQUALS(*iter, pt4);
  }

  // Test the functor as part of a set
  {
    // Some points from lowest to highest
    xms::Pt3d pt1(0, 0, 0);
    xms::Pt3d pt2(0.0001, 0.0001, 0.0001);
    xms::Pt3d pt3(0.001, 0.001, 0.001);
    xms::Pt3d pt4(0.01, 0.01, 0.01);

    std::set<xms::Pt3d, xms::ltPt3d> set_pt3d(xms::ltPt3d(0.0001, 0.0001));

    // Add the points in descending order
    set_pt3d.insert(pt4);
    set_pt3d.insert(pt3);
    set_pt3d.insert(pt2);
    set_pt3d.insert(pt1); // this one will be ignored given our tolerance

    TS_ASSERT_EQUALS(set_pt3d.size(), 3); // given our tol, pt1 and pt2 are =

    // Iterate through the set and see that they are in the right order
    // even though we put them in in the wrong order
    std::set<xms::Pt3d, xms::ltPt3d>::iterator iter;
    iter = set_pt3d.begin();
    TS_ASSERT_EQUALS(*iter, pt2);
    ++iter;
    TS_ASSERT_EQUALS(*iter, pt3);
    ++iter;
    TS_ASSERT_EQUALS(*iter, pt4);
  }

  // Test passing a set that is based of a typedef and uses a functor
  {
    xms::ltPt3d functor1(0.0001, 0.0001);
    SET_WITH_LTPT3D my_set(functor1);
    SET_WITH_LTPT3D::iterator iter;

    iter = my_set.find(xms::Pt3d(0, 0, 0));
    TS_ASSERT_EQUALS(iter, my_set.end());
    iTestPassingMptFunctorTypes(my_set);
  }

  // Test ptTruncate() for Pt2d
  {
    xms::Pt2d in(1.2, -1.2);
    in = xms::ptTruncate(in);
    TS_ASSERT_DELTA(in.x, 1.0, 0.001);
    TS_ASSERT_DELTA(in.y, -1.0, 0.001);
  }

  // Test ptTruncate() for Pt3d
  {
    xms::Pt3d in(1.2, -1.2, 4.0);
    in = xms::ptTruncate(in);
    TS_ASSERT_DELTA(in.x, 1.0, 0.001);
    TS_ASSERT_DELTA(in.y, -1.0, 0.001);
    TS_ASSERT_DELTA(in.z, 4.0, 0.001);
  }

  // TS_FAIL("PtTest::TestIt");
} // MptTester::testLessThanFunctors
#endif
