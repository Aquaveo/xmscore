"""
Test progress_listener.py.
"""
import unittest

from xms.core.misc.progress_listener import set_listener_callback


class TestProgressListener(unittest.TestCase):
    """Test ProgressListener Class."""

    def test_on_begin_operation_string(self):
        """
        Test that beginning an operation reports the stack index it returns to the call back.
        """
        messages = []
        listener = set_listener_callback(messages.append)
        stack_index = listener.on_begin_operation_string('count-jelly-beans')
        self.assertEqual([('begin_operation', stack_index, 'count-jelly-beans')], messages)


if __name__ == '__main__':
    unittest.main()
