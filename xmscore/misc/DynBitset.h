#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief DynBitset typedef and conversions to/from std::vector&lt;unsigned char&gt;.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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

/// \brief Copy a vector of boolean-as-byte values into a DynBitset.
void VecBooleanToDynBitset(const std::vector<unsigned char>& a_from, DynBitset& a_to);
/// \brief Copy a DynBitset into a vector of boolean-as-byte values.
void DynBitsetToVecBoolean(const DynBitset& a_from, std::vector<unsigned char>& a_to);

} // namespace xms
