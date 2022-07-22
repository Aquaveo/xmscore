#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Conversion between Julian and Calendar date times.
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

bool tmCalendarToJulian(int a_year,
                        int a_month,
                        int a_day,
                        int a_hour,
                        int a_minute,
                        int a_second,
                        double* a_julian);
bool tmJulianToCalendar(int* a_year,
                        int* a_month,
                        int* a_day,
                        int* a_hour,
                        int* a_minute,
                        int* a_second,
                        double a_julian);
} // namespace xms
