#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::map types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#include <map>
#include <xmscore/points/ptsfwd.h>
#include <xmscore/stl/vector.h> // VEC_* ShrinkCapacity
#include <xmscore/stl/set.h>    // SET_*

namespace xms
{
// In alphabetical order
typedef std::map<double, double> MapDblDbl;               ///< short rename
typedef std::map<double, int> MapDblInt;                  ///< short rename
typedef std::map<double, std::string> MapDblStr;          ///< short rename
typedef std::map<int, bool> MapIntBool;                   ///< short rename
typedef std::map<int, double> MapIntDbl;                  ///< short rename
typedef std::map<int, float> MapIntFlt;                   ///< short rename
typedef std::map<int, float**> MapIntFlt2d;               ///< short rename
typedef std::map<int, int> MapIntInt;                     ///< short rename
typedef std::map<int, SetInt> MapIntSetInt;               ///< short rename
typedef std::map<int, std::string> MapIntStr;             ///< short rename
typedef std::map<int, Pt3d> MapIntPt3d;                   ///< short rename
typedef std::map<int, VecDbl> MapIntVecDbl;               ///< short rename
typedef std::map<int, VecFlt> MapIntVecFlt;               ///< short rename
typedef std::map<int, VecFlt2d> MapIntVecFlt2d;           ///< short rename
typedef std::map<int, VecInt> MapIntVecInt;               ///< short rename
typedef std::map<int, MapIntDbl> MapIntMapIntDbl;         ///< short rename
typedef std::map<int, MapIntFlt> MapIntMapIntFlt;         ///< short rename
typedef std::map<int, MapIntInt> MapIntMapIntInt;         ///< short rename
typedef std::map<Pt3d, int> MapPt3dInt;                   ///< short rename
typedef std::map<std::string, double> MapStrDbl;          ///< short rename
typedef std::map<std::string, int> MapStrInt;             ///< short rename
typedef std::map<std::string, MapIntDbl> MapStrMapIntDbl; ///< short rename
typedef std::map<std::string, std::string> MapStrStr;     ///< short rename
typedef std::map<std::string, VecStr> MapStrVecStr;       ///< short rename

// multimaps

typedef std::multimap<bool, int> MmapBoolInt;       ///< short rename
typedef std::multimap<double, int> MmapDblInt;      ///< short rename
typedef std::multimap<int, int> MmapIntInt;         ///< short rename
typedef std::multimap<std::string, int> MmapStrInt; ///< short rename

// Streams

//------------------------------------------------------------------------------
/// \brief Streams a map to a_output.
/// \param a_output: The stream.
/// \param a_value: The map.
/// \return stream reference.
//------------------------------------------------------------------------------
template <class _T, class _U>
std::ostream& operator<<(std::ostream& a_output, const std::map<_T, _U>& a_value)
{
  a_output << ",size=" << a_value.size();
  // add loop here like std::vector
  return a_output;
}

//------------------------------------------------------------------------------
/// \brief Streams a multimap to a_output.
/// \param a_output: The stream.
/// \param a_value: The map.
/// \return stream reference.
//------------------------------------------------------------------------------
template <class _T, class _U>
std::ostream& operator<<(std::ostream& a_output, const std::multimap<_T, _U>& a_value)
{
  a_output << ",size=" << a_value.size();
  // add loop here like std::vector above
  return a_output;
}

} // namespace xms
