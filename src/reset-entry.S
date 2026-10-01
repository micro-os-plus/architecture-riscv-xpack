/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2017-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

// ----------------------------------------------------------------------------

// Defined by the compiler for .S files.
// #define __ASSEMBLER__ 1
#include "micro-os-plus/architecture.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED) && defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_RESET_ENTRY_ENABLED)

// ----------------------------------------------------------------------------

    .section  .reset_entry, "ax", @progbits
    .align    2 // number of low order zeros, i.e. align to a multiple of 4

    // µOS++ preferred name. Other projects (like pico SDK) may use
    // `_reset_handler`.

    .globl    reset_entry
    .type     reset_entry, @function
reset_entry:

    // This package does not bring up secondary harts; park them here,
    // so that only the hart that reaches reset first initialises the
    // stack and runs the C startup code.
    csrr      t0, mhartid
    bnez      t0, park_hart

    .option   push

    // Ensure the instruction is not optimised, since gp is not yet set.
    .option   norelax

    // __global_pointer$ is a magic symbol, known by the linker.
    // Unless instructed not to do so, the linker optimises
    // accesses +/- 2KB around this to gp-relative.

#if defined(__riscv_cmodel_compact)

1:
    auipc     a0, %pcrel_hi(__global_pointer$)
    addi      a0, a0, %pcrel_lo(1b)
    ld        gp, 0(a0)
    add       gp, gp, a0

#else // !defined(__riscv_cmodel_compact)

    la        gp, __global_pointer$

#endif // defined(__riscv_cmodel_compact)

    .option pop

    // Install a default trap handler before anything that could trap,
    // so that a fault during start-up has a defined, if minimal,
    // target; the application is expected to install its own handler
    // once the C runtime is up.
    la        t0, default_trap_entry
    csrw      mtvec, t0

    // The linker script usually defines the stack at the end of RAM.
    la        sp, __stack

#if defined(__riscv_flen)

    // Initialise the Floating Point Unit.
    // The code was compiled for an FPU, so the hardware must have one;
    // `misa` is not checked, since it may legally read as zero.
    // `mstatus.FS` (bits 14:13) is first cleared, since this code may
    // be re-entered (for example by a debugger) with the FPU in use,
    // then set to Initial (0b01), which enables the FPU.
    li        t0, RISCV_CSR_MSTATUS_FS
    csrc      mstatus, t0
    li        t0, RISCV_CSR_MSTATUS_FS_INITIAL
    csrs      mstatus, t0

    // Clear the rounding mode and the accrued exceptions.
    csrwi     fcsr, 0

#endif // defined(__riscv_flen)

    // Proceed with the standard C _start() routine.
    j         _start

    .align    2
park_hart:
1:
    wfi
    j         1b

    .align    2
default_trap_entry:
1:
    j         1b

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED) && defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_RESET_ENTRY_ENABLED)

// ----------------------------------------------------------------------------
