#!/usr/bin/env bash
export XMS_VERSION="0.0.6"
export XMS_RUN_TESTS="1"
export CONAN_REFERENCE="xmsinterp/${XMS_VERSION}"
export CONAN_USERNAME="aquaveo"
export CONAN_CHANNEL="stable"
export CONAN_GCC_VERSIONS="5"
export CONAN_ARCHS="x86_64"
export CONAN_BUILD_TYPES="Release"
# export CONAN_UPLOAD="1"
# export CONAN_DOCKER_IMAGE="lasote/conangcc${CONAN_GCC_VERSIONS}"
printenv | grep XMS
printenv | grep CONAN
