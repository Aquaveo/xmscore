#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::set types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard library headers
#include <cstdint> // for int64_t
#include <set>
#include <string>

// 5. Shared code headers
#include <xmscore/points/ptsfwd.h>
namespace xms
{
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
  a_output << std::string(",size=") << a_value.size();
  // add loop here like vector
  return a_output;
}

} // namespace xms {
