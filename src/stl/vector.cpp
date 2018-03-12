//------------------------------------------------------------------------------
/// \file
/// \brief std::vector types for convenience
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//>>> Shared1\shared\guido\xms_stl.cpp copied here

//----- Included files ---------------------------------------------------------

#include <xmscore/stl/vector.h>

using namespace xms;

//----- Function definitions ---------------------------------------------------

////------------------------------------------------------------------------------
///// \brief Convert a VEC_BOOL to a VEC_BOOLEAN
////------------------------------------------------------------------------------
// void VecBoolToVecBoolean (const VEC_BOOL& a_vBool, VEC_BOOLEAN& a_vBoolean)
//{
//  a_vBoolean.resize(a_vBool.size());
//  for (int i = 0; i < (int)a_vBool.size(); ++i)
//  {
//    a_vBoolean[i] = a_vBool[i];
//  }
//}
////------------------------------------------------------------------------------
///// \brief Convert a VEC_BOOLEAN to a VEC_BOOL
////------------------------------------------------------------------------------
// void VecBooleanToVecBool (const VEC_BOOLEAN& a_vBoolean, VEC_BOOL& a_vBool)
//{
//  a_vBool.resize(a_vBoolean.size());
//  for (int i = 0; i < (int)a_vBoolean.size(); ++i)
//  {
//    a_vBool[i] = (a_vBoolean[i] != 0);
//  }
//}
