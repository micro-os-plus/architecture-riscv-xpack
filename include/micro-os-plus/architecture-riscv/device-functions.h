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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include <micro-os-plus/architecture-riscv/types.h>

// ----------------------------------------------------------------------------

/*
 * RISC-V device support functions.
 *
 * The declarations are part of the common design, but each device
 * must define the actual address and include the file
 * <micro-os-plus/architecture-riscv/device-functions-inlines.h>.
 */

// ----------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // `mtime` functions.

#if __riscv_xlen == 64
  static
#endif // __riscv_xlen == 64
      uint64_t
      riscv_device_read_mtime (void);

  static uint32_t
  riscv_device_read_mtime_low (void);

  static uint32_t
  riscv_device_read_mtime_high (void);

#if __riscv_xlen == 64
  static
#endif // __riscv_xlen == 64
      void
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

#if __riscv_xlen == 64
  static
#endif // __riscv_xlen == 64
      void
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
    // ----------------------------------------------------------------------------
    // `mtime` functions.

    /**
     * Read the RTC current counter.
     */
    uint64_t
    mtime (void);

    uint32_t
    mtime_low (void);

    uint32_t
    mtime_high (void);

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
     * Write the RTC comparator.
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
