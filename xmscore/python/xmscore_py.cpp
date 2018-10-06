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
std::string version() {
#ifdef XMS_VERSION
    return XMS_VERSION;
#else
    return "99.99.99";
#endif
}

//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(xmscore_py, m) {
    m.doc() = "Python bindings for the xmscore library"; // optional module docstring
    m.def("version", &version,
          "Get current version of xmscore Python bindings.");
    m.def("__version__", &version,
          "Get current version of xmscore Python bindings.");



    const char* misc_doc = R"pydoc(
        The misc module of the xmscore python library contains classes and
        functions that are shared between all of the xms family of libraries.
        These functions and classes can be used in any of the library to ensure
        that functionality is standardized.
    )pydoc";
    py::module modMisc = m.def_submodule("misc", misc_doc);
    initMisc(modMisc);
}