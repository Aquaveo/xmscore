#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#include <sstream>
#include <utility>

#include <xmscore/xmlocale/xmlocale.h>

namespace xms
{
//----- pairs ------------------------------------------------------------------

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
  for (size_t i = 0; i < a_v.size(); ++i)
  {
    std::string value;
    if (i > 0)
    {
      value = N_(" {1}");
    }
    else
    {
      value = N_("{1}");
    }
    stCFormat(value, a_v[i]);  
    a_ss << value;
  }
  std::string label = N_("={1} \n");
  stCFormat(label, a_label);
  a_ss << label;
} // VecToStream

} // namespace xms {
