from conans import ConanFile, CMake
from conans.errors import ConanException


class XmscoreConan(ConanFile):
    name = "xmscore"
    version = None
    license = "XMSNG Software License"
    url = "https://github.com/Aquaveo/xmscore"
    description = "Support library for XMS products"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "txt", "virtualenv"
    requires = "boost/1.66.0@conan/stable", "cxxtest/4.4@aquaveo/stable"
    exports = "CMakeLists.txt", "LICENSE"
    exports_sources = "xmscore/*"

    def configure(self):
        # Set version dynamically using XMSCORE_VERSION env variable.
        self.version = self.env.get('XMSCORE_VERSION', 'master')

        # Raise ConanExceptions for Unsupported Versions
        s_os = self.settings.os
        s_compiler = self.settings.compiler
        s_compiler_version = self.settings.compiler.version

        if s_compiler == "clang" and s_os == 'Linux':
            raise ConanException("Clang on Linux is not supported.")

        # if s_compiler == "gcc" and s_compiler_version < "5":
        #     raise ConanException("GCC less than 5 is not supported.")

        if s_compiler == "clang" and s_os == 'Darwin' and s_compiler_version < "9.0":
            raise ConanException("Clang > 9.0 is required for Mac.")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = 1
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include/xmscore", src="xmscore")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("license", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        if self.settings.build_type == 'Debug':
            self.cpp_info.libs = ["xmscore_d"]
        else:
            self.cpp_info.libs = ["xmscore"]
