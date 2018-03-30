#!/usr/bin/env bash

mkdir -p x64/release
cd x64/release
conan install ../../.. -s arch="x86_64" -s arch_build="x86_64" -s build_type="Release" -s compiler.libcxx="libstdc++11"
cmake -DBUILD_TESTING=1 -G "CodeBlocks - Unix Makefiles" ../../..
cd ../..

mkdir -p x64/debug
cd x64/debug
conan install ../../.. -s arch="x86_64" -s arch_build="x86_64" -s build_type="Debug" -s compiler.libcxx="libstdc++11"
cmake -DBUILD_TESTING=1 -G "CodeBlocks - Unix Makefiles" ../../..
cd ../..
