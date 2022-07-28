/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
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

  // Type of each entry in a parameter block.
  typedef micro_os_plus_architecture_register_t
      micro_os_plus_semihosting_param_block_t;
  // Type of result.
  typedef micro_os_plus_architecture_signed_register_t
      micro_os_plus_semihosting_response_t;

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline))
  micro_os_plus_semihosting_response_t
  micro_os_plus_semihosting_call_host (int reason, void* arg)
  {
    micro_os_plus_semihosting_response_t value;

    __asm__ volatile(

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

        : [val] "=r"(value) /* Outputs */
        : [rsn] "r"(reason), [arg] "r"(arg), [swi] "i"(RISCV_SEMIHOSTING_CALL_NUMBER) /* Inputs */
        : "a0", "a1", "a2", "a3", "a4", "a5", "memory" /* Clobbers */
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
