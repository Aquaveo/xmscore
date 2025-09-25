#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup math
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------
#define XMSCORE_MATH_H

#include <cmath> // for std::abs

namespace xms
{
//------------------------------------------------------------------------------
/// \brief Rounds
/// \param a: The value.
/// \return int
//------------------------------------------------------------------------------
template <class _T>
int Round(_T a)
{
  return (((a) > 0.0) ? ((int)((a) + 0.5)) : (((a) < 0.0) ? ((int)((a)-0.5)) : 0));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Integer absolute value
/// \param a: The value.
/// \return non-negative value
//------------------------------------------------------------------------------
template <class _T>
_T Miabs(_T a)
{
  return (((a) >= 0) ? (a) : (-(a)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Float absolute value
/// \param a: The value.
/// \return non-negative value
//------------------------------------------------------------------------------
template <class _T>
_T Mfabs(_T a)
{
  return (((a) >= 0.) ? (a) : (-(a)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Max of two values.
/// \param a: The first value.
/// \param b: The second value.
/// \return Max value
//------------------------------------------------------------------------------
template <class _T, class _U>
_T Mmax(_T a, _U b)
{
  return (((a) >= (b)) ? (a) : (b));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Min of two values.
/// \param a: The first value.
/// \param b: The second value.
/// \return Min value
//------------------------------------------------------------------------------
template <class _T, class _U>
_T Mmin(_T a, _U b)
{
  return (((a) >= (_T)(b)) ? (b) : (a));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Max of three values.
/// \param a: The first value.
/// \param b: The second value.
/// \param c: The third value.
/// \return Max value
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
_T Mmax3(_T a, _U b, _V c)
{
  return (((a) >= (b)) ? (((a) >= (c)) ? (a) : (c)) : (((b) >= (c)) ? (b) : (c)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Min of three values.
/// \param a: The first value.
/// \param b: The second value.
/// \param c: The third value.
/// \return Min value
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
_T Mmin3(_T a, _U b, _V c)
{
  return (((a) <= (b)) ? (((a) <= (c)) ? (a) : (c)) : (((b) <= (c)) ? (b) : (c)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Square
/// \param x: The value to square.
/// \return The value squared
//------------------------------------------------------------------------------
template <typename _T>
inline _T sqr(const _T x)
{
  return x * x;
} ///< macro
//------------------------------------------------------------------------------
/// \brief XY distance.
/// \param x1: X coordinate of first point.
/// \param y1: Y coordinate of first point.
/// \param x2: X coordinate of second point.
/// \param y2: Y coordinate of second point.
/// \return XY distance.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V, class _W>
double Mdist(_T x1, _U y1, _V x2, _W y2)
{
  return sqrt((double)(sqr(x1 - x2) + sqr(y1 - y2)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief XY distance squared.
/// \param x1: X coordinate of first point.
/// \param y1: Y coordinate of first point.
/// \param x2: X coordinate of second point.
/// \param y2: Y coordinate of second point.
/// \return XY distance squared.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V, class _W>
double MdistSq(_T x1, _U y1, _V x2, _W y2)
{
  return (double)(sqr(x1 - x2) + sqr(y1 - y2));
} ///< macro
//------------------------------------------------------------------------------
/// \brief XYZ distance.
/// \param x1: X coordinate of first point.
/// \param y1: Y coordinate of first point.
/// \param z1: Z coordinate of first point.
/// \param x2: X coordinate of second point.
/// \param y2: Y coordinate of second point.
/// \param z2: Z coordinate of second point.
/// \return XYZ distance.
//------------------------------------------------------------------------------
template <typename X1, typename Y1, typename Z1, typename X2, typename Y2, typename Z2>
double Mdist(X1 x1, Y1 y1, Z1 z1, X2 x2, Y2 y2, Z2 z2)
{
  return sqrt((double)(sqr(x1 - x2) + sqr(y1 - y2) + sqr(z1 - z2)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Magnituded squared (x*x + y*y + z*z + w*w)
/// \param x: Value in x.
/// \param y: Value in y.
/// \param z: Value in z.
/// \param w: Value in x.
/// \return Magnitude squared.
//------------------------------------------------------------------------------
template <typename _T>
double MagSquared(_T const x, _T const y, _T const z = 0, _T const w = 0)
{
  return (double)(x * x + y * y + z * z + w * w);
} ///< macro
//------------------------------------------------------------------------------
/// \brief Magnituded sqrt(x*x + y*y + z*z + w*w)
/// \param x: Value in x.
/// \param y: Value in y.
/// \param z: Value in z.
/// \param w: Value in x.
/// \return Magnitude.
//------------------------------------------------------------------------------
template <typename _T>
double Mag(_T const x, _T const y, _T const z = 0, _T const w = 0)
{
  return sqrt(MagSquared(x, y, z, w));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns a value between a_min and a_max.
/// \param a_in: Value to be clamped.
/// \param a_min: Minimum value.
/// \param a_max: Maximum value.
/// \return Clamped value.
//------------------------------------------------------------------------------
template <typename _T>
_T Clamp(_T a_in, _T a_min, _T a_max)
{
  return Mmin(Mmax(a_in, a_min), a_max);
} ///< macro

// The following 3 macros ending with EPS should have an epsilon
// value passed to them.  This should be something like FLT_EPSILON or
// DBL_EPS or 1e-6 etc.  The epsilon value is multiplied by the
// sum of the two floats to compute a tolerance

//------------------------------------------------------------------------------
/// \brief Returns true if A == B within an epsilon (DBL EPS).
/// \param A: left hand side.
/// \param B: right hand side.
/// \param epsilon: The epsilon.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool EQ_EPS(_T A, _U B, _V epsilon)
{
  return (std::abs((A) - (B)) <= std::abs(((A) + (B)) * (epsilon)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A < B equal within an epsilon (DBL EPS).
/// \param A: left hand side.
/// \param B: right hand side.
/// \param epsilon: The epsilon.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool LT_EPS(_T A, _U B, _V epsilon)
{
  return (((B) - (A)) > std::abs(((A) + (B)) * (epsilon)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A > B equal within an epsilon (DBL EPS).
/// \param A: left hand side.
/// \param B: right hand side.
/// \param epsilon: The epsilon.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool GT_EPS(_T A, _U B, _V epsilon)
{
  return (((A) - (B)) > std::abs(((A) + (B)) * (epsilon)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A <= B equal within an epsilon (DBL EPS).
/// \param A: left hand side.
/// \param B: right hand side.
/// \param epsilon: The epsilon.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool LTEQ_EPS(_T A, _U B, _V epsilon)
{
  return (LT_EPS((A), (B), (epsilon)) || EQ_EPS((A), (B), (epsilon)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A >= B equal within an epsilon (DBL EPS).
/// \param A: left hand side.
/// \param B: right hand side.
/// \param epsilon: The epsilon.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool GTEQ_EPS(_T A, _U B, _V epsilon)
{
  return (GT_EPS((A), (B), (epsilon)) || EQ_EPS((A), (B), (epsilon)));
} ///< macro

// The following 3 macros ending with TOL should have a tolerance
// passed to them.  This tolerance should be something like
// g_triangletolerancexy, or a tolerance that has been computed
// from the range of the numbers involved.  The numbers are compared
// against the tolerance
// Equal-with-tolerance EQ_TOL is needed, otherwise double values would not be
// equal when, for all practical purposes, they are equal.  Given that a number
// is equal-with-tolerance to another number, then it cannot also be either
// less-than or greater-than that other number.  Therefore, LT_TOL and GT_TOL
// give non-overlapping results rather than the result given by < and >.

//------------------------------------------------------------------------------
/// \brief Returns true if A == B equal within a tolerance.
/// \param A: left hand side.
/// \param B: right hand side.
/// \param tolerance: The tolerance.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool EQ_TOL(const _T& A, const _U& B, const _V& tolerance)
{
  return (std::abs((A) - (B)) <= (tolerance));
}
//------------------------------------------------------------------------------
/// \brief Returns true if A < B equal within a tolerance.
/// \param A: left hand side.
/// \param B: right hand side.
/// \param tolerance: The tolerance.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool LT_TOL(_T A, _U B, _V tolerance)
{
  return (((B) - (A)) > (tolerance));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A > B equal within a tolerance.
/// \param A: left hand side.
/// \param B: right hand side.
/// \param tolerance: The tolerance.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool GT_TOL(_T A, _U B, _V tolerance)
{
  return (((A) - (B)) > (tolerance));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A <= B equal within a tolerance.
/// \param A: left hand side.
/// \param B: right hand side.
/// \param tol: The tolerance.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool LTEQ_TOL(_T A, _U B, _V tol)
{
  return (LT_TOL((A), (B), (tol)) || EQ_TOL((A), (B), (tol)));
} ///< macro
//------------------------------------------------------------------------------
/// \brief Returns true if A >= B equal within a tolerance.
/// \param A: left hand side.
/// \param B: right hand side.
/// \param tol: The tolerance.
/// \return true or false.
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool GTEQ_TOL(_T A, _U B, _V tol)
{
  return (GT_TOL((A), (B), (tol)) || EQ_TOL((A), (B), (tol)));
} ///< macro

} // namespace xms {
