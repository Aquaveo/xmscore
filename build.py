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

        # Add additional configurations for xms options
        if settings['compiler'] == 'Visual Studio' and 'MD' in settings['compiler.runtime']:
            xms_options = dict(options)
            xms_options.update({'xmscore:xms': True})
            if int(settings['compiler.version']) >= 14 and settings['arch'] != "x86":
                xms_options.update({'xmscore:pybind': True})
            updated_builds.append([settings, xms_options, env_vars, build_requires])

        updated_builds.append([settings, options, env_vars, build_requires])

    builder.builds = updated_builds

    builder.run()
