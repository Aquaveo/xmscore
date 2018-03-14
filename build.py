from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    builder = ConanMultiPackager()
    # builder.add({"arch": "x86_64", "build_type": "Debug",  "compiler": "gcc", "compiler.version": "6", "compiler.libcxx": "libstdc++11"})
    builder.add_common_builds()
    builder.run()
