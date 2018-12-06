#!/usr/bin/env bash

set -e

REPO_NAME=${TRAVIS_REPO_SLUG#*/}
ARCHIVE_NAME=deps_${TRAVIS_OS_NAME}_${PLATFORM}_${REPO_NAME}.tar.gz

# Ninja
cd $HOME
if [[ "$TRAVIS_OS_NAME" == "osx" ]]
then
  brew update
  brew upgrade python3
  pip3 install meson==0.43.0 pytest

  wget https://github.com/ninja-build/ninja/releases/download/v1.8.2/ninja-mac.zip
  unzip ninja-mac.zip ninja
else
  pip3 install --user meson==0.43.0

  wget https://github.com/ninja-build/ninja/releases/download/v1.8.2/ninja-linux.zip
  unzip ninja-linux.zip ninja
fi

mkdir -p $HOME/bin
cp ninja $HOME/bin

# Dependencies comming from kiwix-build.
cd ${HOME}
wget http://tmp.kiwix.org/ci/${ARCHIVE_NAME}
tar xf ${HOME}/${ARCHIVE_NAME}
