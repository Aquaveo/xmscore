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
    xmscore_run_tests = os.environ.get('XMSCORE_RUN_TESTS', None)

    for settings, options, env_vars, build_requires, reference in builder.items:
        env_vars.update({
            'XMSCORE_VERSION': xmscore_version,
            "XMSCORE_RUN_TESTS": xmscore_run_tests,
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
            updated_builds.append([settings, xms_options, env_vars, build_requires])

        updated_builds.append([settings, options, env_vars, build_requires])
    builder.builds = updated_builds

    builder.run()
