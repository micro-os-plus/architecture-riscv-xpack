[[![license](https://img.shields.io/github/license/micro-os-plus/architecture-riscv-xpack)](https://github.com/micro-os-plus/architecture-riscv-xpack/blob/xpack/LICENSE)
[![CI on Push](https://github.com/micro-os-plus/architecture-riscv-xpack/workflows/CI%20on%20Push/badge.svg)](https://github.com/micro-os-plus/architecture-riscv-xpack/actions?query=workflow%3A%22CI+on+Push%22)

# A source library xPacks with the µOS++ RISC-V architecture definitions

This project provides support for RISC-V embedded projects.

The project is hosted on GitHub as
[micro-os-plus/architecture-riscv-xpack](https://github.com/micro-os-plus/architecture-riscv-xpack).

## Maintainer info

This page is addressed to developers who plan to include this source
library into their own projects.

For maintainer info, please see the
[README-MAINTAINER](README-MAINTAINER.md) file.

## Install

As a source library xPacks, the easiest way to add it to a project is via
**xpm**, but it can also be used as any Git project, for example as a submodule.

### Prerequisites

A recent [xpm](https://xpack.github.io/xpm/),
which is a portable [Node.js](https://nodejs.org/) command line application.

For details please follow the instructions in the
[xPack install](https://xpack.github.io/install/) page.

### xpm

Note: the package will be available from npmjs.com at a later date.

For now, it can be installed from GitHub:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install github:micro-os-plus/architecture-riscv-xpack
```

When ready, this package will be available as
[`@micro-os-plus/architecture-riscv`](https://www.npmjs.com/package/@micro-os-plus/architecture-riscv)
from the `npmjs.com` registry:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install @micro-os-plus/architecture-riscv@latest

ls -l xpacks/micro-os-plus-architecture-riscv
```

### Git submodule

If, for any reason, **xpm** is not available, the next recommended
solution is to link it as a Git submodule below an `xpacks` folder.

```sh
cd my-project
git init # Unless already a Git project
mkdir -p xpacks

git submodule add https://github.com/micro-os-plus/architecture-riscv-xpack.git \
  xpacks/micro-os-plus-architecture-riscv
```

## Branches

Apart from the unused `master` branch, there are two active branches:

- `xpack`, with the latest stable version (default)
- `xpack-develop`, with the current development version

All development is done in the `xpack-develop` branch, and contributions via
Pull Requests should be directed to this branch.

When new releases are published, the `xpack-develop` branch is merged
into `xpack`.

## User info

This source xPack provides general RISC-V definitions and will eventually
include the implementation for the µOS++ scheduler.

### Status

The µOS++ RISC-V definitions are fully functional for non-RTOS applications;
the scheduler port will be implemented at a later date.

### Design details

From a top down approach, in µOS++, the RISC-V definitions are
grouped by several criteria:

- platform (board)
- device
- core
- hart (hardware thread)

#### Platform

The platform level refers to a device and adds platform specific definitions,
like what GPIO pins are used for various LEDs, buttons, etc.

The portable way to include platform specific definitions in an application is:

```c
#include <micro-os-plus/platform.h>
```

In µOS++, the platform specific definitions are grouped in the
`riscv::platform` namespace.

An example of a platform package is **sifive/platform-sifive-hifive1** with the
SiFive HiFive1 small development board.

#### Device

The RISC-V documentation introduces the term _platform_ as:

> A RISC-V hardware _platform_ can contain one or more RISC-V-compatible
processing cores together with other non-RISC-V-compatible cores,
fixed-function accelerators, various physical memory structures,
I/O devices, and an interconnect structure to allow the components
to communicate.

In modern implementations, this is generally either a physical chip
or a synthesised one.

In other contexts, _platform_ has a broader meaning and may refer to
the environment in which a piece of software is executed; it may be
the hardware or the operating system (OS); to avoid confusions, in
µOS++ the term **device** is used to identify the vendor specific
RISC-V details (with _platform_ being used for the machine, or the board).

Please note that RISC-V defines some common MMIO registers (like
`mtime` and `mtimecmp`), but, for more flexibility, leaves the
implementation to define the actual address. Unfortunately this
increases the software complexity, since the device specific headers
must define some fixed symbols and the header files must be included
in a careful order, to avoid circular references.

In µOS++, the device specific definitions are grouped in the
`riscv::device` namespace.

The portable way to include device specifc definitions in an application is:

```c
#include <micro-os-plus/device.h>
```

Example of device packages are **sifive/devices** with the SiFive
Freedom E310 and E31/E51 Arty devices.

#### Core

The RISC-V documentation introduces the term _core_ as:

> A component is termed a core if it contains an independent
instruction fetch unit. A RISC-V-compatible core might support
multiple RISC-V-compatible hardware threads, or harts, through
multi-threading.

In µOS++, the core specific definitions are grouped in the
`riscv::core` namespace.

The portable way to include architecture specific definitions
in an application is:

```c
#include <micro-os-plus/architecture.h>
```

#### Hart

Hardware threads are the working horses of the software threads;
each hardware thread has its own set of general registers and
Control and Status Registers (CSRs); the OS may schedule a
maximum number of software threads equal with the number of
hardware threads, possibly with some grouping constrains.

In RISC-V, **Control and Status Registers** (**CSR**s) are
a special group of registers, available via specific `csr`
instructions from a separate addressing space not visible in
the memory space.

The `hart` specific definitions are grouped under the `riscv::csr` namespace.

#### Other namespaces

Interrupts and exceptions are grouped under `riscv::irq` and `riscv::exc`.

### Build & integration info

To include this package in a project, consider the following details.

#### Source folders

- `src`

#### Include folders

- `include`

#### Preprocessor definitions

- none required

#### Compiler options

- `-std=c++20` or higher for C++ sources
- `-std=c11` for C sources

#### C++ Namespaces

TBD

#### C++ Classes

TBD

### Known problems

- none

### Examples

TBD

### Tests

TBD

## Change log - incompatible changes

According to [semver](https://semver.org) rules:

> Major version X (X.y.z | X > 0) MUST be incremented if any
backwards incompatible changes are introduced to the public API.

The incompatible changes, in reverse chronological order,
are:

- TBD

## License

The original content is released under the
[MIT License](https://opensource.org/licenses/MIT/),
with all rights reserved to
[Liviu Ionescu](https://github.com/ilg-ul/).
