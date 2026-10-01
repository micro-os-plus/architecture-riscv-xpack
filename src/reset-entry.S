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

#if defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED) \
    && defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_RESET_ENTRY_ENABLED)

// ----------------------------------------------------------------------------

    .section  .reset_entry, "ax", @progbits
    .align    2 // number of low order zeros, i.e. align to a multiple of 4

    // µOS++ prefered name. Other projects (like pico SDK) may use 
    // `_reset_handler`.

    .globl    reset_entry
    .type     reset_entry, @function
reset_entry:

    .option   push

    // Ensure the instruction is not optimized, since gp is not yet set.
    .option   norelax

    // __global_pointer$ is a magic symbol, known by the linker.
    // Unless instructed not to do so, the linker optimizes
    // accesses +/- 2KB around this to gp-relative.

#ifdef __riscv_cmodel_compact

1:
    auipc     a0, %pcrel_hi(__global_pointer__)
    addi      a0, a0, %pcrel_lo(1b)
    ld        gp, 0(a0)
    add       gp, gp, a0

#else

    la        gp, __global_pointer$
    
#endif

    .option pop

    // The linker script usually defines the stack at the end of RAM.
    la        sp, __stack

#if defined(__riscv_fdiv)

    // Initialise the Floating Point Unit
    // From FreeRTOS prvSetupFPU()
    csrr      t0, misa          // Get misa
    li        t1, 0x10028       // 0x10028 = Q,F,D Quad, Single or Double precision floating point
    and       t0, t0, t1
    beqz      t0, 1f            // check if Q,F or D is present into misa
    csrr      t0, mstatus       // Floating point unit is present so need to put it into initial state
    lui       t1, 0x2           // t1 =  0x1 << 12
    or        t0, t0, t1
    csrw      mstatus, t0       // Set FS to initial state
    csrwi     fcsr, 0           // Clear Floating-point Control and Status Register
1:

#endif // __riscv_fdiv

    // Proceed with the standard C _start() routine.
    j         _start

// ----------------------------------------------------------------------------

#endif /* defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED) 
          && defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_RESET_ENTRY_ENABLED) */

// ----------------------------------------------------------------------------
