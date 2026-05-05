#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Observer base class used to receive progress notifications.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <string>

#include <xmscore/misc/boost_defines.h>

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Structs / Classes ------------------------------------------------------
namespace xms
{
class ObserverT;
////////////////////////////////////////////////////////////////////////////////
/// \class Observer
/// \brief Class used with the observer pattern.
class Observer
{
  friend ObserverT; ///< testing class
public:
  Observer();
  virtual ~Observer();

  /// \brief Publish a percent-complete update.
  /// \param a_percentComplete Current progress in [0.0, 1.0].
  /// \return true if the underlying observer was actually notified — i.e.
  ///         the value advanced more than ~0.02 since the last call —
  ///         false when the call was throttled. Note: a false return is
  ///         **not** a cancel/stop signal; callers must not abort on it.
  bool ProgressStatus(double a_percentComplete);
  /// \brief Notify the listener that a new named operation is starting.
  void BeginOperationString(const std::string& a_operation);
  /// \brief Notify the listener that the current operation has finished.
  void EndOperation();
  /// \brief Forward a status message to the listener.
  void UpdateMessage(const std::string& a_message);

private:
  /// \brief Receive the percent-complete value (0.0..1.0). Override in subclasses.
  virtual void OnProgressStatus(double a_percentComplete) = 0;
  /// \brief Override to react to the start of a named operation.
  virtual void OnBeginOperationString(const std::string& a_operation);
  /// \brief Override to react to the end of the current operation.
  virtual void OnEndOperation();
  /// \brief Override to react to a status message from the current operation.
  virtual void OnUpdateMessage(const std::string& a_message);
  /// \brief Override to receive the estimated remaining seconds for the operation.
  virtual void TimeRemainingInSeconds(double a_remainingSeconds);
  /// \brief Override to receive the elapsed seconds since the operation began.
  virtual void TimeElapsedInSeconds(double a_elapsedSeconds);

  class impl;
  BSHP<impl> m_p; ///< implementation class
};                // class Observer

} // namespace xms

//----- Function prototypes ----------------------------------------------------
