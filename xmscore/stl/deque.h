#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief std::deque types for convenience
/// \ingroup stl
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#include <deque>
#include <xmscore/points/ptsfwd.h>

namespace xms
{
//----- deques -----------------------------------------------------------------

//----- Old types --------------------------------------------------------------
/// \deprecated Don't use the "DEQ_..." types. Use the "Deq..." ones below
typedef std::deque<Pt2d> DEQ_PT2D; ///< short rename

//----- New types --------------------------------------------------------------

typedef std::deque<Pt2d> DeqPt2d; ///< short rename

} // namespace xms {
