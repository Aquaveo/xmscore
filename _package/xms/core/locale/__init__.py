"""
The __init__.py for the locale module of the xms.core library.
"""
from .._xmscore.locale import add_message_path, add_text_domain, translate

def n_(message):
    return message