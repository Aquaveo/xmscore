import os
from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    # ConanPackageTools
    # See: https://github.com/conan-io/conan-package-tools/blob/develop/README.md
    builder = ConanMultiPackager()
    builder.add_common_builds()
    updated_builds = []
    # Add environment variables to build definitions
    xmscore_version = os.environ.get('XMSCORE_VERSION', None)

    for settings, options, env_vars, build_requires, reference in builder.items:
        env_vars.update({'XMSCORE_VERSION': xmscore_version})
        settings['compiler.libcxx'] = 'libstdc++11'
        updated_builds.append([settings, options, env_vars, build_requires])
    builder.builds = updated_builds

    builder.run()
