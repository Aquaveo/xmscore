import os
from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    # ConanPackageTools
    # See: https://github.com/conan-io/conan-package-tools/blob/develop/README.md
    builder = ConanMultiPackager()
    builder.add_common_builds()
    updated_builds = []

    # Add environment variables to build definitions
    xms_version = os.environ.get('XMS_VERSION', None)
    xms_run_tests = os.environ.get('XMS_RUN_TESTS', None)

    for settings, options, env_vars, build_requires, reference in builder.items:
        env_vars.update({
            'XMS_VERSION': xms_version,
            "XMS_RUN_TESTS": xms_run_tests,
        })

        # Require c++11 compatibility
        if settings['compiler'] == 'gcc':
            settings.update({
                'compiler.libcxx': 'libstdc++11'
            })

        updated_builds.append([settings, options, env_vars, build_requires])

    builder.builds = updated_builds

    builder.run()
