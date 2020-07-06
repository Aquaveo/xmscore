"""For testing the filesystem module."""
# 1. Standard python modules
import os
import shutil
import tempfile
import unittest

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms.core.filesystem import filesystem

__copyright__ = "(C) Copyright Aquaveo 2019"
__license__ = "All rights reserved"


class FilesystemTests(unittest.TestCase):
    """Tests functions in filesystem.py."""
    def test_file_prefix(self):
        """Tests filesystem.file_prefix()."""
        # 'C:\\temp\\dummy.ext.txt' doesn't work on linux
        str = os.path.join('C:', 'temp', 'dummy.txt')
        self.assertEqual(filesystem.file_prefix(str), 'dummy')
        # 'C:\\temp\\dummy.ext.txt' doesn't work on linus
        str = os.path.join('C:', 'temp', 'dummy.ext.txt')
        self.assertEqual(filesystem.file_prefix(str), 'dummy.ext')
        self.assertEqual(filesystem.file_prefix('C:/temp/dummy.txt'), 'dummy')
        self.assertEqual(filesystem.file_prefix('dummy.txt'), 'dummy')
        self.assertEqual(filesystem.file_prefix(''), '')

    def test_temp_filename(self):
        """Tests filesystem.temp_filename()."""
        # With no args
        f = filesystem.temp_filename()
        self.assertTrue(f)

        # With dir arg
        d = tempfile.mkdtemp()
        f = filesystem.temp_filename(dir=d)
        self.assertEqual(os.path.normpath(os.path.dirname(f)), os.path.normpath(d))

        # With suffix arg
        f = filesystem.temp_filename(suffix='.suffix_test')
        extension = os.path.splitext(f)[1]
        self.assertEqual('.suffix_test', extension)

        # With XMS_PYTHON_APP_TEMP_DIRECTORY environment variable
        d = tempfile.mkdtemp()
        os.environ['XMS_PYTHON_APP_TEMP_DIRECTORY'] = d
        f = filesystem.temp_filename()
        os.environ.pop('XMS_PYTHON_APP_TEMP_DIRECTORY')
        self.assertEqual(os.path.normpath(os.path.dirname(f)), os.path.normpath(d))

        shutil.rmtree(d)
