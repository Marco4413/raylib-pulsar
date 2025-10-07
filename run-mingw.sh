#!/usr/bin/bash

set -xe

if [ "$#" -lt 1 ]; then
    echo -e '\x1B[31mDid not provide a script to run.\x1B[0m'
    exit 1
fi

./libs/cpulsar/pulsar-tools.exe run \
    --no-bind-all                   \
    -Iresources/include             \
    -Lbuild/raylibpulsar.dll        \
    "$1"
