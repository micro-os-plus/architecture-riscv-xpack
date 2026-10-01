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
    && defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_DEBUGGER_ENTRY_POINT_ENABLED)

// ----------------------------------------------------------------------------

// Required to satisfy the linker script definitions:
// ENTRY(_debugger_entry_point)

// For simple devices there is nothing to do when the application is
// started by a debugger, so this jumps directly to the reset entry.

// For devices that need a bootstrap, like the pico 2, this generic
// definition does not apply; leave
// MICRO_OS_PLUS_ARCHITECTURES_RISCV_DEBUGGER_ENTRY_POINT_ENABLED
// undefined and provide `_debugger_entry_point` in the device package.

    .section  .debugger_entry_point, "ax", @progbits
    .align    2 // number of low order zeros, i.e. align to a multiple of 4

    .globl    _debugger_entry_point
    .type     _debugger_entry_point, @function

_debugger_entry_point:

    j         reset_entry

// ----------------------------------------------------------------------------

#endif /* defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED)
          && defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_DEBUGGER_ENTRY_POINT_ENABLED) */

// ----------------------------------------------------------------------------
