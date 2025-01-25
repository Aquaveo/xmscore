
"""
The build.py file for the xms project.
"""
import argparse

from xmsconan.package_tools import packager

import conanfile

# arg parse for skip build and skip upload
parser = argparse.ArgumentParser()
parser.add_argument("--skip-build", help="Skip the build step", action="store_true")
parser.add_argument("--skip-upload", help="Skip the upload step", action="store_true")
parser.add_argument("--version", help="Version to upload", default='*')


if __name__ == "__main__":
    args = parser.parse_args()
    builder = packager.XmsConanPackager(conanfile.LIBRARY_NAME, conanfile.__file__)
    builder.generate_configurations()
    if not args.skip_build:
        builder.run()
    if not args.skip_upload:
        builder.upload(version=args.version)
