#!/usr/bin/bash

set -xe

if [ "$#" -lt 1 ]; then
  echo -e '\x1B[31mDid not provide a script to run.\x1B[0m'
  exit 1
fi

if [ "$OSTYPE" = 'cygwin' -o "$OSTYPE" = 'msys' ]; then
  # Windows
  PULSAR_TOOLS='./libs/pulsar-windows_x86_64/pulsar-tools.exe'
else
  PULSAR_TOOLS='./libs/pulsar-linux_x86_64/pulsar-tools'
fi

"$PULSAR_TOOLS" run   \
  --no-bind-all       \
  -Iresources/include \
  -Lbuild -lraylib    \
  "$1"
