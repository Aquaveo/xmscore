#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Macros etc that make boost more convenient to use.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
#ifndef BSHP
#define BSHP boost::shared_ptr ///< short rename
#endif

#define BSCP boost::scoped_ptr ///< short rename

#define BDPC boost::dynamic_pointer_cast ///< short rename
#define BSPC boost::static_pointer_cast  ///< short rename

#define BWP boost::weak_ptr ///< short rename
// If we want to add stuff for scoped pointers or weak pointers or other
// boost things, we could add them here.

/// \brief utility function
/// \param a_in Shared pointer to copy
/// \return a copy of the shared pointer
template <typename T>
BSHP<T> CopyBSHP(const BSHP<T>& a_in) ///< utility function
{
  BSHP<T> out;
  if (a_in)
  {
    out.reset(new T(*a_in.get()));
  }
  return out;
}

// Use BOOST_FOREACH as FOREACH
#define FOREACH BOOST_FOREACH ///< short rename

} // namespace xms
