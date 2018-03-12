#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::set types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

// 3. Standard library headers
#include <cstdint> // for int64_t
#include <set>

// 5. Shared code headers
#include <xmscore/points/ptsfwd.h>
namespace xms
{
//----- Old types --------------------------------------------------------------
/// \deprecated Don't use the "SET_..." types. Use the "Set..." ones below
typedef std::set<Pt2d> SET_MP2; ///< short rename
typedef std::set<Pt3d> SET_MP3; ///< short rename
typedef std::set<Pt4d> SET_MP4; ///< short rename

typedef std::set<size_t> SET_SIZET;    ///< short rename
typedef std::set<int> SET_INT;         ///< short rename
typedef std::set<int> SET_I;           ///< short rename
typedef std::set<float> SET_FLT;       ///< short rename
typedef std::set<double> SET_DBL;      ///< short rename
typedef std::set<std::string> SET_STR; ///< short rename

//----- New types --------------------------------------------------------------

typedef std::set<Pt2d> SetPt2d; ///< short rename
typedef std::set<Pt3d> SetPt3d; ///< short rename
typedef std::set<Pt4d> SetPt4d; ///< short rename

typedef std::set<size_t> SetSizet;    ///< short rename
typedef std::set<int> SetInt;         ///< short rename
typedef std::set<int64_t> SetInt64;   ///< short rename
typedef std::set<float> SetFlt;       ///< short rename
typedef std::set<double> SetDbl;      ///< short rename
typedef std::set<std::string> SetStr; ///< short rename

//------------------------------------------------------------------------------
/// \brief Streams a set to a_output.
/// \param a_output: The stream.
/// \param a_value: The set.
/// \return stream reference.
//------------------------------------------------------------------------------
template <class _T>
std::ostream& operator<<(std::ostream& a_output, const std::set<_T>& a_value)
{
  a_output << ",size=" << a_value.size();
  // add loop here like vector
  return a_output;
}

} // namespace xms {
