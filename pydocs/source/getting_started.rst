***************
Getting Started
***************

Installation
============

XmsCore can be installed using `Anaconda <https://www.anaconda.com/download/>`_::

   conda install -c aquaveo xmscore

This installs ``xms.core`` and all of its dependencies.

Package Layout
==============

The Python package is split into a handful of small subpackages, each of which
mirrors a directory in the C++ library:

.. list-table::
   :header-rows: 1
   :widths: 25 75

   * - Subpackage
     - Purpose
   * - :mod:`xms.core.misc`
     - Progress and observer interfaces used by long-running XMS operations.
   * - :mod:`xms.core.filesystem`
     - Cross-platform path and directory helpers used across the XMS Python
       applications.
   * - :mod:`xms.core.time`
     - Conversions between Julian floating-point time and
       :class:`datetime.datetime`.

Observing Progress
==================

The :class:`Observer <xms.core.misc.Observer>` interface is used by many XMS
classes (for example :class:`InterpIdw <xmsinterp.interpolate.InterpIdw>`) to
report progress. Subclass it and pass an instance to the consumer:

.. code-block:: python

    from xms.core.misc import Observer

    class ExampleObserver(Observer):
        """Observer that records progress events into a dictionary."""

        def __init__(self):
            super().__init__()
            self.status = {
                'operation': None,
                'operation_begin': False,
                'operation_end': False,
                'percent_complete': None,
                'message': '',
                'remaining_seconds': None,
                'elapsed_seconds': None,
            }

        def on_progress_status(self, percent_complete):
            self.status['percent_complete'] = percent_complete

        def on_begin_operation_string(self, operation):
            self.status['operation_begin'] = True
            self.status['operation'] = operation

        def on_end_operation(self):
            self.status['operation_end'] = True

        def on_update_message(self, message):
            self.status['message'] = message

        def time_remaining_in_seconds(self, remaining_seconds):
            self.status['remaining_seconds'] = remaining_seconds

        def time_elapsed_in_seconds(self, elapsed_seconds):
            self.status['elapsed_seconds'] = elapsed_seconds

For applications that need to receive progress messages from nested operations,
use :class:`ProgressListener <xms.core.misc.ProgressListener>`. It exposes a
``stack_index`` for each in-flight operation so that a UI can show a stack of
progress bars. Constructing a ``ProgressListener`` registers it as the active
process-wide listener, so subsequent XMS operations route their events through
its callback. The :func:`set_listener_callback
<xms.core.misc.progress_listener.set_listener_callback>` helper builds and
returns one wired to a single callable:

.. code-block:: python

    from xms.core.misc.progress_listener import set_listener_callback

    def on_event(msg):
        msg_type, stack_index, message = msg
        print(f'[{stack_index}] {msg_type}: {message}')

    # Keep `listener` alive — when it goes out of scope no further events fire.
    listener = set_listener_callback(on_event)

Filesystem Helpers
==================

:mod:`xms.core.filesystem.filesystem` provides path utilities that behave
consistently on Windows and POSIX:

.. code-block:: python

    from xms.core.filesystem import filesystem as fs

    fs.make_or_clear_dir('/tmp/xms-output')
    fs.copyfile('input.h5', '/tmp/xms-output/input.h5')

    rel = fs.compute_relative_path('/data/projects', '/data/projects/run/output.h5')
    # 'run/output.h5' on both Windows and Linux

Time Conversions
================

XMS uses Julian floating-point time internally. Convert to and from Python
``datetime`` with :mod:`xms.core.time`:

.. code-block:: python

    from datetime import datetime
    from xms.core.time import datetime_to_julian, julian_to_datetime

    julian = datetime_to_julian(datetime(2024, 1, 15, 12, 0, 0))
    when = julian_to_datetime(julian)
