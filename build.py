from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    import os
    xmscore_version = os.environ.get('XMSCORE_VERSION', None)
    print('XMSCORE_VERSION in build.py: {}'.format(xmscore_version))
    # ConanPackageTools
    # See: https://github.com/conan-io/conan-package-tools/blob/develop/README.md
    builder = ConanMultiPackager()
    builder.add_common_builds()
    updated_builds = []
    # Add environment variables
    for settings, options, env_vars, build_requires, reference in builder.items:
        env_vars.update({'XMSCORE_VERSION': xmscore_version})
        updated_builds.append([settings, options, env_vars, build_requires])
    builder.builds = updated_builds
    builder.run()
