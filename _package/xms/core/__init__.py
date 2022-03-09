"""
The __init__.py for the core module of the xms.core library.
"""
import os

from . import filesystem  # NOQA: F401
from . import locale  # NOQA: F401
from . import misc  # NOQA: F401

__version__ = '6.0.0'

locale.add_message_path(
    os.path.join(
        os.path.abspath(os.path.dirname(__file__)),
        'locales'))
