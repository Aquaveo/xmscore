"""For testing the filesystem module."""
# 1. Standard python modules
import filecmp
import os
from pathlib import Path
import platform
import shutil
import tempfile
import unittest
from unittest import mock
import uuid

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms.core.filesystem import filesystem
from xms.core.filesystem.filesystem import (clear_folder, compute_relative_path, copyfile, does_file_exist,
                                            is_somewhere_below_system_temp, make_or_clear_dir,
                                            paths_are_equal, removefile, resolve_relative_path)

__copyright__ = "(C) Copyright Aquaveo 2019"
__license__ = "All rights reserved"


def _make_bob_file(dir_: str | Path) -> str:
    """Makes a file in dir_ named 'bob.txt' with 'bob' in the file."""
    temp_file_path = os.path.join(str(dir_), 'bob.txt')
    with open(temp_file_path, 'w') as file:
        file.write('bob')
    return temp_file_path


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
                ('/temp/dummy.txt', 'dummy'),
                ('/temp/dummy.ext.txt', 'dummy.ext'),
                ('dummy.txt', 'dummy'),
                ('', ''),
            ]
        for input, result in paths:
            self.assertEqual(result, filesystem.file_prefix(input))  # Test using str
            if input != '':
                self.assertEqual(result, filesystem.file_prefix(Path(input)))  # Test using pathlib

    def test_temp_filename(self):
        """Tests filesystem.temp_filename()."""
        # With no args
        f = filesystem.temp_filename()
        self.assertTrue(f)

        # With dir arg
        temp_dir = tempfile.mkdtemp()
        f = filesystem.temp_filename(dir=temp_dir)  # Test using str
        self.assertEqual(os.path.normpath(os.path.dirname(f)), os.path.normpath(temp_dir))
        f = filesystem.temp_filename(dir=Path(temp_dir))  # Test using pathlib
        self.assertEqual(os.path.normpath(os.path.dirname(f)), os.path.normpath(temp_dir))

        # With suffix arg
        f = filesystem.temp_filename(suffix='.suffix_test')
        extension = os.path.splitext(f)[1]
        self.assertEqual('.suffix_test', extension)

        # With XMS_PYTHON_APP_TEMP_DIRECTORY environment variable
        temp_dir = tempfile.mkdtemp()
        os.environ['XMS_PYTHON_APP_TEMP_DIRECTORY'] = temp_dir
        f = filesystem.temp_filename()
        os.environ.pop('XMS_PYTHON_APP_TEMP_DIRECTORY')
        self.assertEqual(os.path.normpath(os.path.dirname(f)), os.path.normpath(temp_dir))

        shutil.rmtree(temp_dir)

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
        temp_dir = tempfile.mkdtemp()
        file_path = _make_bob_file(temp_dir)
        assert Path(file_path).is_file()
        clear_folder(temp_dir)
        assert not Path(file_path).is_file()

        # Test using pathlib
        file_path = _make_bob_file(temp_dir)
        assert Path(file_path).is_file()
        clear_folder(Path(temp_dir))
        assert not Path(file_path).is_file()

        shutil.rmtree(temp_dir)

    def test_make_or_clear_dir(self):
        """Tests filesystem.make_or_clear_dir()."""
        temp_dir = tempfile.mkdtemp()
        dir1 = str(uuid.uuid4())
        dir2 = str(uuid.uuid4())

        # Test using str
        path = os.path.join(temp_dir, dir1, dir2)
        assert not Path(path).is_dir()
        make_or_clear_dir(path)
        assert Path(path).is_dir()
        file_path = _make_bob_file(path)
        assert Path(file_path).is_file()
        make_or_clear_dir(path)
        assert not Path(file_path).is_file()
        assert Path(path).is_dir()
        shutil.rmtree(path)

        # Test using pathlib
        path = Path(temp_dir) / dir1 / dir2
        assert not path.is_dir()
        make_or_clear_dir(path)
        assert path.is_dir()
        file_path = _make_bob_file(path)
        assert Path(file_path).is_file()
        make_or_clear_dir(path)
        assert not Path(file_path).is_file()
        assert path.is_dir()

        shutil.rmtree(temp_dir)

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
        temp_dir = tempfile.mkdtemp()
        file_path = _make_bob_file(temp_dir)
        file_path_copy = os.path.join(temp_dir, 'bob_copy.txt')
        copyfile(file_path, file_path_copy)
        assert filecmp.cmp(file_path, file_path_copy)
        shutil.rmtree(temp_dir)

        # Test using pathlib
        temp_dir = tempfile.mkdtemp()
        file_path = _make_bob_file(temp_dir)
        file_path_copy = os.path.join(temp_dir, 'bob_copy.txt')
        copyfile(Path(file_path), Path(file_path_copy))
        assert filecmp.cmp(file_path, file_path_copy)
        shutil.rmtree(temp_dir)

    def test_removefile(self):
        """Tests filesystem.removefile()."""
        # Test using str
        temp_dir = tempfile.mkdtemp()
        file_path = _make_bob_file(temp_dir)
        assert Path(file_path).is_file()
        removefile(file_path)
        assert not Path(file_path).is_file()

        # Test using pathlib
        file_path = _make_bob_file(temp_dir)
        assert Path(file_path).is_file()
        removefile(Path(file_path))
        assert not Path(file_path).is_file()

        shutil.rmtree(temp_dir)

    def test_is_somewhere_below_system_temp(self):
        """Tests filesystem.is_somewhere_below_system_temp()."""
        temp_dir = tempfile.mkdtemp()
        file_path = _make_bob_file(temp_dir)
        self.assertTrue(True, is_somewhere_below_system_temp(file_path))
        self.assertTrue(True, is_somewhere_below_system_temp(Path(file_path)))
        Path(file_path).unlink()
        shutil.rmtree(temp_dir)

    def test_clear_folder_with_subdirectory(self):
        """Exercises the shutil.rmtree() branch of clear_folder() when an entry is a directory."""
        temp_dir = tempfile.mkdtemp()
        try:
            sub_dir = os.path.join(temp_dir, 'subdir')
            os.makedirs(sub_dir)
            _make_bob_file(sub_dir)  # populate subdir so rmtree has something to remove
            assert Path(sub_dir).is_dir()
            clear_folder(temp_dir)
            assert not Path(sub_dir).exists()
        finally:
            if Path(temp_dir).exists():
                shutil.rmtree(temp_dir)

    def test_clear_folder_swallows_errors(self):
        """clear_folder() prints and continues when an entry cannot be removed."""
        temp_dir = tempfile.mkdtemp()
        try:
            _make_bob_file(temp_dir)  # one entry so the loop runs
            # Force the inner unlink to raise; the except branch should swallow it and print.
            with mock.patch('xms.core.filesystem.filesystem.os.unlink',
                            side_effect=OSError('forced for coverage')):
                with mock.patch('builtins.print') as mock_print:
                    clear_folder(temp_dir)
                    mock_print.assert_called()  # confirms the except branch ran
        finally:
            shutil.rmtree(temp_dir, ignore_errors=True)

    def test_copyfile_same_source_and_destination(self):
        """copyfile() swallows shutil.SameFileError when src and dest are the same path."""
        temp_dir = tempfile.mkdtemp()
        try:
            file_path = _make_bob_file(temp_dir)
            # shutil.copyfile raises SameFileError when src and dst point to the same file.
            copyfile(file_path, file_path)  # should not raise
            # File should still exist and be unchanged.
            with open(file_path) as f:
                self.assertEqual('bob', f.read())
        finally:
            shutil.rmtree(temp_dir)

    def test_removefile_swallows_errors(self):
        """removefile() ignores errors raised by os.remove (e.g. nonexistent file)."""
        # Nonexistent path raises FileNotFoundError inside os.remove; the helper must swallow.
        removefile(os.path.join(tempfile.gettempdir(), 'this-file-does-not-exist-xyz.txt'))

    def test_resolve_relative_path_with_already_absolute_relative(self):
        """If relative_path is already absolute, resolve_relative_path returns its normpath."""
        if platform.system() == 'Windows':
            absolute_path = 'C:\\some\\base'
            already_absolute = 'D:\\elsewhere\\file.txt'
            expected = os.path.normpath(already_absolute)
        else:
            absolute_path = '/some/base'
            already_absolute = '/elsewhere/file.txt'
            expected = '/elsewhere/file.txt'
        self.assertEqual(expected, resolve_relative_path(absolute_path, already_absolute))

    def test_resolve_relative_path_with_file_as_absolute_path(self):
        """When absolute_path points at an existing file, its directory is used as the base."""
        temp_dir = tempfile.mkdtemp()
        try:
            file_path = _make_bob_file(temp_dir)  # absolute_path is a real file
            expected = os.path.normpath(os.path.join(temp_dir, 'sibling.txt'))
            self.assertEqual(expected, resolve_relative_path(file_path, 'sibling.txt'))
        finally:
            shutil.rmtree(temp_dir)

    def test_resolve_relative_path_swallows_errors(self):
        """resolve_relative_path returns '' when an unexpected error occurs."""
        # Passing None for relative_path makes os.path.isabs raise TypeError, exercising the except.
        self.assertEqual('', resolve_relative_path('/tmp', None))

    def test_does_file_exist_absolute(self):
        """does_file_exist() returns True for an existing absolute path."""
        temp_dir = tempfile.mkdtemp()
        try:
            file_path = _make_bob_file(temp_dir)
            self.assertTrue(does_file_exist(file_path, temp_dir))
            self.assertTrue(does_file_exist(Path(file_path), Path(temp_dir)))
        finally:
            shutil.rmtree(temp_dir)

    def test_does_file_exist_relative(self):
        """does_file_exist() resolves relative paths against proj_dir before checking."""
        temp_dir = tempfile.mkdtemp()
        try:
            _make_bob_file(temp_dir)
            self.assertTrue(does_file_exist('bob.txt', temp_dir))
            self.assertFalse(does_file_exist('nonexistent.txt', temp_dir))
        finally:
            shutil.rmtree(temp_dir)

    def test_does_file_exist_swallows_errors(self):
        """does_file_exist() returns False when path handling raises."""
        # None as the file argument makes os.path.isabs raise TypeError, exercising the except.
        self.assertFalse(does_file_exist(None, '/tmp'))

    def test_compute_relative_path_swallows_errors(self):
        """compute_relative_path falls back to str(file) when relpath raises."""
        # None breaks os.path.relpath with TypeError, exercising the except branch.
        # The fallback returns str(file) with backslashes flipped to forward slashes.
        result = compute_relative_path(None, 'D:\\some\\path')
        self.assertEqual('D:/some/path', result)
