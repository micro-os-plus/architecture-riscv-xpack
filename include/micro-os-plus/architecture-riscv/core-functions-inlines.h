/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) void
  riscv_core_enable_machine_external_interrupts (void)
  {
    riscv_csr_set_mie_bits (RISCV_CSR_MIP_MEIP);
  }

  /**
   * @brief Disable external interrupts (used by PLIC).
   */
  static inline __attribute__ ((always_inline)) void
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

    inline __attribute__ ((always_inline)) void
    enable_machine_external_interrupts (void)
    {
      riscv_core_enable_machine_external_interrupts ();
    }

    inline __attribute__ ((always_inline)) void
    disable_machine_external_interrupts (void)
    {
      riscv_core_disable_machine_external_interrupts ();
    }

    // ------------------------------------------------------------------------
  } // namespace core
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
