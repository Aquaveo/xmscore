"""
The Observer class for the xms.core library.
"""
from .._xmscore.misc import Observer as Obs


class Observer(Obs):
    """
    Mock Observer class for testing.
    """
    def __init__(self):
        """
        The __init__ function for the Observer class.
        """
        super(Observer, self).__init__()

    def on_progress_status(self, percent_complete):
        """
        Captures the progress of an operation.

        Args:
            percent_complete (float):  The percent complete
        """
        pass

    def on_begin_operation_string(self, operation):
        """
        The operation string.

        Args:
            operation: Name of the operation being monitored.
        """
        pass

    def on_end_operation(self):
        """
        The end operation event.
        """
        pass

    def on_update_message(self, message):
        """
        When update message has been sent.

        Args:
            message: The new message
        """
        pass

    def time_remaining_in_seconds(self, remaining_seconds):
        """
        Sets the time remaining in seconds.

        Args:
            remaining_seconds (Float): The time remaining for the current operation that the class is observing.
        """
        pass

    def time_elapsed_in_seconds(self, elapsed_seconds):
        """
        Sets the time elapsed since the operation began.

        Args:
            elapsed_seconds (Float): The elapsed time since the operation began.
        """
        pass
