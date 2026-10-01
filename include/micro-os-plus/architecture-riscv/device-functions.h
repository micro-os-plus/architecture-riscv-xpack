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
 * must define the actual addresses 
 * (`MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS` and
 * `MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS`, as integer constants) 
 * before including this header; the inline definitions are then included
 * automatically at the end.
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
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
  riscv_device_read_mtime (void);

  /**
   * @brief Read the low 32 bits of the `mtime` register.
   * @par Parameters
   *  None.
   * @return The low word of `mtime`.
   *
   * @details
   * The low word wraps around every 2^32 ticks. Combining the two
   * halves is not atomic on RV32; use the 64-bit function to get a
   * consistent value.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtime_low (void);

  /**
   * @brief Read the high 32 bits of the `mtime` register.
   * @par Parameters
   *  None.
   * @return The high word of `mtime`.
   *
   * @details
   * Combining the two halves is not atomic on RV32; use the 64-bit
   * function to get a consistent value.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtime_high (void);

  /**
   * @brief Write the 64-bit `mtime` register.
   * @param value The new value of the machine timer.
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
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtime (uint64_t value);

  /**
   * @brief Write the low 32 bits of the `mtime` register.
   * @param value The new low word.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The other word is not changed. To write the full value, use
   * `riscv_device_write_mtime()`, which uses a safe sequence on RV32.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtime_low (uint32_t value);

  /**
   * @brief Write the high 32 bits of the `mtime` register.
   * @param value The new high word.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The other word is not changed. To write the full value, use
   * `riscv_device_write_mtime()`, which uses a safe sequence on RV32.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtime_high (uint32_t value);

  // --------------------------------------------------------------------------
  // `mtimecmp` functions.

  /**
   * @brief Read the 64-bit `mtimecmp` register.
   * @par Parameters
   *  None.
   * @return The current value of the timer comparator.
   *
   * @details
   * A machine timer interrupt is pending while `mtime` is greater
   * than or equal to `mtimecmp`. On RV32 the value is read with two
   * 32-bit accesses; since `mtimecmp` is changed only by software, the
   * result is consistent unless it is written concurrently by an
   * interrupt handler or another hart.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
  riscv_device_read_mtimecmp (void);

  /**
   * @brief Read the low 32 bits of the `mtimecmp` register.
   * @par Parameters
   *  None.
   * @return The low word of `mtimecmp`.
   *
   * @details
   * Combining the two halves is not atomic on RV32; use the 64-bit
   * function to get a consistent value.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtimecmp_low (void);

  /**
   * @brief Read the high 32 bits of the `mtimecmp` register.
   * @par Parameters
   *  None.
   * @return The high word of `mtimecmp`.
   *
   * @details
   * Combining the two halves is not atomic on RV32; use the 64-bit
   * function to get a consistent value.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtimecmp_high (void);

  /**
   * @brief Write the 64-bit `mtimecmp` register.
   * @param value The new value of the timer comparator.
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
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtimecmp (uint64_t value);

  /**
   * @brief Write the low 32 bits of the `mtimecmp` register.
   * @param value The new low word.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The other word is not changed. Writing the two halves separately
   * may trigger a spurious timer interrupt, if an intermediate value is
   * not larger than `mtime`; use `riscv_device_write_mtimecmp()`.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtimecmp_low (uint32_t value);

  /**
   * @brief Write the high 32 bits of the `mtimecmp` register.
   * @param value The new high word.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The other word is not changed. Writing the two halves separately
   * may trigger a spurious timer interrupt, if an intermediate value is
   * not larger than `mtime`; use `riscv_device_write_mtimecmp()`.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
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
    // ------------------------------------------------------------------------
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
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
    mtime (void) noexcept;

    /**
     * @brief Read the low 32 bits of `mtime`.
     * @par Parameters
     *  None.
     * @return The low word.
     *
     * @details
     * The C++ equivalent of `riscv_device_read_mtime_low()`.
     */
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtime_low (void) noexcept;

    /**
     * @brief Read the high 32 bits of `mtime`.
     * @par Parameters
     *  None.
     * @return The high word.
     *
     * @details
     * The C++ equivalent of `riscv_device_read_mtime_high()`.
     */
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtime_high (void) noexcept;

    /**
     * @brief Write the 64-bit `mtime` register.
     * @param value The new value of the machine timer.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtime()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtime (uint64_t value) noexcept;

    /**
     * @brief Write the low 32 bits of `mtime`.
     * @param value The new low word.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtime_low()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtime_low (uint32_t value) noexcept;

    /**
     * @brief Write the high 32 bits of `mtime`.
     * @param value The new high word.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtime_high()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtime_high (uint32_t value) noexcept;

    // ------------------------------------------------------------------------
    // `mtimecmp` functions.

    /**
     * @brief Read the 64-bit `mtimecmp` register.
     * @par Parameters
     *  None.
     * @return The current value of the timer comparator.
     *
     * @details
     * The C++ equivalent of `riscv_device_read_mtimecmp()`.
     */
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
    mtimecmp (void) noexcept;

    /**
     * @brief Read the low 32 bits of `mtimecmp`.
     * @par Parameters
     *  None.
     * @return The low word.
     *
     * @details
     * The C++ equivalent of `riscv_device_read_mtimecmp_low()`.
     */
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtimecmp_low (void) noexcept;

    /**
     * @brief Read the high 32 bits of `mtimecmp`.
     * @par Parameters
     *  None.
     * @return The high word.
     *
     * @details
     * The C++ equivalent of `riscv_device_read_mtimecmp_high()`.
     */
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtimecmp_high (void) noexcept;

    /**
     * @brief Write the 64-bit `mtimecmp` register.
     * @param value The new value of the timer comparator.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtimecmp()`; on RV32
     * the write sequence prevents spurious timer interrupts.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtimecmp (uint64_t value) noexcept;

    /**
     * @brief Write the low 32 bits of `mtimecmp`.
     * @param value The new low word.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtimecmp_low()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtimecmp_low (uint32_t value) noexcept;

    /**
     * @brief Write the high 32 bits of `mtimecmp`.
     * @param value The new high word.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_device_write_mtimecmp_high()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtimecmp_high (uint32_t value) noexcept;

    // ------------------------------------------------------------------------
  } // namespace device
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

// The inline definitions need the device specific MMIO addresses; they
// are included only if the device defined both of them before including
// this header.
#if defined(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS)
#if defined(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS)
#include "inlines/device-functions-inlines.h"
#endif // defined(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS)
#endif // defined(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_H_

// ----------------------------------------------------------------------------
