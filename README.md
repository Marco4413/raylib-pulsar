# raylib-pulsar

> [!NOTE]
> This project is used as an example on how to implement custom bindings for
> Pulsar written in C.

> [!IMPORTANT]
> This project is based on the experimental [`feature/pulsar-tools/ext-bindings`](https://github.com/Marco4413/Pulsar/tree/feature/pulsar-tools/ext-bindings)
> branch of [Pulsar](https://github.com/Marco4413/Pulsar).

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
[libs/raylib](libs/raylib) directory.

The only files required are the static library file (`libraylib.a`) and the main
header file (`raylib.h`).

> [!IMPORTANT]
> If you plan on using the bundled script files to build the project, make sure
> that, if you're building Raylib yourself, the file structure follows the one
> used by official Raylib releases.

Example minimal directory structure (for MinGW build):

```bash
libs/raylib
├── LICENSE
├── include
│   └── raylib.h
└── lib
    └── libraylib.a
```

### Pulsar Setup

Currently there is no official release of Pulsar, so the only way to get prebuilt
binaries is through [GitHub Actions](https://github.com/Marco4413/Pulsar/actions/workflows/build.yaml).

You need all [CPulsar header files](https://github.com/Marco4413/Pulsar/tree/feature/pulsar-tools/ext-bindings/include/cpulsar),
a built dynamic library of CPulsar (`libcpulsar.so` on Linux or `cpulsar.dll`
on Windows), and optionally `pulsar-tools` to run the examples.

> [!IMPORTANT]
> Make sure to either build or download prebuilt binaries from the correct branch
> of Pulsar ([`feature/pulsar-tools/ext-bindings`](https://github.com/Marco4413/Pulsar/tree/feature/pulsar-tools/ext-bindings)).

> [!IMPORTANT]
> If you plan on using the bundled script files to build the project, make sure
> that, if you're building Pulsar yourself, the file structure follows the one
> used by Pulsar artifacts.

Example minimal directory structure (for MinGW build):

```bash
libs/cpulsar
├── LICENSE.md
├── cpulsar.dll
├── include
│   └── cpulsar
│       ├── cbuffer.h
│       ├── core.h
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

When all libraries are set up, you can use either the [`build-mingw.sh`](build-mingw.sh)
or [`build-linux.sh`](build-linux.sh) scripts to build the project on your platform
of choice. The output will be found at `build/raylibpulsar.dll` or `build/libraylibpulsar.so`.

> [!NOTE]
> Refer to the scripts to see compiler flags.

## Running Examples

> [!IMPORTANT]
> You must have followed the [Building](#building) section before being able to
> run any example.

Use either [`run-mingw.sh`](run-mingw.sh) or [`run-linux.sh`](run-linux.sh)
depending on your platform and provide the example you want to run to the script.

> [!NOTE]
> The main difference between the two scripts is the name of the dynamic library
> used. There may be a common extension for Pulsar native libraries in the future.
