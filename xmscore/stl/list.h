#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::list types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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
