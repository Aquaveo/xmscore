//------------------------------------------------------------------------------
/// \file
/// \brief root module for xmscore Python bindings.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <xmscore/python/misc/misc_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
//PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

std::string version() {
    return "1.0.0";
}


//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(xmscore_py, m) {
    m.doc() = "Python bindings for xmscore"; // optional module docstring
    m.def("version", &version,
          "Get current version of xmscore Python bindings.");

    py::module modMisc = m.def_submodule("misc");
    initMisc(modMisc);
}