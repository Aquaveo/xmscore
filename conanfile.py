from conans import ConanFile, CMake, tools
from conans.errors import ConanException
import os


class XmscoreConan(ConanFile):
    name = "xmscore"
    # version = None  # This no longer worked after conan version 1.11
    license = "FreeBSD Software License"
    url = "https://github.com/Aquaveo/xmscore"
    description = "Support library for XMS products"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "xms": [True, False],
        "pybind": [True, False],
        "testing": [True, False],
    }
    default_options = "xms=False", "pybind=False", "testing=False"
    generators = "cmake", "txt"
    build_requires = "cxxtest/4.4@aquaveo/stable"
    exports = "CMakeLists.txt", "LICENSE"
    exports_sources = "xmscore/*"

    def configure(self):
        # Set version dynamically using XMS_VERSION env variable.
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

    def requirements(self):
        """requirements"""
        if self.options.xms and self.settings.compiler.version == "12":
            self.requires("boost/1.60.0@aquaveo/stable")
        else:
            self.requires("boost/1.66.0@conan/stable")
        # Pybind if not Visual studio 2013 or clang
        if not self.settings.compiler == "clang" \
                and not (self.settings.compiler == 'Visual Studio' \
                and self.settings.compiler.version == "12") \
                and self.options.pybind:
            self.requires("pybind11/2.2.2@aquaveo/stable")

    def build(self):
        cmake = CMake(self)

        if self.settings.compiler == 'Visual Studio' \
           and self.settings.compiler.version == "12":
            cmake.definitions["XMS_BUILD"] = self.options.xms


        # CXXTest doesn't play nice with PyBind. Also, it would be nice to not
        # have tests in release code. Thus, if we want to run tests, we will
        # build a test version (without python), run the tests, and then (on
        # sucess) rebuild the library without tests.
        cmake.definitions["XMS_VERSION"] = '{}'.format(self.version)
        cmake.definitions["IS_PYTHON_BUILD"] = self.options.pybind
        cmake.definitions["BUILD_TESTING"] = self.options.testing
        cmake.definitions["XMS_TEST_PATH"] = "test_files"
        cmake.definitions["PYTHON_TARGET_VERSION"] = self.env.get("PYTHON_TARGET_VERSION", "3.6")

        cmake.configure(source_folder=".")
        cmake.build()
        cmake.install()

        if self.options.testing:
            print("***********(0.0)*************")
            try:
                cmake.test()
            except ConanException:
                raise
            finally:
                if os.path.isfile("TEST-cxxtest.xml"):
                    with open("TEST-cxxtest.xml", "r") as f:
                        for line in f.readlines():
                            no_newline = line.strip('\n')
                            print(no_newline)
                print("***********(0.0)*************")
        elif self.options.pybind:
            with tools.pythonpath(self):
                self.run('python -m unittest discover -v -p *_pyt.py -s {}/xmscore/python'.format(
                    os.path.join(self.build_folder)), cwd=os.path.join(self.package_folder, "_package"))
                # Create and upload wheel to PyPi if release and windows
                is_release = self.env.get("RELEASE_PYTHON", False)
                if self.settings.os == "Windows" and is_release:
                    self.run('python setup.py bdist_wheel --plat-name=win_amd64 --dist-dir {}'.format(
                        os.path.join(self.build_folder, "dist")), cwd=os.path.join(self.package_folder, "_package"))
                    self.run('twine upload dist/*', cwd=".")


    def package(self):
        self.copy("license", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        self.env_info.PYTHONPATH.append(os.path.join(self.package_folder, "site-packages"))
        if self.settings.build_type == 'Debug':
            self.cpp_info.libs = ["xmscorelib_d"]
        else:
            self.cpp_info.libs = ["xmscorelib"]
