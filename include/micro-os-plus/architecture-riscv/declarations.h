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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_DECLARATIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_DECLARATIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-riscv/types.h"

#include <stdint.h>

// ----------------------------------------------------------------------------

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /**
     * @brief Table of local (core) interrupt handlers.
     *
     * @details
     * Indexed by the `mcause` interrupt number (see
     * `riscv_interrupts_local_enum_t`); used by the trap dispatcher.
     *
     * Not defined in this package; each device package must define it
     * (for example `devices-sifive`, in `device-interrupts.cpp`), with
     * `RISCV_INTERRUPTS_LOCAL_LAST_NUMBER + 1` entries (the macro is
     * also defined by the device package).
     */
    extern riscv_core_trap_handler_ptr_t local_interrupt_handlers[];

    /**
     * @brief Table of global (PLIC) interrupt handlers.
     *
     * @details
     * Indexed by the PLIC source ID returned by
     * `riscv::plic::claim_interrupt()`; entry 0 is not a valid source.
     *
     * Not defined in this package; each device package must define it
     * (for example `devices-sifive`, in `device-interrupts.cpp`), with
     * `RISCV_INTERRUPTS_GLOBAL_LAST_NUMBER + 1` entries (the macro is
     * also defined by the device package).
     */
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
