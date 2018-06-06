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
    py::class_<xms::PublicObserver, PyObserver, boost::shared_ptr<xms::PublicObserver>>(m, "Observer")
        .def(py::init())
        .def("progress_status", &xms::PublicObserver::ProgressStatus)
        .def("begin_operation_string", &xms::PublicObserver::BeginOperationString)
        .def("end_operation", &xms::PublicObserver::EndOperation)
        .def("update_message", &xms::PublicObserver::UpdateMessage)
        .def("on_progress_status", &xms::PublicObserver::on_progress_status)
        .def("on_begin_operation_string", &xms::PublicObserver::on_begin_operation_string)
        .def("on_end_operation", &xms::PublicObserver::on_end_operation)
        .def("on_update_message", &xms::PublicObserver::on_update_message)
        .def("time_remaining_in_seconds", &xms::PublicObserver::time_remaining_in_seconds)
        .def("time_elapsed_in_seconds", &xms::PublicObserver::time_elapsed_in_seconds)
        ;
}