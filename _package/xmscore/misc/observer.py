from .._xmscore.misc import Observer as Obs


class Observer(Obs):
    """Mock Observer class for testing."""

    def __init__(self):
        super(Observer, self).__init__()

    def on_progress_status(self, percent_complete):
        self.on_progress_status(percent_complete)

    def on_begin_operation_string(self, operation):
        self.on_begin_operation_string(operation)

    def on_end_operation(self):
        self.on_end_operation()

    def on_update_message(self, message):
        self.on_update_message(message)

    def time_remaining_in_seconds(self, remaining_seconds):
        self.time_remaining_in_seconds(remaining_seconds)

    def time_elapsed_in_seconds(self, elapsed_seconds):
        self.time_elapsed_in_seconds(elapsed_seconds)
