#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <boost/shared_ptr.hpp>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
////////////////////////////////////////////////////////////////////////////////
/// \class Singleton
/// \brief Base class for classes that follow the singleton pattern.
template <typename T>
class Singleton
{
public:
  //----------------------------------------------------------------------------
  /// \brief Get the instance of the singleton.
  /// \param a_delete If true delete the instance and recreate next time.
  ///          RETURNS AN INVALID INSTANCE.
  /// \param a_new A new pointer to use as the instance when called the first
  ///          time or just after the instance has been deleted.
  /// \return A reference to the instance.
  //----------------------------------------------------------------------------
  static T& Instance(bool a_delete = false, T* a_new = NULL)
  {
    static boost::shared_ptr<T> theSingleInstance;

    if (a_delete)
    {
      if (theSingleInstance)
      {
        theSingleInstance.reset();
      }
    }
    else
    {
      if (NULL == theSingleInstance)
      {
        theSingleInstance.reset(a_new ? a_new : new T);
      }
    }
    if (theSingleInstance)
    {
      return *theSingleInstance;
    }
    else
    {
      return *theSingleInstance.get();
    }
  } // Instance

  //----------------------------------------------------------------------------
  /// \brief Delete the singleton instance.
  //----------------------------------------------------------------------------
  static void Delete() { Instance(true, boost::shared_ptr<T>()); }
}; // class Singleton
////////////////////////////////////////////////////////////////////////////////
/// \class SharedSingleton
/// \brief Singleton which can share the same instance with other singletons.
///
/// This allows a derived instance to be accessed as either the derived type or
/// or as the base type.  A utility may need to access the instance only as a
/// base type, not knowing anything about the derived type, while the calling
/// code may need to access functionality in the derived type.  Create this
/// for the base type and for 1 or more derived types, initializing each to the
/// same instance shared pointer of the most derived type.  Then access that
/// instance through any singleton that has the appropriate type.
template <typename T>
class SharedSingleton
{
public:
  typedef boost::shared_ptr<T> Ptr; ///< Instance pointer

  //----------------------------------------------------------------------------
  /// \brief Get a singleton instance
  /// \param a_new A new pointer to use as the instance when called the first
  ///          time or just after the instance has been deleted.
  /// \param a_delete If true delete the current instance and RETURN AN INVALID
  ///          INSTANCE.
  /// \return A boost::shared_ptr with the instance.
  static Ptr Instance(Ptr a_new = Ptr(), bool a_delete = false)
  {
    static boost::shared_ptr<T> theSingleInstance;

    if (a_delete)
    {
      if (theSingleInstance)
      {
        theSingleInstance.reset();
      }
    }
    else
    {
      // assert((NULL == theSingleInstance) ^ (NULL == a_new)); // init iff not
      // Above commented because need to return whether initialized or not
      if (NULL == theSingleInstance) // init because not
      {
        theSingleInstance = a_new;
      }
    }
    return theSingleInstance;
  } // Instance

  //----------------------------------------------------------------------------
  /// \brief Delete the current instance
  //----------------------------------------------------------------------------
  static void Delete() { Instance(Ptr(), true); }
}; // class SharedSingleton

} // namespace xms
