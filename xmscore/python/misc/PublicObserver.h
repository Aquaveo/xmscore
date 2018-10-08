#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief an Observer class with public virtual methods.
///
///        This is necessary for the Python bindings. Python isn't able to
///        override methods that aren't public.
/// \ingroup
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <xmscore/misc/Observer.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------
namespace xms
{

class PublicObserver : public xms::Observer
{
public:
  /* Inherit the constructors */
  using xms::Observer::Observer;

  /* Virtual methods called by overrides of Observer virtual methods */
  virtual void on_progress_status(double a_percentComplete) {}
  virtual void on_begin_operation_string(const std::string& a_operation) {}
  virtual void on_end_operation() {}
  virtual void on_update_message(const std::string& a_message) {}
  virtual void time_remaining_in_seconds(double a_remainingSeconds) {}
  virtual void time_elapsed_in_seconds(double a_elapsedSeconds) {}

private:
  void OnProgressStatus(double a_percentComplete) override {
    on_progress_status(a_percentComplete);
  }
  void OnBeginOperationString(const std::string& a_operation) override {
    on_begin_operation_string(a_operation);
  }
  void OnEndOperation() override {
    on_end_operation();
  }
  void OnUpdateMessage(const std::string& a_message) override {
    on_update_message(a_message);
  }
  void TimeRemainingInSeconds(double a_remainingSeconds) override {
    time_remaining_in_seconds(a_remainingSeconds);
  }
  void TimeElapsedInSeconds(double a_elapsedSeconds) override {
    time_elapsed_in_seconds(a_elapsedSeconds);
  }
};

} // namespace xms