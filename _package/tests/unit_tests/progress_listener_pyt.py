"""
Test progress_listener.py.
"""
import unittest

from xms.core.misc.progress_listener import set_listener_callback


class TestProgressListener(unittest.TestCase):
    """Test ProgressListener Class."""

    def test_on_begin_operation_string(self):
        """
        Test that beginning an operation returns and reports stack index 1 for the outermost operation.
        """
        messages = []
        listener = set_listener_callback(messages.append)
        self.assertEqual(1, listener.on_begin_operation_string('count-jelly-beans'))
        self.assertEqual([('begin_operation', 1, 'count-jelly-beans')], messages)

    def test_nested_operations(self):
        """
        Test that the begin stack index tracks how many operations are in flight.
        """
        messages = []
        listener = set_listener_callback(messages.append)
        listener.on_begin_operation_string('count-jelly-beans')
        listener.on_begin_operation_string('count-red-jelly-beans')
        listener.on_end_operation(2)
        listener.on_begin_operation_string('count-green-jelly-beans')
        expected = [
            ('begin_operation', 1, 'count-jelly-beans'),
            ('begin_operation', 2, 'count-red-jelly-beans'),
            ('end_operation', 2, ''),
            ('begin_operation', 2, 'count-green-jelly-beans'),
        ]
        self.assertEqual(expected, messages)


if __name__ == '__main__':
    unittest.main()
