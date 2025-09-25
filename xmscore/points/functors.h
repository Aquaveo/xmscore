#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Less than functors that use tolerances ---------------------------------

#include <xmscore/math/math.h>
#include <xmscore/points/pt.h>

namespace xms
{
////////////////////////////////////////////////////////////////////////////////
/// \class ltPt3
/// \brief less than Pt3
template <typename T>
class ltPt3
{
private:
  T m_xytol; ///< xy tolerance
  T m_ztol;  ///< z tolerance

public:
  //----------------------------------------------------------------------------
  /// \brief constructor
  /// \param a_xytol: XY tolerance.
  /// \param a_ztol: Z tolerance.
  //----------------------------------------------------------------------------
  ltPt3(T a_xytol, T a_ztol)
  : m_xytol(a_xytol)
  , m_ztol(a_ztol)
  {
  } // ltPt3::ltPt3
  //----------------------------------------------------------------------------
  /// \brief does comparison
  /// \param lhs: Left hand side.
  /// \param rhs: Right hand side.
  /// \return true if a_lhs < a_rhs.
  //----------------------------------------------------------------------------
  bool operator()(const Pt3<T> lhs, const Pt3<T> rhs) const
  {
    if (EQ_TOL(lhs.x, rhs.x, m_xytol))
    {
      if (EQ_TOL(lhs.y, rhs.y, m_xytol))
      {
        if (EQ_TOL(lhs.z, rhs.z, m_ztol))
        {
          return false;
        }
        else if (LT_TOL(lhs.z, rhs.z, m_ztol))
          return true;
        else
          return false;
      }
      else if (LT_TOL(lhs.y, rhs.y, m_xytol))
        return true;
      else
        return false;
    }
    else if (LT_TOL(lhs.x, rhs.x, m_xytol))
      return true;
    else
      return false;
  } // operator()
};  // ltPt3

////////////////////////////////////////////////////////////////////////////////
/// \class ltPt3_2D
/// \brief less than Pt3 comparing in 2D, or, only x and y
template <typename T>
class ltPt3_2D
{
private:
  double m_xytol; ///< xy tolerance

public:
  //----------------------------------------------------------------------------
  /// \brief constructor
  /// \param a_xytol: XY tolerance.
  //----------------------------------------------------------------------------
  ltPt3_2D(T a_xytol)
  : m_xytol(a_xytol)
  {
  } // ltPt3_2D::ltPt3_2D
  //----------------------------------------------------------------------------
  /// \brief Tests only x and y
  /// \param a_lhs: Left hand side.
  /// \param a_rhs: Right hand side.
  /// \return true if a_lhs < a_rhs.
  //----------------------------------------------------------------------------
  bool operator()(const Pt3<T> a_lhs, const Pt3<T> a_rhs) const
  {
    if (EQ_TOL(a_lhs.x, a_rhs.x, m_xytol))
    {
      if (EQ_TOL(a_lhs.y, a_rhs.y, m_xytol))
      {
        return false;
      }
      else if (LT_TOL(a_lhs.y, a_rhs.y, m_xytol))
        return true;
      else
        return false;
    }
    else if (LT_TOL(a_lhs.x, a_rhs.x, m_xytol))
      return true;
    else
      return false;
  } // ltPt3_2D::operator()
};  // ltPt3_2D

////////////////////////////////////////////////////////////////////////////////
/// \class ltPt2
/// \brief less than Pt2
template <typename T>
class ltPt2
{
private:
  double m_xytol; ///< xy tolerance

public:
  //----------------------------------------------------------------------------
  /// \brief constructor
  /// \param a_xytol: XY tolerance.
  //----------------------------------------------------------------------------
  ltPt2(T a_xytol)
  : m_xytol(a_xytol)
  {
  } // ltPt2::ltPt2
  //----------------------------------------------------------------------------
  /// \brief Tests only x and y
  /// \param a_lhs: Left hand side.
  /// \param a_rhs: Right hand side.
  /// \return true if a_lhs < a_rhs.
  //----------------------------------------------------------------------------
  bool operator()(const Pt2<T> a_lhs, const Pt2<T> a_rhs) const
  {
    if (EQ_TOL(a_lhs.x, a_rhs.x, m_xytol))
    {
      if (EQ_TOL(a_lhs.y, a_rhs.y, m_xytol))
      {
        return false;
      }
      else if (LT_TOL(a_lhs.y, a_rhs.y, m_xytol))
        return true;
      else
        return false;
    }
    else if (LT_TOL(a_lhs.x, a_rhs.x, m_xytol))
      return true;
    else
      return false;
  } // ltPt2::operator()
};  // ltPt2

typedef ltPt3<double> ltPt3d;       ///< short name typedef
typedef ltPt3_2D<double> ltPt3d_2D; ///< short name typedef
typedef ltPt2<double> ltPt2d;       ///< short name typedef

//------------------------------------------------------------------------------
/// \brief Truncate to an integer
/// \param a_in Point to be truncated
/// \return truncated version of a_in
//------------------------------------------------------------------------------
template <typename _T>
Pt2<_T> ptTruncate(Pt2<_T> const& a_in)
{
  Pt2<_T> out;
  out.x = static_cast<int>(a_in.x);
  out.y = static_cast<int>(a_in.y);
  return out;
}
//------------------------------------------------------------------------------
/// \brief Truncate to an integer
/// \param a_in Point to be truncated
/// \return truncated version of a_in
//------------------------------------------------------------------------------
template <typename _T>
Pt3<_T> ptTruncate(Pt3<_T> const& a_in)
{
  Pt3<_T> out;
  out.x = static_cast<int>(a_in.x);
  out.y = static_cast<int>(a_in.y);
  out.z = static_cast<int>(a_in.z);
  return out;
}
//------------------------------------------------------------------------------
/// \brief Truncate to an integer
/// \param a_in Point to be truncated
/// \return truncated version of a_in
//------------------------------------------------------------------------------
template <typename _T>
Pt4<_T> ptTruncate(Pt4<_T> const& a_in)
{
  Pt4<_T> out;
  out.x = static_cast<int>(a_in.x);
  out.y = static_cast<int>(a_in.y);
  out.z = static_cast<int>(a_in.z);
  out.w = static_cast<int>(a_in.w);
  return out;
}

} // namespace xms
