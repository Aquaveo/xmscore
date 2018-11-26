//------------------------------------------------------------------------------
/// \file
/// \brief root module for xmscore Python bindings.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <sstream>

#include <pybind11/pybind11.h>
#include <xmscore/python/misc/misc_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
#ifndef XMS_VERSION
  #define XMS_VERSION "99.99.99";
#endif

//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(xmscore, m) {
    m.doc() = "Python bindings for the xmscore library"; // optional module docstring
    m.attr("__version__") = XMS_VERSION;

    const char* misc_doc = R"pydoc(
        The misc module of the xmscore python library contains classes and
        functions that are shared between all of the xms family of libraries.
        These functions and classes can be used in any of the library to ensure
        that functionality is standardized.
    )pydoc";
    py::module modMisc = m.def_submodule("misc", misc_doc);
    initMisc(modMisc);
}