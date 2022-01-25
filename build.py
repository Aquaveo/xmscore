"""
The build.py file for the xmscore project.
"""
import os

from cpt.packager import ConanMultiPackager


if __name__ == "__main__":
    # ConanPackageTools
    # See: https://github.com/conan-io/conan-package-tools/blob/develop/README.md
    builder = ConanMultiPackager()
    builder.add_common_builds()

    # Add environment variables to build definitions
    xms_version = os.getenv('XMS_VERSION', None)
    python_target_version = os.getenv('PYTHON_TARGET_VERSION', "3.6")
    release_python = os.getenv('RELEASE_PYTHON', 'False')
    aquapi_username = os.getenv('AQUAPI_USERNAME', None)
    aquapi_password = os.getenv('AQUAPI_PASSWORD', None)
    aquapi_url = os.getenv('AQUAPI_URL', None)

    for settings, _, env_vars, _, _ in builder.items:
        # General Options
        env_vars.update({
            'XMS_VERSION': xms_version,
            'PYTHON_TARGET_VERSION': python_target_version,
            'RELEASE_PYTHON': release_python,
            'AQUAPI_USERNAME': aquapi_username,
            'AQUAPI_PASSWORD': aquapi_password,
            'AQUAPI_URL': aquapi_url,
        })

        # Require C++ standard compatibility
        if settings['compiler'] == 'gcc':
            settings.update({
                'compiler.libcxx': 'libstdc++11'
            })
            compiler_version = int(settings['compiler.version'])
            if compiler_version in [5, 6]:
                settings.update({'compiler.cppstd': '14'})
            elif compiler_version == 7:
                settings.update({'compiler.cppstd': '17'})
        elif settings['compiler'] == 'apple-clang':
            settings.update({'compiler.cppstd': 'gnu17'})
        elif settings['compiler'] == 'Visual Studio':
            settings.update({'compiler.cppstd': '17'})

    pybind_updated_builds = []
    for settings, options, env_vars, build_requires, _ in builder.items:
        # pybind option
        # If any release build except VS2013
        if (not settings['compiler'] == "Visual Studio" or int(settings['compiler.version']) > 12) \
                and settings['build_type'] == 'Release':
            pybind_options = dict(options)
            pybind_options.update({'xmscore:pybind': True})
            pybind_updated_builds.append([settings, pybind_options, env_vars, build_requires])

        pybind_updated_builds.append([settings, options, env_vars, build_requires])
    builder.builds = pybind_updated_builds

    testing_updated_builds = []
    for settings, options, env_vars, build_requires, _ in builder.items:
        # testing option - can't do testing with wchar_t=typedef or pybind builds
        if options.get('xmscore:wchar_t', 'typedef') != 'typedef' and not options.get('xmscore:pybind', False):
            testing_options = dict(options)
            testing_options.update({'xmscore:testing': True})
            testing_updated_builds.append([settings, testing_options, env_vars, build_requires])
        testing_updated_builds.append([settings, options, env_vars, build_requires])
    builder.builds = testing_updated_builds
    
    builder.run()
