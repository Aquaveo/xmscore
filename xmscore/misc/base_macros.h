#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Macros used in xmscore.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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
