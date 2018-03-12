#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

#include <sstream>
#include <utility>

namespace xms
{
//----- pairs ----------------------------------------------------------------

typedef std::pair<int, int> PAIR_I_I; ///< short rename

//------------------------------------------------------------------------------
/// \brief Streams a pair to a_output.
/// \param a_output: The stream.
/// \param a_value: The pair.
/// \return stream reference.
//------------------------------------------------------------------------------
template <class _T, class _U>
std::ostream& operator<<(std::ostream& a_output, const std::pair<_T, _U>& a_value)
{
  a_output << ",size=" << a_value.size();
  // add loop here like std::vector
  return a_output;
}
//------------------------------------------------------------------------------
/// \brief Export a vector or bitset to a stringstream.
/// \param a_ss: The stream.
/// \param a_v: The vector.
/// \param a_label: A label
//------------------------------------------------------------------------------
template <typename T>
void VecToStream(std::stringstream& a_ss, const T& a_v, std::string a_label)
{
  // if (!a_v.empty() && !a_ss.str().empty()) { a_ss << ","; }
  for (size_t i = 0; i < a_v.size(); ++i)
  {
    if (i > 0)
      a_ss << " ";
    a_ss << a_v[i];
  }
  a_ss << "=" << a_label << " ";
  a_ss << "\n";
} // VecToStream

} // namespace xms {
