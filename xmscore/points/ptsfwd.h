#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Include this small header instead of pt.h
///
/// This file was created with the same idea as iosfwd. You can't forward
/// declare a Pt3d because it is a typedef - so you have to include the header
/// where Pt3d is defined. But instead of including the large header file that
/// defines the Pt classes, you can just include this small header. -MJK
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

namespace xms
{
//----- Forward declarations ---------------------------------------------------

template <class T>
class Pt2; ///< 2d point template
template <class T>
class Pt3; ///< 3d point template
template <class T>
class Pt4; ///< 4d point template

//----- Typedefs ---------------------------------------------------------------

typedef Pt2<int> Pt2i;    ///< 2d point int
typedef Pt2<float> Pt2f;  ///< 2d point float
typedef Pt2<double> Pt2d; ///< 2d point double

typedef Pt3<int> Pt3i;    ///< 3d point int
typedef Pt3<float> Pt3f;  ///< 3d point float
typedef Pt3<double> Pt3d; ///< 3d point double

typedef Pt4<int> Pt4i;    ///< 4d point int
typedef Pt4<float> Pt4f;  ///< 4d point float
typedef Pt4<double> Pt4d; ///< 4d point double

} // namespace xms
