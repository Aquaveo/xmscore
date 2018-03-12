#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

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

  bool ProgressStatus(double a_percentComplete);
  void BeginOperationString(const std::string& a_operation);
  void EndOperation();
  void UpdateMessage(const std::string& a_message);

private:
  /// virtual function to receive the progress status
  /// \param[in] a_percentComplete: Percent complete between 0.0 and 1.0.
  virtual void OnProgressStatus(double a_percentComplete) = 0;
  virtual void OnBeginOperationString(const std::string& a_operation);
  virtual void OnEndOperation();
  virtual void OnUpdateMessage(const std::string& a_message);
  virtual void TimeRemainingInSeconds(double a_remainingSeconds);
  virtual void TimeElapsedInSeconds(double a_elapsedSeconds);

  class impl;
  BSHP<impl> m_p; ///< implementation class
};                // class Observer

} // namespace xms

//----- Function prototypes ----------------------------------------------------
