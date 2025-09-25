#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup points
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard Library Headers
#include <iosfwd> // fwd decl ostream
#include <stdexcept>

// 4. External Library Headers

// 5. Shared Headers
#include <xmscore/points/ptsfwd.h>

namespace xms
{
//------------------------------------------------------------------------------
// NOTES: All member functions are defined here. None are defined in .cpp files.
//        See the notes below from MSDN "Members of Class Templates".
//
// C++ member templates are supported as long as they are fully defined within
// the enclosing class. For example, the following is supported:
//
// template<typename T>
// class X
// {
// public:
//   template<typename U>
//   void mf(const U &u)
//   {
//   }
// };
//
// While the following is not:
// template<typename T>
// class X
// {
// public:
//    template<typename U>
//    void mf(const U &u);
// };
//
// template<typename T> template <typename U>
// void X<T>::mf(const U &u)
// {
// }
//------------------------------------------------------------------------------

//----- Forward declarations ---------------------------------------------------

// Moved to ptsfwd.h so that you can include just that file instead.
// template <class T> class Pt2;
// template <class T> class Pt3;
// template <class T> class Pt4;

//----- Typedefs ---------------------------------------------------------------

// Moved to ptsfwd.h so that you can include just that file instead.
// typedef Pt2<int>    Pt2i;
// typedef Pt2<float>  Pt2f;
// typedef Pt2<double> Pt2d;
//
// typedef Pt3<int>    Pt3i;
// typedef Pt3<float>  Pt3f;
// typedef Pt3<double> Pt3d;
//
// typedef Pt4<int>    Pt4i;
// typedef Pt4<float>  Pt4f;
// typedef Pt4<double> Pt4d;

//----- Classes / Structs ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \brief 2D Point template class
////////////////////////////////////////////////////////////////////////////////
template <class T>
class Pt2
{
  //  friend std::ostream& operator<<(std::ostream&, const Pt2&);
public:
  // Member variables

  T x; ///< x coordinate
  T y; ///< y coordinate

  // Constructors

  Pt2()
  : x((T)0)
  , y((T)0)
  {
  } ///< default constructor
  /// \brief constructor
  /// \param[in] a_x: X value.
  /// \param[in] a_y: Y value.
  Pt2(T a_x, T a_y)
  : x(a_x)
  , y(a_y)
  {
  }
  /// \brief constructor
  /// \param[in] a: Value used for x and y.
  explicit Pt2(const T& a)
  : x(a)
  , y(a)
  {
  }
  // (single arg ctors should be explicit)

  // copy constructor
  /// \param[in] a: Point to copy from.
  Pt2(const Pt2& a)
  : x(a.x)
  , y(a.y)
  {
  } ///< copy construcor

  // constructors for conversions (all explicit)
  /// \brief constructor.
  /// \param a: Pt2.
  template <class U>
  explicit Pt2(const Pt2<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  {
  }
  /// \brief constructor.
  /// \param a: Pt3.
  template <class U>
  explicit Pt2(const Pt3<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  {
  }
  /// \brief constructor.
  /// \param a: Pt4.
  template <class U>
  explicit Pt2(const Pt4<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  {
  }

  // Destructor

  ~Pt2() {} ///< destructor. can't be virtual

  /// operator= (Assignment operator)
  /// \param[in] a: A constant.
  /// \return Pt2 reference.
  template <class U>
  inline const Pt2& operator=(const U& a)
  {
    x = (T)a;
    y = (T)a;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt2.
  /// \return Pt2 reference.
  template <class U>
  inline const Pt2& operator=(const Pt2<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt3.
  /// \return Pt2 reference.
  template <class U>
  inline const Pt2& operator=(const Pt3<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt4.
  /// \return Pt2 reference.
  template <class U>
  inline const Pt2& operator=(const Pt4<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    return *this;
  }

  // Logical operators

  /// operator==
  /// \param[in] a: A constant.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const U& a) const
  {
    return (x == a && y == a);
  }
  /// operator==
  /// \param[in] a: Pt2.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt2<U>& a) const
  {
    return (x == a.x && y == a.y);
  }
  /// operator==
  /// \param[in] a: Pt3.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt3<U>& a) const
  {
    return (x == a.x && y == a.y);
  }
  /// operator==
  /// \param[in] a: Pt4.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt4<U>& a) const
  {
    return (x == a.x && y == a.y);
  }

  /// operator!=
  /// \param[in] a: A constant.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const U& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt2.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt2<U>& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt3.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt3<U>& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt4.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt4<U>& a) const
  {
    return !(*this == a);
  }

  /// operator<
  /// \param[in] a: A constant.
  /// \return true if <.
  template <class U>
  inline bool operator<(const U& a) const
  {
    if (x < a)
      return 1;
    else if (x > a)
      return 0;
    else
    {
      if (y < a)
        return 1;
      else
        return 0;
    }
  }
  /// operator<
  /// \param[in] a: Pt2.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt2<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else
        return 0;
    }
  }
  /// operator<
  /// \param[in] a: Pt3.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt3<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else
        return 0;
    }
  }
  /// operator<
  /// \param[in] a: Pt4.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt4<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else
        return 0;
    }
  }

  /// operator<=
  /// \param[in] a: A constant.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const U& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt2.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt2<U>& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt3.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt3<U>& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt4.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt4<U>& a) const
  {
    return (*this < a || *this == a);
  }

  /// operator>
  /// \param[in] a: A constant.
  /// \return true if >.
  template <class U>
  inline bool operator>(const U& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt2.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt2<U>& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt3.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt3<U>& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt4.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt4<U>& a) const
  {
    return !(*this <= a);
  }

  /// operator>=
  /// \param[in] a: A constant.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const U& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt2.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt2<U>& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt3.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt3<U>& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt4.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt4<U>& a) const
  {
    return (*this > a || *this == a);
  }

  // Arithmetic operators

  /// operator+
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator+(const U& a) const // Pt2 + int (etc)
  {
    return Pt2((T)(x + a), (T)(y + a));
  }
  /// operator+
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator+(const Pt2<U>& a) const // Pt2 + Pt2
  {
    return Pt2((T)(x + a.x), (T)(y + a.y));
  }
  /// operator+
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator+(const Pt3<U>& a) const // Pt2 + Pt3
  {
    return Pt2((T)(x + a.x), (T)(y + a.y));
  }
  /// operator+
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator+(const Pt4<U>& a) const // Pt2 + Pt4
  {
    return Pt2((T)(x + a.x), (T)(y + a.y));
  }

  /// operator-
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator-(const U& a) const // Pt2 - int (etc)
  {
    return Pt2((T)(x - a), (T)(y - a));
  }
  /// operator-
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator-(const Pt2<U>& a) const // Pt2 - Pt2
  {
    return Pt2((T)(x - a.x), (T)(y - a.y));
  }
  /// operator-
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator-(const Pt3<U>& a) const // Pt2 - Pt3
  {
    return Pt2((T)(x - a.x), (T)(y - a.y));
  }
  /// operator-
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator-(const Pt4<U>& a) const // Pt2 - Pt4
  {
    return Pt2((T)(x - a.x), (T)(y - a.y));
  }

  /// unary operator-
  /// \return Pt2.
  inline Pt2 operator-() const // -Pt2
  {
    return Pt2((T)(-x), (T)(-y));
  }

  /// operator*
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator*(const U& a) const // Pt2 * int (etc)
  {
    return Pt2((T)(x * a), (T)(y * a));
  }
  /// operator*
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator*(const Pt2<U>& a) const // Pt2 * Pt2
  {
    return Pt2((T)(x * a.x), (T)(y * a.y));
  }
  /// operator*
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator*(const Pt3<U>& a) const // Pt2 * Pt3
  {
    return Pt2((T)(x * a.x), (T)(y * a.y));
  }
  /// operator*
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator*(const Pt4<U>& a) const // Pt2 * Pt4
  {
    return Pt2((T)(x * a.x), (T)(y * a.y));
  }

  /// operator/
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator/(const U& a) const // Pt2 / int (etc)
  {
    return Pt2((T)(x / a), (T)(y / a));
  }
  /// operator/
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator/(const Pt2<U>& a) const // Pt2 / Pt2
  {
    return Pt2((T)(x / a.x), (T)(y / a.y));
  }
  /// operator/
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator/(const Pt3<U>& a) const // Pt2 / Pt3
  {
    return Pt2((T)(x / a.x), (T)(y / a.y));
  }
  /// operator/
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline Pt2 operator/(const Pt4<U>& a) const // Pt2 / Pt4
  {
    return Pt2((T)(x / a.x), (T)(y / a.y));
  }

  /// operator+=
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline void operator+=(const U& a) // Pt2 += int (etc)
  {
    x = (T)(x + a);
    y = (T)(y + a);
  }
  /// operator+=
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline void operator+=(const Pt2<U>& a) // Pt2 += Pt2
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
  }
  /// operator+=
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline void operator+=(const Pt3<U>& a) // Pt2 += Pt3
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
  }
  /// operator+=
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline void operator+=(const Pt4<U>& a) // Pt2 += Pt4
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
  }

  /// operator-=
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline void operator-=(const U& a) // Pt2 -= int (etc)
  {
    x = (T)(x - a);
    y = (T)(y - a);
  }
  /// operator-=
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline void operator-=(const Pt2<U>& a) // Pt2 -= Pt2
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
  }
  /// operator-=
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline void operator-=(const Pt3<U>& a) // Pt2 -= Pt3
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
  }
  /// operator-=
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline void operator-=(const Pt4<U>& a) // Pt2 -= Pt4
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
  }

  /// operator*=
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline void operator*=(const U& a) // Pt2 *= int (etc)
  {
    x = (T)(x * a);
    y = (T)(y * a);
  }
  /// operator*=
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline void operator*=(const Pt2<U>& a) // Pt2 *= Pt2
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
  }
  /// operator*=
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline void operator*=(const Pt3<U>& a) // Pt2 *= Pt3
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
  }
  /// operator*=
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline void operator*=(const Pt4<U>& a) // Pt2 *= Pt4
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
  }

  /// operator/=
  /// \param[in] a: A constant.
  /// \return Pt2.
  template <class U>
  inline void operator/=(const U& a) // Pt2 /= int (etc)
  {
    x = (T)(x / a);
    y = (T)(y / a);
  }
  /// operator/=
  /// \param[in] a: Pt2.
  /// \return Pt2.
  template <class U>
  inline void operator/=(const Pt2<U>& a) // Pt2 /= Pt2
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
  }
  /// operator/=
  /// \param[in] a: Pt3.
  /// \return Pt2.
  template <class U>
  inline void operator/=(const Pt3<U>& a) // Pt2 /= Pt3
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
  }
  /// operator/=
  /// \param[in] a: Pt4.
  /// \return Pt2.
  template <class U>
  inline void operator/=(const Pt4<U>& a) // Pt2 /= Pt4
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
  }

  // Other stuff

  /// Setter
  /// \param a_x: x.
  /// \param a_y: y.
  void Set(T a_x, T a_y)
  {
    x = a_x;
    y = a_y;
  }
  /// Setter
  /// \param a: Value to use for x and y.
  void Set(T a)
  {
    x = a;
    y = a;
  }

  /// operator[]
  /// \param a: index: 0 = x, 1 = y
  /// \return Value.
  T operator[](unsigned int a) const { return *(&x + a); }
  /// operator[]
  /// \param a: index: 0 = x, 1 = y
  /// \return Value.
  T& operator[](unsigned int a) { return *(&x + a); }

  /// at
  /// \param a: index: 0 = x, 1 = y
  /// \return Value.
  const T& at(unsigned int a) const
  {
    switch (a)
    {
    case 0:
      return x;
    case 1:
      return y;
    default:
      throw std::out_of_range("Pt2<T>::at(): error out of range");
    }
  }
  ///  OVERLOAD
  /// \param a: index: 0 = x, 1 = y
  /// \return Value.
  T& at(unsigned int a) // non-const version
  {
    // Use the const version. See Effective C++ 3rd Edition Item 3.
    return const_cast<T&>(static_cast<const Pt2<T>&>(*this).at(a));
  }

  /// \brief For serialization
  /// \param archive: The archive.
  /// \param version: The version.
  template <typename Archive>
  void serialize(Archive& archive, const unsigned int version)
  {
    (void)version; // For doxygen which couldn't handle commenting it out.
    archive& x;
    archive& y;
  }

}; // Pt2

////////////////////////////////////////////////////////////////////////////////
/// 3d point template class
////////////////////////////////////////////////////////////////////////////////
template <class T>
class Pt3
{
  //  friend std::ostream& operator<<(std::ostream&, const Pt3&);
public:
  // Member variables

  T x; ///< x coordinate
  T y; ///< y coordinate
  T z; ///< z coordinate

  // Constructors

  Pt3()
  : x((T)0)
  , y((T)0)
  , z((T)0)
  {
  } ///< default constructor
  /// \brief constructor
  /// \param[in] a_x: X value.
  /// \param[in] a_y: Y value.
  /// \param[in] a_z: Z value.
  Pt3(T a_x, T a_y, T a_z)
  : x(a_x)
  , y(a_y)
  , z(a_z)
  {
  }
  /// \brief constructor. Z is set to 0.0.
  /// \param[in] a_x: X value.
  /// \param[in] a_y: Y value.
  Pt3(T a_x, T a_y)
  : x(a_x)
  , y(a_y)
  , z(0.0)
  {
  }
  /// \brief constructor
  /// \param[in] a: Value used for x, y and z.
  explicit Pt3(T a)
  : x(a)
  , y(a)
  , z(a)
  {
  }
  // (single arg ctors should be explicit)

  /// copy constructor
  /// \param[in] a: Point to copy from.
  Pt3(const Pt3& a)
  : x(a.x)
  , y(a.y)
  , z(a.z)
  {
  }

  // constructors for conversions (all explicit)
  /// \brief constructor. Z is set to 0
  /// \param a: Pt2.
  template <class U>
  explicit Pt3(const Pt2<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  , z(0)
  {
  }
  /// \brief constructor.
  /// \param a: Pt3.
  template <class U>
  explicit Pt3(const Pt3<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  , z((T)a.z)
  {
  }
  /// \brief constructor.
  /// \param a: Pt4.
  template <class U>
  explicit Pt3(const Pt4<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  , z((T)a.z)
  {
  }

  ~Pt3() {} ///< destructor. can't be virtual

  /// operator= (Assignment operator)
  /// \param[in] a: A constant.
  /// \return Pt3 reference.
  template <class U>
  inline const Pt3& operator=(const U& a)
  {
    x = (T)a;
    y = (T)a;
    z = (T)a;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt2.
  /// \return Pt3 reference.
  template <class U>
  inline const Pt3& operator=(const Pt2<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt3.
  /// \return Pt3 reference.
  template <class U>
  inline const Pt3& operator=(const Pt3<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    z = (T)a.z;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt4.
  /// \return Pt3 reference.
  template <class U>
  inline const Pt3& operator=(const Pt4<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    z = (T)a.z;
    return *this;
  }

  // Logical operators

  /// operator==
  /// \param[in] a: A constant.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const U& a) const
  {
    return (x == a && y == a && z == a);
  }
  /// operator==
  /// \param[in] a: Pt2.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt2<U>& a) const
  {
    return (x == a.x && y == a.y);
  }
  /// operator==
  /// \param[in] a: Pt3.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt3<U>& a) const
  {
    return (x == a.x && y == a.y && z == a.z);
  }
  /// operator==
  /// \param[in] a: Pt4.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt4<U>& a) const
  {
    return (x == a.x && y == a.y && z == a.z);
  }

  /// operator!=
  /// \param[in] a: A constant.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const U& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt2.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt2<U>& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt3.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt3<U>& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt4.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt4<U>& a) const
  {
    return !(*this == a);
  }

  /// operator<
  /// \param[in] a: A constant.
  /// \return true if <.
  template <class U>
  inline bool operator<(const U& a) const
  {
    if (x < a)
      return 1;
    else if (x > a)
      return 0;
    else
    {
      if (y < a)
        return 1;
      else if (y > a)
        return 0;
      else
      {
        if (z < a)
          return 1;
        else
          return 0;
      }
    }
  }
  /// operator<
  /// \param[in] a: Pt2.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt2<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else
        return 0;
    }
  }
  /// operator<
  /// \param[in] a: Pt3.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt3<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else if (y > a.y)
        return 0;
      else
      {
        if (z < a.z)
          return 1;
        else
          return 0;
      }
    }
  }
  /// operator<
  /// \param[in] a: Pt4.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt4<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else if (y > a.y)
        return 0;
      else
      {
        if (z < a.z)
          return 1;
        else
          return 0;
      }
    }
  }

  /// operator<=
  /// \param[in] a: A constant.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const U& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt2.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt2<U>& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt3.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt3<U>& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt4.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt4<U>& a) const
  {
    return (*this < a || *this == a);
  }

  /// operator>
  /// \param[in] a: A constant.
  /// \return true if >.
  template <class U>
  inline bool operator>(const U& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt2.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt2<U>& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt3.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt3<U>& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt4.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt4<U>& a) const
  {
    return !(*this <= a);
  }

  /// operator>=
  /// \param[in] a: A constant.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const U& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt2.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt2<U>& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt3.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt3<U>& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt4.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt4<U>& a) const
  {
    return (*this > a || *this == a);
  }

  // Arithmetic operators

  /// operator+
  /// \param[in] a: A constant.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator+(const U& a) const // Pt3 + int (etc)
  {
    return Pt3((T)(x + a), (T)(y + a), (T)(z + a));
  }
  /// operator+
  /// \param[in] a: Pt2.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator+(const Pt2<U>& a) const // Pt3 + Pt2
  {
    return Pt3((T)(x + a.x), (T)(y + a.y), z);
  }
  /// operator+
  /// \param[in] a: Pt3.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator+(const Pt3<U>& a) const // Pt3 + Pt3
  {
    return Pt3((T)(x + a.x), (T)(y + a.y), (T)(z + a.z));
  }
  /// operator+
  /// \param[in] a: Pt4.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator+(const Pt4<U>& a) const // Pt3 + Pt4
  {
    return Pt3((T)(x + a.x), (T)(y + a.y), (T)(z + a.z));
  }

  /// operator-
  /// \param[in] a: A constant.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator-(const U& a) const // Pt3 - int (etc)
  {
    return Pt3((T)(x - a), (T)(y - a), (T)(z - a));
  }
  /// operator-
  /// \param[in] a: Pt2.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator-(const Pt2<U>& a) const // Pt3 - Pt2
  {
    return Pt3((T)(x - a.x), (T)(y - a.y), z);
  }
  /// operator-
  /// \param[in] a: Pt3.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator-(const Pt3<U>& a) const // Pt3 - Pt3
  {
    return Pt3((T)(x - a.x), (T)(y - a.y), (T)(z - a.z));
  }
  /// operator-
  /// \param[in] a: Pt4.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator-(const Pt4<U>& a) const // Pt3 - Pt4
  {
    return Pt3((T)(x - a.x), (T)(y - a.y), (T)(z - a.z));
  }

  /// unary operator-
  /// \return Pt3.
  inline Pt3 operator-() const // -Pt3
  {
    return Pt3((T)(-x), (T)(-y), (T)(-z));
  }

  /// operator*
  /// \param[in] a: A constant.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator*(const U& a) const // Pt3 * int (etc)
  {
    return Pt3((T)(x * a), (T)(y * a), (T)(z * a));
  }
  /// operator*
  /// \param[in] a: Pt2.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator*(const Pt2<U>& a) const // Pt3 * Pt2
  {
    return Pt3((T)(x * a.x), (T)(y * a.y), z);
  }
  /// operator*
  /// \param[in] a: Pt3.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator*(const Pt3<U>& a) const // Pt3 * Pt3
  {
    return Pt3((T)(x * a.x), (T)(y * a.y), (T)(z * a.z));
  }
  /// operator*
  /// \param[in] a: Pt4.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator*(const Pt4<U>& a) const // Pt3 * Pt4
  {
    return Pt3((T)(x * a.x), (T)(y * a.y), (T)(z * a.z));
  }

  /// operator/
  /// \param[in] a: Pt3.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator/(const U& a) const // Pt3 / int (etc)
  {
    return Pt3((T)(x / a), (T)(y / a), (T)(z / a));
  }
  /// operator/
  /// \param[in] a: Pt2.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator/(const Pt2<U>& a) const // Pt3 / Pt2
  {
    return Pt3((T)(x / a.x), (T)(y / a.y), z);
  }
  /// operator/
  /// \param[in] a: Pt3.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator/(const Pt3<U>& a) const // Pt3 / Pt3
  {
    return Pt3((T)(x / a.x), (T)(y / a.y), (T)(z / a.z));
  }
  /// operator/
  /// \param[in] a: Pt4.
  /// \return Pt3.
  template <class U>
  inline Pt3 operator/(const Pt4<U>& a) const // Pt3 / Pt4
  {
    return Pt3((T)(x / a.x), (T)(y / a.y), (T)(z / a.z));
  }

  /// operator+=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator+=(const U& a) // Pt3 += int (etc)
  {
    x = (T)(x + a);
    y = (T)(y + a);
    z = (T)(z + a);
  }
  /// operator+=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator+=(const Pt2<U>& a) // Pt3 += Pt2
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
  }
  /// operator+=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator+=(const Pt3<U>& a) // Pt3 += Pt3
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
    z = (T)(z + a.z);
  }
  /// operator+=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator+=(const Pt4<U>& a) // Pt3 += Pt4
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
    z = (T)(z + a.z);
  }

  /// operator-=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator-=(const U& a) // Pt3 -= int (etc)
  {
    x = (T)(x - a);
    y = (T)(y - a);
    z = (T)(z - a);
  }
  /// operator-=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator-=(const Pt2<U>& a) // Pt3 -= Pt2
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
  }
  /// operator-=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator-=(const Pt3<U>& a) // Pt3 -= Pt3
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
    z = (T)(z - a.z);
  }
  /// operator-=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator-=(const Pt4<U>& a) // Pt3 -= Pt4
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
    z = (T)(z - a.z);
  }

  /// operator*=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator*=(const U& a) // Pt3 *= int (etc)
  {
    x = (T)(x * a);
    y = (T)(y * a);
    z = (T)(z * a);
  }
  /// operator*=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator*=(const Pt2<U>& a) // Pt3 *= Pt2
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
  }
  /// operator*=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator*=(const Pt3<U>& a) // Pt3 *= Pt3
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
    z = (T)(z * a.z);
  }
  /// operator*=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator*=(const Pt4<U>& a) // Pt3 *= Pt4
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
    z = (T)(z * a.z);
  }

  /// operator/=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator/=(const U& a) // Pt3 /= int (etc)
  {
    x = (T)(x / a);
    y = (T)(y / a);
    z = (T)(z / a);
  }
  /// operator/=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator/=(const Pt2<U>& a) // Pt3 /= Pt2
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
  }
  /// operator/=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator/=(const Pt3<U>& a) // Pt3 /= Pt3
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
    z = (T)(z / a.z);
  }
  /// operator/=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator/=(const Pt4<U>& a) // Pt3 /= Pt4
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
    z = (T)(z / a.z);
  }

  // Other stuff

  /// Setter
  /// \param a_x: x.
  /// \param a_y: y.
  /// \param a_z: z.
  void Set(T a_x, T a_y, T a_z)
  {
    x = a_x;
    y = a_y;
    z = a_z;
  }
  /// Setter
  /// \param a: Value to use for x, y and z.
  void Set(T a)
  {
    x = a;
    y = a;
    z = a;
  }

  /// operator[]
  /// \param a: index: 0 = x, 1 = y, 2 = z
  /// \return Value.
  T operator[](unsigned int a) const { return *(&x + a); }
  /// operator[]
  /// \param a: index: 0 = x, 1 = y, 2 = z
  /// \return Value.
  T& operator[](unsigned int a) { return *(&x + a); }

  /// at
  /// \param a: index: 0 = x, 1 = y, 2 = z
  /// \return Value.
  const T& at(unsigned int a) const
  {
    switch (a)
    {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range("Pt3<T>::at(): error out of range");
    }
  }
  /// ----- OVERLOAD -----
  /// \param a: index: 0 = x, 1 = y, 2 = z
  /// \return Value.
  T& at(unsigned int a) // non-const version
  {
    // Use the const version. See Effective C++ 3rd Edition Item 3.
    return const_cast<T&>(static_cast<const Pt3<T>&>(*this).at(a));
  }

  // Typedefs

  typedef T value_type; ///< value_type

  /// \brief For serialization
  /// \param archive: The archive.
  /// \param version: The version.
  template <typename Archive>
  void serialize(Archive& archive, const unsigned int version)
  {
    (void)version; // For doxygen which couldn't handle commenting it out.
    archive& x;
    archive& y;
    archive& z;
  }

}; // Pt3

/// Multiply Pt3 by int.
/// \param a: Multiplier.
/// \param pt: Point
/// \return Point
template <class T>
inline Pt3<T> operator*(int a, const Pt3<T>& pt)
{
  return (pt * a);
}

/// Multiply Pt3 by float.
/// \param a: Multiplier.
/// \param pt: Point
/// \return Point
template <class T>
inline Pt3<T> operator*(float a, const Pt3<T>& pt)
{
  return (pt * a);
}

/// Multiply Pt3 by double.
/// \param a: Multiplier.
/// \param pt: Point
/// \return Point
template <class T>
inline Pt3<T> operator*(double a, const Pt3<T>& pt)
{
  return (pt * a);
}

////////////////////////////////////////////////////////////////////////////////
/// 4D point template class
////////////////////////////////////////////////////////////////////////////////
template <class T>
class Pt4
{
  // friend std::ostream& operator<<(std::ostream&, const Pt4&);
public:
  // Member variables

  T x; ///< x coordinate
  T y; ///< y coordinate
  T z; ///< z coordinate
  T w; ///< w coordinate

  // Constructors

  Pt4()
  : x((T)0)
  , y((T)0)
  , z((T)0)
  , w((T)0)
  {
  } ///< default constructor
  /// \brief constructor
  /// \param[in] a_x: X value.
  /// \param[in] a_y: Y value.
  /// \param[in] a_z: Z value.
  /// \param[in] a_w: W value.
  Pt4(T a_x, T a_y, T a_z, T a_w)
  : x(a_x)
  , y(a_y)
  , z(a_z)
  , w(a_w)
  {
  }
  /// \brief constructor
  /// \param[in] a: Value used for x, y, z and w.
  explicit Pt4(T a)
  : x(a)
  , y(a)
  , z(a)
  , w(a)
  {
  }
  // (single arg ctors should be explicit)

  /// copy constructor
  /// \param[in] a: Point to copy from.
  Pt4(const Pt4& a)
  : x(a.x)
  , y(a.y)
  , z(a.z)
  , w(a.w)
  {
  }

  // constructors for conversions (all explicit)
  /// \brief constructor. (Pt4<T>) Pt2<U>
  /// \param a: Pt2. z and w are set to 0.
  template <class U>
  explicit Pt4(const Pt2<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  , z((T)0)
  , w((T)0)
  {
  }
  /// \brief constructor. (Pt4<T>) Pt3<U>
  /// \param a: Pt3. w is set to 0.
  template <class U>
  explicit Pt4(const Pt3<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  , z((T)a.z)
  , w((T)0)
  {
  }
  /// \brief constructor. (Pt4<T>) Pt4<U>
  /// \param a: Pt4.
  template <class U>
  explicit Pt4(const Pt4<U>& a)
  : x((T)a.x)
  , y((T)a.y)
  , z((T)a.z)
  , w((T)a.w)
  {
  }

  ~Pt4() {} ///< Destructor. can't be virtual

  /// operator= (Assignment operator)
  /// \param[in] a: A constant.
  /// \return Pt4 reference.
  template <class U>
  inline const Pt4& operator=(const U& a)
  {
    x = (T)a;
    y = (T)a;
    z = (T)a;
    w = (T)a;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt2.
  /// \return Pt4 reference.
  template <class U>
  inline const Pt4& operator=(const Pt2<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt3.
  /// \return Pt4 reference.
  template <class U>
  inline const Pt4& operator=(const Pt3<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    z = (T)a.z;
    return *this;
  }
  /// operator= (Assignment operator)
  /// \param[in] a: Pt4.
  /// \return Pt4 reference.
  template <class U>
  inline const Pt4& operator=(const Pt4<U>& a)
  {
    x = (T)a.x;
    y = (T)a.y;
    z = (T)a.z;
    w = (T)a.w;
    return *this;
  }

  // Logical operators

  /// operator==
  /// \param[in] a: A constant.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const U& a) const
  {
    return (x == a && y == a && z == a && w == a);
  }
  /// operator==
  /// \param[in] a: Pt2.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt2<U>& a) const
  {
    return (x == a.x && y == a.y);
  }
  /// operator==
  /// \param[in] a: Pt3.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt3<U>& a) const
  {
    return (x == a.x && y == a.y && z == a.z);
  }
  /// operator==
  /// \param[in] a: Pt4.
  /// \return true if ==.
  template <class U>
  inline bool operator==(const Pt4<U>& a) const
  {
    return (x == a.x && y == a.y && z == a.z && w == a.w);
  }

  /// operator!=
  /// \param[in] a: A constant.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const U& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt2.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt2<U>& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt3.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt3<U>& a) const
  {
    return !(*this == a);
  }
  /// operator!=
  /// \param[in] a: Pt4.
  /// \return true if !=.
  template <class U>
  inline bool operator!=(const Pt4<U>& a) const
  {
    return !(*this == a);
  }

  /// operator<
  /// \param[in] a: A constant.
  /// \return true if <.
  template <class U>
  inline bool operator<(const U& a) const
  {
    if (x < a)
      return 1;
    else if (x > a)
      return 0;
    else
    {
      if (y < a)
        return 1;
      else if (y > a)
        return 0;
      else
      {
        if (z < a)
          return 1;
        else if (z < a)
          return 0;
        else
        {
          if (w < a)
            return 1;
          else
            return 0;
        }
      }
    }
  }
  /// operator<
  /// \param[in] a: Pt2.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt2<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else
        return 0;
    }
  }
  /// operator<
  /// \param[in] a: Pt3.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt3<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else if (y > a.y)
        return 0;
      else
      {
        if (z < a.z)
          return 1;
        else
          return 0;
      }
    }
  }
  /// operator<
  /// \param[in] a: Pt4.
  /// \return true if <.
  template <class U>
  inline bool operator<(const Pt4<U>& a) const
  {
    if (x < a.x)
      return 1;
    else if (x > a.x)
      return 0;
    else
    {
      if (y < a.y)
        return 1;
      else if (y > a.y)
        return 0;
      else
      {
        if (z < a.z)
          return 1;
        else if (z < a.z)
          return 0;
        else
        {
          if (w < a.w)
            return 1;
          else
            return 0;
        }
      }
    }
  }

  /// operator<=
  /// \param[in] a: A constant.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const U& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt2.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt2<U>& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt3.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt3<U>& a) const
  {
    return (*this < a || *this == a);
  }
  /// operator<=
  /// \param[in] a: Pt4.
  /// \return true if <=.
  template <class U>
  inline bool operator<=(const Pt4<U>& a) const
  {
    return (*this < a || *this == a);
  }

  /// operator>
  /// \param[in] a: A constant.
  /// \return true if >.
  template <class U>
  inline bool operator>(const U& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt2.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt2<U>& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt3.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt3<U>& a) const
  {
    return !(*this <= a);
  }
  /// operator>
  /// \param[in] a: Pt4.
  /// \return true if >.
  template <class U>
  inline bool operator>(const Pt4<U>& a) const
  {
    return !(*this <= a);
  }

  /// operator>=
  /// \param[in] a: A constant.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const U& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt2.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt2<U>& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt3.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt3<U>& a) const
  {
    return (*this > a || *this == a);
  }
  /// operator>=
  /// \param[in] a: Pt4.
  /// \return true if >=.
  template <class U>
  inline bool operator>=(const Pt4<U>& a) const
  {
    return (*this > a || *this == a);
  }

  // Arithmetic operators

  /// operator+
  /// \param[in] a: A constant.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator+(const U& a) const // Pt4 + int (etc)
  {
    return Pt4((T)(x + a), (T)(y + a), (T)(z + a), (T)(w + a));
  }
  /// operator+
  /// \param[in] a: Pt2.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator+(const Pt2<U>& a) const // Pt4 + Pt2
  {
    return Pt4((T)(x + a.x), (T)(y + a.y), z, w);
  }
  /// operator+
  /// \param[in] a: Pt3.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator+(const Pt3<U>& a) const // Pt4 + Pt3
  {
    return Pt4((T)(x + a.x), (T)(y + a.y), (T)(z + a.z), w);
  }
  /// operator+
  /// \param[in] a: Pt4.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator+(const Pt4<U>& a) const // Pt4 + Pt4
  {
    return Pt4((T)(x + a.x), (T)(y + a.y), (T)(z + a.z), (T)(w + a.w));
  }

  /// operator-
  /// \param[in] a: A constant.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator-(const U& a) const // Pt4 - int (etc)
  {
    return Pt4((T)(x - a), (T)(y - a), (T)(z - a), (T)(w - a));
  }
  /// operator-
  /// \param[in] a: Pt2.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator-(const Pt2<U>& a) const // Pt4 - Pt2
  {
    return Pt4((T)(x - a.x), (T)(y - a.y), z, w);
  }
  /// operator-
  /// \param[in] a: Pt3.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator-(const Pt3<U>& a) const // Pt4 - Pt3
  {
    return Pt4((T)(x - a.x), (T)(y - a.y), (T)(z - a.z), w);
  }
  /// operator-
  /// \param[in] a: Pt4.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator-(const Pt4<U>& a) const // Pt4 - Pt4
  {
    return Pt4((T)(x - a.x), (T)(y - a.y), (T)(z - a.z), (T)(w - a.w));
  }

  /// unary operator-
  /// \return Pt4.
  inline Pt4 operator-() const // -Pt4
  {
    return Pt4((T)(-x), (T)(-y), (T)(-z), (T)(-w));
  }

  /// operator*
  /// \param[in] a: A constant.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator*(const U& a) const // Pt4 * int (etc)
  {
    return Pt4((T)(x * a), (T)(y * a), (T)(z * a), (T)(w * a));
  }
  /// operator*
  /// \param[in] a: Pt2.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator*(const Pt2<U>& a) const // Pt4 * Pt2
  {
    return Pt4((T)(x * a.x), (T)(y * a.y), z, w);
  }
  /// operator*
  /// \param[in] a: Pt3.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator*(const Pt3<U>& a) const // Pt4 * Pt3
  {
    return Pt4((T)(x * a.x), (T)(y * a.y), (T)(z * a.z), w);
  }
  /// operator*
  /// \param[in] a: Pt4.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator*(const Pt4<U>& a) const // Pt4 * Pt4
  {
    return Pt4((T)(x * a.x), (T)(y * a.y), (T)(z * a.z), (T)(w * a.w));
  }

  /// operator/
  /// \param[in] a: Pt4.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator/(const U& a) const // Pt4 / int (etc)
  {
    return Pt4((T)(x / a), (T)(y / a), (T)(z / a), (T)(w / a));
  }
  /// operator/
  /// \param[in] a: Pt2.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator/(const Pt2<U>& a) const // Pt4 / Pt2
  {
    return Pt4((T)(x / a.x), (T)(y / a.y), z, w);
  }
  /// operator/
  /// \param[in] a: Pt3.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator/(const Pt3<U>& a) const // Pt4 / Pt3
  {
    return Pt4((T)(x / a.x), (T)(y / a.y), (T)(z / a.z), w);
  }
  /// operator/
  /// \param[in] a: Pt4.
  /// \return Pt4.
  template <class U>
  inline Pt4 operator/(const Pt4<U>& a) const // Pt4 / Pt4
  {
    return Pt4((T)(x / a.x), (T)(y / a.y), (T)(z / a.z), (T)(w / a.w));
  }

  /// operator+=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator+=(const U& a) // Pt4 += int (etc)
  {
    x = (T)(x + a);
    y = (T)(y + a);
    z = (T)(z + a);
    w = (T)(w + a);
  }
  /// operator+=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator+=(const Pt2<U>& a) // Pt4 += Pt2
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
  }
  /// operator+=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator+=(const Pt3<U>& a) // Pt4 += Pt3
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
    z = (T)(z + a.z);
  }
  /// operator+=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator+=(const Pt4<U>& a) // Pt4 += Pt4
  {
    x = (T)(x + a.x);
    y = (T)(y + a.y);
    z = (T)(z + a.z);
    w = (T)(w + a.w);
  }

  /// operator-=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator-=(const U& a) // Pt4 -= int (etc)
  {
    x = (T)(x - a);
    y = (T)(y - a);
    z = (T)(z - a);
    w = (T)(w - a);
  }
  /// operator-=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator-=(const Pt2<U>& a) // Pt4 -= Pt2
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
  }
  /// operator-=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator-=(const Pt3<U>& a) // Pt4 -= Pt3
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
    z = (T)(z - a.z);
  }
  /// operator-=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator-=(const Pt4<U>& a) // Pt4 -= Pt4
  {
    x = (T)(x - a.x);
    y = (T)(y - a.y);
    z = (T)(z - a.z);
    w = (T)(w - a.w);
  }

  /// operator*=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator*=(const U& a) // Pt4 *= int (etc)
  {
    x = (T)(x * a);
    y = (T)(y * a);
    z = (T)(z * a);
    w = (T)(w * a);
  }
  /// operator*=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator*=(const Pt2<U>& a) // Pt4 *= Pt2
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
  }
  /// operator*=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator*=(const Pt3<U>& a) // Pt4 *= Pt3
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
    z = (T)(z * a.z);
  }
  /// operator*=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator*=(const Pt4<U>& a) // Pt4 *= Pt4
  {
    x = (T)(x * a.x);
    y = (T)(y * a.y);
    z = (T)(z * a.z);
    w = (T)(w * a.w);
  }

  /// operator/=
  /// \param[in] a: A constant.
  template <class U>
  inline void operator/=(const U& a) // Pt4 /= int (etc)
  {
    x = (T)(x / a);
    y = (T)(y / a);
    z = (T)(z / a);
    w = (T)(w / a);
  }
  /// operator/=
  /// \param[in] a: Pt2.
  template <class U>
  inline void operator/=(const Pt2<U>& a) // Pt4 /= Pt2
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
  }
  /// operator/=
  /// \param[in] a: Pt3.
  template <class U>
  inline void operator/=(const Pt3<U>& a) // Pt4 /= Pt3
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
    z = (T)(z / a.z);
  }
  /// operator/=
  /// \param[in] a: Pt4.
  template <class U>
  inline void operator/=(const Pt4<U>& a) // Pt4 /= Pt4
  {
    x = (T)(x / a.x);
    y = (T)(y / a.y);
    z = (T)(z / a.z);
    w = (T)(w / a.w);
  }

  // Other stuff

  /// Setter
  /// \param a_x: x.
  /// \param a_y: y.
  /// \param a_z: z.
  /// \param a_w: w.
  void Set(T a_x, T a_y, T a_z, T a_w)
  {
    x = a_x;
    y = a_y;
    z = a_z;
    w = a_w;
  }
  /// Setter
  /// \param a: Value to use for x, y and z.
  void Set(T a)
  {
    x = a;
    y = a;
    z = a;
    w = a;
  }

  /// operator[]
  /// \param a: index: 0 = x, 1 = y, 2 = z, 3 = w
  /// \return Value.
  T operator[](unsigned int a) const { return *(&x + a); }
  /// operator[]
  /// \param a: index: 0 = x, 1 = y, 2 = z, 3 = w
  /// \return Value.
  T& operator[](unsigned int a) { return *(&x + a); }

  /// at
  /// \param a: index: 0 = x, 1 = y, 2 = z, 3 = w
  /// \return Value.
  const T& at(unsigned int a) const
  {
    switch (a)
    {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::out_of_range("Pt4<T>::at(): error out of range");
    }
  }
  /// ----- OVERLOAD -----
  /// \param a: index: 0 = x, 1 = y, 2 = z, w = 3
  /// \return Value.
  T& at(unsigned int a) // non-const version
  {
    // Use the const version. See Effective C++ 3rd Edition Item 3.
    return const_cast<T&>(static_cast<const Pt4<T>&>(*this).at(a));
  }

  /// \brief For serialization
  /// \param archive: The archive.
  /// \param version: The version.
  template <typename Archive>
  void serialize(Archive& archive, const unsigned int version)
  {
    (void)version; // For doxygen which couldn't handle commenting it out.
    archive& x;
    archive& y;
    archive& z;
    archive& w;
  }

}; // Pt4

//------------------------------------------------------------------------------
/// \brief Convert from one Pt3 to another.
/// \param a_from: Converting from this.
/// \param a_to: Converting to this.
/// \return Point
//------------------------------------------------------------------------------
template <class _From, class _To>
_To& Pt3Convert(const _From& a_from, _To& a_to)
{
  a_to.x = static_cast<const typename _To::value_type>(a_from.x);
  a_to.y = static_cast<const typename _To::value_type>(a_from.y);
  a_to.z = static_cast<const typename _To::value_type>(a_from.z);
  return a_to;
}; // PtConvert

////////////////////////////////////////////////////////////////////////////////
// Stream I/O
////////////////////////////////////////////////////////////////////////////////

//
// This code ported by GMS from "The Standard C++ Library" by Nicolai M.
// Josuttis
//

//------------------------------------------------------------------------------
// Pt2<T>

//------------------------------------------------------------------------------
/// \brief operator<<
/// \param strm: the stream.
/// \param a_pt: The point
/// \return stream
//------------------------------------------------------------------------------
template <typename T, typename charT, typename traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& strm,
                                                     const Pt2<T>& a_pt)
{
  // string stream
  // - with same format
  // - without special field width
  std::basic_ostringstream<charT, traits> s;
  s.copyfmt(strm);
  s.width(0);

  // fill string stream
  s << a_pt.x << "," << a_pt.y;

  // print string stream
  strm << s.str();

  return strm;
} // operator<< for Pt2<T>
//------------------------------------------------------------------------------
/// \brief operator>>
/// \param strm: the stream.
/// \param a_pt: The point
/// \return stream
//------------------------------------------------------------------------------
template <typename T, typename charT, typename traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& strm,
                                                     Pt2<T>& a_pt)
{
  T x, y;

  // read x
  strm >> x;

  // if available
  // - read ',' and y value
  if (strm.peek() == ',')
  {
    strm.ignore();
    strm >> y;
  }
  else
  {
    y = static_cast<T>(0);
  }

  if (strm)
  {
    a_pt = Pt2<T>(x, y);
  }

  return strm;
} // operator>> for Pt2<T>

//------------------------------------------------------------------------------
// Pt3<T>

//------------------------------------------------------------------------------
/// \brief operator<<
/// \param strm: the stream.
/// \param a_pt: The point
/// \return stream
//------------------------------------------------------------------------------
template <typename T, typename charT, typename traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& strm,
                                                     const Pt3<T>& a_pt)
{
  // string stream
  // - with same format
  // - without special field width
  std::basic_ostringstream<charT, traits> s;
  s.copyfmt(strm);
  s.width(0);

  // fill string stream
  s << a_pt.x << "," << a_pt.y << "," << a_pt.z;

  // print string stream
  strm << s.str();

  return strm;
} // operator<< for Pt3<T>
//------------------------------------------------------------------------------
/// \brief operator>>
/// \param strm: the stream.
/// \param a_pt: The point
/// \return stream
//------------------------------------------------------------------------------
template <typename T, typename charT, typename traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& strm,
                                                     Pt3<T>& a_pt)
{
  T x, y, z;

  // read x
  strm >> x;

  // if available
  // - read ',' and y and z values
  if (strm.peek() == ',')
  {
    strm.ignore();
    strm >> y;
    if (strm.peek() == ',')
    {
      strm.ignore();
      strm >> z;
    }
    else
    {
      z = static_cast<T>(0);
    }
  }
  else
  {
    y = static_cast<T>(0);
    z = static_cast<T>(0);
  }

  if (strm)
  {
    a_pt = Pt3<T>(x, y, z);
  }

  return strm;
} // operator>> for Pt3<T>

//------------------------------------------------------------------------------
// Pt4<T>

//------------------------------------------------------------------------------
/// \brief operator<<
/// \param strm: the stream.
/// \param a_pt: The point
/// \return stream
//------------------------------------------------------------------------------
template <typename T, typename charT, typename traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& strm,
                                                     const Pt4<T>& a_pt)
{
  // string stream
  // - with same format
  // - without special field width
  std::basic_ostringstream<charT, traits> s;
  s.copyfmt(strm);
  s.width(0);

  // fill string stream
  s << a_pt.x << "," << a_pt.y << "," << a_pt.z << "," << a_pt.w;

  // print string stream
  strm << s.str();

  return strm;
} // operator<< for Pt4<T>
//------------------------------------------------------------------------------
/// \brief operator>>
/// \param strm: the stream.
/// \param a_pt: The point
/// \return stream
//------------------------------------------------------------------------------
template <typename T, typename charT, typename traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& strm,
                                                     Pt4<T>& a_pt)
{
  T x, y, z, w;

  // read x
  strm >> x;

  // if available
  // - read ',' and y and z values
  if (strm.peek() == ',')
  {
    strm.ignore();
    strm >> y;
    if (strm.peek() == ',')
    {
      strm.ignore();
      strm >> z;
      if (strm.peek() == ',')
      {
        strm.ignore();
        strm >> w;
      }
      else
      {
        w = static_cast<T>(0);
      }
    }
    else
    {
      z = static_cast<T>(0);
      w = static_cast<T>(0);
    }
  }
  else
  {
    y = static_cast<T>(0);
    z = static_cast<T>(0);
    w = static_cast<T>(0);
  }

  if (strm)
  {
    a_pt = Pt4<T>(x, y, z, w);
  }

  return strm;
} // operator>> for Pt4<T>

} // namespace xms
