"""
Conanfile base for the xmscore projects.
"""
import os

from conan import ConanFile, tools
from conan.tools.cmake import CMake
from conan.errors import ConanException


class XmsConanFile(ConanFile):
    """
    XmsConan class used for defining the conan info.
    """
    license = "FreeBSD Software License"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "pybind": [True, False],
        "testing": [True, False],
    }
    generators = "cmake", "txt"
    test_requires = "cxxtest/4.4@aquaveo/stable"
    xms_dependencies = []
    extra_exports = []
    extra_export_sources = []

    default_options = {
        'pybind': False,
        'testing': False,
    }

    def requirements(self):
        """Requirements."""
        self.requires("boost/1.86.0")
        # Pybind if not clang
        if not self.settings.compiler == "clang" and self.options.pybind:
            self.requires("pybind11/2.9.1@aquaveo/stable")

        for dependency in self.xms_dependencies:
            self.requires(dependency)

    def configure_options(self):
        """
        Configure the options for the conan class.
        """
        # TODO: Do we want to delete the options?
        if self.settings.build_type != "Release":
            del self.options.pybind

    def configure(self):
        """
        The configure method.
        """
        self.version = self.env.get('XMS_VERSION', '99.99.99')

        # Raise ConanExceptions for Unsupported Versions
        s_os = self.settings.os
        s_compiler = self.settings.compiler
        s_compiler_version = self.settings.compiler.version

        if s_compiler == "apple-clang" and s_os == 'Linux':
            raise ConanException("Clang on Linux is not supported.")

        if s_compiler == "gcc" and float(s_compiler_version.value) < 5.0:
            raise ConanException("GCC < 5.0 is not supported.")

        if s_compiler == "apple-clang" and s_os == 'Macos' \
                and float(s_compiler_version.value) < 9.0:
            raise ConanException("Clang > 9.0 is required for Mac.")

        for dependency in self.xms_dependencies:
            dep_name, _, _ = dependency.split('/')
            self.options[dep_name].pybind = self.options.pybind
            self.options[dep_name].testing = self.options.testing

    def build(self):
        """
        The build method for the conan class.
        """
        cmake = CMake(self)

        # CxxTest doesn't play nice with PyBind. Also, it would be nice to not
        # have tests in release code. Thus, if we want to run tests, we will
        # build a test version (without python), run the tests, and then (on
        # success) rebuild the library without tests.
        cmake.definitions["IS_PYTHON_BUILD"] = self.options.pybind
        cmake.definitions["BUILD_TESTING"] = self.options.testing
        cmake.definitions["XMS_TEST_PATH"] = "test_files"

        # Version Info
        cmake.definitions["XMS_VERSION"] = '{}'.format(self.version)
        cmake.definitions["PYTHON_TARGET_VERSION"] = self.env.get(
            "PYTHON_TARGET_VERSION", "3.10")

        cmake.configure(source_folder=".")
        cmake.build()
        cmake.install()

        # Run the tests if it is testing configuration.
        if self.options.testing:
            self.run_cxx_tests(cmake)

        # If this build is python run the python tests.
        elif self.options.pybind:
            self.run_python_tests_and_upload()

    def package(self):
        """
        The package method of the conan class.
        """
        self.copy("license", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        """
        The package_info method of the conan class.
        """
        self.env_info.PYTHONPATH.append(
            os.path.join(self.package_folder, "_package"))
        if self.settings.build_type == 'Debug':
            self.cpp_info.libs = [f'{self.name}lib_d']
        else:
            self.cpp_info.libs = [f'{self.name}lib']

    def run_cxx_tests(self, cmake):
        """
        A function to run the cxx_tests.
        """
        try:
            cmake.test(output_on_failure=True)
        except ConanException:
            raise
        finally:
            if os.path.isfile("TEST-cxxtest.xml"):
                with open("TEST-cxxtest.xml", "r") as f:
                    for line in f.readlines():
                        no_newline = line.strip('\n')
                        self.output.info(no_newline)

    def run_python_tests_and_upload(self):
        """A method to run the python tests, and upload if this is a release."""
        with tools.pythonpath(self):

            # Install required packages for python testing.
            packages_to_install = ['"numpy<2.0"', 'wheel']
            if not self.settings.os == "Macos":
                self.run(f'pip install --user {" ".join(packages_to_install)}')
            else:
                self.run(f'pip install {" ".join(packages_to_install)}')

            # Run python tests.
            path_to_python_tests = os.path.join(
                self.source_folder, '_package', 'tests')
            self.run(f'python -m unittest discover -v -p *_pyt.py -s {path_to_python_tests}',
                     cwd=os.path.join(self.package_folder, "_package"))

            # Create and upload wheel to aquapi if release and windows
            # We are uploading to aquapi here instead of pypi because pypi doesn't accept
            # the type of package 'linux_x86_64 that we want to upload. They only accept
            # manylinux1 as the plat-tag
            is_release = self.env.get("RELEASE_PYTHON", 'False') == 'True'
            is_mac_os = self.settings.os == 'Macos'
            is_gcc_7 = self.settings.os == "Linux" and float(
                self.settings.compiler.version.value) == 7.0
            is_windows_md = (self.settings.os == "Windows" and str(
                self.settings.compiler.runtime) == "MD")
            if is_release and (is_mac_os or is_gcc_7 or is_windows_md):
                self.upload_python_package()

    def upload_python_package(self):
        """
        Upload the python package to AQUAPI_URL.
        """
        devpi_url = self.env.get("AQUAPI_URL", 'NO_URL')
        devpi_username = self.env.get("AQUAPI_USERNAME", 'NO_USERNAME')
        devpi_password = self.env.get("AQUAPI_PASSWORD", 'NO_PASSWORD')
        self.run('devpi use {}'.format(devpi_url))
        self.run(
            'devpi login {} --password {}'.format(devpi_username, devpi_password))
        self.run('python setup.py bdist_wheel --dist-dir {}'.format(
            os.path.join(self.build_folder, "dist")), cwd=os.path.join(self.package_folder, "_package"))
        self.run(
            'devpi upload --from-dir {}'.format(os.path.join(self.build_folder, "dist")), cwd=".")

    def export_sources(self):
        """
        Specify sources to be exported.
        """
        self.copy('*', src=f'{self.name}', dst=f'{self.name}')
        self.copy('*', src='_package', dst='_package')

        for item in self.extra_export_sources:
            if os.path.isdir(item):
                self.copy('*', src=f'{item}', dst=f'{item}')
            else:
                self.copy(f'{item}')

    def export(self):
        """
        Specify files to be exported.
        """
        self.copy('CMakeLists.txt')
        self.copy('LICENSE')

        for item in self.extra_exports:
            if os.path.isdir(item):
                self.copy('*', src=f'{item}', dst=f'{item}')
            else:
                self.copy(f'{item}')
