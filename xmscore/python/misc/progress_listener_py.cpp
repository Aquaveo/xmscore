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
#include <xmscore/python/misc/PublicProgressListener.h>
#include <xmscore/python/misc/PyProgressListener.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initProgressListener(py::module &m) {
  py::class_<xms::PublicProgressListener, PyProgressListener,
             boost::shared_ptr<xms::PublicProgressListener>> listener(m, "ProgressListener");

  // Initializer
  listener.def(py::init());

  // ---------------------------------------------------------------------------
  // function: on_progress_status
  // ---------------------------------------------------------------------------
  listener.def("on_progress_status", &xms::PublicProgressListener::on_progress_status,
               py::arg("stack_index"), py::arg("percent_complete"));

  // ---------------------------------------------------------------------------
  // function: on_begin_operation_string
  // ---------------------------------------------------------------------------
  listener.def("on_begin_operation_string", &xms::PublicProgressListener::on_begin_operation_string,
               py::arg("operation"));

  // ---------------------------------------------------------------------------
  // function: on_end_operation
  // ---------------------------------------------------------------------------
  listener.def("on_end_operation", &xms::PublicProgressListener::on_end_operation,
               py::arg("stack_index"));

  // ---------------------------------------------------------------------------
  // function: on_update_message
  // ---------------------------------------------------------------------------
  listener.def("on_update_message", &xms::PublicProgressListener::on_update_message,
               py::arg("stack_index"), py::arg("message"));
}