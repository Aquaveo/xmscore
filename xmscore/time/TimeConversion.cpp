//------------------------------------------------------------------------------
/// \file
/// \brief Routines for date time conversion.
/// \ingroup time
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/time/TimeConversion.h>

// 3. Standard library headers
#include <cmath>

// 4. External library headers
#include <boost/date_time.hpp>

// 5. Shared code headers

// 6. Non-shared code headers
#include <xmscore/misc/StringUtil.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

namespace
{
enum TimeEra {
  ERA_BCE, ///< Time era BCE (BC)
  ERA_CE   ///< Time era CE (AD)
};

//------------------------------------------------------------------------------
/// \brief Convert a calendar date and time to Julian date and time.
///
///  (Julian day number algorithm adopted from Press et al.)
///           era = 0 represents BCE (BC), and era = 1 represents CE (AD).
///          \verbatim
///          -Taken from JavaScript Code found at website:
///                http://aa.usno.navy.mil/data/docs/JulianDate.html
///           Contact info. provided by website:
///             Marc A. Murison
///             Astronomical Applications Dept.
///             U.S. Naval Observatory
///             3450 Massachusetts Ave, NW
///             Washington, DC  20392-5420
///          \endverbatim
///
/// \param a_era The input era: ERA_BCE - BC, ERA_CE - AD.
/// \param a_year The input year.
/// \param a_month The input month.
/// \param a_day The input day.
/// \param a_hour The input hour.
/// \param a_minute The input minute.
/// \param a_second The input second.
/// \param a_julian The output julian date and time.
/// \return Returns 1 if successful and -1 if unsuccessful.
//------------------------------------------------------------------------------
int iCalendarToJulian(TimeEra a_era,
                      int a_year,
                      int a_month,
                      int a_day,
                      int a_hour,
                      int a_minute,
                      int a_second,
                      double* a_julian)
{
  double jy, ja, jm, tmpyr;
  double intgr, gregcal, dayfrac, frac;

  if (a_year == 0)
  {
    // There is no year 0 in the Julian system!
    return -1;
  }
  if (a_year == 1582 && a_month == 10 && a_day > 4 && a_day < 15 && a_era == ERA_BCE)
  {
    // The dates 5 through 14 October, 1582
    // do not exist in the Gregorian system!
    return -1;
  }

  tmpyr = a_year;

  if (a_era == ERA_BCE)
  {
    tmpyr = 1 - tmpyr;
  }
  if (a_month > 2)
  {
    jy = tmpyr;
    jm = a_month + 1;
  }
  else
  {
    jy = tmpyr - 1;
    jm = a_month + 13;
  }

  intgr = floor(floor(365.25 * jy) + floor(30.6001 * jm) + a_day + 1720995);

  // check for switch to Gregorian calendar
  gregcal = 15 + 31 * (10 + 12 * 1582);
  if (a_day + 31 * (a_month + 12 * tmpyr) >= gregcal)
  {
    ja = floor(0.01 * jy);
    intgr += 2 - ja + floor(0.25 * ja);
  }

  // correct for half-day offset
  dayfrac = a_hour / 24.0 - 0.5;
  if (dayfrac < 0.0)
  {
    dayfrac += 1.0;
    --intgr;
  }

  // now set the fraction of a day
  frac = dayfrac + (a_minute + a_second / 60.0) / 60.0 / 24.0;

  // round to the nearest second
  // we don't want to round

  *a_julian = intgr + frac;
  return 1;
} // iCalendarToJulian
//------------------------------------------------------------------------------
/// \brief Convert a Julian date and time To calendar date and time.
///
///           (algorithm adopted from Press et al.)
///           era = 0 represents BCE (BC), and era = 1 represents CE (AD).
///          \verbatim
///          -Taken from JavaScript Code found at website:
///                http://aa.usno.navy.mil/data/docs/JulianDate.html
///           Contact info. provided by website:
///             Marc A. Murison
///             Astronomical Applications Dept.
///             U.S. Naval Observatory
///             3450 Massachusetts Ave, NW
///             Washington, DC  20392-5420  \endverbatim */
///
/// \param a_era The returned era: ERA_BCE - BC, ERA_CE - AD.
/// \param a_year The returned year.
/// \param a_month The returned month.
/// \param a_day The returned day.
/// \param a_hour The returned hour.
/// \param a_minute The returned minute.
/// \param a_second The returned second.
/// \param a_julian The input julian date and time.
//------------------------------------------------------------------------------
void iJulianToCalendar(TimeEra* a_era,
                       int* a_year,
                       int* a_month,
                       int* a_day,
                       int* a_hour,
                       int* a_minute,
                       int* a_second,
                       double a_julian)
{
  double j1, j2, j3, j4, j5;
  double intgr, frac, gregjd, tmp;
  double dayfrac, f;

  // get the date from the Julian day number
  intgr = floor(a_julian);
  frac = a_julian - intgr;
  gregjd = 2299161;
  // Gregorian Calendar Correction
  if (intgr >= gregjd)
  {
    tmp = floor(((intgr - 1867216) - 0.25) / 36524.25);
    j1 = intgr + 1 + tmp - floor(0.25 * tmp);
  }
  else
  {
    j1 = intgr;
  }

  // correction for half day offset
  dayfrac = frac + 0.5;
  if (dayfrac >= 1.0)
  {
    dayfrac -= 1.0;
    ++j1;
  }

  j2 = j1 + 1524;
  j3 = floor(6680.0 + ((j2 - 2439870) - 122.1) / 365.25);
  j4 = floor(j3 * 365.25);
  j5 = floor((j2 - j4) / 30.6001);

  *a_day = (int)floor(j2 - j4 - floor(j5 * 30.6001));
  *a_month = (int)floor(j5 - 1);
  if (*a_month > 12)
  {
    *a_month -= 12;
  }
  *a_year = (int)floor(j3 - 4715);
  if (*a_month > 2)
  {
    --*a_year;
  }
  if (*a_year <= 0)
  {
    --*a_year;
  }

  // get time of day from day fraction
  *a_hour = (int)floor(dayfrac * 24.0);
  *a_minute = (int)floor((dayfrac * 24.0 - *a_hour) * 60.0);
  f = ((dayfrac * 24.0 - *a_hour) * 60.0 - *a_minute) * 60.0;
  *a_second = (int)floor(f);
  f -= *a_second;
  if (f > 0.5)
  {
    ++*a_second;
  }
  if (*a_second == 60)
  {
    *a_second = 0;
    ++*a_minute;
  }
  if (*a_minute == 60)
  {
    *a_minute = 0;
    ++*a_hour;
  }
  if (*a_hour == 24)
  {
    *a_hour = 0;
    ++*a_day;
  }

  if (*a_year < 0)
  {
    *a_year = -*a_year;
    *a_era = ERA_BCE;
  }
  else
  {
    *a_era = ERA_CE;
  }
} // iJulianToCalendar
} // namespace
//------------------------------------------------------------------------------
/// \brief Convert a calendar date and time to Julian date and time.
/// \param a_year The input year.
/// \param a_month The input month.
/// \param a_day The input day.
/// \param a_hour The input hour.
/// \param a_minute The input minute.
/// \param a_second The input second.
/// \param a_julian The output julian date and time.
/// \return Returns true if successful.
//------------------------------------------------------------------------------
bool tmCalendarToJulian(int a_year,
                        int a_month,
                        int a_day,
                        int a_hour,
                        int a_minute,
                        int a_second,
                        double* a_julian)
{
  int result = iCalendarToJulian(ERA_CE, a_year, a_month, a_day, a_hour, a_minute, a_second, a_julian);
  if (result <= 0)
    return false;
  return true;
} // tmCalendarToJulian
//------------------------------------------------------------------------------
/// \brief Convert a Julian date and time To calendar date and time.
/// \param a_year The returned year.
/// \param a_month The returned month.
/// \param a_day The returned day.
/// \param a_hour The returned hour.
/// \param a_minute The returned minute.
/// \param a_second The returned second.
/// \param a_julian The input julian date and time.
/// \return Returns true if successful.
//------------------------------------------------------------------------------
bool tmJulianToCalendar(int* a_year,
                        int* a_month,
                        int* a_day,
                        int* a_hour,
                        int* a_minute,
                        int* a_second,
                        double a_julian)
{
  TimeEra era = ERA_BCE;
  iJulianToCalendar(&era, a_year, a_month, a_day, a_hour, a_minute, a_second, a_julian);
  if (era == ERA_BCE)
    return false;

  boost::gregorian::date date(*a_year, *a_month, *a_day);
  boost::posix_time::time_duration timeDuration(*a_hour, *a_minute, *a_second, 0);
  boost::posix_time::ptime dt(date, timeDuration);
  if (dt.is_special())
    return false;

  return true;
} // tmJulianToCalendar
} // namespace xms

#ifdef CXX_TEST

#include <xmscore/time/TimeConversion.t.h>

using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class TimeConversionUnitTests
/// \brief Tests for TimeConversion.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test conversions between Julian to calendar date and times.
//------------------------------------------------------------------------------
void TimeConversionUnitTests::testJulianConversions()
{
  TimeEra era1, era2, era3, era4;
  int yr1, mo1, day1, hr1, min1, sec1;
  int yr2, mo2, day2, hr2, min2, sec2;
  int yr3, mo3, day3, hr3, min3, sec3;
  int yr4, mo4, day4, hr4, min4, sec4, result;
  double julian1, julian2, julian3, julian4;

  std::ostringstream out;
  out << "Calendar conversion:\n\n";

  era1 = ERA_BCE;
  yr1 = mo1 = day1 = hr1 = min1 = sec1 = 0;
  julian1 = 2655.5;
  iJulianToCalendar(&era1, &yr1, &mo1, &day1, &hr1, &min1, &sec1, julian1);

  yr2 = 4706;
  mo2 = 4;
  day2 = 10;
  era2 = ERA_BCE;
  hr2 = min2 = sec2 = 0;
  julian2 = 0.0;
  result = iCalendarToJulian(era2, yr2, mo2, day2, hr2, min2, sec2, &julian2);
  TS_ASSERT_EQUALS(1, result);

  era3 = ERA_CE;
  yr3 = 2004;
  mo3 = 6;
  day3 = 3;
  hr3 = 2;
  min3 = 8;
  sec3 = 32;
  julian3 = 0.0;
  result = iCalendarToJulian(era3, yr3, mo3, day3, hr3, min3, sec3, &julian3);
  TS_ASSERT_EQUALS(1, result);

  era4 = ERA_BCE;
  yr4 = mo4 = day4 = hr4 = min4 = sec4 = 0;
  julian4 = 2453159.5892592594;
  iJulianToCalendar(&era4, &yr4, &mo4, &day4, &hr4, &min4, &sec4, julian4);

  TS_ASSERT_EQUALS(era1, era2);
  TS_ASSERT_EQUALS(yr1, yr2);
  TS_ASSERT_EQUALS(mo1, mo2);
  TS_ASSERT_EQUALS(day1, day2);
  TS_ASSERT_EQUALS(hr1, hr2);
  TS_ASSERT_EQUALS(min1, min2);
  TS_ASSERT_DELTA(julian1, julian2, 1.0e-5);

  TS_ASSERT_EQUALS(era3, era4);
  TS_ASSERT_EQUALS(yr3, yr4);
  TS_ASSERT_EQUALS(mo3, mo4);
  TS_ASSERT_EQUALS(day3, day4);
  TS_ASSERT_EQUALS(hr3, hr4);
  TS_ASSERT_EQUALS(min3, min4);
  TS_ASSERT_DELTA(julian3, julian4, 1.0e-5);
} // TimeConversionUnitTests::testJulianConversions
//------------------------------------------------------------------------------
/// \brief Test julian to calendar date conversion.
//------------------------------------------------------------------------------
void TimeConversionUnitTests::testJulianToCalendar()
{
  int year, month, day, hour, minute, second;
  TS_ASSERT(tmJulianToCalendar(&year, &month, &day, &hour, &minute, &second, 2447727.5430902778));
  TS_ASSERT_EQUALS(1989, year);
  TS_ASSERT_EQUALS(7, month);
  TS_ASSERT_EQUALS(20, day);
  TS_ASSERT_EQUALS(1, hour);
  TS_ASSERT_EQUALS(2, minute);
  TS_ASSERT_EQUALS(3, second);
} // TimeConversionUnitTests::testJulianToCalendar
//------------------------------------------------------------------------------
/// \brief Test julian to calendar date conversion with invalid julian date.
//------------------------------------------------------------------------------
void TimeConversionUnitTests::testJulianToCalendarInvalid()
{
  int year, month, day, hour, minute, second;
  TS_ASSERT(!tmJulianToCalendar(&year, &month, &day, &hour, &minute, &second, -1));
  TS_ASSERT(!tmJulianToCalendar(&year, &month, &day, &hour, &minute, &second, -99999999));
} // TimeConversionUnitTests::testJulianToCalendarInvalid
//------------------------------------------------------------------------------
/// \brief Test calendar to julian date conversion.
//------------------------------------------------------------------------------
void TimeConversionUnitTests::testCalendarToJulian()
{
  double julian;
  TS_ASSERT(tmCalendarToJulian(1989, 7, 20, 1, 2, 3, &julian));
  TS_ASSERT_DELTA(2447727.5430902778, julian, 1.0e-5);
} // TimeConversionUnitTests::testCalendarToJulian
//------------------------------------------------------------------------------
/// \brief Test calendar to julian date conversion with invalid values.
//------------------------------------------------------------------------------
void TimeConversionUnitTests::testCalendarToJulianInvalid()
{
  double julian;
  TS_ASSERT(!tmCalendarToJulian(0, 7, 20, 1, 2, 3, &julian));
  TS_ASSERT_EQUALS(1, iCalendarToJulian(ERA_BCE, 1582, 10, 4, 0, 0, 0, &julian));
  TS_ASSERT_EQUALS(-1, iCalendarToJulian(ERA_BCE, 1582, 10, 5, 0, 0, 0, &julian));
  TS_ASSERT_EQUALS(-1, iCalendarToJulian(ERA_BCE, 1582, 10, 14, 0, 0, 0, &julian));
  TS_ASSERT_EQUALS(1, iCalendarToJulian(ERA_BCE, 1582, 10, 15, 0, 0, 0, &julian));
  // seems like this should also be true but it wasn't like this in XMDF code
  // TS_ASSERT_EQUALS(-1, iCalendarToJulian(ERA_CE, 1582, 10, 5, 0, 0, 0, &julian));
} // TimeConversionUnitTests::testCalendarToJulianInvalid

#endif
