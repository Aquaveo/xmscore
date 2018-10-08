#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief 64 or 32 bit detection.
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif
