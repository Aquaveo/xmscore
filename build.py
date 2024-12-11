"""
The build.py file for the xms project.
"""
from xmsconan.package_tools import packager

import conanfile


if __name__ == "__main__":
    builder = packager.XmsConanPackager(conanfile.LIBRARY_NAME, conanfile.__file__)
    builder.generate_configurations()
    builder.run()
