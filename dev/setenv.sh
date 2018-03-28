export XMS_VERSION="1.0.7"
export XMS_RUN_TESTS="1"
export CONAN_REFERENCE="xmscore/${XMS_VERSION}"
export CONAN_USERNAME="aquaveo"
export CONAN_CHANNEL="stable"
export CONAN_GCC_VERSIONS="5"
# export CONAN_UPLOAD="<conanserver>"
# export CONAN_DOCKER_IMAGE="lasote/conangcc${CONAN_GCC_VERSIONS}"
printenv | grep XMS
printenv | grep CONAN
