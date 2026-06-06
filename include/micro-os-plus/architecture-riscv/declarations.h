/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2017-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/mit.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_DECLARATIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_DECLARATIONS_H_

// ----------------------------------------------------------------------------

#include <micro-os-plus/architecture-riscv/types.h>

#include <stdint.h>

// ----------------------------------------------------------------------------

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace core
  {
    // ------------------------------------------------------------------------

    extern riscv_core_trap_handler_ptr_t local_interrupt_handlers[];
    extern riscv_core_trap_handler_ptr_t global_interrupt_handlers[];

    // ------------------------------------------------------------------------
  } // namespace core

  namespace architecture
  {
    // ------------------------------------------------------------------------

    // TODO: add C++ declarations here.

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_DECLARATIONS_H_

// ----------------------------------------------------------------------------
