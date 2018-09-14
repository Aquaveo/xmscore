//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <boost/shared_ptr.hpp>
#include <xmscore/python/misc/misc_py.h>
#include <xmscore/python/misc/PublicObserver.h>
#include <xmscore/python/misc/PyObserver.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initObserver(py::module &m) {
  py::options options;

  // Observer Class
	py::class_<xms::PublicObserver, PyObserver, 
      boost::shared_ptr<xms::PublicObserver>> observer(m, "Observer");

	// Initializer
  observer.def(py::init());

  // ---------------------------------------------------------------------------
  // function: progress_status
  // ---------------------------------------------------------------------------
  const char* progress_status_doc = R"pydoc(
      Method to publish the progress status

      Args:
          percent_complete (float): Method to publish the progress status

      Returns:
          bool: Was the progress bar updated
  )pydoc";
  observer.def("progress_status", &xms::PublicObserver::ProgressStatus, 
               progress_status_doc, py::arg("percent_complete"));

  // ---------------------------------------------------------------------------
  // function: begin_operation_string
  // ---------------------------------------------------------------------------
  const char* begin_operation_string_doc = R"pydoc(
      Publishes the name of the operation and starts the timing of 
      the operation.

      Args:
          operation (str): String identifying the name of the operation 
              that is being observed by this class.
  )pydoc";
  observer.def("begin_operation_string", 
               &xms::PublicObserver::BeginOperationString, 
               begin_operation_string_doc, py::arg("operation"));

  // ---------------------------------------------------------------------------
  // function: end_operation
  // ---------------------------------------------------------------------------
  const char* end_operation_doc = R"pydoc(
      Ends the operation.
  )pydoc";
  observer.def("end_operation", &xms::PublicObserver::EndOperation, 
               end_operation_doc);

  // ---------------------------------------------------------------------------
  // function: update_message
  // ---------------------------------------------------------------------------
  const char* update_message_doc = R"pydoc(
      Updates the message but not the percent complete.

      Args:
          message (str): The new message.
  )pydoc";    
  observer.def("update_message", &xms::PublicObserver::UpdateMessage,
               update_message_doc, py::arg("message"));

  // ---------------------------------------------------------------------------
  // function: on_progress_status
  // ---------------------------------------------------------------------------
  const char* on_progress_status_doc = R"pydoc(
      Captures the progress of an operation.

      Args:
          percent_complete (float): The percent complete.
  )pydoc";
  observer.def("on_progress_status", &xms::PublicObserver::on_progress_status,
               on_progress_status_doc, py::arg("percent_complete"));

  // ---------------------------------------------------------------------------
  // function: on_begin_operation_string
  // ---------------------------------------------------------------------------
  const char* on_begin_operation_string_doc = R"pydoc(
      ???

      Args:
          operation (str): Name of the operation being monitored.
  )pydoc";
  observer.def("on_begin_operation_string", 
               &xms::PublicObserver::on_begin_operation_string,
               on_begin_operation_string_doc, py::arg("operation"));

  // ---------------------------------------------------------------------------
  // function: on_end_operation
  // ---------------------------------------------------------------------------
  const char* on_end_operation_doc = R"pydoc(
      Virtual function for derived class to get end operation event.
  )pydoc";
  observer.def("on_end_operation", &xms::PublicObserver::on_end_operation,
               on_end_operation_doc);

  // ---------------------------------------------------------------------------
  // function: on_update_message
  // ---------------------------------------------------------------------------
  const char* on_update_message_doc = R"pydoc(
      Virtual function to be notified that the message has been set.

      Args:
          message (str): The new message.
  )pydoc";   
  observer.def("on_update_message", &xms::PublicObserver::on_update_message,
    on_update_message_doc, py::arg("message"));

  // ---------------------------------------------------------------------------
  // function: time_remaining_in_seconds
  // ---------------------------------------------------------------------------
  const char* time_remaining_in_seconds_doc = R"pydoc(
      Sets the time remaining in seconds.

      Args:
          seconds_remaining (float): The time remaining for the current 
              operation that the class is observing.
  )pydoc";  
  observer.def("time_remaining_in_seconds", 
               &xms::PublicObserver::time_remaining_in_seconds,
               time_remaining_in_seconds_doc, py::arg("seconds_remaining"));

  // ---------------------------------------------------------------------------
  // function: time_elapsed_in_seconds
  // ---------------------------------------------------------------------------
  const char* time_elapsed_in_seconds_doc = R"pydoc(
      Sets the time elapsed since the operation began.

      Args:
          elapsed_seconds (float): The elapsed time since the operation began.
  )pydoc"; 
  observer.def("time_elapsed_in_seconds", 
               &xms::PublicObserver::time_elapsed_in_seconds,
               time_elapsed_in_seconds_doc, py::arg("elapsed_seconds"));

}