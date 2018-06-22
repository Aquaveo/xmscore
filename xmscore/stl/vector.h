#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Vector types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

// 3. Standard library headers
#include <iostream>
#include <vector>

// 4. External Library Headers

// 5. Shared code headers
#include <xmscore/points/pt.h>

namespace xms
{
// 1d arrays
typedef std::vector<bool> VecBool;           ///< short rename
typedef std::vector<char> VecChar;           ///< short rename
typedef std::vector<unsigned char> VecUchar; ///< short rename
typedef std::vector<double> VecDbl;          ///< short rename
typedef std::vector<float> VecFlt;           ///< short rename
typedef std::vector<int> VecInt;             ///< short rename
typedef std::vector<unsigned int> VecUint;   ///< short rename
typedef std::vector<short> VecShort;         ///< short rename
typedef std::vector<std::string> VecStr;     ///< short rename
typedef std::vector<void*> VecVoid;          ///< short rename
typedef std::vector<std::size_t> VecSizet;   ///< short rename

// 2d arrays
typedef std::vector<VecFlt> VecFlt2d;     ///< short rename
typedef std::vector<VecInt> VecInt2d;     ///< short rename
typedef std::vector<VecDbl> VecDbl2d;     ///< short rename
typedef std::vector<VecStr> VecStr2d;     ///< short rename
typedef std::vector<VecSizet> VecSizet2d; ///< short rename
                                          // 3d arrays
typedef std::vector<VecFlt2d> VecFlt3d;   ///< short rename
typedef std::vector<VecInt2d> VecInt3d;   ///< short rename
typedef std::vector<VecDbl2d> VecDbl3d;   ///< short rename
typedef std::vector<VecStr2d> VecStr3d;   ///< short rename
                                          // 4d arrays
typedef std::vector<VecDbl3d> VecDbl4d;   ///< short rename
typedef std::vector<VecFlt3d> VecFlt4d;   ///< short rename

// 1d arrays
typedef std::vector<Pt4d> VecPt4d; ///< short rename
typedef std::vector<Pt3d> VecPt3d; ///< short rename
typedef std::vector<Pt3f> VecPt3f; ///< short rename
typedef std::vector<Pt2d> VecPt2d; ///< short rename
typedef std::vector<Pt2f> VecPt2f; ///< short rename
typedef std::vector<Pt2i> VecPt2i; ///< short rename

// 2d arrays
typedef std::vector<VecPt2d> VecPt2d2d; ///< short rename
typedef std::vector<VecPt2f> VecPt2f2d; ///< short rename
typedef std::vector<VecPt3d> VecPt3d2d; ///< short rename
typedef std::vector<VecPt3f> VecPt3f2d; ///< short rename

// 3d arrays
typedef std::vector<VecPt3d2d> VecPt3d3d; ///< short rename
// 4d arrays

//----- Template functions -----------------------------------------------------

//------------------------------------------------------------------------------
/// \brief Streams a vector to a_output.
/// \param a_output: The stream.
/// \param a_value: The vector.
/// \return stream reference.
//------------------------------------------------------------------------------
template <class _T>
std::ostream& operator<<(std::ostream& a_output, const std::vector<_T>& a_value)
{
  a_output << ",size=" << a_value.size();
  for (unsigned int ii = 0; ii < a_value.size(); ++ii)
  {
    a_output << "," << ii << "=" << a_value[ii];
  }
  return a_output;
}
//------------------------------------------------------------------------------
/// \brief removes any excess capacity in a vector (size() will equal capacity())
/// \param v: A vector
//------------------------------------------------------------------------------
template <class T>
void stShrinkCapacity(std::vector<T>& v)
{
  std::vector<T> tmp(v);
  v.swap(tmp);
} // stShrinkCapacity

//----- Functions --------------------------------------------------------------

} // namespace xms
