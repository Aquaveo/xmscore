#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief initializer functions for members of interpolate python module.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Function declarations --------------------------------------------------
void initMisc(py::module &);

void initObserver(py::module &);
void initProgressListener(py::module &);
