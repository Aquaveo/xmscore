from .._xmscore import misc as xm


class Observer(xm.Observer):
    """Mock Observer class for testing."""

    def __init__(self, instance=None):
        if instance:
            self._instance = instance
        else:
            self._instance = xm.Observer()

    def on_progress_status(self, percent_complete):
        self._instance.on_progress_status(percent_complete)

    def on_begin_operation_string(self, operation):
        self._instance.on_begin_operation_string(operation)

    def on_end_operation(self):
        self._instance.on_end_operation()

    def on_update_message(self, message):
        self._instance.on_end_operation()

    def time_remaining_in_seconds(self, remaining_seconds):
        self._instance.time_remaining_in_seconds(remaining_seconds)

    def time_elapsed_in_seconds(self, elapsed_seconds):
        self._instance.time_elapsed_in_seconds(elapsed_seconds)