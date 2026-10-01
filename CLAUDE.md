# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working
with code in this repository.

@.github/copilot-instructions.md

## Project overview

This is the **architecture-riscv** source library
(`@micro-os-plus/architecture-riscv`), an `xpm`/npm package within the
µOS++ embedded framework. It provides the RISC-V architecture port: CSR
accessors, core/device/platform support functions, PLIC helpers,
instruction wrappers, the semihosting host call, and the reset and
debugger entry points. It is consumed via `xpm install`, as a Git
submodule under `xpacks/@micro-os-plus/architecture-riscv`, or via
`add_subdirectory()` / `subdir()` in consumer CMake/Meson builds.

The library is not independently buildable and has no `tests/` folder,
despite the testing commands listed in `.github/copilot-instructions.md`.
Changes can only be compiled and verified from a consumer project built
with a RISC-V cross toolchain (`riscv-none-elf-gcc`).

RISC-V has no standardised HAL, so device and platform layers are left
to vendor-specific packages (e.g. `sifive/devices`,
`sifive/platform-sifive-hifive1`).

## Repository layout

- `include/micro-os-plus/architecture.h` — the single public entry
  header; it checks for C++20, optionally includes
  `micro-os-plus/project-config.h` and
  `micro-os-plus/architecture-defines.h`, then, only when
  `MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED` is defined, pulls in the
  RISC-V headers (only `defines.h` when `__ASSEMBLER__` is defined).
- `include/micro-os-plus/architecture-riscv/` — declarations; each
  `*-functions.h` header includes its matching file in `inlines/` at
  the end. `plic-functions.h`, `device-functions.h`, and
  `platform-functions.h` are not included by `architecture.h`; they are
  meant to be included by device/platform packages.
- `include/micro-os-plus/architecture-riscv/inlines/` — inline
  definitions.
- `src/semihosting.cpp` — `micro_os_plus_semihosting_call_host()`,
  using the `slli`/`ebreak`/`srai` RISC-V semihosting sequence.
- `src/show-cpuid.cpp` — `micro_os_plus_architecture_show_cpuid()`.
- `src/reset-entry.S` — `reset_entry`: sets `gp` and `sp`, initialises
  the FPU when `__riscv_fdiv` is defined, then continues to `_start`.
  Expects the linker script to define `__global_pointer$` and `__stack`.
- `src/debugger-entry-point.S` — `_debugger_entry_point`, which jumps
  to `reset_entry`; required by linker scripts using
  `ENTRY(_debugger_entry_point)`. Platforms with a bootstrap (e.g.
  pico 2) override it in the application.
- `scripts/` — Node.js maintenance scripts and Liquid templates.
- `config/` — formatter configurations (`.clang-format`,
  `.cmake-format.py`, prettier) and `top-templates.json`.

### Conditional compilation

Every source file is wrapped in preprocessor guards, so nothing is
compiled unless the consumer enables it:

- `MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED` — all sources and the
  header content.
- `MICRO_OS_PLUS_ARCHITECTURES_RISCV_RESET_ENTRY_ENABLED` —
  `reset-entry.S`.
- `MICRO_OS_PLUS_ARCHITECTURES_RISCV_DEBUGGER_ENTRY_POINT_ENABLED` —
  `debugger-entry-point.S`.
- `MICRO_OS_PLUS_SEMIHOSTING_ENABLED` — `semihosting.cpp`; the file
  also requires `micro-os-plus/semihosting.h` (from the separate
  semihosting package) to be reachable via `__has_include`, and must
  include it before testing the macro.

These macros are not defined by this package (the `defaultDefine`
entries in `xcdl-package.jsonc` are commented out); consumers define
them, typically in `micro-os-plus/project-config.h` or the generated
`micro-os-plus/architecture-defines.h`. The dependency on
`micro-os-plus.semihosting` is deliberately not declared, as it would
be circular.

### Namespaces

- C++: `riscv::architecture`, `riscv::core`, `riscv::csr`,
  `riscv::device`, `riscv::board`, `riscv::plic`, and
  `micro_os_plus::architecture`. The `riscv::irq` and `riscv::exc`
  namespaces described in `README.md` do not exist in the headers.
- C: functions are prefixed (`riscv_core_*`, `riscv_csr_*`,
  `riscv_device_*`, `micro_os_plus_architecture_*`) and declared within
  `extern "C"` blocks.
- Many definitions depend on `__riscv_xlen` (32 or 64); keep both
  variants consistent when editing.

## Build metadata and generated files

`xcdl-package.jsonc` is the source of truth for build integration. It
declares the component `micro-os-plus.architectures.riscv` (alias
`micro-os-plus.architecture`) with two child components,
`debugger-entry-point` and `reset-entry`.

`CMakeLists.txt` and `meson.build` are generated from it; do not edit
them directly. Edit `xcdl-package.jsonc` (or the templates in
`scripts/templates/`) and regenerate:

```sh
xpm run xcdl-export
```

The script flattens nested components (children become dependencies of
the parent), topologically sorts them, and renders
`scripts/templates/CMakeLists-liquid.txt` and
`scripts/templates/meson-liquid.build`.

Resulting consumer targets:

- CMake: `micro-os-plus::architectures-riscv` (also aliased as
  `micro-os-plus::architecture`), which links
  `micro-os-plus::architectures-riscv-debugger-entry-point` and
  `micro-os-plus::architectures-riscv-reset-entry`. All are INTERFACE
  libraries; sources are compiled by the consumer.
- Meson: `micro_os_plus_architectures_riscv_dependency`,
  `micro_os_plus_architecture_dependency`, and the two
  `..._debugger_entry_point_dependency` / `..._reset_entry_dependency`
  objects.

When adding a source file, add it to `xcdl-package.jsonc` and
regenerate; do not add it to the CMake/Meson files by hand.

Files carrying a `DO NOT EDIT! Automatically generated from template
file: npm-packages-helper/...` header (`scripts/*.mjs`,
`scripts/templates/*`, `.vscode/settings.json`,
`.github/workflows/test-ci.yml`) are generated from the
`@xpack/npm-packages-helper` package via `npm run generate-top-commons`;
changes to them belong upstream in that helper.

## Commands

```sh
npm install                  # install Node.js dev dependencies
xpm install                  # install xpm dev dependencies (clang)
xpm run xcdl-export          # regenerate CMakeLists.txt and meson.build
xpm run clang-format         # format src/ and include/ C/C++ files
xpm run cmake-format         # format CMake files
xpm run jsonc-format         # format JSON/JSONC files
```

`clang-format` does not cover the `.S` assembly files; format those by
hand, following the existing column alignment.

## Branches

- `xpack-development` — development; all work and pull requests target
  this branch.
- `xpack` — stable releases; `xpack-development` is merged into it.
- `master` — unused.

## Known inconsistencies

These exist in the repository at the time of writing; do not treat
them as authoritative:

- `README.md` lists the CMake target as
  `micro-os-plus::architecture-riscv` and the Meson dependency as
  `micro_os_plus_architecture_riscv_dependency`; the actual names use
  `architectures` (plural), as listed above. It also states that there
  are no source files to add, which is no longer true.
- `README.md` and `README-MAINTAINER.md` reference
  `.github/workflows/ci.yml` and `test-all.yml`; only `test-ci.yml`
  exists.
- `test-ci.yml` and `README-MAINTAINER.md` invoke `xpm run install-ci`,
  `test-ci`, `install-all`, and `test-all`, none of which are defined
  in `package.json`.
- `.github/skills/code-review/SKILL.md` describes itself as being for
  the "µOS++ Intrusive Lists project".
