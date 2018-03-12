#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Macros etc that make boost more convenient to use.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers
#include <vector>

// 4. External Library Headers
#include <boost/dynamic_bitset.hpp>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
typedef boost::dynamic_bitset<size_t> DynBitset; ///< vector of flags

void VecBooleanToDynBitset(const std::vector<unsigned char>& a_from, DynBitset& a_to);
void DynBitsetToVecBoolean(const DynBitset& a_from, std::vector<unsigned char>& a_to);

} // namespace xms
