#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief "trampoline" class for inheritance in Python bindings.
///
///        See: https://pybind11.readthedocs.io/en/stable/advanced/classes.html#overriding-virtual-functions-in-python
/// \ingroup
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------
// 1.
#include <xmscore/python/misc/PublicObserver.h>

// 2.

// 3. Standard Library Headers

// 4. External Library Headers
#include <pybind11/pybind11.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------
class PyObserver: public xms::PublicObserver
{
public:
 /* Inherit the constructors */
  using xms::PublicObserver::PublicObserver;

  void on_progress_status(double a_percentComplete) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicObserver,
      on_progress_status,
      a_percentComplete
    );
  }

  void on_begin_operation_string(const std::string& a_operation) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicObserver,
      on_begin_operation_string,
      a_operation
    );
  }

  void on_end_operation() override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicObserver,
      on_end_operation
    );
  }

  void on_update_message(const std::string& a_message) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicObserver,
      on_update_message,
      a_message
    );
  }

  void time_remaining_in_seconds(double a_remainingSeconds) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicObserver,
      time_remaining_in_seconds,
      a_remainingSeconds
    );
  }

  void time_elapsed_in_seconds(double a_elapsedSeconds) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicObserver,
      time_elapsed_in_seconds,
      a_elapsedSeconds
    );
  }
};