#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Utilities for c-style arrays.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief Returns the number of elements of a C/C++ array.
///
///  It uses the XmArraySizeHelper template function.
//------------------------------------------------------------------------------
#define XM_COUNTOF(array) (sizeof(::xms::caArraySizeHelper(array)))

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//------------------------------------------------------------------------------
/// \brief Helper to get the number of elements of a C/C++ array.
/// \param array Array of data
/// \return array size
///
/// Found this here:
///  <http://blogs.msdn.com/the1/pages/210011.aspx>. Note that "it doesn't
///  work with types defined inside a function because _ArraySizeHelper expects
///  a type that is accessible in the global scope." In the future could change
///  to a C++11 version from <http://www.g-truc.net/post-0708.html>:
///  \code
///  template <typename T, std::size_t N>
///  constexpr std::size_t caCountOf(T const (&)[N]) noexcept
///  {
///    return N;
///  }
///  #define XM_COUNTOF(array) (::xms::caCountOf(array)))
///  \endcode
//------------------------------------------------------------------------------
template <typename T, size_t N>
char (&caArraySizeHelper(T (&array)[N]))[N];

} // namespace xms
