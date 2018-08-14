//------------------------------------------------------------------------------
/// \file XmUGridUtils.cpp
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/python/misc/PyUtils.h>
#include <xmscore/misc/DynBitset.h>


/// XMS Namespace
namespace xms
{

//------------------------------------------------------------------------------
/// \brief Create Pt3d from py::iterable
/// \param[in] pt: py::iterable object that represents a Pt3d
/// \return a boost::shared_ptr to a Pt3d
//------------------------------------------------------------------------------
Pt3d Pt3dFromPyIter(const py::tuple& pt)
{
  if(py::len(pt) != 3) {
    throw py::type_error("Input point should be a 3-tuple");
  } else {
    Pt3d point(pt[0].cast<double>(), pt[1].cast<double>(), pt[2].cast<double>());
    return point;
  }
} // Pt3dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from Pt3d
/// \param[in] pt: Pt3d object that represents a py::iterable
/// \return a boost::shared_ptr to a py::iterable
//------------------------------------------------------------------------------
py::tuple PyIterFromPt3d(const Pt3d& pt)
{      
  return py::make_tuple(pt.x, pt.y, pt.z);
} // PyIterFromPt3d
//------------------------------------------------------------------------------
/// \brief Create VecPt3d from py::iterable
/// \param[in] pt: py::iterable object that represents a VecPt3d
/// \return a VecPt3d
//------------------------------------------------------------------------------
boost::shared_ptr<VecPt3d> VecPt3dFromPyIter(const py::iterable& pts)
{
  boost::shared_ptr<xms::VecPt3d> vec_pts(new xms::VecPt3d());
  for (auto item : pts) {
    if(!py::isinstance<py::iterable>(item)) {
      throw py::type_error("First arg must be a n-tuple of 3-tuples");
    }
    py::tuple tuple = item.cast<py::iterable>();
    Pt3d point;
    point = Pt3dFromPyIter(tuple);
    vec_pts->push_back(point);
  }
  return vec_pts;
} // VecPt3dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecPt3d
/// \param[in] pt: VecPt3d object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecPt3d(const VecPt3d& pts)
{
  py::array_t<double, py::array::c_style> a({(int)pts.size(), 3});
  auto r = a.mutable_unchecked<2>();
  int i = 0;
  for (ssize_t i = 0; i < r.shape(0); i++) {
   r(i, 0) = pts[i].x;
   r(i, 1) = pts[i].y;
   r(i, 2) = pts[i].z;
  }
  return a;
} // PyIterFromVecPt3d
//------------------------------------------------------------------------------
/// \brief Create VecPt3d2d from py::iterable
/// \param[in] pt: py::iterable object that represents a VecPt3d2d
/// \return a boost::shared_ptr to a VecPt3d2d
//------------------------------------------------------------------------------
boost::shared_ptr<VecPt3d2d> VecPt3d2dFromPyIter(const py::iterable& pts)
{
  boost::shared_ptr<VecPt3d2d> vec_pt3d2d(new VecPt3d2d(py::len(pts)));
  int i = 0;
  for (auto poly : pts) {
      if (!py::isinstance<py::iterable>(poly)) {
          throw py::type_error("Second arg must be an n-tuple of n-tuples of 3-tuples");
      }
      xms::VecPt3d vec_pt3d(py::len(poly));
      int j = 0;
      for (auto p : poly) {
          if (!py::isinstance<py::iterable>(poly)) {
              throw py::type_error("Second arg must be an n-tuple of n-tuples of 3-tuples");
          }
          py::tuple pt = p.cast<py::tuple>();
          if (py::len(pt) != 3) {
              throw py::type_error("Second arg must be an n-tuple of n-tuples of 3-tuples");
          } else {
              xms::Pt3d point(pt[0].cast<double>(), pt[1].cast<double>(), pt[2].cast<double>());
              vec_pt3d.at(j) = point;
          }
      }
      vec_pt3d2d->at(i) = vec_pt3d;
  }
  return vec_pt3d2d;
} // VecPt3d2dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecPt3d2d
/// \param[in] pt: VecPt3d2d object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecPt3d2d(const VecPt3d2d& pts)
{
	return py::make_tuple();
} // PyIterFromVecPt3d2d
//------------------------------------------------------------------------------
/// \brief Create VecInt2d from py::iterable
/// \param[in] pt: py::iterable object that represents a VecInt2d
/// \return a boost::shared_ptr to a VecInt2d
//------------------------------------------------------------------------------
boost::shared_ptr<VecInt2d> VecInt2dFromPyIter(const py::iterable& int2d)
{
  boost::shared_ptr<xms::VecInt2d> vec_int2d(new xms::VecInt2d(py::len(int2d)));
  auto sizes = py::tuple(py::len(int2d));
  int j = 0;
  for (auto item : int2d) {
    if(!py::isinstance<py::iterable>(item)) {
      throw py::type_error("First arg must be a n-tuple of n-tuples");
    }
    py::tuple tuple = item.cast<py::iterable>();
    xms::VecInt inner_vec(py::len(tuple));
    for (int i = 0; i < py::len(tuple); i++) {
      double point(tuple[i].cast<double>());
      inner_vec[i] = point;
    }
    sizes[j] = inner_vec.size();
    vec_int2d->at(j) = inner_vec;
    j++;
  }
  return vec_int2d;
} // VecPt3d2dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecPt3d2d
/// \param[in] pt: VecPt3d2d object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecInt2d(const VecInt2d& int2d)
{
  std::vector<py::iterable> inners(int2d.size());

  for (int i = 0; i < int2d.size(); i++) {
      auto inner = py::tuple(int2d.at(i).size());
      for (int j = 0; j < int2d.at(i).size(); j++) {
        inner[j] = int2d.at(i).at(j);
      }
      inners.at(i) = inner;
  }

  auto tuple = py::tuple(inners.size());
  for (int i = 0; i < inners.size(); i++) {
      tuple[i] = inners.at(i);
  }
  return tuple;
} // PyIterFromVecPt3d2d
//------------------------------------------------------------------------------
/// \brief Create VecInt from py::iterable
/// \param[in] pt: py::iterable object that represents a VecInt
/// \return a boost::shared_ptr to a VecInt
//------------------------------------------------------------------------------
boost::shared_ptr<VecInt> VecIntFromPyIter(const py::iterable& ints)
{
  boost::shared_ptr<VecInt> vec_ints(new VecInt());
  vec_ints->resize(py::len(ints));
  int i = 0;
  for (auto item : ints) {
    vec_ints->at(i)= item.cast<int>();
    i++;
  }
  return vec_ints;
} // VecIntFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecInt
/// \param[in] pt: VecInt object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecInt(const VecInt& ints, bool numpy)
{
  if (!numpy) {
    // NOTE: This is a copy operation
    auto tuple_ret = py::tuple(ints.size());
    for (size_t i = 0; i < tuple_ret.size(); ++i) {
      tuple_ret[i] = ints.at(i);
    }
    return tuple_ret;
  } else {
    return py::array(ints.size(), ints.data());
  }
} // PyIterFromVecInt
//------------------------------------------------------------------------------
/// \brief Create VecDbl from py::iterable
/// \param[in] pt: py::iterable object that represents a VecDbl
/// \return a boost::shared_ptr to a VecDbl
//------------------------------------------------------------------------------
boost::shared_ptr<VecDbl> VecDblFromPyIter(const py::iterable& dbls)
{
  boost::shared_ptr<VecDbl> vec_dbls(new VecDbl());
  vec_dbls->resize(py::len(dbls));
  int i = 0;
  for (auto item : dbls) {
    vec_dbls->at(i)= item.cast<double>();
    i++;
  }
  return vec_dbls;
} // VecDblFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecDbl
/// \param[in] pt: VecDbl object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecDbl(const VecDbl& dbls, bool numpy)
{      
  if (!numpy) {
    // NOTE: This is a copy operation
    auto tuple_ret = py::tuple(dbls.size());
    for (size_t i = 0; i < tuple_ret.size(); ++i) {
      tuple_ret[i] = dbls.at(i);
    }
    return tuple_ret;
  } else {
    return py::array(dbls.size(), dbls.data());
  }
} // PyIterFromVecDbl
//------------------------------------------------------------------------------
/// \brief Create VecFlt from py::iterable
/// \param[in] pt: py::iterable object that represents a VecFlt
/// \return a boost::shared_ptr to a VecFlt
//------------------------------------------------------------------------------
boost::shared_ptr<VecFlt> VecFltFromPyIter(const py::iterable& flts)
{
  boost::shared_ptr<VecFlt> vec_flts(new VecFlt());
  vec_flts->resize(py::len(flts));
  int i = 0;
  for (auto item : flts) {
    vec_flts->at(i)= item.cast<float>();
    i++;
  }
  return vec_flts;
} // VecFltFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecFlt
/// \param[in] pt: VecFlt object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecFlt(const VecFlt& flts, bool numpy)
{
  if (!numpy) {
    // NOTE: This is a copy operation
    auto tuple_ret = py::tuple(flts.size());
    for (size_t i = 0; i < tuple_ret.size(); ++i) {
      tuple_ret[i] = flts.at(i);
    }
    return tuple_ret;
  } else {
    return py::array(flts.size(), flts.data());
  }
} // PyIterFromVecFlt
//------------------------------------------------------------------------------
/// \brief Create DynBitset from py::iterable
/// \param[in] pt: py::iterable object that represents a DynBitset
/// \return a boost::shared_ptr to a DynBitset
//------------------------------------------------------------------------------
DynBitset DynamicBitsetFromPyIter(const py::iterable& bitset)
{
  DynBitset dyn_bitset;
  std::vector<unsigned char> bitvals;
  for (auto item : bitset) {
    py::bool_ flag = item.cast<py::bool_>();
    if (flag) {
      bitvals.push_back(1);
    } else {
      bitvals.push_back(0);
    }
  }
  VecBooleanToDynBitset(bitvals, dyn_bitset);
  return dyn_bitset;
} // DynamicBitsetFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from DynBitset
/// \param[in] pt: DynBitset object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromDynamicBitset(const DynBitset& bitset, bool numpy)
{      
  std::vector<unsigned char> vec_bools;
  DynBitsetToVecBoolean(bitset, vec_bools);
  if (!numpy) {
    // NOTE: This is a copy operation
    auto tuple_ret = py::tuple(vec_bools.size());
    for (size_t i = 0; i < tuple_ret.size(); ++i) {
      tuple_ret[i] = vec_bools.at(i);
    }
    return tuple_ret;
  } else {
    return py::array(vec_bools.size(), vec_bools.data());
  }
} // PyIterFromDynamicBitset
//------------------------------------------------------------------------------
/// \brief Create std::pair<int, int> from py::iterable
/// \param[in] pt: py::iterable object that represents a std::pair<int, int>
/// \return a boost::shared_ptr to a std::pair<int, int>
//------------------------------------------------------------------------------
std::pair<int, int> IntPairFromPyIter(const py::iterable& intpair)
{
  py::tuple pr = intpair.cast<py::tuple>();
  if (py::len(pr) != 2) {
      throw py::type_error("arg must be an 2-tuple");
  } else {
      std::pair<int, int> ret(1, 1);//ret(pr[0].cast<int>, pr[1].cast<int>);
      return ret;
  }
} // IntPairFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from std::pair<int, int>
/// \param[in] pt: std::pair<int, int> object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromIntPair(const std::pair<int, int>& intpair)
{
  return py::make_tuple(intpair.first, intpair.second);
} // PyIterFromIntPair
//------------------------------------------------------------------------------
/// \brief Create std::vector<std::pair<int, int>> from py::iterable
/// \param[in] pt: py::iterable object that represents a std::vector<std::pair<int, int>>
/// \return a boost::shared_ptr to a std::vector<std::pair<int, int>>
//------------------------------------------------------------------------------
boost::shared_ptr<std::vector<std::pair<int, int>>> VecIntPairFromPyIter(const py::iterable& intpairs)
{
  boost::shared_ptr<std::vector<std::pair<int, int>>> vec_pairs(new std::vector<std::pair<int, int>>);
  vec_pairs->resize(py::len(intpairs));
  int i = 0;
  for (auto item : intpairs) {
    py::tuple prs = item.cast<py::tuple>();
    vec_pairs->at(i)= IntPairFromPyIter(prs);
    i++;
  }
  return vec_pairs;
} // VecIntPairFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from std::vector<std::pair<int, int>>
/// \param[in] pt: std::vector<std::pair<int, int>> object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecIntPair(const std::vector<std::pair<int, int>>& intpairs)
{
  // NOTE: This is a copy operation
  auto tuple_ret = py::tuple(intpairs.size());
  for (size_t i = 0; i < tuple_ret.size(); ++i) {
    tuple_ret[i] = PyIterFromIntPair(intpairs.at(i));
  }
  return tuple_ret;
} // PyIterFromVecIntPair

} // namespace xms