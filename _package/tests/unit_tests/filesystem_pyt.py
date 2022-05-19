"""For testing the filesystem module."""
# 1. Standard python modules
import os
import platform
import shutil
import tempfile
import unittest

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms.core.filesystem import filesystem
from xms.core.filesystem.filesystem import compute_relative_path
from xms.core.filesystem.filesystem import resolve_relative_path

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

    def test_make_filename_unique(self):
        """See name."""
        # Create a temporary directory to do our test in
        with tempfile.TemporaryDirectory() as directory:
            filepath = os.path.join(directory, 'make_unique.html')

            # Verify that make_filename_unique just returns the filename if it doesn't exist
            self.assertEqual(False, os.path.exists(filepath))
            filepath_unique = filesystem.make_filename_unique(filepath)
            self.assertEqual(filepath, filepath_unique)

            # Verify that make_filename_unique returns a unique filename if it does exist
            with open(filepath, 'w'):
                self.assertEqual(True, os.path.exists(filepath))
                filepath_unique = filesystem.make_filename_unique(filepath)
                self.assertEqual(os.path.dirname(filepath), os.path.dirname(filepath_unique))
                self.assertEqual('make_unique(2).html', os.path.basename(filepath_unique))

                # Verify that it will loop until it finds a unique name
                with open(filepath_unique, 'w'):
                    self.assertEqual(True, os.path.exists(filepath_unique))
                    filepath_unique2 = filesystem.make_filename_unique(filepath)
                    self.assertEqual(os.path.dirname(filepath), os.path.dirname(filepath_unique2))
                    self.assertEqual('make_unique(3).html', os.path.basename(filepath_unique2))

    def test_compute_relative_path(self):
        """See name."""
        if platform.system() == 'Windows':
            self.assertEqual('my_file.txt', compute_relative_path('C:\\temp', 'C:\\temp\\my_file.txt'))
            self.assertEqual("model/filename.txt", compute_relative_path('C:\\temp', "C:\\temp\\model\\filename.txt"))
            self.assertEqual("../filename.txt", compute_relative_path('\\\\maple\\c\\temp\\model',
                                                                      "\\\\maple\\c\\temp\\filename.txt"))
            self.assertEqual('D:/temp/my_file.txt', compute_relative_path('C:\\temp', 'D:\\temp\\my_file.txt'))
        else:
            self.assertEqual('my_file.txt', compute_relative_path('/temp', '/temp/my_file.txt'))
            self.assertEqual("model/filename.txt", compute_relative_path('/temp', "/temp/model/filename.txt"))
            self.assertEqual("../filename.txt", compute_relative_path('/maple/c/temp/model',
                                                                      "/maple/c/temp/filename.txt"))

    def test_resolve_relative_path(self):
        """See name."""
        if platform.system() == 'Windows':
            self.assertEqual("C:\\MP3DU\\test1\\project\\project.mfs", resolve_relative_path("C:\\MP3DU/test1/",
                                                                                             ".\\project\\project.mfs"))
            self.assertEqual("C:\\temp\\filename.txt", resolve_relative_path("C:\\temp", "filename.txt"))
            self.assertEqual("C:\\temp\\model\\filename.txt", resolve_relative_path("C:\\temp",
                                                                                    ".\\model\\filename.txt"))
            self.assertEqual("C:\\temp\\filename.txt", resolve_relative_path("C:\\temp\\model", "..\\filename.txt"))
            self.assertEqual("\\\\maple\\c\\temp\\filename.txt", resolve_relative_path("\\\\maple\\c\\temp\\model",
                                                                                       "..\\filename.txt"))
            self.assertEqual("D:\\temp\\filename.txt", resolve_relative_path("C:\\temp", "D:\\temp\\filename.txt"))
        else:
            self.assertEqual("/MP3DU/test1/project/project.mfs", resolve_relative_path("/MP3DU/test1/",
                                                                                       "./project/project.mfs"))
            self.assertEqual("/temp/filename.txt", resolve_relative_path("/temp", "filename.txt"))
            self.assertEqual("/temp/model/filename.txt", resolve_relative_path("/temp", "./model/filename.txt"))
            self.assertEqual("/temp/filename.txt", resolve_relative_path("/temp/model", "../filename.txt"))
            self.assertEqual("/maple/c/temp/filename.txt", resolve_relative_path("/maple/c/temp/model",
                                                                                 "../filename.txt"))