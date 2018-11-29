//------------------------------------------------------------------------------
/// \file XmUGridUtils.cpp
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <pybind11/pybind11.h>

#include <sstream>
#include <iostream>

#include <xmscore/misc/DynBitset.h>
#include <xmscore/misc/StringUtil.h>
#include <xmscore/python/misc/PyUtils.h>

namespace py = pybind11;

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
  if(py::len(pt) > 3 || py::len(pt) < 0) {  // 0 check might not be needed but just to be safe
    throw py::type_error("Input point should be a an empty tuple, or a 1, 2, or 3 tuple");
  } else {
    if (py::len(pt) == 1)
    {
      Pt3d point(pt[0].cast<double>());
	  return point;
    }
	else if (py::len(pt) == 2)
    {
      Pt3d point(pt[0].cast<double>(), pt[1].cast<double>());
	  return point;
    }
    else if (py::len(pt) == 3)
    {
      Pt3d point(pt[0].cast<double>(), pt[1].cast<double>(), pt[2].cast<double>());
	  return point;
    }
    return Pt3d();
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
/// \brief Create Pt2d from py::iterable
/// \param[in] pt: py::iterable object that represents a Pt2d
/// \return a boost::shared_ptr to a Pt2d
//------------------------------------------------------------------------------
Pt2d Pt2dFromPyIter(const py::tuple& pt)
{
  if(py::len(pt) > 2 || py::len(pt) < 0) {  // 0 check might not be needed but just to be safe
    throw py::type_error("Input point should be a an empty tuple, or a 1, or 2 tuple");
  } else {
    if (py::len(pt) == 1)
    {
      Pt2d point(pt[0].cast<double>());
	    return point;
    }
	else if (py::len(pt) == 2)
    {
      Pt2d point(pt[0].cast<double>(), pt[1].cast<double>());
	    return point;
    }
    return Pt2d();
  }
} // Pt2dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from Pt2d
/// \param[in] pt: Pt2d object that represents a py::iterable
/// \return a boost::shared_ptr to a py::iterable
//------------------------------------------------------------------------------
py::tuple PyIterFromPt2d(const Pt2d& pt)
{      
  return py::make_tuple(pt.x, pt.y);
} // PyIterFromPt2d
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
      throw py::type_error("First arg must be an iterable object");
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
/// \brief Create VecPt2d from py::iterable
/// \param[in] pt: py::iterable object that represents a VecPt2d
/// \return a VecPt2d
//------------------------------------------------------------------------------
boost::shared_ptr<VecPt2d> VecPt2dFromPyIter(const py::iterable& pts)
{
  boost::shared_ptr<xms::VecPt2d> vec_pts(new xms::VecPt2d());
  for (auto item : pts) {
    if(!py::isinstance<py::iterable>(item)) {
      throw py::type_error("First arg must be an iterable object");
    }
    py::tuple tuple = item.cast<py::iterable>();
    Pt2d point;
    point = Pt2dFromPyIter(tuple);
    vec_pts->push_back(point);
  }
  return vec_pts;
} // VecPt2dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecPt2d
/// \param[in] pt: VecPt2d object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecPt2d(const VecPt2d& pts)
{
  py::array_t<double, py::array::c_style> a({(int)pts.size(), 2});
  auto r = a.mutable_unchecked<2>();
  int i = 0;
  for (ssize_t i = 0; i < r.shape(0); i++) {
   r(i, 0) = pts[i].x;
   r(i, 1) = pts[i].y;
  }
  return a;
} // PyIterFromVecPt2d
//------------------------------------------------------------------------------
/// \brief Create VecPt3d2d from py::iterable
/// \param[in] pt: py::iterable object that represents a VecPt3d2d
/// \return a boost::shared_ptr to a VecPt3d2d
//------------------------------------------------------------------------------
boost::shared_ptr<VecPt3d2d> VecPt3d2dFromPyIter(const py::iterable& pt3d2d)
{
  boost::shared_ptr<VecPt3d2d> vec_pt3d2d(new VecPt3d2d(py::len(pt3d2d)));
  int i = 0;
  for (auto pts : pt3d2d) {
      if (!py::isinstance<py::iterable>(pts)) {
          throw py::type_error("Second arg must be an iterable");
      }
      py::tuple tuple = pts.cast<py::iterable>();
      xms::VecPt3d vec_pt3d = *xms::VecPt3dFromPyIter(tuple);
      vec_pt3d2d->at(i) = vec_pt3d;
      i++;
  }
  return vec_pt3d2d;
} // VecPt3d2dFromPyIter
//------------------------------------------------------------------------------
/// \brief Create py::iterable from VecPt3d2d
/// \param[in] pt: VecPt3d2d object that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecPt3d2d(const VecPt3d2d& vecPt3d2d)
{
    py::tuple pt3d2d(vecPt3d2d.size());
    for (int i = 0; i < vecPt3d2d.size(); i++) {
        std::cout << "Iter" << std::endl;
        auto inside_poly = vecPt3d2d[i];
        py::array_t<double, py::array::c_style> poly_points = xms::PyIterFromVecPt3d(inside_poly);
        pt3d2d[i] = poly_points;
    }
    return pt3d2d;
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
//------------------------------------------------------------------------------
/// \brief Create a __repr__ string from a VecPt3d
/// \param[in] a_pts: vector of points.
/// \return a string
//------------------------------------------------------------------------------
std::string StringFromVecPt3d(const VecPt3d& a_pts)
{
  bool printDotDotDot(false);
  VecPt3d p;
  if (a_pts.size() < 7)
  {
    p = a_pts;
  }
  else
  {
    printDotDotDot = true;
    size_t idx = a_pts.size();
    p.insert(p.end(), a_pts.begin(), a_pts.begin()+3);
    p.insert(p.end(), a_pts.begin()+(idx-3), a_pts.end());
  }
  std::stringstream ss;
  ss << "(length " << a_pts.size() << "): \n";
  ss << "[";
  for (size_t i=0; i<p.size(); ++i)
  {
    if (printDotDotDot && i == 3)
      ss << " ...\n";
    if (i > 0)
      ss << " ";
    ss << "(" << STRstd(p[i].x) << ", " << STRstd(p[i].y) << ", " << STRstd(p[i].z) << ")";
    if (i+1 != p.size())
      ss << ", \n";
  }
  ss << "]\n";
  return ss.str();
} // StringFromVecPt3d
//------------------------------------------------------------------------------
/// \brief Create a __repr__ string from a VecPt3d2d
/// \param[in] a_vals: 2d vector of Pt3ds.
/// \return a string
//------------------------------------------------------------------------------
std::string StringFromVecPt3d2d(const VecPt3d2d& a_vals)
{
  bool printDotDotDot(false);
  std::stringstream ss;
  VecPt3d2d v;
  if (a_vals.size() < 7)
  {
    v = a_vals;
  }
  else
  {
    printDotDotDot = true;
    size_t idx = a_vals.size();
    v.insert(v.end(), a_vals.begin(), a_vals.begin()+3);
    v.insert(v.end(), a_vals.begin()+(idx-3), a_vals.end());
  }

  ss << "(length " << a_vals.size() << "):\n";
  ss << "[";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (printDotDotDot && i == 3)
      ss << " ...\n";
    if (i > 0)
      ss << " ";
    std::string strVecPt3d = StringFromVecPt3d(v[i]);
    strVecPt3d.pop_back();
    ss << strVecPt3d;
    if (i + 1 != v.size())
      ss << ",\n";
   }
  ss << "]\n";
  return ss.str();
} // StringFromVecPt3d2d
//------------------------------------------------------------------------------
/// \brief Create a __repr__ string from a VecInt
/// \param[in] a_vals: vector of ints.
/// \return a string
//------------------------------------------------------------------------------
std::string StringFromVecInt(const VecInt& a_vals)
{
  std::stringstream ss;
  ss << "(length " << a_vals.size() << "): ";
  VecInt v;
  bool printDotDotDot(false);
  if (a_vals.size() < 11)
  {
    v = a_vals;
  }
  else
  {
    printDotDotDot = true;
    size_t idx = a_vals.size();
    v.insert(v.end(), a_vals.begin(), a_vals.begin()+5);
    v.insert(v.end(), a_vals.begin()+(idx-5), a_vals.end());
  }

  ss << "[";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (printDotDotDot && i == 5)
      ss << "... ";
    ss << v[i];
    if (i + 1 != v.size())
      ss << ", ";
  }
  ss << "]\n";
  return ss.str();
} // StringFromVecInt
//------------------------------------------------------------------------------
/// \brief Create a __repr__ string from a VecInt2d
/// \param[in] a_vals: 2d vector of ints.
/// \return a string
//------------------------------------------------------------------------------
std::string StringFromVecInt2d(const VecInt2d& a_vals)
{
  bool printDotDotDot(false);
  std::stringstream ss;
  VecInt2d v;
  if (a_vals.size() < 7)
  {
    v = a_vals;
  }
  else
  {
    printDotDotDot = true;
    size_t idx = a_vals.size();
    v.insert(v.end(), a_vals.begin(), a_vals.begin()+3);
    v.insert(v.end(), a_vals.begin()+(idx-3), a_vals.end());
  }

  ss << "(length " << a_vals.size() << "):\n";
  ss << "[";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (printDotDotDot && i == 3)
      ss << " ...\n";
    if (i > 0)
      ss << " ";
    std::string strVecInt = StringFromVecInt(v[i]);
    strVecInt.pop_back();
    ss << strVecInt;
    if (i + 1 != v.size())
      ss << ",\n";
   }
  ss << "]\n";
  return ss.str();
} // StringFromVecInt2d
//------------------------------------------------------------------------------
/// \brief Create a __repr__ string from a DynBitset
/// \param[in] a_vals: dynamic bitset
/// \return a string
//------------------------------------------------------------------------------
std::string StringFromDynBitset(const DynBitset& a_vals)
{
  VecInt v;
  v.reserve(a_vals.size());
  for (size_t i = 0; i < a_vals.size(); ++i)
  {
    v.push_back(a_vals[i] ? 1 : 0);
  }
  return StringFromVecInt(v);
} // StringFromDynBitset
//------------------------------------------------------------------------------
/// \brief Create a __repr__ string from a DynBitset
/// \param[in] a_vals: dynamic bitset
/// \return a string
//------------------------------------------------------------------------------
std::string StringFromVecFlt(const VecFlt& a_vals)
{
  std::stringstream ss;
  ss << "(length " << a_vals.size() << "): ";
  VecFlt v;
  bool printDotDotDot(false);
  if (a_vals.size() < 11)
  {
    v = a_vals;
  }
  else
  {
    printDotDotDot = true;
    size_t idx = a_vals.size();
    v.insert(v.end(), a_vals.begin(), a_vals.begin()+5);
    v.insert(v.end(), a_vals.begin()+(idx-5), a_vals.end());
  }

  ss << "[";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (printDotDotDot && i == 5)
      ss << "... ";
    ss << STRstd(v[i]);
    if (i + 1 != v.size())
      ss << ", ";
  }
  ss << "]\n";
  return ss.str();
} // StringFromDynBitset

} // namespace xms
