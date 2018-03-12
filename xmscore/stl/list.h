#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::list types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

#include <list>

namespace xms
{
//----- Old types --------------------------------------------------------------
/// \deprecated Don't use the "LIST_..." types. Use the "List..." ones below
typedef std::list<Pt2d> LIST_MP2; ///< short rename

//----- New types --------------------------------------------------------------

typedef std::list<Pt2d> ListPt2d; ///< short rename

} // namespace xms {
