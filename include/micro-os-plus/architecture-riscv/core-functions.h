/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // Support functions.

  uint32_t
  riscv_core_get_running_frequency_hz (void);

  void
  riscv_core_update_running_frequency (void);

  static void
  riscv_core_enable_machine_external_interrupts (void);

  static void
  riscv_core_disable_machine_external_interrupts (void);

  /**
   * Hardware trap entry point (assembly).
   */
  void
  riscv_trap_entry (void);

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
    // Support functions.

    /**
     * Get the previously computed CPU frequency.
     */
    uint32_t
    running_frequency_hz (void);

    /**
     * Compute the CPU frequency. Call this after changing the
     * clock settings.
     */
    void
    update_running_frequency (void);

    /**
     * @brief Enable external interrupts (used by PLIC).
     */
    void
    enable_machine_external_interrupts (void);

    /**
     * @brief Disable external interrupts (used by PLIC).
     */
    void
    disable_machine_external_interrupts (void);

    // ------------------------------------------------------------------------
  } // namespace core
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_H_

// ----------------------------------------------------------------------------
