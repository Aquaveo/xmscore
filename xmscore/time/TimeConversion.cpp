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

// 5. Shared code headers

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

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
/// \param a_bEra The input era: ERA_BCE - BC, ERA_CE - AD.
/// \param a_yr The input year.
/// \param a_mo The input month.
/// \param a_day The input day.
/// \param a_hr The input hour.
/// \param a_min The input minute.
/// \param a_sec The input second.
/// \param a_julian The output julian date and time.
/// \return Returns 1 if successful and -1 if unsuccessful.
//------------------------------------------------------------------------------
int tmCalendarToJulian(TimeEra a_bEra,
                       int a_yr,
                       int a_mo,
                       int a_day,
                       int a_hr,
                       int a_min,
                       int a_sec,
                       double* a_julian)
{
  double jy, ja, jm, tmpyr;
  double intgr, gregcal, dayfrac, frac;

  if (a_yr == 0)
  {
    // There is no year 0 in the Julian system!
    return -1;
  }
  if ((a_yr == 1582) && (a_mo == 10) && (a_day > 4) && (a_day < 15) && (a_bEra == ERA_BCE))
  {
    // The dates 5 through 14 October, 1582
    // do not exist in the Gregorian system!
    return -1;
  }

  tmpyr = a_yr;

  if (a_bEra == ERA_BCE)
  {
    tmpyr = 1 - tmpyr;
  }
  if (a_mo > 2)
  {
    jy = tmpyr;
    jm = a_mo + 1;
  }
  else
  {
    jy = tmpyr - 1;
    jm = a_mo + 13;
  }

  intgr = floor(floor(365.25 * jy) + floor(30.6001 * jm) + a_day + 1720995);

  // check for switch to Gregorian calendar
  gregcal = 15 + 31 * (10 + 12 * 1582);
  if (a_day + 31 * (a_mo + 12 * tmpyr) >= gregcal)
  {
    ja = floor(0.01 * jy);
    intgr += 2 - ja + floor(0.25 * ja);
  }

  // correct for half-day offset
  dayfrac = a_hr / 24.0 - 0.5;
  if (dayfrac < 0.0)
  {
    dayfrac += 1.0;
    --intgr;
  }

  // now set the fraction of a day
  frac = dayfrac + (a_min + a_sec / 60.0) / 60.0 / 24.0;

  // round to the nearest second
  // we don't want to round

  *a_julian = intgr + frac;
  return 1;
} // tmCalendarToJulian
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
/// \param a_bEra The returned era: ERA_BCE - BC, ERA_CE - AD.
/// \param a_yr The returned year.
/// \param a_mo The returned month.
/// \param a_day The returned day.
/// \param a_hr The returned hour.
/// \param a_min The returned minute.
/// \param a_sec The returned second.
/// \param a_julian The input julian date and time.
//------------------------------------------------------------------------------
void tmJulianToCalendar(TimeEra* a_bEra,
                        int* a_yr,
                        int* a_mo,
                        int* a_day,
                        int* a_hr,
                        int* a_min,
                        int* a_sec,
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
  *a_mo = (int)floor(j5 - 1);
  if (*a_mo > 12)
  {
    *a_mo -= 12;
  }
  *a_yr = (int)floor(j3 - 4715);
  if (*a_mo > 2)
  {
    --*a_yr;
  }
  if (*a_yr <= 0)
  {
    --*a_yr;
  }

  // get time of day from day fraction
  *a_hr = (int)floor(dayfrac * 24.0);
  *a_min = (int)floor((dayfrac * 24.0 - *a_hr) * 60.0);
  f = ((dayfrac * 24.0 - *a_hr) * 60.0 - *a_min) * 60.0;
  *a_sec = (int)floor(f);
  f -= *a_sec;
  if (f > 0.5)
  {
    ++*a_sec;
  }
  if (*a_sec == 60)
  {
    *a_sec = 0;
    ++*a_min;
  }
  if (*a_min == 60)
  {
    *a_min = 0;
    ++*a_hr;
  }
  if (*a_hr == 24)
  {
    *a_hr = 0;
    ++*a_day;
  }

  if (*a_yr < 0)
  {
    *a_yr = -*a_yr;
    *a_bEra = ERA_BCE;
  }
  else
  {
    *a_bEra = ERA_CE;
  }
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
    int     yr1, mo1, day1, hr1, min1, sec1;
    int     yr2, mo2, day2, hr2, min2, sec2;
    int     yr3, mo3, day3, hr3, min3, sec3;
    int     yr4, mo4, day4, hr4, min4, sec4, result;
    double  julian1, julian2, julian3, julian4;

    std::ostringstream out;
    out << "Calendar conversion:\n\n";

    era1 = ERA_BCE;
    yr1 = mo1 = day1 = hr1 = min1 = sec1 = 0;
    julian1 = 2655.5;
    tmJulianToCalendar(&era1, &yr1, &mo1, &day1, &hr1, &min1, &sec1, julian1);

    yr2  = 4706;
    mo2  = 4;
    day2 = 10;
    era2 = ERA_BCE;
    hr2  = min2 = sec2 = 0;
    julian2 = 0.0;
    result = tmCalendarToJulian(era2, yr2, mo2, day2, hr2, min2, sec2, &julian2);
    TS_ASSERT_EQUALS(1, result);

    era3 = ERA_CE;
    yr3  = 2004;
    mo3  = 6;
    day3 = 3;
    hr3  = 2;
    min3 = 8;
    sec3 = 32;
    julian3 = 0.0;
    result = tmCalendarToJulian(era3, yr3, mo3, day3, hr3, min3, sec3, &julian3);
    TS_ASSERT_EQUALS(1, result);

    era4 = ERA_BCE;
    yr4 = mo4 = day4 = hr4 = min4 = sec4 = 0;
    julian4 = 2453159.5892592594;
    tmJulianToCalendar(&era4, &yr4, &mo4, &day4, &hr4, &min4, &sec4, julian4);

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

#endif
