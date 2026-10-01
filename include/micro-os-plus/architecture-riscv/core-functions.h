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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-riscv/defines.h"
#include "micro-os-plus/architecture-riscv/csr-functions.h"

#include <stdint.h>

// ----------------------------------------------------------------------------
// RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // Support functions.
  //
  // Unless otherwise stated, the non-inline functions declared here are
  // not defined in this package; they must be provided by the RTOS
  // port, by the device package, or by the application.

  /**
   * @brief Get the core clock frequency.
   * @par Parameters
   *  None.
   * @return The frequency in Hz, as computed by the last call to
   *  `riscv_core_update_running_frequency()`.
   *
   * @details
   * The C equivalent of `riscv::core::running_frequency_hz()`.
   *
   * Not defined in this package; usually provided by the RTOS port
   * (`rtos-riscv`), as an alias of the C++ function.
   */
  uint32_t
  riscv_core_get_running_frequency_hz (void);

  /**
   * @brief Compute the core clock frequency.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The C equivalent of `riscv::core::update_running_frequency()`.
   *
   * Not defined in this package; usually provided by the RTOS port
   * (`rtos-riscv`), as an alias of the C++ function.
   */
  void
  riscv_core_update_running_frequency (void);

  /**
   * @brief Enable the machine external interrupts.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * Sets the `MEIP` bit in `mie`, which enables the interrupts
   * forwarded by the PLIC to this hart. The individual sources must
   * also be enabled in the PLIC, and the global `mstatus.MIE` bit
   * must be set for the interrupts to be taken.
   *
   * The change is atomic (a single `csrrs`), so the function can be
   * called from interrupt handlers.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_core_enable_machine_external_interrupts (void);

  /**
   * @brief Disable the machine external interrupts.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * Clears the `MEIP` bit in `mie`; the PLIC configuration is not
   * changed. The change is atomic (a single `csrrc`).
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_core_disable_machine_external_interrupts (void);

  /**
   * @brief Hardware trap entry point.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The address to be written in `mtvec`, which saves the context and
   * dispatches exceptions and interrupts. It is not a regular
   * function and must not be called directly.
   *
   * Not defined in this package; usually provided in assembly by the
   * RTOS port (`rtos-riscv`, in `trap-entry.S`).
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
     * @brief Get the core clock frequency.
     * @par Parameters
     *  None.
     * @return The frequency in Hz, as computed by the last call to
     *  `update_running_frequency()`.
     *
     * @details
     * Not defined in this package; usually provided by the RTOS port
     * (`rtos-riscv`), which may compute the frequency on the first
     * call.
     */
    uint32_t
    running_frequency_hz (void);

    /**
     * @brief Compute the core clock frequency.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * Must be called after changing the clock settings, so that
     * `running_frequency_hz()` returns the new value.
     *
     * Not defined in this package; usually provided by the RTOS port
     * (`rtos-riscv`).
     */
    void
    update_running_frequency (void);

    /**
     * @brief Enable the machine external interrupts.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of
     * `riscv_core_enable_machine_external_interrupts()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    enable_machine_external_interrupts (void) noexcept;

    /**
     * @brief Disable the machine external interrupts.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of
     * `riscv_core_disable_machine_external_interrupts()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    disable_machine_external_interrupts (void) noexcept;

    // ------------------------------------------------------------------------
  } // namespace core
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/core-functions-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_CORE_FUNCTIONS_H_

// ----------------------------------------------------------------------------
