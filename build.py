"""
The build.py file for the xmscore project.
"""
import os

from cpt.packager import ConanMultiPackager
from conanfile import LIBRARY_NAME

# ----------------------------------------------------------------
# DO NOT EDIT PAST THIS FILE WITHOUT AUTHORIZATION
# ----------------------------------------------------------------
def get_builder():
    builder = ConanMultiPackager()
    builder.add_common_builds()

    # Add environment variables to build definitions
    xms_version = os.getenv('XMS_VERSION', None)
    python_target_version = os.getenv('PYTHON_TARGET_VERSION', "3.10")
    release_python = os.getenv('RELEASE_PYTHON', 'False')
    aquapi_username = os.getenv('AQUAPI_USERNAME', None)
    aquapi_password = os.getenv('AQUAPI_PASSWORD', None)
    aquapi_url = os.getenv('AQUAPI_URL', None)

    for settings, options, env_vars, _, _ in builder.items:
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
                settings.update({'cppstd': '14'})
            elif compiler_version == 7:
                settings.update({'cppstd': '17'})
        elif settings['compiler'] == 'apple-clang':
            settings.update({'cppstd': 'gnu17'})
        elif settings['compiler'] == 'Visual Studio':
            settings.update({'cppstd': '17'})

        options.update({
            f'{LIBRARY_NAME}:wchar_t': 'builtin',
            f'{LIBRARY_NAME}:pybind': False,
            f'{LIBRARY_NAME}:testing': False,
        })

    # wchar_t builders
    wchar_t_update_builds = []
    for settings, options, env_vars, build_requires, _ in builder.items:
        # wchar_t builds are only built for Visual Studio builds.
        if settings['compiler'] == 'Visual Studio':
            # Set wchar_t options and add a build configuration
            wchar_t_options = dict(options)
            wchar_t_options.update({
                f'{LIBRARY_NAME}:wchar_t': 'typedef',
            })
            wchar_t_update_builds.append([settings, wchar_t_options, env_vars, build_requires])

    # pybind builders
    pybind_updated_builds = []
    for settings, options, env_vars, build_requires, _ in builder.items:
        # Pybind builds are built for 64-bit, non-debug MD(d) builds.
        if settings['arch'] == 'x86_64' and settings['build_type'] != 'Debug' and \
             (settings['compiler'] != 'Visual Studio' or settings['compiler.runtime'] in ['MD', 'MDd']):
            # Pybind is only built for visual studio versions greater than 12.
            if settings['compiler'] == 'Visual Studio' and int(settings['compiler.version']) <= 12:
                continue
            # Update conan options and add a build configuration
            pybind_options = dict(options)
            pybind_options.update({
                f'{LIBRARY_NAME}:pybind': True,
            })
            pybind_updated_builds.append([settings, pybind_options, env_vars, build_requires])

    # testing_builders
    testing_update_builds = []
    for settings, options, env_vars, build_requires, _ in builder.items:
        # Testing builds are built for each base configuration
        testing_options = dict(options)
        testing_options.update({
            f'{LIBRARY_NAME}:testing': True,
        })
        testing_update_builds.append([settings, testing_options, env_vars, build_requires])

    builder.builds = builder.builds + wchar_t_update_builds + pybind_updated_builds + testing_update_builds

    return builder


if __name__ == "__main__":
    builder = get_builder()
    builder.run()
