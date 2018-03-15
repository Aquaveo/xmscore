#!/bin/bash

echo "IN SCRIPT"
echo "BEFORE"
echo $XMSCORE_VERSION
echo ${XMSCORE_VERSION}
echo $TRAVIS_BRANCH
echo ${TRAVIS_BRANCH}
XMSCORE_VERSION=$TRAVIS_BRANCH
echo "AFTER"
echo $XMSCORE_VERSION
echo ${XMSCORE_VERSION}
echo $TRAVIS_BRANCH
echo ${TRAVIS_BRANCH}

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi
    pyenv activate conan
fi

python build.py
