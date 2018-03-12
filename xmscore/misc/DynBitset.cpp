//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/misc/DynBitset.h>

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

//------------------------------------------------------------------------------
/// \brief Convert from a VecBoolean to a DynBitset.
/// \param[in]  a_from: VecBoolean array in.
/// \param[out] a_to: DynBitset out.
//------------------------------------------------------------------------------
void VecBooleanToDynBitset(const std::vector<unsigned char>& a_from, DynBitset& a_to)
{
  a_to.resize(a_from.size());
  for (size_t i = 0; i < a_from.size(); ++i)
  {
    a_to[i] = a_from[i] != 0;
  }
} // VecBooleanToDynBitset
//------------------------------------------------------------------------------
/// \brief Convert from a DynBitset to a VecBoolean.
/// \param[in]  a_from: DynBitset array in.
/// \param[out] a_to: VecBoolean out.
//------------------------------------------------------------------------------
void DynBitsetToVecBoolean(const DynBitset& a_from, std::vector<unsigned char>& a_to)
{
  a_to.clear();
  a_to.reserve(a_from.size());
  for (size_t i = 0; i < a_from.size(); ++i)
  {
    a_to.push_back(a_from[i]);
  }
} // DynBitsetToVecBoolean

} // namespace xms
