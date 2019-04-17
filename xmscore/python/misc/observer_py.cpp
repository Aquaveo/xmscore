//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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
  py::class_<xms::PublicObserver, PyObserver, boost::shared_ptr<xms::PublicObserver>> observer(m, "Observer");

  // Initializer
  observer.def(py::init());

  // ---------------------------------------------------------------------------
  // function: progress_status
  // ---------------------------------------------------------------------------
  observer.def("progress_status", &xms::PublicObserver::ProgressStatus, 
               py::arg("percent_complete"));

  // ---------------------------------------------------------------------------
  // function: begin_operation_string
  // ---------------------------------------------------------------------------
  observer.def("begin_operation_string", &xms::PublicObserver::BeginOperationString,
               py::arg("operation"));

  // ---------------------------------------------------------------------------
  // function: end_operation
  // ---------------------------------------------------------------------------
  observer.def("end_operation", &xms::PublicObserver::EndOperation);

  // ---------------------------------------------------------------------------
  // function: update_message
  // ---------------------------------------------------------------------------
  observer.def("update_message", &xms::PublicObserver::UpdateMessage,
               py::arg("message"));

  // ---------------------------------------------------------------------------
  // function: on_progress_status
  // ---------------------------------------------------------------------------
  observer.def("on_progress_status", &xms::PublicObserver::on_progress_status,
               py::arg("percent_complete"));

  // ---------------------------------------------------------------------------
  // function: on_begin_operation_string
  // ---------------------------------------------------------------------------
  observer.def("on_begin_operation_string", &xms::PublicObserver::on_begin_operation_string,
               py::arg("operation"));

  // ---------------------------------------------------------------------------
  // function: on_end_operation
  // ---------------------------------------------------------------------------
  observer.def("on_end_operation", &xms::PublicObserver::on_end_operation);

  // ---------------------------------------------------------------------------
  // function: on_update_message
  // ---------------------------------------------------------------------------
  observer.def("on_update_message", &xms::PublicObserver::on_update_message,
               py::arg("message"));

  // ---------------------------------------------------------------------------
  // function: time_remaining_in_seconds
  // ---------------------------------------------------------------------------
  observer.def("time_remaining_in_seconds", &xms::PublicObserver::time_remaining_in_seconds,
               py::arg("seconds_remaining"));

  // ---------------------------------------------------------------------------
  // function: time_elapsed_in_seconds
  // ---------------------------------------------------------------------------
  observer.def("time_elapsed_in_seconds", &xms::PublicObserver::time_elapsed_in_seconds,
               py::arg("elapsed_seconds"));
}