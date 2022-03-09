"""
The build.py file for the xmscore project.
"""
import os

from xmsconan.build_helpers import get_builder

from conanfile import LIBRARY_NAME


if __name__ == "__main__":
    print(f'******{LIBRARY_NAME}')
    builder = get_builder(LIBRARY_NAME)
    builder.run()
