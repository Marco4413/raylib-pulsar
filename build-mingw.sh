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
    -o build/raylibpulsar.dll \
    src/main.c src/bindings.c \
    -Llibs/raylib/lib -Llibs/cpulsar \
    -l:libraylib.a    -l:cpulsar.dll \
    -lgdi32 -lwinmm

# gdi32 and winmm are required by raylib
