"""For testing the locale module."""
# 1. Standard python modules
import unittest

# 4. Local modules
from xms.core.locale import n_, translate_for_domain, xmscore as _

# 2. Third party modules
# 3. Aquaveo modules

__copyright__ = "(C) Copyright Aquaveo 2019"
__license__ = "All rights reserved"


class LocaleUnitTests(unittest.TestCase):
    """Tests functions in locale module."""
    def test_marked_untranslated(self):
        """Translate a marked string with no translation."""
        expected = (
            "This message should not be modified by documentation.\n"
            "It is used for testing marked messages with no modifications.\n"
            "Modifying it will cause tests to fail.\n")
        translated = _("This message should not be modified by documentation.\n"
                       "It is used for testing marked messages with no modifications.\n"
                       "Modifying it will cause tests to fail.\n")

        self.assertEqual(expected, translated)

    def test_marked_translated(self):
        """Translate a marked string with a translation."""
        expected = (
            "This message should not be modified by documentation.\n"
            "It is used for testing marked messages with a modification.\n"
            "Modifying it will cause tests to fail.\n"
            "Specifically, it will cause testMarkedTranslated to fail.\n")
        translated = _("This message should not be modified by documentation.\n"
                       "It is used for testing marked messages with a modification.\n"
                       "Modifying it will cause tests to fail.\n")

        self.assertEqual(expected, translated)

    def test_unmarked(self):
        """Translate an unmarked string."""
        expected = (
            "This message should not be modified by documentation.\n"
            "It is used for testing modification of unmarked messages.\n"
            "Modifying it will cause tests to fail.\n")
        translated = translate_for_domain('xmscore')(
            "This message should not be modified by documentation.\n"
            "It is used for testing modification of unmarked messages.\n"
            "Modifying it will cause tests to fail.\n")

        self.assertEqual(expected, translated)

    def test_null_marked(self):
        """Translate a null-marked string."""
        expected = \
            "This message should not be modified by documentation.\n" \
            "It is used for testing modification of null-marked messages.\n" \
            "Modifying it will cause tests to fail.\n"
        translated = \
            n_("This message should not be modified by documentation.\n"
               "It is used for testing modification of null-marked messages.\n"
               "Modifying it will cause tests to fail.\n")

        self.assertEqual(expected, translated)
