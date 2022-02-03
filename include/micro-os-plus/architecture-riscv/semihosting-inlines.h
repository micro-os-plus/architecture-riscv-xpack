/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2015 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_SEMIHOSTING_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_SEMIHOSTING_INLINES_H_

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

// The hint that differentiates the semihosting call.
#define RISCV_SEMIHOSTING_CALL_NUMBER 7

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) int
  micro_os_plus_semihosting_call_host (int reason, void* arg)
  {
    register int value __asm__("a0") = reason;
    register void* ptr __asm__("a1") = arg;

    __asm__ volatile(

        // Workaround for RISC-V lack of multiple EBREAKs.
        " .option push \n"
        " .option norvc \n"
        " slli x0, x0, 0x1f \n"
        " ebreak \n"
        " srai x0, x0, %[swi] \n"
        " .option pop \n"

        : "=r"(value) /* Outputs */
        : "0"(value),
          "r"(ptr), [swi] "i"(RISCV_SEMIHOSTING_CALL_NUMBER) /* Inputs */
        : "memory" /* Clobbers */
    );

    return value;
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_SEMIHOSTING_INLINES_H_

// ----------------------------------------------------------------------------
