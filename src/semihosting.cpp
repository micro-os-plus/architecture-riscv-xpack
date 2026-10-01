/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2023-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED)

// The whole implementation depends on this header: it must be included
// before testing MICRO_OS_PLUS_SEMIHOSTING_ENABLED, which may be defined
// in `micro-os-plus/semihosting-defines.h`, and its declaration gives the
// definition below C linkage.
#if __has_include("micro-os-plus/semihosting.h")
#include "micro-os-plus/semihosting.h"

#if defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------

/**
 * @details
 * The RISC-V implementation of the semihosting call, declared in the
 * `semihosting` package. The operation number is passed in `a0` and
 * the address of the parameter block in `a1`; the result is returned
 * by the host in `a0`.
 *
 * The `ebreak` is surrounded by the `slli x0, x0, 0x1f` and
 * `srai x0, x0, 7` instructions, which the debugger checks to
 * distinguish a semihosting call from a regular breakpoint. The
 * sequence is aligned to 16 bytes and assembled without compressed
 * instructions, so that the three instructions are always 32-bit and
 * in the same page, as required by the specification.
 *
 * The core is halted by the debugger while the host performs the
 * operation, which may take a long time; interrupts are not serviced
 * meanwhile, so it should not be used in timing critical code.
 */
micro_os_plus_semihosting_response_t
micro_os_plus_semihosting_call_host (
    int reason, micro_os_plus_semihosting_param_block_t* arg)
{
  micro_os_plus_semihosting_response_t value;

  __asm__ volatile (

      " mv a0, %[rsn] \n"
      " mv a1, %[arg] \n"

      " .balign 16 \n"
      // Workaround for RISC-V lack of multiple EBREAKs.
      " .option push \n"
      " .option norvc \n"
      " slli x0, x0, 0x1f \n"
      " ebreak \n"
      " srai x0, x0, %[swi] \n"
      " .option pop \n"

      " mv %[val], a0"

      // Only `a0` (operation number, then result) and `a1` (parameter
      // block) are used; the semihosting specification requires the
      // host to preserve all other registers. The host may read and
      // write memory through the parameter block, hence `memory`.
      : [val] "=r"(value) /* Outputs */
      : [rsn] "r"(reason), [arg] "r"(arg),
        [swi] "i"(RISCV_SEMIHOSTING_CALL_NUMBER) /* Inputs */
      : "a0", "a1", "memory" /* Clobbers */
  );

  return value;
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------

#endif // __has_include("micro-os-plus/semihosting.h")

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED)

// ----------------------------------------------------------------------------
