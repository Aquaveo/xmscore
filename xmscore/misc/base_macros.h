#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Macros used in xmsng.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//------------------------------------------------------------------------------
/// \brief A macro to disallow the copy constructor and operator= functions.
///        This should be used in the private: declarations for a class.
///        (Or inherit privately from boost::noncopyable.)
//------------------------------------------------------------------------------
#define XM_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;         \
  void operator=(const TypeName&) = delete;

} // namespace xms
