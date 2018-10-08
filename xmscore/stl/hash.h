#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::hash_map types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#include <hash_map>

namespace xms
{
//----- Old types --------------------------------------------------------------
/// \deprecated Don't use the "LIST_..." types. Use the "List..." ones below
typedef stdext::hash_map<std::string, std::string> HASH_S_S; ///< short rename
typedef stdext::hash_map<int, std::string> HASH_I_S;         ///< short rename

//----- New types --------------------------------------------------------------

typedef stdext::hash_map<std::string, std::string> HashStrStr; ///< short rename
typedef stdext::hash_map<int, std::string> HashIntStr;         ///< short rename

} // namespace xms
