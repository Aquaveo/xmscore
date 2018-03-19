xmscore {#mainpage}
============
\tableofcontents

xmscore {#xmscore}
============

Introduction {#Introduction}
------------

xmscore is a support library for xms libraries and products.

<table align="center" border="0">
  <tr>
    <td>![](./html/images/Aquaveo_Logo.png)</td>
  </tr>
</table>

License {#License}
-------

The code is distributed under the xmsng Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at [http://www.aquaveo.com/xmsng/LICENSE_1_0.txt](http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)). 

Testing {#Testing}
-------

The code has numerous unit tests which use the [CxxTest](http://cxxtest.com/) framework. A good way to see how to use the code is to look at the unit tests. Unit tests are located at the bottom of .cpp files within a "#if CXX_TEST" code block. Header files that are named with ".t.h" contain the test suite class definitions.

The Code {#TheCode}
--------
### Namespaces {#Namespaces}
* "xms" - Most code is in this namespace. The use of other namespaces is kept to a minimum. Two-letter prefixes are used as "pseudo-namespaces" in code modules. Preprocessor macros typically start with "XM_" to prevent name collisions.
* "xmt" - Testing code will be put into this namespace once CXX_TEST is upgraded such that it will find the testing code in this namespace.

"xmscore" Name {#xmscoreName}
------------
The name "xmscore" comes from the "XMS" (GMS, SMS, WMS) water modeling software created by Aquaveo.
