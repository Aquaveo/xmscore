"""
The build.py file for the xms project.
"""
from xmsconan.build_helpers import get_builder

from conanfile import LIBRARY_NAME


if __name__ == "__main__":
    builder = get_builder(LIBRARY_NAME)
    builder.run()
