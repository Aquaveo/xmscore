#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::deque types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

#include <deque>
#include <xmscore/points/ptsfwd.h>

namespace xms
{
//----- deques ---------------------------------------------------------------

//----- Old types --------------------------------------------------------------
/// \deprecated Don't use the "DEQ_..." types. Use the "Deq..." ones below
typedef std::deque<Pt2d> DEQ_PT2D; ///< short rename

//----- New types --------------------------------------------------------------

typedef std::deque<Pt2d> DeqPt2d; ///< short rename

} // namespace xms {
