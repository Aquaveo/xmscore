"""
The Observer class for the xms.core library.
"""
from .._xmscore.misc import ProgressListener as Prog


def set_listener_callback(call_back):
    """Sets a call back method that is called by the progress listener class.

    Args:
        call_back (callable): takes a tuple (string, int, string) (msg_type, stack_index, message)

    Returns:
         (ProgressListener): this class with the call back set
    """
    p = ProgressListener()
    p.call_back = call_back
    return p


class ProgressListener(Prog):
    """
    Mock Observer class for testing.
    """
    def __init__(self):
        """
        The __init__ function for the Observer class.
        """
        super().__init__()

    def on_progress_status(self, stack_index, percent_complete):
        """
        Captures the progress of an operation.

        Args:
            stack_index (int): stack index for the progress
            percent_complete (float):  The percent complete
        """
        msg = f'Percent complete {int(100 * percent_complete)}'
        self.call_back(('progress_status', stack_index, msg))

    def on_begin_operation_string(self, operation):
        """
        The operation string.

        Args:
            operation: Name of the operation being monitored.

        Returns:
            (int): stack index for the operation
        """
        stack_index = self.on_begin_operation_string(operation)
        self.call_back(('begin_operation', stack_index, operation))
        return stack_index

    def on_end_operation(self, stack_index):
        """
        The end operation event.
        """
        self.call_back(('end_operation', stack_index, ''))

    def on_update_message(self, stack_index, message):
        """
        When update message has been sent.

        Args:
            stack_index (int): stack index for the progress
            message: The new message
        """
        self.call_back(('update_message', -1, message))

    def call_back(self, msg_tuple):
        """Convenience function.

        Args:
            msg_tuple (tuple(str, int, str)): msg_type, stack_index, message
        """
        pass
