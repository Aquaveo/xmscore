from conans import ConanFile, CMake


class XmscoreConan(ConanFile):
    name = "xmscore"
    version = "1.0.0"
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
        self.copy("*license*", dst="licenses", ignore_case=True, keep_path=False)

    def package_info(self):
        if self.settings.build_type.value.lower() == 'debug':
            self.cpp_info.libs = ["xmscore_d"]
        else:
            self.cpp_info.libs = ["xmscore"]
