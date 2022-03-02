import gettext

class Locale:
    def __init__(self, locale):
        self._locale = locale
        self._translation = None

    def __call__(self, message):
        if self._translation is None:
            self._translation = gettext.translation(self._locale)
        return self._translation.gettext(message)


def N_(message):
    return message