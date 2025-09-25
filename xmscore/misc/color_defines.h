#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Definitions for color types and functions so they don't have to be included from
///        Microsoft headers
///  \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers
#include <stdint.h>

// 4. External Library Headers

// 5. Shared Headers
#include <xmscore/misc/environment.h>
// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
#if defined(ENV64BIT)
typedef uint64_t XM_ULONG_PTR;
#elif defined(ENV32BIT)
typedef unsigned long XM_ULONG_PTR;
#else
#error "Must define either ENV32BIT or ENV64BIT"
#endif

typedef unsigned long XM_DWORD;    ///< DWORD rename
typedef XM_ULONG_PTR XM_DWORD_PTR; ///< DWORD_PTR  rename
typedef unsigned short XM_WORD;    ///< WORD rename
typedef unsigned char XM_BYTE;     ///< BYTE rename rename
typedef XM_DWORD XM_COLORREF;      ///< COLORREF rename

#define XM_LOBYTE(w) ((xms::XM_BYTE)(((xms::XM_DWORD_PTR)(w)) & 0xff)) ///< Returns the low byte
#define XmsGetRValue(rgb) (XM_LOBYTE(rgb))                             ///< GetRValue Rename
#define XmsGetGValue(rgb) (XM_LOBYTE(((xms::XM_WORD)(rgb)) >> 8))      ///< GetGValue Rename
#define XmsGetBValue(rgb) (XM_LOBYTE((rgb) >> 16))                     ///< GetBValue Rename
#define XmsRGB(r, g, b)                                                                \
  ((xms::XM_COLORREF)(((xms::XM_BYTE)(r) | ((xms::XM_WORD)((xms::XM_BYTE)(g)) << 8)) | \
                      (((xms::XM_WORD)(xms::XM_BYTE)(b)) << 16))) ///< RGB rename
}
