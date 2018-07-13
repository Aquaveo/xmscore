@echo off
set XMS_VERSION=1.0.27
REM set CONAN_VISUAL_VERSIONS=12
set CONAN_REFERENCE=xmscore/%XMS_VERSION%
set CONAN_CHANNEL=stable
set CONAN_GCC_VERSIONS=5
REM set CONAN_ARCHS=x86
REM set CONAN_BUILD_TYPES=Debug
set CONAN_USERNAME=aquaveo
set CONAN_PASSWORD=aquaveo
set CONAN_UPLOAD=https://conan.aquaveo.com

REM export CONAN_UPLOAD="<conanserver>"
set | findstr "XMS"
set | findstr "CONAN"
