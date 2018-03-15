import os
from conans import ConanFile, CMake
from conans.errors import ConanException

xmscore_version = os.environ.get('XMSCORE_VERSION', 'master')
travis_branch = os.environ.get('TRAVIS_BRANCH', 'master')
print('XMSCORE_VERSION in conanfile.py: {}'.format(xmscore_version))
print('TRAVIS_BRANCH in conanfile.py: {}'.format(travis_branch))


class XmscoreConan(ConanFile):
    name = "xmscore"
    version = xmscore_version
    license = "XMSNG Software License"
    url = "https://github.com/Aquaveo/xmscore"
    description = "Support library for XMS products"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    requires = "boost/1.66.0@conan/stable"
    exports = "CMakeLists.txt", "LICENSE"
    exports_sources = "xmscore/*"

    def configure(self):
        s_os = self.settings.os
        s_compiler = self.settings.compiler
        s_compiler_version = self.settings.compiler.version

        if s_compiler == "clang" and s_os == 'Linux':
            raise ConanException("Clang on Linux is not supported.")

        if s_compiler == "clang" and s_os == 'Darwin' and s_compiler_version < "9.0":
            raise ConanException("Clang > 9.0 is required for Mac.")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="xmscore")
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
