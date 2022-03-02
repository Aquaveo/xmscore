import gettext

class Locale:
    """
    A localization class.
    """
    def __init__(self):
        """
        Initialize the Locale.
        """
        self._locale = locale
        self._translation = None

    def __call__(self, message):
        """
        Translate a message.

        Args:
            message: The message to translate.

        Returns:
            A translated version of the message if available,
            or the unmodified message otherwise.
        """
        if self._translation is None:
            self._translation = gettext.translation("en_US")
        return self._translation.gettext(message)


def N_(message):
    """
    A null translator.

    Use this to mark messages that should not be translated, so
    other developers know not to mark it translatable.

    Args:
        message: The message to not translate.

    Returns:
        The message, untranslated.
    """
    return message
