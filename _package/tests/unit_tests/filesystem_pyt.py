"""For testing the filesystem module."""
# 1. Standard python modules
import filecmp
import os
from pathlib import Path
import platform
import shutil
import tempfile
import unittest
import uuid

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms.core.filesystem import filesystem
from xms.core.filesystem.filesystem import (clear_folder, compute_relative_path, copyfile,
                                            is_somewhere_below_system_temp, make_or_clear_dir,
                                            paths_are_equal, removefile, resolve_relative_path)

__copyright__ = "(C) Copyright Aquaveo 2019"
__license__ = "All rights reserved"


class FilesystemTests(unittest.TestCase):
    """Tests functions in filesystem.py."""
    def test_file_prefix(self):
        """Tests filesystem.file_prefix()."""
        if platform.system() == 'Windows':
            paths = [
                ('C:\\temp\\dummy.txt', 'dummy'),
                ('C:\\temp\\dummy.ext.txt', 'dummy.ext'),
                ('C:/temp/dummy.txt', 'dummy'),
                ('dummy.txt', 'dummy'),
                ('', ''),
            ]
        else:
            paths = [
                ('dummy', '/temp/dummy.txt'),
                ('dummy.ext', '/temp/dummy.ext.txt'),
                ('dummy', 'dummy.txt'),
                ('', ''),
            ]
        for input, result in paths:
            self.assertEqual(result, filesystem.file_prefix(input))  # Test using str
            self.assertEqual(result, filesystem.file_prefix(Path(input)))  # Test using pathlib

    def test_temp_filename(self):
        """Tests filesystem.temp_filename()."""
        # With no args
        f = filesystem.temp_filename()
        self.assertTrue(f)

        # With dir arg
        d = tempfile.mkdtemp()
        f = filesystem.temp_filename(dir=d)  # Test using str
        self.assertEqual(os.path.normpath(os.path.dirname(f)), os.path.normpath(d))
        f = filesystem.temp_filename(dir=Path(d))  # Test using pathlib
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
            filepath_unique = filesystem.make_filename_unique(filepath)  # Test using str
            self.assertEqual(filepath, filepath_unique)
            filepath_unique = filesystem.make_filename_unique(filepath)  # Test using pathlib
            self.assertEqual(filepath, filepath_unique)

            # Verify that make_filename_unique returns a unique filename if it does exist
            with open(filepath, 'w'):
                self.assertEqual(True, os.path.exists(filepath))
                filepath_unique = filesystem.make_filename_unique(filepath)  # Test using str
                self.assertEqual(os.path.dirname(filepath), os.path.dirname(filepath_unique))
                self.assertEqual('make_unique(2).html', os.path.basename(filepath_unique))
                filepath_unique = filesystem.make_filename_unique(Path(filepath))  # Test using pathlib
                self.assertEqual(os.path.dirname(filepath), os.path.dirname(filepath_unique))
                self.assertEqual('make_unique(2).html', os.path.basename(filepath_unique))

                # Verify that it will loop until it finds a unique name
                with open(filepath_unique, 'w'):
                    self.assertEqual(True, os.path.exists(filepath_unique))
                    filepath_unique2 = filesystem.make_filename_unique(filepath)  # Test using str
                    self.assertEqual(os.path.dirname(filepath), os.path.dirname(filepath_unique2))
                    self.assertEqual('make_unique(3).html', os.path.basename(filepath_unique2))
                    filepath_unique2 = filesystem.make_filename_unique(Path(filepath))  # Test using pathlib
                    self.assertEqual(os.path.dirname(filepath), os.path.dirname(filepath_unique2))
                    self.assertEqual('make_unique(3).html', os.path.basename(filepath_unique2))

    def test_compute_relative_path(self):
        """See name."""
        if platform.system() == 'Windows':
            # path, file, result
            paths = [
                ('C:\\temp', 'C:\\temp\\my_file.txt', 'my_file.txt'),
                ('C:\\temp', "C:\\temp\\model\\filename.txt", "model/filename.txt"),
                ('\\\\maple\\c\\temp\\model', "\\\\maple\\c\\temp\\filename.txt", "../filename.txt"),
                ('C:\\temp', 'D:\\temp\\my_file.txt', 'D:/temp/my_file.txt')
            ]
        else:
            # path, file, result
            paths = [
                ('/temp', '/temp/my_file.txt', 'my_file.txt'),
                ('/temp', "/temp/model/filename.txt", "model/filename.txt"),
                ('/maple/c/temp/model', "/maple/c/temp/filename.txt", "../filename.txt")
            ]
        for absolute, relative, result in paths:
            self.assertEqual(result, compute_relative_path(absolute, relative))  # Test using str
            self.assertEqual(result, compute_relative_path(Path(absolute), Path(relative)))  # Test using pathlib

    def test_resolve_relative_path(self):
        """See name."""
        if platform.system() == 'Windows':
            # absolute_path, relative_path, result
            paths = [
                ("C:\\MP3DU/test1/", ".\\project\\project.mfs", "C:\\MP3DU\\test1\\project\\project.mfs"),
                ("C:\\temp", "filename.txt", "C:\\temp\\filename.txt"),
                ("C:\\temp", ".\\model\\filename.txt", "C:\\temp\\model\\filename.txt"),
                ("C:\\temp\\model", "..\\filename.txt", "C:\\temp\\filename.txt"),
                ("\\\\maple\\c\\temp\\model", "..\\filename.txt", "\\\\maple\\c\\temp\\filename.txt"),
                ("C:\\temp", "D:\\temp\\filename.txt", "D:\\temp\\filename.txt"),
            ]
        else:
            # absolute_path, relative_path, result
            paths = [
                ("/MP3DU/test1/", "./project/project.mfs", "/MP3DU/test1/project/project.mfs"),
                ("/temp", "filename.txt", "/temp/filename.txt"),
                ("/temp", "./model/filename.txt", "/temp/model/filename.txt"),
                ("/temp/model", "../filename.txt", "/temp/filename.txt"),
                ("/maple/c/temp/model", "../filename.txt", "/maple/c/temp/filename.txt")
            ]
        for absolute, relative, result in paths:
            self.assertEqual(result, resolve_relative_path(absolute, relative))  # Test using str
            self.assertEqual(result, resolve_relative_path(Path(absolute), Path(relative)))  # Test using pathlib

    def test_clear_folder(self):
        """Tests filesystem.clear_folder()."""
        # Test using str
        d = tempfile.mkdtemp()
        temp_file = tempfile.TemporaryFile(mode='w', dir=d)
        assert Path(temp_file).is_file()
        clear_folder(d)
        assert not Path(temp_file).is_file()

        # Test using pathlib
        temp_file = tempfile.TemporaryFile(mode='w', dir=d)
        assert Path(temp_file).is_file()
        clear_folder(Path(d))
        assert not Path(temp_file).is_file()

        shutil.rmtree(d)

    def test_make_or_clear_dir(self):
        """Tests filesystem.make_or_clear_dir()."""
        d = tempfile.mkdtemp()
        dir1 = str(uuid.uuid4())
        dir2 = str(uuid.uuid4())

        # Test using str
        path = os.path.join(d, dir1, dir2)
        assert not Path(path).is_dir()
        make_or_clear_dir(path)
        assert Path(path).is_dir()
        temp_file = tempfile.TemporaryFile(mode='w', dir=path)
        assert Path(temp_file).is_file()
        make_or_clear_dir(path)
        assert not Path(temp_file).is_file()
        assert Path(path).is_dir()
        Path(path).unlink()

        # Test using pathlib
        path = Path(d) / dir1 / dir2
        assert not path.is_dir()
        make_or_clear_dir(path)
        assert path.is_dir()
        temp_file = tempfile.TemporaryFile(mode='w', dir=path)
        assert Path(temp_file).is_file()
        make_or_clear_dir(path)
        assert not Path(temp_file).is_file()
        assert path.is_dir()
        path.unlink()

        shutil.rmtree(d)

    def test_paths_are_equal(self):
        """Tests filesystem.paths_are_equal()."""
        if platform.system() == 'Windows':
            path1 = 'C:\\temp\\bob.txt'
            path2 = 'C:\\temp\\bob.txt'
            assert paths_are_equal(path1, path2)  # Test using str
            assert paths_are_equal(Path(path1), Path(path2))  # Test using pathlib
        else:
            path1 = '/temp/my_file.txt'
            path2 = '/temp/my_file.txt'
            assert paths_are_equal(path1, path2)  # Test using str
            assert paths_are_equal(Path(path1), Path(path2))  # Test using pathlib

    def test_copyfile(self):
        """Tests filesystem.copyfile()."""
        # Test using str
        d = tempfile.mkdtemp()
        temp_file = tempfile.TemporaryFile(mode='w', dir=d)
        with Path(temp_file).open('w') as file:
            file.write('bob')
        temp_file_copy = os.path.join(d, 'copy')
        copyfile(temp_file, temp_file_copy)
        assert filecmp.cmp(temp_file, temp_file_copy)
        shutil.rmtree(d)

        # Test using pathlib
        d = tempfile.mkdtemp()
        temp_file = tempfile.TemporaryFile(mode='w', dir=d)
        with Path(temp_file).open('w') as file:
            file.write('bob')
        temp_file_copy = os.path.join(d, 'copy')
        copyfile(Path(temp_file), Path(temp_file_copy))
        assert filecmp.cmp(temp_file, temp_file_copy)
        shutil.rmtree(d)

    def test_removefile(self):
        """Tests filesystem.removefile()."""
        # Test using str
        temp_file = tempfile.TemporaryFile(mode='w')
        assert Path(temp_file).is_file()
        removefile(temp_file)
        assert Path(temp_file).is_file()

        # Test using pathlib
        temp_file = tempfile.TemporaryFile(mode='w')
        assert Path(temp_file).is_file()
        removefile(Path(temp_file))
        assert Path(temp_file).is_file()

    def test_is_somewhere_below_system_temp(self):
        """Tests filesystem.is_somewhere_below_system_temp()."""
        temp_file = tempfile.TemporaryFile(mode='w')
        self.assertTrue(True, is_somewhere_below_system_temp(temp_file))
        self.assertTrue(True, is_somewhere_below_system_temp(Path(temp_file)))
        Path(temp_file).unlink()
