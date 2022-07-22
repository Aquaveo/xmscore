"""Time conversion methods."""
# 1. Standard python modules
from datetime import datetime
from typing import Optional

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from .. import _xmscore

__copyright__ = "(C) Copyright Aquaveo 2022"
__license__ = "All rights reserved"


time_cpp = _xmscore.time


def julian_to_datetime(julian: float) -> Optional[datetime]:
    """Convert a Julian date and time floating point to a Python datetime.

    Args:
        julian (float): The Julian double to convert

    Returns:
        datetime.datetime: A Python datetime representing julian, or None if date is invalid.
    """
    result = time_cpp.tmJulianToCalendar(julian)
    if result is None:
        return None
    year, month, day, hour, minute, second = result
    return datetime(year=year, month=month, day=day,
                    hour=hour, minute=minute, second=second,
                    microsecond=0)


def datetime_to_julian(dt: datetime) -> Optional[float]:
    """Convert a Python datetime to a Julian double.

    Args:
        dt: A Python datetime to convert.

    Returns:
        The Julian floating point representation of the date.
    """
    julian = time_cpp.tmCalendarToJulian(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second)
    return julian
