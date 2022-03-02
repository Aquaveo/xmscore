//------------------------------------------------------------------------------
/// \file
/// \brief root module for xmscore Python bindings.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <sstream>

#include <pybind11/pybind11.h>

#include <xmscore/locale/locale.h>
#include <xmscore/python/misc/misc_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
#ifndef XMS_VERSION
  #define XMS_VERSION N_("99.99.99");
#endif

//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(_xmscore, m) {
    m.doc() = N_("Python bindings for the xmscore library"); // optional module docstring
    m.attr(N_("__version__")) = XMS_VERSION;

    py::module modMisc = m.def_submodule(N_("misc"));
    initMisc(modMisc);
}