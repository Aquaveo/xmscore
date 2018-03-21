//------------------------------------------------------------------------------
/// \file
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

#include <xmscore/points/pt.h>

//----- Function definitions ---------------------------------------------------

#if CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// TESTS
////////////////////////////////////////////////////////////////////////////////

#include <xmscore/points/pt.t.h>
#include <cfloat>
#include <limits>

namespace // unnamed namespace
{
/// EQ_EPS isn't in shared1 so I defined this here until it is
#define iEQ_EPS(A, B, epsilon) (fabs((A) - (B)) <= fabs(((A) + (B)) * (epsilon)))

//------------------------------------------------------------------------------
/// \brief gmEqualPointsXYZ isn't in shared1 so can't use
///        TS_ASSERT_DELTA_PT3D
//------------------------------------------------------------------------------
bool iTS_ASSERT_DELTA_PT3D(const xms::Pt3d& a_pt1, const xms::Pt3d& a_pt2, double a_eps)
{
  if (iEQ_EPS(a_pt1.x, a_pt2.x, a_eps) && iEQ_EPS(a_pt1.y, a_pt2.y, a_eps) &&
      iEQ_EPS(a_pt1.z, a_pt2.z, a_eps))
    return true;
  return false;
} // iTS_ASSERT_DELTA_PT3D
} // unnamed namespace
//------------------------------------------------------------------------------
/// \brief tests for points
//------------------------------------------------------------------------------
void PtUnitTests::testIt()
{
  // TS_FAIL("MptUnitTester::testPoints");

  // Test constructors
  {
    xms::Pt3d pt;
    TS_ASSERT_DELTA(pt.x, 0, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 0, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 0, DBL_EPSILON);
  }
  {
    xms::Pt3d pt(1, 2, 3);
    TS_ASSERT_DELTA(pt.x, 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 3, DBL_EPSILON);
  }
  {
    xms::Pt3d pt(4);
    TS_ASSERT_DELTA(pt.x, 4, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 4, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 4, DBL_EPSILON);
  }
  {
    xms::Pt2d pt2d(1, 2);
    xms::Pt3d pt(pt2d);
    TS_ASSERT_DELTA(pt.x, 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 0, DBL_EPSILON);
  }
  {
    xms::Pt3d pt3d(1, 2, 3);
    xms::Pt3d pt(pt3d);
    TS_ASSERT_DELTA(pt.x, 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 3, DBL_EPSILON);
  }
  {
    xms::Pt4d pt4d(1, 2, 3, 4);
    xms::Pt3d pt(pt4d);
    TS_ASSERT_DELTA(pt.x, 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 3, DBL_EPSILON);
  }

  // Test operator=
  {
    xms::Pt3d pt;
    pt = 2;
    iTS_ASSERT_DELTA_PT3D(pt, xms::Pt3d(2), DBL_EPSILON);
  }
  {
    xms::Pt2d pt1(1, 2);
    xms::Pt3d pt2;
    pt2 = pt1;
    TS_ASSERT_DELTA(pt2.x, 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt2.y, 2, DBL_EPSILON);
  }
  {
    xms::Pt3d pt1(1, 2, 3);
    xms::Pt3d pt2;
    pt2 = pt1;
    iTS_ASSERT_DELTA_PT3D(pt2, xms::Pt3d(1, 2, 3), DBL_EPSILON);
  }
  {
    xms::Pt4d pt1(1, 2, 3, 4);
    xms::Pt3d pt2;
    pt2 = pt1;
    iTS_ASSERT_DELTA_PT3D(pt2, xms::Pt3d(1, 2, 3), DBL_EPSILON);
  }

  // Test operator==
  {
    xms::Pt3d pt(4);
    TS_ASSERT(pt == 4);
  }
  {
    xms::Pt2d pt1(4);
    xms::Pt3d pt2(4);
    TS_ASSERT(pt1 == pt2);
  }
  {
    xms::Pt3d pt1(4);
    xms::Pt3d pt2(4);
    TS_ASSERT(pt1 == pt2);
  }
  {
    xms::Pt4d pt1(4);
    xms::Pt3d pt2(4);
    TS_ASSERT(pt1 == pt2);
  }

  // Test operator!=
  {
    xms::Pt3d pt(4);
    TS_ASSERT(pt != 3);
  }
  {
    xms::Pt2d pt1(3);
    xms::Pt3d pt2(4);
    TS_ASSERT(pt1 != pt2);
  }
  {
    xms::Pt3d pt1(3);
    xms::Pt3d pt2(4);
    TS_ASSERT(pt1 != pt2);
  }
  {
    xms::Pt4d pt1(3);
    xms::Pt3d pt2(4);
    TS_ASSERT(pt1 != pt2);
  }

  // Test operator<
  {
    xms::Pt3d pt(1, 2, 3);
    TS_ASSERT(pt < 2);
  }
  {
    xms::Pt3d pt(1, 2, 3);
    TS_ASSERT(pt < xms::Pt2d(2));
  }
  {
    xms::Pt3d pt(1, 2, 3);
    TS_ASSERT_EQUALS(pt < xms::Pt3d(1, 2, 3), false);
  }
  {
    xms::Pt3d pt(1, 1, 3);
    TS_ASSERT_EQUALS(pt < xms::Pt4d(1, 2, 3, 4), true);
  }

  // Test operator+
  {
    xms::Pt3d pt(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt + 1, xms::Pt3d(2, 3, 4), DBL_EPSILON);
  }
  {
    xms::Pt2d pt1(1, 2);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 + pt1, xms::Pt3d(2, 4, 3), DBL_EPSILON);
  }
  {
    xms::Pt3d pt1(1, 2, 3);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 + pt1, xms::Pt3d(2, 4, 6), DBL_EPSILON);
  }
  {
    xms::Pt4d pt1(1, 2, 3, 4);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 + pt1, xms::Pt3d(2, 4, 6), DBL_EPSILON);
  }

  // Test operator-
  {
    xms::Pt3d pt(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt - 1, xms::Pt3d(0, 1, 2), DBL_EPSILON);
  }
  {
    xms::Pt2d pt1(1, 2);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 - pt1, xms::Pt3d(0, 0, 3), DBL_EPSILON);
  }
  {
    xms::Pt3d pt1(1, 2, 3);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 - pt1, xms::Pt3d(0, 0, 0), DBL_EPSILON);
  }
  {
    xms::Pt4d pt1(1, 2, 3, 4);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 - pt1, xms::Pt3d(0, 0, 0), DBL_EPSILON);
  }

  // Test unary operator-
  {
    xms::Pt2i pt1(1, -2);
    xms::Pt2i pt2;
    pt2 = -pt1;
    TS_ASSERT_EQUALS(pt2, xms::Pt2i(-1, 2));
  }
  {
    xms::Pt3d pt1(1, -2, 3);
    xms::Pt3d pt2;
    pt2 = -pt1;
    iTS_ASSERT_DELTA_PT3D(pt2, xms::Pt3d(-1, 2, -3), DBL_EPSILON);
  }
  {
    xms::Pt4f pt1(1, -2, 3, -4);
    xms::Pt4f pt2;
    pt2 = -pt1;
    TS_ASSERT_EQUALS(pt2, xms::Pt4f(-1, 2, -3, 4));
  }

  // Test operator*
  {
    xms::Pt3d pt(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt * 2, xms::Pt3d(2, 4, 6), DBL_EPSILON);
  }
  {
    xms::Pt2d pt1(1, 2);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 * pt1, xms::Pt3d(1, 4, 3), DBL_EPSILON);
  }
  {
    xms::Pt3d pt1(1, 2, 3);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 * pt1, xms::Pt3d(1, 4, 9), DBL_EPSILON);
  }
  {
    xms::Pt4d pt1(1, 2, 3, 4);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 * pt1, xms::Pt3d(1, 4, 9), DBL_EPSILON);
  }

  // Test operator/
  {
    xms::Pt3d pt(2, 4, 6);
    iTS_ASSERT_DELTA_PT3D(pt / 2, xms::Pt3d(1, 2, 3), DBL_EPSILON);
  }
  {
    xms::Pt2d pt1(1, 2);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 / pt1, xms::Pt3d(1, 1, 3), DBL_EPSILON);
  }
  {
    xms::Pt3d pt1(1, 2, 3);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 / pt1, xms::Pt3d(1, 1, 1), DBL_EPSILON);
  }
  {
    xms::Pt4d pt1(1, 2, 3, 4);
    xms::Pt3d pt2(1, 2, 3);
    iTS_ASSERT_DELTA_PT3D(pt2 / pt1, xms::Pt3d(1, 1, 1), DBL_EPSILON);
  }

  // Test Set
  {
    xms::Pt3d pt;
    pt.Set(0, 1, 2);
    TS_ASSERT_DELTA(pt.x, 0, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.y, 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.z, 2, DBL_EPSILON);
  }

  // Test const operator[]
  {
    xms::Pt3d pt(1, 2, 3);
    TS_ASSERT_DELTA(pt[0], 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt[1], 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt[2], 3, DBL_EPSILON);
  }

  // Test operator[]
  {
    xms::Pt3d pt(1, 2, 3);
    pt[0] = 3;
    pt[1] = 2;
    pt[2] = 1;
    TS_ASSERT_DELTA(pt[0], 3, DBL_EPSILON);
    TS_ASSERT_DELTA(pt[1], 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt[2], 1, DBL_EPSILON);
  }

  // Test at
  {
    xms::Pt3d pt(1, 2, 3);
    TS_ASSERT_DELTA(pt.at(0), 1, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.at(1), 2, DBL_EPSILON);
    TS_ASSERT_DELTA(pt.at(2), 3, DBL_EPSILON);
  }
  // TS_ASSERT_THROWS(pt.at(3), std::out_of_range&);

} // PtUnitTests::testIt
//------------------------------------------------------------------------------
/// \brief tests for point streams
//------------------------------------------------------------------------------
void PtUnitTests::testStreams()
{
  using namespace xms;

  // TS_FAIL("PtUnitTests::testStreams");

  // operator<<

  // Pt2<>
  {
    std::stringstream sstrm;
    Pt2i pt(1, 2);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1,2");
  }
  {
    std::stringstream sstrm;
    Pt2f pt(1.5, 2.5);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1.5,2.5");
  }
  {
    std::stringstream sstrm;
    Pt2d pt(1.5, 2.5);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1.5,2.5");
  }
  {
    std::stringstream sstrm;
    Pt2<char> pt('1', '2');
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1,2");
  }

  // Pt3<>
  {
    std::stringstream sstrm;
    Pt3i pt(1, 2, 3);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1,2,3");
  }
  {
    std::stringstream sstrm;
    Pt3f pt(1.5, 2.5, 3.5);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1.5,2.5,3.5");
  }
  {
    std::stringstream sstrm;
    Pt3d pt(1.5, 2.5, 3.5);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1.5,2.5,3.5");
  }
  {
    std::stringstream sstrm;
    Pt3<char> pt('1', '2', '3');
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1,2,3");
  }

  // Pt4<>
  {
    std::stringstream sstrm;
    Pt4i pt(1, 2, 3, 4);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1,2,3,4");
  }
  {
    std::stringstream sstrm;
    Pt4f pt(1.5, 2.5, 3.5, 4.5);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1.5,2.5,3.5,4.5");
  }
  {
    std::stringstream sstrm;
    Pt4d pt(1.5, 2.5, 3.5, 4.5);
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1.5,2.5,3.5,4.5");
  }
  {
    std::stringstream sstrm;
    Pt4<char> pt('1', '2', '3', '4');
    sstrm << pt;
    TS_ASSERT_EQUALS(sstrm.str(), "1,2,3,4");
  }

  // operator>>

  // Pt2<>
  {
    std::stringstream sstrm;
    sstrm << "1,2";
    Pt2i pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt2i(1, 2));
  }
  {
    std::stringstream sstrm;
    sstrm << "1.5,2.5";
    Pt2f pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt2f(1.5, 2.5));
  }
  {
    std::stringstream sstrm;
    sstrm << "1.5,2.5";
    Pt2d pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt2d(1.5, 2.5));
  }
  {
    std::stringstream sstrm;
    sstrm << "1,2";
    Pt2<char> pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt2<char>('1', '2'));
  }

  // Pt3<>
  {
    std::stringstream sstrm;
    sstrm << "1,2,3";
    Pt3i pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt3i(1, 2, 3));
  }
  {
    std::stringstream sstrm;
    sstrm << "1.5,2.5,3.5";
    Pt3f pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt3f(1.5, 2.5, 3.5));
  }
  {
    std::stringstream sstrm;
    sstrm << "1.5,2.5,3.5";
    Pt3d pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt3d(1.5, 2.5, 3.5));
  }
  {
    std::stringstream sstrm;
    sstrm << "1,2,3";
    Pt3<char> pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt3<char>('1', '2', '3'));
  }

  // Pt4<>
  {
    std::stringstream sstrm;
    sstrm << "1,2,3,4";
    Pt4i pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt4i(1, 2, 3, 4));
  }
  {
    std::stringstream sstrm;
    sstrm << "1.5,2.5,3.5,4.5";
    Pt4f pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt4f(1.5, 2.5, 3.5, 4.5));
  }
  {
    std::stringstream sstrm;
    sstrm << "1.5,2.5,3.5,4.5";
    Pt4d pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt4d(1.5, 2.5, 3.5, 4.5));
  }
  {
    std::stringstream sstrm;
    sstrm << "1,2,3,4";
    Pt4<char> pt;
    sstrm >> pt;
    TS_ASSERT_EQUALS(pt, Pt4<char>('1', '2', '3', '4'));
  }

} // PtUnitTests::testStreams
#endif
