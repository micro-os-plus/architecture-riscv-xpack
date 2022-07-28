# Change & release log

Releases in reverse chronological order.

Please check
[GitHub](https://github.com/micro-os-plus/architecture-riscv-xpack/issues/)
and close existing issues and pull requests.

## 2022-07-28

* v4.1.0
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
