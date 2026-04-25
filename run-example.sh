#!/usr/bin/bash

set -xe

if [ "$#" -lt 1 ]; then
    echo -e '\x1B[31mDid not provide a script to run.\x1B[0m'
    exit 1
fi

PULSAR_TOOLS='./libs/cpulsar/pulsar-tools'
# if on Windows append .exe
if [ "$OSTYPE" = 'cygwin' -o "$OSTYPE" = 'msys' ]; then
    PULSAR_TOOLS="$PULSAR_TOOLS.exe"
fi

"$PULSAR_TOOLS" run     \
    --no-bind-all       \
    -Iresources/include \
    -Lbuild -lraylib    \
    "$1"
