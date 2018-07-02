@echo off
set XMS_VERSION=None
set XMS_RUN_TESTS=1
set CONAN_VISUAL_VERSIONS=14
set CONAN_REFERENCE=xmscore/%XMS_VERSION%
set CONAN_USERNAME=aquaveo
set CONAN_CHANNEL=testing
set CONAN_GCC_VERSIONS=5
REM export CONAN_UPLOAD="<conanserver>"
set | findstr "XMS"
set | findstr "CONAN"
