# Change & release log

Releases in reverse chronological order.

Please check
[GitHub](https://github.com/micro-os-plus/architecture-riscv-xpack/issues/)
and close existing issues and pull requests.

## 2026-11-08

* v7.0.1
* 5457138 #8: Use tail to reach _start from reset entry
* e391ffe .clang-format cleanup
* 69553b2 README update

## 2026-11-07

* f317573 7.0.0
* 89a6a28 README update
* 9822a68 prepare v7.0.0
* 2c9b296 prepare v7.0.0
* f66d253 re-generate top commons

## 2026-10-09

* dabc063 MICRO_OS_PLUS_ARCHITECTURE_RISCV_ENABLED
* 0277c1d MICRO_OS_PLUS_ALWAYS_INLINE
* 7353c22 micro-os-plus.architecture.riscv
* 633148d re-generate top commons
* 953d14f move to maintenance

## 2026-10-02

* 92f75c2 .gitignore CODE-REVIEW
* 5d31ee1 .npmignore CODE-REVIEW
* 25f934e README update
* 03b0e39 CLAUDE.md updates
* 52a54ca package.json prettier
* c0690f7 xcdl and generated make/meson
* e7d5e1a check RISCV_PLATFORM_RTC_FREQUENCY_HZ
* 74985ad use _RISCV_HAS_DEVICE_ADDRESSES
* 1a5f2cb cosmetics
* 0eec67d fix __global_pointer$ references
* b6231ea noexcept, nodiscard, static inlines
* 1988c78 doxygen updates
* c448cb2 consistent #else & #endif comments

## 2026-10-01

* cba06e4 fix guards consistency
* 34bf356 cosmetics
* 312a3cc cosmetics
* 0ebdc7d add csr read & write
* 63a86a6 semihosting.cpp: clobber only a0, a1 and memory
* a2f85e2 add platform rtc_frequency_hz() declaration
* 32a51fc semihosting-inlines.h reorder
* 7c5f990 more doxygen comments
* 4f3b83b implement show-cpuid
* 81933a3 add functions to read misa, mvendorid, marchid, mimpid
* 59423cc add __riscv_xlen fallback
* c016733 defines.h: update for recent isa versions
* 8e54a2b add doxygen comments
* 54dd492 csr functions output only in register
* 3ce8521 fix mstatus & mie return values
* 6348112 _debugger_entry_point clarifications
* 431d314 reset-entry.S: park all other harts
* 74af757 defines.h: add more CSR_MSTATUS_*
* 6e87ad1 reset-entry.S fix FPU initialisation
* 4c5324e re-work device plic support
* 14e736e core-functions.h standalone
* b968a50 rename MICRO_OS_PLUS_DEVICE_RISCV_MMIO_*
* 14ddbe0 add some doxygen comments
* cb27a0a use RISCV_STATIC_ASSERT
* 984938e use RISCV_UL for assemby syntax
* 2f28f75 add memory clobber
* b08a52a add 64-bit mcycle, mtime, mtimecmp
* a13175f mtimecmp use volatile
* 8819f02 semihosting.cpp re-work conditions
* 461c785 add reset-entry.S
* 6861f7b add debugger-entry-point.S
* 4f0c33b use MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED
* 44eccb0 _ARCHITECTURE_STACK_FILL_MAGIC update
* c86b73d __ASSEMBLER__
* d9d2d74 add data/instruction barrier
* 9800b82 add architecture_fence*

## 2026-09-10

## 2026-09-10

* a97fa93 6.0.0
* 32f865b prepare v6.0.0
* 41f3791 remove linker scripts

## 2026-09-09

* 5da7984 README update
* 419b176 5.1.0
* aa4b862 prepare v5.1.0
* b3d5140 re-format

## 2026-09-08

* 0150285 architecture.h __ASSEMBLY__
* cadd9d4 add micro_os_plus_semihosting_register_t

## 2026-09-07

* bf22010 cosmetics xpm packages
* 7b75d63 add show-cpuid

## 2026-08-05

* 19ddea8 readme cosmetics

## 2026-08-04

* 8052bbb 5.0.0
* c3a6757 prepare v5.0.0
* f8176c2 re-generate top commons

## 2026-07-31

* a172bb5 CHANGELOG update
* 0705830 xcdl-package.jsonc update
* 37a7f6d update guards & includes

## 2026-07-22

* 351f4f0 prepare 5.0.0
* 780394f xcdl export
* c07d045 re-work includes
* 98d177f re-generate top commons
* b79195e re-generate top commons
* 1a68ac8 extract semihosting.cpp
* 7f7663c fix copyright notices

## 2026-06-06

* 036a3df copyright update 2026

## 2025-11-20

* ede63b1 rename npm-pack

## 2025-10-07

* 4bcf370 update copyright notices

## 2023-11-28

* d1ef44b README updates
* 8509b6e package.json: cosmetise scripts

## 2023-10-19

* 9215ac5 package.json: cosmetise description
* a7b4471 README updates

## 2023-07-14

* 92ed5f2 README updates
* fa45973 package.json: cosmetise urls
* 5625c25 package.json: minXpm 0.16.2

## 2023-06-04

* b1fc258 update for @scope/name

## 2023-06-03

* 39ca32a lower case ci.yml
* 5a019d3 package.json min 0.16.0

## 2023-05-08

* 03d57b0 .npmignore update
* 99627ed README updates
* 5e0620b README updates
* 6c4bd98 READMEs update
* 1e5a1a6 meson.build cosmetics

## 2022-08-16

* a9fb5e2 package.json min 0.14.0 & defaults

## 2022-08-03

* d97774b README updates
* 452f77c .vscode/settings.json: cmake.ignoreCMakeListsMissing
* 87537f4 .vscode/settings.json: makefile.configureOnOpen

## 2022-08-02

* ce9c653 READMEs updates

## 2022-07-28

* 2bff438 CHANGELOG update
* e5a9bac 4.1.0
* 6943ac8 prepare v4.1.0
* e19aa16 #5: remove linker script ARM sections
* 5f43150 #7: add sections-flash.ld
* 963be52 #6: rework semihosting_call_host() to avoid asm() registers
* 31ebece #4: add signed_register_t for semihosting result

## 2022-07-25

* 0f03dd3 add preliminary xpack.json

## 2022-07-24

* v4.0.0

## 2022-07-21

* move rtos out

## 2021-03-10

* v3.0.2
* gitkeep device/include
* v3.0.1
* fix/silence warnings

## 2021-03-09

* v3.0.0
* separate rtos-port folder
* fix/silence warnings

## 2021-03-01

* v2.0.0

## 2021-02-28

* rename micro_os_plus

## 2021-02-04

* v1.1.0
* first restructured release; renamed architecture-riscv

## 2020-09-19

* v1.0.3
* bump startup to 1.0.8

## 2018-04-16

* v1.0.2
* bump deps & move back to npm
* update README developer info

## 2018-01-24

* v1.0.1
* update dependencies

## 2018-01-24

* v1.0.0

### 2018-01-20

* [#271] Reimplement RISC-V semihosting
* semihosting asm: remove "cc"

### 2018-01-15

* [#2] Use wfi() in infinite loops
* [#3] Add semihosting call_host() implementation

##  (2018-01-09)

* v0.2.0

## 2017-11-10

* README: reformat prerequisites
* arch-functions.cpp: fix typo
* README: explain xpm install
* README: refer to CHANGELOG in message
* README: update license with links
* do not ignore package-lock

## 2017-11-07

* traps.cpp: add `handle_machine_ext()` declaration
* ignore package-lock for now
* rework interrupts to use namespaces

## 2017-10-30

* arch-defines: fix `MCAUSE_CAUSE` for 32-bits
* traps.cpp: fix section `.traps_handlers`
* reset-entry.S: cosmetise comments

## 2017-10-29

* include/\*: rename csr set/clear_\*_bits
* include/\*/defines.h: simplify & prefix
* include/\*/types.h: add exc & irq enums
* include/platform-functions-inlines.h added
* src/traps.cpp: rename `riscv_interrupts_local_handlers`
* include/core-functions.h: move `riscv_trap_entry()` here
* include/\*: update guard macros

## 2017-10-28

* src/traps.cpp: move local handlers to device
* include/architecture-riscv/defines.h: number of exc
* update for device-peripherals.h

## 2017-10-26

* v1.1.0
* update for new GitHub names

## 2017-10-04

* v0.0.4
* package.json clean-ups
* add CHANGELOG.md

## 2017-09-18

* v0.0.3
* add enable/disable M external interrupts
* add plic-functions.h
* traps.cpp: use new plic api
* csr-functions*.h: add `mhartid()`
* `*_exception_`, `*_interrupt_local_`
  - for improved readability, use full names
  - use local_device array, if needed

## 2017-09-04

* v0.0.2
* v0.0.1
* initial version, copied from µOS++.
