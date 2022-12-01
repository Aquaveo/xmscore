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
#include <xmscore/python/misc/PublicProgressListener.h>

// 2.

// 3. Standard Library Headers

// 4. External Library Headers
#include <pybind11/pybind11.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------
class PyProgressListener: public xms::PublicProgressListener
{
public:
 /* Inherit the constructors */
  using xms::PublicProgressListener::PublicProgressListener;

  void on_progress_status(int a_stack_index, double a_percentComplete) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicProgressListener,
      on_progress_status,
      a_stack_index,
      a_percentComplete
    );
  }

  int on_begin_operation_string(const std::string& a_operation) override {
    PYBIND11_OVERLOAD(
      int,
      xms::PublicProgressListener,
      on_begin_operation_string,
      a_operation
    );
  }

  void on_end_operation(int a_stack_index) override {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicProgressListener,
      on_end_operation,
      a_stack_index
    );
  }

  void on_update_message(int a_stack_index, const std::string& a_message) override
  {
    PYBIND11_OVERLOAD(
      void,
      xms::PublicProgressListener,
      on_update_message,
      a_stack_index,
      a_message
    );
  }
};