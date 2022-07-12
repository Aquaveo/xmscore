"""For testing the time_conversion module."""
# 1. Standard python modules
import datetime
import unittest

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms.core.time import datetime_to_julian, julian_to_datetime

__copyright__ = "(C) Copyright Aquaveo 2019"
__license__ = "All rights reserved"


class TimeConversionTests(unittest.TestCase):
    """Tests functions in time_conversion.py."""
    def test_datetime_to_julian(self):
        """Test conversions between Julian to calendar date and times."""
        date_time = datetime.datetime(year=2004, month=6, day=3, hour=2, minute=8, second=32)
        julian = datetime_to_julian(date_time)
        self.assertEqual(2453159.5892592594, julian)

    def test_julian_to_datetime(self):
        """Test conversions between Julian to calendar date and times."""
        date_time = julian_to_datetime(2453159.5892592594)
        expected_date_time = datetime.datetime(year=2004, month=6, day=3, hour=2, minute=8, second=32)
        self.assertEqual(expected_date_time, date_time)
