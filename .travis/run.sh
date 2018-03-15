#!/bin/bash

echo "RUN SCRIPT"
export XMSCORE_VERSION=$TRAVIS_BRANCH
echo $XMSCORE_VERSION
echo $TRAVIS_BRANCH

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi
    pyenv activate conan
fi

python build.py
