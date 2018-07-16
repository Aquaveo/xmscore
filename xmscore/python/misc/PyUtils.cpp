//------------------------------------------------------------------------------
/// \file XmUGridUtils.cpp
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/python/misc/PyUtils.h>


/// XMS Namespace
namespace xms
{

//------------------------------------------------------------------------------
/// \brief Create Pt3d from py::iterable
/// \param[in] pt: py::iterable object that represents a Pt3d
/// \return a boost::shared_ptr to a Pt3d
//------------------------------------------------------------------------------
Pt3d Pt3dFromPyIter(const py::iterable& pt)
{
  if(py::len(pt) != 3) {
    throw py::type_error("Input point should be a 3-tuple");
  } else {
    return point(pt[0].cast<double>(), pt[1].cast<double>(), pt[2].cast<double>());
  }
}
//------------------------------------------------------------------------------
/// \brief Create py::iterable from Pt3d
/// \param[in] pt: Pt3d object that represents a py::iterable
/// \return a boost::shared_ptr to a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromPt3d(const Pt3d& pt)
{      
  return py::make_tuple(pt.x, pt.y, pt.z);
}

// VecPt3d
boost::shared_ptr<VecPt3d> VecPt3dFromPyIter(const py::iterable& pts)
{      

}
boost::shared_ptr<py::iterable> PyIterFromVecPt3d(const VecPt3d& pts)
{      

}

// VecPt3d2d
boost::shared_ptr<VecPt3d2d> VecPt3d2dFromPyIter(const py::iterable& pts)
{      

}
boost::shared_ptr<py::iterable> PyIterFromVecPt3d2d(const VecPt3d2d& pts)
{      

}

// VecInt
boost::shared_ptr<VecInt> VecIntFromPyIter(const py::iterable& ints)
{      

}
boost::shared_ptr<py::iterable> PyIterFromVecInt(const VecInt& ints)
{

}

// VecDouble
boost::shared_ptr<VecDouble> VecDoubleFromPyIter(const py::iterable& dbls)
{      

}
boost::shared_ptr<py::iterable> PyIterFromVecDouble(const VecDouble& dbls)
{      

}

// VecFloat
boost::shared_ptr<VecFloat> VecFloatFromPyIter(const py::iterable& flts)
{      

}
boost::shared_ptr<py::iterable> PyIterFromVecFloat(const VecFloat& flts)
{      

}

// VecBool
boost::shared_ptr<VecBool> VecBoolFromPyIter(const py::iterable& bools)
{      

}
boost::shared_ptr<py::iterable> PyIterFromVecBool(const VecBool& bools)
{      

}

// DynamicBitset
boost::shared_ptr<DynBitset> DynamicBitsetFromPyIter(const py::iterable& bitset)
{      

}
boost::shared_ptr<py::iterable> PyIterFromDynamicBitset(const DynBitset& bitset)
{      

}
}