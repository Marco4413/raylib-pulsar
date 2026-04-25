#!/usr/bin/bash

set -xe

if [ ! -d build ]; then mkdir build; fi

gcc -std=c99 \
    -ggdb    \
    -Wall -Wextra      \
    -Wpedantic -Werror \
    -shared -fPIC      \
    -DPULSAR_DEBUG      \
    -DCPULSAR_SHAREDLIB \
    -Iinclude              \
    -Ilibs/cpulsar/include \
    -Ilibs/raylib/include  \
    -o build/raylib.cpulsar.linux.so \
    src/main.c src/bindings.c \
    -Llibs/cpulsar -Llibs/raylib/lib \
    -l:libraylib.a -l:libcpulsar.so
