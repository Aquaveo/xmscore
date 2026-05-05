#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Conversion between Julian and Calendar date times.
/// \ingroup time
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------
// 1.

// 2.

// 3. Standard Library Headers

// 4. External Library Headers

// 5. Shared Headers

// 6. Non-shared Headers

namespace xms
{

/// \brief Convert a calendar date and time to a Julian date and time.
bool tmCalendarToJulian(int a_year,
                        int a_month,
                        int a_day,
                        int a_hour,
                        int a_minute,
                        int a_second,
                        double* a_julian);
/// \brief Convert a Julian date and time to a calendar date and time.
bool tmJulianToCalendar(int* a_year,
                        int* a_month,
                        int* a_day,
                        int* a_hour,
                        int* a_minute,
                        int* a_second,
                        double a_julian);
} // namespace xms
