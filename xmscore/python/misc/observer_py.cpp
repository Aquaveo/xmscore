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
#include <xmscore/xmlocale/xmlocale.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initObserver(py::module &m) {
  py::class_<xms::PublicObserver, PyObserver, boost::shared_ptr<xms::PublicObserver>> observer(m, N_("Observer"));

  // Initializer
  observer.def(py::init());

  // ---------------------------------------------------------------------------
  // function: progress_status
  // ---------------------------------------------------------------------------
  observer.def(N_("progress_status"), &xms::PublicObserver::ProgressStatus, 
               py::arg(N_("percent_complete")));

  // ---------------------------------------------------------------------------
  // function: begin_operation_string
  // ---------------------------------------------------------------------------
  observer.def(N_("begin_operation_string"), &xms::PublicObserver::BeginOperationString,
               py::arg(N_("operation")));

  // ---------------------------------------------------------------------------
  // function: end_operation
  // ---------------------------------------------------------------------------
  observer.def(N_("end_operation"), &xms::PublicObserver::EndOperation);

  // ---------------------------------------------------------------------------
  // function: update_message
  // ---------------------------------------------------------------------------
  observer.def(N_("update_message"), &xms::PublicObserver::UpdateMessage,
               py::arg(N_("message")));

  // ---------------------------------------------------------------------------
  // function: on_progress_status
  // ---------------------------------------------------------------------------
  observer.def(N_("on_progress_status"), &xms::PublicObserver::on_progress_status,
               py::arg(N_("percent_complete")));

  // ---------------------------------------------------------------------------
  // function: on_begin_operation_string
  // ---------------------------------------------------------------------------
  observer.def(N_("on_begin_operation_string"), &xms::PublicObserver::on_begin_operation_string,
               py::arg(N_("operation")));

  // ---------------------------------------------------------------------------
  // function: on_end_operation
  // ---------------------------------------------------------------------------
  observer.def(N_("on_end_operation"), &xms::PublicObserver::on_end_operation);

  // ---------------------------------------------------------------------------
  // function: on_update_message
  // ---------------------------------------------------------------------------
  observer.def(N_("on_update_message"), &xms::PublicObserver::on_update_message,
               py::arg(N_("message")));

  // ---------------------------------------------------------------------------
  // function: time_remaining_in_seconds
  // ---------------------------------------------------------------------------
  observer.def(N_("time_remaining_in_seconds"), &xms::PublicObserver::time_remaining_in_seconds,
               py::arg(N_("seconds_remaining")));

  // ---------------------------------------------------------------------------
  // function: time_elapsed_in_seconds
  // ---------------------------------------------------------------------------
  observer.def(N_("time_elapsed_in_seconds"), &xms::PublicObserver::time_elapsed_in_seconds,
               py::arg(N_("elapsed_seconds")));
}