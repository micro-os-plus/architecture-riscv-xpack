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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-riscv/types.h"

// ----------------------------------------------------------------------------

/*
 * RISC-V device support functions.
 *
 * The declarations are part of the common design, but each device
 * must define the actual address and include the file
 * "micro-os-plus/architecture-riscv/inlines/device-functions-inlines.h".
 */

// ----------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // `mtime` functions.

  /**
   * @brief Read the 64-bit `mtime` register.
   * @par Parameters
   *  None.
   * @return The current value of the machine timer.
   *
   * @details
   * On RV64 the register is read with a single 64-bit access.
   *
   * On RV32 the register cannot be read atomically; the high word is
   * read before and after the low word, and the sequence is repeated
   * if the low word overflowed in between, so the result is always
   * consistent.
   */
  static uint64_t
  riscv_device_read_mtime (void);

  static uint32_t
  riscv_device_read_mtime_low (void);

  static uint32_t
  riscv_device_read_mtime_high (void);

  /**
   * @brief Write the 64-bit `mtime` register.
   * @param [in] value The new value of the machine timer.
   * @par Returns
   *  Nothing.
   *
   * @details
   * On RV64 the register is written with a single 64-bit access.
   *
   * On RV32 the low word is first cleared, so that it cannot overflow
   * into the high word while the high word is written, then the high
   * and the low words are written. The sequence is not atomic with
   * respect to interrupts; if needed, the caller must disable them.
   */
  static void
  riscv_device_write_mtime (uint64_t value);

  static void
  riscv_device_write_mtime_low (uint32_t value);

  static void
  riscv_device_write_mtime_high (uint32_t value);

  // --------------------------------------------------------------------------
  // `mtimecmp` functions.

  static uint64_t
  riscv_device_read_mtimecmp (void);

  static uint32_t
  riscv_device_read_mtimecmp_low (void);

  static uint32_t
  riscv_device_read_mtimecmp_high (void);

  /**
   * @brief Write the 64-bit `mtimecmp` register.
   * @param [in] value The new value of the timer comparator.
   * @par Returns
   *  Nothing.
   *
   * @details
   * On RV64 the register is written with a single 64-bit access.
   *
   * On RV32 the sequence recommended by the RISC-V privileged
   * specification is used: the low word is first set to the maximum
   * value, so that no intermediate comparator value is smaller than
   * both the old and the new values, then the high and the low words
   * are written. This prevents spurious timer interrupts. The sequence
   * is not atomic with respect to interrupts; if needed, the caller
   * must disable them.
   */
  static void
  riscv_device_write_mtimecmp (uint64_t value);

  static void
  riscv_device_write_mtimecmp_low (uint32_t value);

  static void
  riscv_device_write_mtimecmp_high (uint32_t value);

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace device
  {
    // --------------------------------------------------------------------------
    // `mtime` functions.

    /**
     * @brief Read the 64-bit `mtime` register.
     * @par Parameters
     *  None.
     * @return The current value of the machine timer.
     *
     * @details
     * The C++ equivalent of `riscv_device_read_mtime()`; on RV32 the
     * result is consistent even if the low word overflows during
     * the read.
     */
    uint64_t
    mtime (void);

    uint32_t
    mtime_low (void);

    uint32_t
    mtime_high (void);

    /**
     * @brief Write the 64-bit `mtime` register.
     * @param [in] value The new value of the machine timer.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtime()`.
     */
    void
    mtime (uint64_t value);

    void
    mtime_low (uint32_t value);

    void
    mtime_high (uint32_t value);

    // ------------------------------------------------------------------------
    // `mtimecmp` functions.

    /**
     * Read the RTC comparator.
     */
    uint64_t
    mtimecmp (void);

    uint32_t
    mtimecmp_low (void);

    uint32_t
    mtimecmp_high (void);

    /**
     * @brief Write the 64-bit `mtimecmp` register.
     * @param [in] value The new value of the timer comparator.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtimecmp()`; on RV32
     * the write sequence prevents spurious timer interrupts.
     */
    void
    mtimecmp (uint64_t value);

    void
    mtimecmp_low (uint32_t value);

    void
    mtimecmp_high (uint32_t value);

    // ------------------------------------------------------------------------
  } // namespace device
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_H_

// ----------------------------------------------------------------------------
