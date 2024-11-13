# Build System
Microjava uses GNU Make-based build system. Previosly CMake was used as the build system, but it sometimes there's a need to make low-level build adjustments, which leads to ugly workarounds in CMake.

## Modules
The software consisted of modules. Modules can have dependencies, link other modules etc.

### Module name

A module is identified by folder path of it's Makefile relative to repository root. For example, module with core Makefile `mal/rp2040/Makefile` called `mal/rp2040` (yes, it's that simple).

### Module types
Type should be defined in `MODULE_TYPE` variable.

Supported types:
- static_lib
- executable
- interface

### Dependencies
Each module can define `DEPENDENCY` variable with names of other modules that should be built before it.

**WARNING**: Build system does not provide dependencies cycle check. Be careful when defining complex dependency trees.

### Paths
All paths should be relative to the module root.

### Static library
Builds static library with given parameters. The output file is placed in the `build/lib` directory.
| Variable | Required | Description |
| -------- | -------- | ----------- |
| SOURCE_FILES | No | List of source files |
| INCLUDE_PATH | No | Path to folders with private header files |
| HEADERS | No | Folders with header files that should be exported to another modules (e.g. if `A` depends on `B`, `A` can include files from `B`'s `HEADERS`) |
| OUTPUT | Yes | Name of output file. Each library **SHOULD** have unique name |

### Executable
Builds executable with given parameters. The output file is placed in the `build/executable` directory.
| Variable | Required | Description |
| -------- | -------- | ----------- |
| SOURCE_FILES | No | List of source files |
| INCLUDE_PATH | No | Path to folders with header files |
| STATIC_LIBS | No | Names of static libraries that should be linked to executable (`OUTPUT` variable in static library module) |
| LINKER_SCRIPT | No | Path to linker script |
| OUTPUT | Yes | Name of output file. Each executable **SHOULD** have unique name |

### Interface
Convinient way to define module with header files only. Does not produce explicit output.
| Variable | Required | Description |
| -------- | -------- | ----------- |
| HEADERS | No | Folders with header files that should be exported to another modules (e.g. if `A` depends on `B`, `A` can include files from `B`'s `HEADERS`) |

## Build execution
To execute build of a single module run the following command from the repo root:
```shell
make -f make/module.mk MODULE=<module name> <global variables> build
```

### Global variables
These variables apply to all modules. Some modules may ignore it, but they are propagated to all modules that are triggered as dependencies of the current module.

| Variable | Required | Description |
| -------- | -------- | ----------- |
| BOARD | Yes | Target board |
| TOOLCHAIN_PREFIX | No | Prefix of GNU binutils commands. E.g. in `arm-none-eabi-gcc` prefix is `arm-none-eabi` (without last `-`). By default, toolchain without prefix will be used |
| CPU | No | Target CPU type. Used as a value of the `-mcpu` compiler option. By default, compiler-specific default options will be used |

## Board primary modules
Each target is built using single primary module and dependencies. Primary modules can be found under `make/target` directory.

## Root Makefile
Root Makefile encapsulates board-specific module build invokation under convenient interface. Just run `make TARGET=<board>` and see it for yourself.