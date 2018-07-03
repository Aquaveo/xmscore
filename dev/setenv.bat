@echo off
set XMS_VERSION=None
set XMS_RUN_TESTS=1
rem set CONAN_VISUAL_VERSIONS=14
set CONAN_REFERENCE=xmscore/%XMS_VERSION%
set CONAN_USERNAME=aquaveo
set CONAN_CHANNEL=testing
set CONAN_GCC_VERSIONS=5
rem set CONAN_ARCHS=x86_64
rem set CONAN_BUILD_TYPES=Debug
rem set CONAN_USERNAME=aquaveo
rem set CONAN_PASSWORD=aquaveo
rem set CONAN_UPLOAD=https://conan.aquaveo.com

REM export CONAN_UPLOAD="<conanserver>"
set | findstr "XMS"
set | findstr "CONAN"
