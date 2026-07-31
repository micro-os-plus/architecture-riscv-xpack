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
#include "micro-os-plus/semihosting.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------

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

      : [val] "=r"(value) /* Outputs */
      : [rsn] "r"(reason), [arg] "r"(arg),
        [swi] "i"(RISCV_SEMIHOSTING_CALL_NUMBER) /* Inputs */
      : "a0", "a1", "a2", "a3", "a4", "a5", "memory" /* Clobbers */
  );

  return value;
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------
