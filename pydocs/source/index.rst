.. image:: _static/aquaveo.png
   :height: 35px
   :width: 250px
   :align: right

*****************
XmsCore |version|
*****************

The xmscore library is a support library for other Aquaveo products. It contains
classes and helpers used across the XMS family of libraries (xmsinterp, xmsmesh,
xmsgrid, xmsstamper, etc.). The Python bindings expose the subset of xmscore
that is useful from Python tooling and tests.

Index
=====

**Getting Started**

* :doc:`getting_started`

.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Getting Started

   getting_started.rst

**misc**

The ``misc`` package contains general-purpose utilities. The
:class:`Observer <xms.core.misc.Observer>` and
:class:`ProgressListener <xms.core.misc.ProgressListener>` classes are used by
other Aquaveo libraries to report progress and status messages from
long-running operations.

* :doc:`modules/misc/Observer`
* :doc:`modules/misc/ProgressListener`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: misc

   modules/misc/Observer.rst
   modules/misc/ProgressListener.rst

**filesystem**

The ``filesystem`` package contains path and directory utilities shared across
XMS Python applications.

* :doc:`modules/filesystem/filesystem`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: filesystem

   modules/filesystem/filesystem.rst

**time**

The ``time`` package converts between XMS Julian time values and Python
:class:`datetime.datetime` objects.

* :doc:`modules/time/time_conversion`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: time

   modules/time/time_conversion.rst

Acknowledgements
================

This library is from work done by Aquaveo developers to support other Aquaveo
libraries.
