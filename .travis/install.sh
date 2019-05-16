#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    brew update || brew update
    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv
    brew install cmake || true

    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi

    pyenv install 3.6.8
    pyenv global 3.6.8
    pyenv virtualenv 3.6.8 conan conan-package-tools
    pyenv install 3.6-dev
    pyenv rehash
    pyenv activate conan
fi

export PATH=$(pyenv root)/versions/3.6.8/bin:/hom/conan/.local/bin:$PATH
pip install conan --upgrade
pip install conan_package_tools devpi-client wheel

python --version

conan user
