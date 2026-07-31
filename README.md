# raylib-pulsar

> [!NOTE]
> This project is used as an example on how to implement custom bindings for
> [Pulsar](https://github.com/Marco4413/Pulsar) written in C.

## Project Structure

All libraries are within the [`libs`](libs) folder, refer to the [Building](#building)
section to see how it's set up.

All C code can be found within the [src](src) and [include](include) directories.
That is the code which binds functions and is ran when calling natives.

Pulsar files which provide function declarations and constants are found within
[resources/include](resources/include).

## Building

Since the purpose of this project is to be an example, no build systems are used
to compile [Raylib](https://github.com/raysan5/raylib) and [Pulsar](https://github.com/Marco4413/Pulsar)
from scratch. Therefore, manual setup is needed before being able to build.

### Raylib Setup

Download the [release of Raylib](https://github.com/raysan5/raylib/releases/tag/5.5)
which suits your platform (or build it yourself) and extract all files into the
[libs/raylib-5.5_win64_mingw](libs/raylib-5.5_win64_mingw) directory on Windows or
the [libs/raylib-5.5_linux_amd64](libs/raylib-5.5_linux_amd64) directory on Linux.

The only files required are the static library file (`libraylib.a`) and the main
header file (`raylib.h`).

> [!IMPORTANT]
> If you plan on using the bundled script files to build the project, make sure
> that, if you're building Raylib yourself, the file structure follows the one
> used by official Raylib releases.

Example minimal directory structure (for MinGW build):

```bash
libs/raylib-5.5_win64_mingw
├── LICENSE
├── include
│   └── raylib.h
└── lib
    └── libraylib.a
```

### Pulsar Setup

There are a few ways to get Pulsar binaries:
- [Building it yourself](https://github.com/Marco4413/Pulsar#building).
- From the [Build GitHub Action](https://github.com/Marco4413/Pulsar/actions/workflows/build.yaml) artifacts.
- From [GitHub Releases](https://github.com/Marco4413/Pulsar/releases).

You need all [CPulsar header files](https://github.com/Marco4413/Pulsar/tree/feature/pulsar-tools/ext-bindings/include/cpulsar),
a built dynamic library of CPulsar (`libcpulsar.so` on Linux or `cpulsar.dll`
on Windows), and optionally `pulsar-tools` to run the examples.

Extract all files into the [libs/pulsar-windows_x86_64](libs/pulsar-windows_x86_64)
directory on Windows or the [libs/pulsar-linux_x86_64](libs/pulsar-linux_x86_64)
directory on Linux.

> [!IMPORTANT]
> If you plan on using the bundled script file to build the project, make sure
> that, if you're building Pulsar yourself, the file structure follows the one
> used by Pulsar artifacts.

Example minimal directory structure (for MinGW build):

```bash
libs/pulsar-windows_x86_64
├── LICENSE.md
├── cpulsar.dll
├── include
│   └── cpulsar
│       ├── cbuffer.h
│       ├── core.h
│       ├── opaque.h
│       ├── parser.h
│       ├── platform.h
│       ├── runtime
│       │   ├── customdata.h
│       │   ├── customtype.h
│       │   ├── locals.h
│       │   ├── stack.h
│       │   └── value.h
│       ├── runtime.h
│       └── version.h
└── pulsar-tools.exe
```

---

When all libraries are set up, you can use the [`build.sh`](build.sh)
script to build the project. The output will be found at
`build/raylib.cpulsar.windows.dll` or `build/raylib.cpulsar.linux.so`.

> [!NOTE]
> Refer to the script to see compiler flags.

## Running Examples

> [!IMPORTANT]
> You must have followed the [Building](#building) section before being able to
> run any example.

Use [`run-example.sh`](run-example.sh) and provide the example you want to run to the script.
