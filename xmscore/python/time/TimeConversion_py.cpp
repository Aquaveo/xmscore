//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <xmscore/time/TimeConversion.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------

void initTimeConversion(py::module& geometry)
{
  // ---------------------------------------------------------------------------
  // function: tmCalendarToJulian
  // ---------------------------------------------------------------------------
  geometry.def("tmCalendarToJulian",
               [](int a_yr, int a_mo, int a_day, int a_hr, int a_min, int a_sec) -> py::object {
                 double julian = 0.0;
                 bool success =
                   xms::tmCalendarToJulian(a_yr, a_mo, a_day, a_hr, a_min, a_sec, &julian);
                 if (success)
                   return py::cast(julian);
                 return py::none();
               });
  // ---------------------------------------------------------------------------
  // function: tmJulianToCalendar
  // ---------------------------------------------------------------------------
  geometry.def("tmJulianToCalendar", [](double a_julian) -> py::object {
    int year, month, day, hour, minute, second;
    bool success = xms::tmJulianToCalendar(&year, &month, &day, &hour, &minute, &second, a_julian);
    if (success)
      return py::make_tuple(year, month, day, hour, minute, second);
    return py::none();
  });
}
