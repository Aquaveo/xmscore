from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    import os
    xmscore_version = os.environ.get('XMSCORE_VERSION', None)
    travis_branch = os.environ.get('TRAVIS_BRANCH', None)
    print('XMSCORE_VERSION in build.py: {}'.format(xmscore_version))
    print('TRAVIS_BRANCH in build.py: {}'.format(travis_branch))
    builder = ConanMultiPackager()
    # To Add Configurations Explicitly:
    # builder.add({"arch": "x86_64", "build_type": "Debug",  "compiler": "gcc", "compiler.version": "6", "compiler.libcxx": "libstdc++11"})  # noqa: F401
    builder.add_common_builds()
    builder.run()
