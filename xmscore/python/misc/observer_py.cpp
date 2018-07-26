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
		.def("progress_status", &xms::PublicObserver::ProgressStatus, 
			"Method to publish the progress status",
			py::arg("percent_complete")
		)
		.def("begin_operation_string", &xms::PublicObserver::BeginOperationString,
			"Publishes the name of the operation and starts the timing of the operation.", 
			py::arg("operation")
		)
		.def("end_operation", &xms::PublicObserver::EndOperation, "Ends the operation.")
		.def("update_message", &xms::PublicObserver::UpdateMessage, 
			"Updates the message but not the percent complete.",py::arg("message")
		)
		.def("on_progress_status", &xms::PublicObserver::on_progress_status,
			"captures the progress of an operation", py::arg("percent_complete")
		)
        .def("on_begin_operation_string", &xms::PublicObserver::on_begin_operation_string,
			"captures the progress of an operation", py::arg("operation")
		)
        .def("on_end_operation", &xms::PublicObserver::on_end_operation,
			"Virtual function for derived class to get end operation event."
		)
        .def("on_update_message", &xms::PublicObserver::on_update_message,
			"virtual function to be notified that the message has been set",py::arg("message")
		)
        .def("time_remaining_in_seconds", &xms::PublicObserver::time_remaining_in_seconds,
			"Sets the time remaining in seconds",py::arg("seconds_remaining")
		)
        .def("time_elapsed_in_seconds", &xms::PublicObserver::time_elapsed_in_seconds,
			"Sets the time elapsed since the operation began",py::arg("elapsed_seconds")
		)
        ;
}