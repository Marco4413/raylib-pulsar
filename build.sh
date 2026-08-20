#!/usr/bin/bash

set -xe

if [ ! -d build ]; then mkdir build; fi

CC="${CC:-cc}"

CFLAGS="
  $CFLAGS
  -std=c99
  -Wall -Wextra
  -Wpedantic -Werror
  -shared -fPIC
  -DPULSAR_DEBUG
  -DCPULSAR_SHAREDLIB
  -Iinclude"

LDDFLAGS="$LDDFLAGS"

if [ "$OSTYPE" = 'cygwin' -o "$OSTYPE" = 'msys' ]; then
  # Windows
  CFLAGS="
    $CFLAGS
    -Ilibs/pulsar-windows_x86_64/include
    -Ilibs/raylib-5.5_win64_mingw/include
    -o build/raylib.cpulsar.windows.dll"
  LDDFLAGS="
    $LDDFLAGS
    -Llibs/pulsar-windows_x86_64
    -Llibs/raylib-5.5_win64_mingw/lib
    -l:libraylib.a
    -l:cpulsar.dll -lgdi32 -lwinmm"
else
  CFLAGS="
    $CFLAGS
    -Ilibs/pulsar-linux_x86_64/include
    -Ilibs/raylib-5.5_linux_amd64/include
    -o build/raylib.cpulsar.linux.so"
  LDDFLAGS="
    $LDDFLAGS
    -Llibs/pulsar-linux_x86_64
    -Llibs/raylib-5.5_linux_amd64/lib
    -l:libraylib.a
    -l:libcpulsar.so"
fi

"$CC" $CFLAGS src/main.c src/bindings.c $LDDFLAGS
