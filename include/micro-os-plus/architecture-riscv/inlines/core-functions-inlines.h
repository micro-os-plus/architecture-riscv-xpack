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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_CORE_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_CORE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_core_enable_machine_external_interrupts (void)
  {
    riscv_csr_set_mie_bits (RISCV_CSR_MIP_MEIP);
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_core_disable_machine_external_interrupts (void)
  {
    riscv_csr_clear_mie_bits (RISCV_CSR_MIP_MEIP);
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace core
  {
    // ------------------------------------------------------------------------

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    enable_machine_external_interrupts (void) noexcept
    {
      riscv_core_enable_machine_external_interrupts ();
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    disable_machine_external_interrupts (void) noexcept
    {
      riscv_core_disable_machine_external_interrupts ();
    }

    // ------------------------------------------------------------------------
  } // namespace core
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_CORE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
