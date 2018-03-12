#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::map types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

#include <map>
#include <xmscore/points/ptsfwd.h>
#include <xmscore/stl/vector.h> // VEC_* ShrinkCapacity
#include <xmscore/stl/set.h>    // SET_*

namespace xms
{
//----- Old types --------------------------------------------------------------
/// \deprecated Don't use the "MAP_..." types. Use the "Map..." ones below
typedef std::map<int, Pt3d> MAP_I_MPT3; ///< short rename
typedef std::map<Pt3d, int> MAP_MP3_I;  ///< short rename

typedef std::map<int, int> MAP_I_I;                         ///< short rename
typedef std::map<int, float> MAP_I_F;                       ///< short rename
typedef std::map<int, float**> MAP_I_FLT2D;                 ///< short rename
typedef std::map<int, double> MAP_I_DBL;                    ///< short rename
typedef std::map<int, bool> MAP_I_BOOL;                     ///< short rename
typedef std::map<int, VEC_FLT> MAP_I_VEC_FLT;               ///< short rename
typedef std::map<int, VEC_FLT2D> MAP_I_VEC_FLT2D;           ///< short rename
typedef std::map<int, VEC_DBL> MAP_I_VEC_DBL;               ///< short rename
typedef std::map<int, VEC_INT> MAP_I_VEC_I;                 ///< short rename
typedef std::map<int, SET_INT> MAP_I_SET_INT;               ///< short rename
typedef std::map<int, MAP_I_DBL> MAP_I_MAP_I_DBL;           ///< short rename
typedef std::map<int, MAP_I_F> MAP_I_MAP_I_F;               ///< short rename
typedef std::map<int, MAP_I_I> MAP_I_I_I;                   ///< short rename
typedef std::map<double, double> MAP_DBL_DBL;               ///< short rename
typedef std::map<double, int> MAP_DBL_I;                    ///< short rename
typedef std::map<double, std::string> MAP_DBL_STR;          ///< short rename
typedef std::map<std::string, int> MAP_STR_I;               ///< short rename
typedef std::map<std::string, double> MAP_STR_D;            ///< short rename
typedef std::map<int, std::string> MAP_I_STR;               ///< short rename
typedef std::map<std::string, std::string> MAP_STR_STR;     ///< short rename
typedef std::map<std::string, VEC_STR> MAP_STR_VEC_STR;     ///< short rename
typedef std::map<std::string, MAP_I_DBL> MAP_STR_MAP_I_DBL; ///< short rename

// multimaps

typedef std::multimap<int, int> MMAP_I_I;         ///< short rename
typedef std::multimap<double, int> MMAP_D_I;      ///< short rename
typedef std::multimap<std::string, int> MMAP_S_I; ///< short rename
typedef std::multimap<bool, int> MMAP_B_I;        ///< short rename

//----- New types --------------------------------------------------------------

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
