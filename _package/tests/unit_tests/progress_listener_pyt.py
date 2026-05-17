"""For testing the Python ProgressListener wrapper module."""
# 1. Standard python modules
import unittest

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms.core.misc.progress_listener import ProgressListener, set_listener_callback

__copyright__ = "(C) Copyright Aquaveo 2026"
__license__ = "All rights reserved"


# NOTE on the deliberately-uncovered lines in progress_listener.py:
#
#   ProgressListener.on_begin_operation_string (line 61) self-recursively calls
#   ``self.on_begin_operation_string(operation)`` inside its own body.  Invoking
#   it from Python would recurse until the stack overflows, so we do not call
#   it here.  This pattern matches the also-untested bodies in observer.py
#   (Observer.on_progress_status and siblings).  Those self-recursive bodies
#   look like a production-code bug and have been flagged to a developer for
#   review; once corrected, they should be added to coverage.


class ProgressListenerTests(unittest.TestCase):
    """Direct tests of the Python-side ProgressListener wrapper.

    These tests deliberately exercise the Python methods themselves rather
    than going through the C++ engine that normally dispatches the
    callbacks.  The wrappers are simple — they format a message and forward
    it to ``call_back`` — so calling them directly is the most precise way
    to cover them.
    """

    def setUp(self):
        """Capture call_back invocations into ``self.messages`` for assertions."""
        self.messages = []
        self.listener = ProgressListener()
        self.listener.call_back = self.messages.append  # type: ignore[assignment]

    def test_init_constructs_default_instance(self):
        """A bare ProgressListener can be constructed (covers ``__init__`` body)."""
        # Re-instantiate locally so we are not relying on setUp side effects.
        listener = ProgressListener()
        self.assertIsInstance(listener, ProgressListener)

    def test_set_update_delay_seconds_delegates_to_super(self):
        """set_update_delay_seconds() should accept an int delay without raising."""
        # The override forwards to the C++ implementation; we only need the call
        # to complete without error to cover the wrapper body.
        self.listener.set_update_delay_seconds(0)

    def test_on_progress_status_emits_formatted_message(self):
        """on_progress_status formats the percent and calls call_back."""
        self.listener.on_progress_status(3, 0.5)
        self.assertEqual([('progress_status', 3, 'Percent complete 50')], self.messages)

    def test_on_end_operation_emits_end_message(self):
        """on_end_operation forwards an 'end_operation' tuple to call_back."""
        self.listener.on_end_operation(7)
        self.assertEqual([('end_operation', 7, '')], self.messages)

    def test_on_update_message_emits_update_tuple(self):
        """on_update_message forwards an 'update_message' tuple to call_back."""
        self.listener.on_update_message(2, 'half done')
        # The wrapper uses a sentinel stack index of -1 for update messages.
        self.assertEqual([('update_message', -1, 'half done')], self.messages)

    def test_default_call_back_is_a_no_op(self):
        """The default ProgressListener.call_back returns None and raises nothing."""
        # Re-use the default (unassigned) call_back from a freshly-built instance.
        listener = ProgressListener()
        self.assertIsNone(listener.call_back(('anything', 0, 'message')))

    def test_set_listener_callback_returns_configured_instance(self):
        """set_listener_callback() returns a ProgressListener with the supplied call_back."""
        received = []

        def my_cb(msg_tuple):
            received.append(msg_tuple)

        listener = set_listener_callback(my_cb)
        self.assertIsInstance(listener, ProgressListener)
        self.assertIs(my_cb, listener.call_back)
        # Confirm the wiring works end-to-end via on_update_message.
        listener.on_update_message(0, 'wired')
        self.assertEqual([('update_message', -1, 'wired')], received)


if __name__ == '__main__':
    unittest.main()
