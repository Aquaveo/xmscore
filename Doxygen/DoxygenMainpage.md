xmscore {#mainpage}
============
\tableofcontents

xmscore {#xmscore}
============

Introduction {#XmscoreIntroduction}
------------

`xmscore` is a support library for the XMS family of C++ libraries
(xmsinterp, xmsmesh, xmsgrid, xmsstamper, ...). It collects the small,
general-purpose pieces those libraries all need so they don't each grow
their own copy: error handling and logging, an observer/progress
reporting interface, lightweight numeric and point types, STL helpers
that keep ABI stable across the suite, and time conversion utilities.

A subset of the C++ API is exposed to Python via pybind11 as the
`xms.core` package — see the [Python documentation](./pydocs) for that
side of the library.

<table align="center" border="0">
  <tr>
    <td>![](Aquaveo_Logo.png)</td>
  </tr>
</table>

License {#XmscoreLicense}
-------

The code is distributed under the FreeBSD Software License. (See accompanying
file LICENSE or copy at
[http://www.aquaveo.com/bsd/LICENSE.txt](http://www.aquaveo.com/bsd/license.txt)).

Module Overview {#XmscoreModules}
---------------

The C++ source lives under `xmscore/` in the repository. Each subdirectory
is a small, focused module:

| Module        | Header location           | What's inside |
| ------------- | ------------------------- | --- |
| \ref dataio   | `xmscore/dataio/`         | Stream IO helpers (`daStreamIo`) for reading/writing the XMS binary stream format. |
| \ref math     | `xmscore/math/`           | Numeric helpers used across XMS (rounding, comparison, simple geometry helpers). |
| \ref misc     | `xmscore/misc/`           | The bulk of the library: assertion/error handling (`XmError`), logging (`XmLog`), observer/progress reporting (`Observer`, `Progress`), `Singleton`, `StringUtil`, `DynBitset`, and shared typedefs/macros. |
| \ref points   | `xmscore/points/`         | 2D/3D point types (`Pt2`, `Pt3`, ...) and associated functors. |
| \ref stl      | `xmscore/stl/`            | Thin wrappers around `std::vector`, `std::map`, `std::set`, `std::deque`, `std::list`, `std::pair` used to keep ABI/serialization stable across the suite. |
| \ref time     | `xmscore/time/`           | Calendar / Julian-date conversions (`TimeConversion`). |
| \ref core_testing | `xmscore/testing/`    | `TestTools` shared by the CxxTest unit tests of this and dependent libraries. |

The `xmscore/python/` directory contains the pybind11 bindings; it is not
part of the C++ API surface.

Common Idioms {#XmscoreIdiomsRef}
-------------

For end-to-end recipes covering the patterns most heavily relied upon by the
downstream XMS libraries — `XM_LOG`, the `XM_ENSURE_TRUE` family, `Progress`
and `Observer`, `DaStreamReader` / `DaStreamWriter`, `BSHP<T>`, and the
testing assertion macros — see [Common Idioms](@ref XmscoreCommonIdioms).

Python {#XmscorePython}
------

This library is available as a Python module. See
[Python Documentation](./pydocs).

Testing {#XmscoreTesting}
-------

The code has numerous unit tests which use the
[CxxTest](http://cxxtest.com/) framework. A good way to see how to use the
code is to look at the unit tests. Unit tests are located at the bottom of
.cpp files within a `#if CXX_TEST` code block. Header files that are named
with `.t.h` contain the test suite class definitions.

The Code {#XmscoreTheCode}
--------
### Namespaces {#XmscoreNamespaces}
* `xms` — Most code is in this namespace. The use of other namespaces is kept
  to a minimum. Two-letter prefixes are used as "pseudo-namespaces" in code
  modules. Preprocessor macros typically start with `XM_` to prevent name
  collisions.
* `xmt` — Testing code will be put into this namespace once CXX_TEST is
  upgraded such that it will find the testing code in this namespace.

"xmscore" Name {#xmscoreName}
------------
The name "xmscore" comes from the "XMS" (GMS, SMS, WMS) water modeling
software created by Aquaveo.

Module Groups {#XmscoreGroups}
-------------

The following Doxygen groups collect the documentation for each module.
Each group is also reachable from the navigation tree.

\defgroup dataio dataio
\brief Stream IO helpers for the XMS binary stream format.

\defgroup math math
\brief Numeric helpers used across the XMS suite.

\defgroup misc misc
\brief General-purpose utilities: errors, logging, observer/progress, strings, bitsets, and shared typedefs.

\defgroup points points
\brief 2D/3D point types and the functors that operate on them.

\defgroup stl stl
\brief Thin wrappers around standard containers to stabilize ABI across the suite.

\defgroup time time
\brief Calendar / Julian-date conversions.

\defgroup core_testing testing
\brief Test utilities shared with dependent libraries.
