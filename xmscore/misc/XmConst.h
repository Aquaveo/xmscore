#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Clearly named constants
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------
// 1. Standard library headers

// 3. Standard Library Headers
#include <limits>

// 4. External Library Headers

// 5. Shared Headers

// 6. Non-shared Headers
namespace xms
{
// Use std::min and std::max, not Windows' versions.
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

// Integer range constants
static const int XM_INT_HIGHEST = std::numeric_limits<int>::max();   ///< 2147483647
static const int XM_INT_LOWEST = std::numeric_limits<int>::lowest(); ///< (-2147483647 - 1)

// Unsigned integer range constants
static const unsigned int XM_UINT_HIGHEST =
  std::numeric_limits<unsigned int>::max(); ///< 4294967295
static const unsigned int XM_UINT_LOWEST = std::numeric_limits<unsigned int>::lowest(); ///< 0

// Key double constants
static const double XM_DBL_HIGHEST =
  std::numeric_limits<double>::max(); ///< 1.7976931348623157e+308
static const double XM_DBL_LOWEST =
  std::numeric_limits<double>::lowest(); ///< -1.7976931348623157e+308
static const double XM_DBL_NEAREST_ZERO =
  std::numeric_limits<double>::min(); ///< 2.2250738585072014e-308

// Key float constants
static const float XM_FLT_HIGHEST = std::numeric_limits<float>::max();      ///< 3.40282347e+38
static const float XM_FLT_LOWEST = std::numeric_limits<float>::lowest();    ///< -3.40282347e+38
static const float XM_FLT_NEAREST_ZERO = std::numeric_limits<float>::min(); ///< 1.17549435e-38

} // namespace xms