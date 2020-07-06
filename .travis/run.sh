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

flake8 --exclude .tox,.git,__pycache__,pydocs/source/conf.py,docs/source/conf.py,build,dist,tests/fixtures/*,*.pyc,*.egg-info,.cache,.eggs --ignore=D200,D212 --max-line-length=120 --docstring-convention google --isolated --import-order-style=appnexus --application-import-names=xms.core --application-package-names=xms --count --statistics .
python build.py
