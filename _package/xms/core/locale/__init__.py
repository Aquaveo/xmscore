"""
The __init__.py for the locale module of the xms.core library.
"""
from ._locale import n_, translate_for_domain  # NOQA: F401
from .._xmscore.locale import add_message_path, translate  # NOQA: F401
