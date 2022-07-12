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

enum TimeEra { ERA_BCE,  ///< Time era BCE (BC)
               ERA_CE    ///< Time era CE (AD)
};

int tmCalendarToJulian(TimeEra a_bEra,
                       int a_yr,
                       int a_mo,
                       int a_day,
                       int a_hr,
                       int a_min,
                       int a_sec,
                       double* a_julian);
void tmJulianToCalendar(TimeEra* a_bEra,
                        int* a_yr,
                        int* a_mo,
                        int* a_day,
                        int* a_hr,
                        int* a_min,
                        int* a_sec,
                        double a_julian);
} // namespace xms
