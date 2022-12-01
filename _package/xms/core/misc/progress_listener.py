"""
The Observer class for the xms.core library.
"""
from .._xmscore.misc import ProgressListener as Prog


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
        self.on_progress_status(stack_index, percent_complete)
        msg = f'Percent complete {int(100 * percent_complete)}'
        self.message_received('progress_status', stack_index, msg)

    def on_begin_operation_string(self, operation):
        """
        The operation string.

        Args:
            operation: Name of the operation being monitored.

        Returns:
            (int): stack index for the operation
        """
        stack_index = self.on_begin_operation_string(operation)
        self.message_received('begin_operation', stack_index, operation)
        return stack_index

    def on_end_operation(self, stack_index):
        """
        The end operation event.
        """
        self.on_end_operation(stack_index)
        self.message_received('end_operation', stack_index, '')

    def on_update_message(self, stack_index, message):
        """
        When update message has been sent.

        Args:
            stack_index (int): stack index for the progress
            message: The new message
        """
        self.on_update_message(stack_index, message)
        self.message_received('update_message', -1, message)

    def message_received(self, msg_type, stack_index, message):
        """Convenience function.

        Args:
            msg_type (str): type of message
            stack_index (int): stack index for the progress
            message: The new message
        """
        pass