#pragma once
//------------------------------------------------------------------------------
/// \file PyUtils.h
/// \brief Contains helper functions as well as several utility functions for pybind
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers

// 4. External library headers
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <boost/shared_ptr.hpp>
#include <xmscore/points/ptsfwd.h>
#include <xmscore/stl/vector.h>

// 5. Shared code headers

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

/// XMS Namespace
namespace xms
{

// Pt3d
Pt3d Pt3dFromPyIter(const py::iterable& pt);
py::iterable PyIterFromPt3d(const Pt3d& pt);

// VecPt3d
boost::shared_ptr<VecPt3d> VecPt3dFromPyIter(const py::iterable& pts);
py::iterable PyIterFromVecPt3d(const VecPt3d& pts);

// VecPt3d2d
boost::shared_ptr<VecPt3d2d> VecPt3d2dFromPyIter(const py::iterable& pts);
boost::shared_ptr<py::iterable> PyIterFromVecPt3d2d(const VecPt3d2d& pts);

// VecInt
boost::shared_ptr<VecInt> VecIntFromPyIter(const py::iterable& ints);
boost::shared_ptr<py::iterable> PyIterFromVecInt(const VecInt& ints);

// VecDouble
boost::shared_ptr<VecDouble> VecDoubleFromPyIter(const py::iterable& dbls);
boost::shared_ptr<py::iterable> PyIterFromVecDouble(const VecDouble& dbls);

// VecFloat
boost::shared_ptr<VecFloat> VecFloatFromPyIter(const py::iterable& flts);
boost::shared_ptr<py::iterable> PyIterFromVecFloat(const VecFloat& flts);

// VecBool
boost::shared_ptr<VecBool> VecBoolFromPyIter(const py::iterable& bools);
boost::shared_ptr<py::iterable> PyIterFromVecBool(const VecBool& bools);

// DynamicBitset
boost::shared_ptr<DynBitset> DynamicBitsetFromPyIter(const py::iterable& bitset);
boost::shared_ptr<py::iterable> PyIterFromDynamicBitset(const DynBitset& bitset);
    
}