xmscore {#mainpage}
============
\tableofcontents

xmscore {#xmscore}
============

Introduction {#XmscoreIntroduction}
------------

xmscore is a support library for xms libraries and products.

<table align="center" border="0">
  <tr>
    <td>![](Aquaveo_Logo.png)</td>
  </tr>
</table>

License {#XmscoreLicense}
-------

The code is distributed under the FreeBSD Software License. (See accompanying file LICENSE or copy at [http://www.aquaveo.com/bsd/LICENSE.txt](http://www.aquaveo.com/bsd/license.txt)). 

Python
------

This library is available as a python module. See [Python Documentation](./pydocs)

Testing {#XmscoreTesting}
-------

The code has numerous unit tests which use the [CxxTest](http://cxxtest.com/) framework. A good way to see how to use the code is to look at the unit tests. Unit tests are located at the bottom of .cpp files within a "#if CXX_TEST" code block. Header files that are named with ".t.h" contain the test suite class definitions.

The Code {#XmscoreTheCode}
--------
### Namespaces {#XmscoreNamespaces}
* "xms" - Most code is in this namespace. The use of other namespaces is kept to a minimum. Two-letter prefixes are used as "pseudo-namespaces" in code modules. Preprocessor macros typically start with "XM_" to prevent name collisions.
* "xmt" - Testing code will be put into this namespace once CXX_TEST is upgraded such that it will find the testing code in this namespace.

"xmscore" Name {#xmscoreName}
------------
The name "xmscore" comes from the "XMS" (GMS, SMS, WMS) water modeling software created by Aquaveo.
