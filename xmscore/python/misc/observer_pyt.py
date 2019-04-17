"""Test InterpLinear_py.cpp."""
import unittest
import time
from xmscore.misc import Observer


class MockObserver(Observer):
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
        print("*******updating time{}".format(remaining_seconds))
        self.status['remaining_seconds'] = remaining_seconds

    def time_elapsed_in_seconds(self, elapsed_seconds):
        self.status['elapsed_seconds'] = elapsed_seconds


class TestObserver(unittest.TestCase):
    """Test Observer Class."""

    def setUp(self):
        """Set up for each test case."""
        self.observer = MockObserver()

    def test_on_progress_status(self):
        percent_complete = 12
        self.observer.progress_status(percent_complete)
        self.assertEqual(percent_complete, self.observer.status['percent_complete'])

    def test_on_begin_operation_string(self):
        operation = 'count-jelly-beans'
        self.observer.begin_operation_string(operation)
        self.assertEqual(operation, self.observer.status['operation'])

    def test_on_end_operation(self):
        self.observer.end_operation()
        self.assertTrue(self.observer.status['operation_end'])

    def test_on_update_message(self):
        message = '21 jelly beans counted so far.'
        self.observer.update_message(message)
        self.assertEqual(message, self.observer.status['message'])

    def test_time_remaining_in_seconds(self):
        self.observer.begin_operation_string('Test Operation')
        time.sleep(0.1)
        self.observer.progress_status(0.2)
        remaining = self.observer.status['remaining_seconds']
        remaining_base = (self.observer.status['elapsed_seconds'] * 0.8) / 0.2
        DELTA = 1e-5
        self.assertAlmostEqual(remaining_base, remaining, delta=DELTA)

    def test_time_elapsed_in_seconds(self):
        self.observer.begin_operation_string('Test Operation')
        time.sleep(0.1)
        self.observer.progress_status(0.2)
        base_time_elapsed = (self.observer.status['remaining_seconds'] * 0.2) / 0.8
        time_elapsed = self.observer.status['elapsed_seconds']
        self.assertAlmostEqual(base_time_elapsed, time_elapsed, places=9)

    def test_progress_status_update(self):
        percent_complete = 12
        ret1 = self.observer.progress_status(percent_complete)
        self.assertTrue(ret1)
        self.assertEqual(percent_complete, self.observer.status['percent_complete'])

        updated_percent_complete = percent_complete + 0.03
        ret2 = self.observer.progress_status(updated_percent_complete)
        self.assertTrue(ret2)
        self.assertEqual(updated_percent_complete, self.observer.status['percent_complete'])

    def test_progress_status_no_update(self):
        percent_complete = 12
        ret1 = self.observer.progress_status(percent_complete)
        self.assertTrue(ret1)
        self.assertEqual(percent_complete, self.observer.status['percent_complete'])

        ret2 = self.observer.progress_status(percent_complete + 0.01)
        self.assertFalse(ret2)
        self.assertEqual(percent_complete, self.observer.status['percent_complete'])

    def test_begin_operation_string(self):
        operation = 'count-gum-balls'
        self.observer.begin_operation_string(operation)
        self.assertEqual(operation, self.observer.status['operation'])
        self.assertEqual(None, self.observer.status['percent_complete'])

    def test_end_operation(self):
        self.observer.end_operation()
        self.assertTrue(self.observer.status['operation_end'])

    def test_update_message(self):
        message = '21 jelly beans counted so far.'
        self.observer.update_message(message)
        self.assertEqual(message, self.observer.status['message'])


if __name__ == '__main__':
    unittest.main()
