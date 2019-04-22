Installation
------------

XmsCore can be installed using `Anaconda <https://www.anaconda.com/download/>`_.

You can install XmsCore using the `conda <https://www.anaconda.com/download/>`_ command::

   conda install -c aquaveo xmscore

This will install XmsCore and **all** the needed dependencies.


Usage
-----

Currently the xmscore python library only has one public interface. The :class:`Observer <xmscore.misc.observer>`
interface is used by some of the classes in other aquaveo libraries to help determine progress of certain work
flows. The :class:`Observer <xmscore.misc.observer>` class has several functions that you can override to get
the progress from functions that accept an Observer object.

.. code-block:: python

    from xmscore.misc import Observer

    class ExampleObserver(Observer):
        """Mock Observer class for testing."""

        def __init__(self):
            self.status = {
                'operation': None,
                'operation_end': False,
                'operation_begin': False,
                'percent_complete': None,
                'message': '',
                'remaining_seconds': None,
                'elapsed_seconds': None
            }
            super(MockObserver, self).__init__()

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

This example :class:`Observer <xmscore.misc.Observer>` can be passed to other classes/functions such
as :func:`set_observer <xmsinterp.interpolate.InterpIdw.set_observer>` function of the
:class:`InterpIdw <xmsinterp.interpolate.InterpIdw>` class. As the interp class goes through
operations, this example observer will update the dictionary and you can retrieve the desired data.
