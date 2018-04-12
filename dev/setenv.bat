@echo off
set XMS_VERSION=1.0.8
set XMS_RUN_TESTS=1
set CONAN_VISUAL_VERSIONS=12
set CONAN_REFERENCE=xmscore/%XMS_VERSION%
set CONAN_USERNAME=aquaveo
set CONAN_CHANNEL=stable
set CONAN_GCC_VERSIONS=5
REM export CONAN_UPLOAD="<conanserver>"
set | findstr "XMS"
set | findstr "CONAN"