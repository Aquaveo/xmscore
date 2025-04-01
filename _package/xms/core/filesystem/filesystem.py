"""Filesystem utility methods."""
# 1. Standard python modules
import os
from pathlib import Path
import shutil
import sys
import tempfile

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules


__copyright__ = "(C) Copyright Aquaveo 2019"
__license__ = "All rights reserved"


def clear_folder(folder: str | Path) -> None:
    """Deletes everything in folder.

    From https://stackoverflow.com/questions/185936

    Args:
        folder: The folder to clear.
    """
    for the_file in os.listdir(folder):
        file_path = os.path.join(folder, the_file)
        try:
            if os.path.isfile(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print(e)


def make_or_clear_dir(output_dir: str | Path) -> None:
    """Makes or clears the output directory.

    Args:
        output_dir: The folder to make or clear.
    """
    if os.path.isdir(output_dir):
        clear_folder(output_dir)
    else:
        os.makedirs(output_dir, exist_ok=True)


def paths_are_equal(path1: str | Path, path2: str | Path) -> bool:
    """Returns true if the two file paths are equal.

    Args:
        path1: The first path.
        path2: The second path.

    Returns:
        True if they are equal.
    """
    return os.path.normpath(path1) == os.path.normpath(path2)


def copyfile(src: str | Path, dest: str | Path) -> None:
    """Copy a file on disk, suppressing errors if source and destination are the same file.

    Args:
        src: Source file path.
        dest: Destination file path.
    """
    try:
        shutil.copyfile(src, dest)
    except shutil.SameFileError:
        pass


def removefile(filename: str | Path) -> None:
    """Delete a file from disk, ignoring any errors.

    Args:
        filename: Path of file to be removed.
    """
    try:
        os.remove(filename)
    except Exception:
        pass


def resolve_relative_path(absolute_path: str | Path, relative_path: str | Path) -> str:
    """Given a path and a path that is relative to it, return the full path.

    Args:
        absolute_path: An absolute path.
        relative_path: A path relative to the absolute path.

    Returns:
        The full path to the item indicated by relative_path.
    """
    # If they give us a filename, try to get just the path
    normpath = ''
    try:
        if os.path.isabs(relative_path):  # If already absolute, just return
            return os.path.normpath(relative_path)
        if Path(absolute_path).is_file():
            absolute_path = os.path.dirname(absolute_path)
        resolved_path = os.path.join(absolute_path, str(relative_path).strip("'"))
        normpath = os.path.normpath(resolved_path)
    except Exception:
        pass
    return normpath


def does_file_exist(file: str | Path, proj_dir: str | Path) -> bool:
    """Determine if a file in our persistent data still exist.

    If file is not absolute, will check if relative from the project directory exists.

    Args:
       file: Relative or absolute file path to check the existence of
       proj_dir: Project path to resolve relative paths to

    Returns:
        True if the file exists.
    """
    try:
        if not os.path.isabs(file):  # Convert relative to absolute
            file = resolve_relative_path(proj_dir, file)
        return os.path.exists(file)
    except Exception:
        return False


def compute_relative_path(path: str | Path, file: str | Path) -> str:
    r"""Computes and returns the path of file relative to path.

    Also changes all '\' to '/' so tests work on Windows and Linux.

    If the paths are on different drives, the original "file" path is returned (but with '\' to '/')

    Args:
        path: A full path included in 'file'.
        file: A full path to a file.

    Returns:
        A relative path.
    """
    try:
        return os.path.relpath(file, path).replace('\\', '/')
    except Exception:
        return str(file).replace('\\', '/')


def is_somewhere_below_system_temp(filename: str | Path) -> bool:
    """Returns true if a component is locked, given its main_file.

    Args:
        filename: The file.

    Returns:
        See description.
    """
    temp_dir = Path(tempfile.gettempdir()).resolve()
    filepath = Path(filename).resolve()
    return temp_dir in filepath.parents


def file_prefix(filepath: str | Path) -> str:
    """Returns the first part of the filename; no extension, no path.

    Args:
        filepath: The path and filename.

    Returns:
        See description.
    """
    basename = os.path.basename(filepath)
    return os.path.splitext(basename)[0]


def temp_filename(dir: str | Path = None, suffix: str = '') -> str:
    """Returns a temporary filename, in the XMS temp directory by default.

    Args:
        dir: If provided, filename will be in the directory. Otherwise it will be in the
             system temp directory.
        suffix: The suffix to use for the file. You must include a '.' if you want it to be an extension.

    Returns:
        See description.
    """
    if dir:  # If we call the next line with dir == '', it seems to use the working directory.
        file = tempfile.NamedTemporaryFile(mode='wt', suffix=suffix, dir=dir, delete=True)
    else:
        xms_temp = os.environ.get('XMS_PYTHON_APP_TEMP_DIRECTORY', 'unknown')
        if xms_temp != 'unknown':
            file = tempfile.NamedTemporaryFile(mode='wt', suffix=suffix, dir=xms_temp, delete=True)
        else:
            file = tempfile.NamedTemporaryFile(mode='wt', suffix=suffix, delete=True)

    filename = file.name
    file.close()
    return filename


def make_filename_unique(filepath: str | Path) -> str | None:
    """Appends a suffix to the file if needed to make it unique.

    Example: file.txt becomes file(2).txt

    Args:
        filepath: Filepath to consider.

    Returns:
        The unique filename or None if it fails.
    """
    if not os.path.exists(filepath):
        return str(filepath)

    path, name = os.path.split(filepath)
    name, extension = os.path.splitext(name)

    for i in range(2, sys.maxsize):
        unique_filename = os.path.join(path, f'{name}({i}){extension}')
        if not os.path.exists(unique_filename):
            return unique_filename

    return None  # pragma: no cover
