#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi
    pyenv activate conan
    export PATH=$(pyenv root)/versions/3.6.8/bin:/home/conan/.local/bin:$PATH
    ls $(pyenv root)/versions/3.6.8/bin
else
    sudo docker login -u ${AQUAVEO_DOCKER_USERNAME_SECRET} -p ${AQUAVEO_DOCKER_USERNAME_PASSWORD} docker.aquaveo.com
fi

python build.py
