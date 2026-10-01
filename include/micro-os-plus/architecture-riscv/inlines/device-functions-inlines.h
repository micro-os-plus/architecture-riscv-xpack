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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_DEVICE_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_DEVICE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

// Inline implementations for the common device support functions.
// Not included by architecture files, but by device files.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  /**
   * @details
   * On RV32, the high word is read before and after the low word; if
   * the two high values differ, the low word overflowed between the
   * reads and the sequence is repeated.
   */
  static inline __attribute__ ((always_inline)) uint64_t
  riscv_device_read_mtime (void)
  {
#if __riscv_xlen == 64

    return *(volatile uint64_t*)(RISCV_MMIO_MTIME_ADDRESS);

#else // !(__riscv_xlen == 64)

  uint32_t high;
  uint32_t low;

  do
    {
      high = riscv_device_read_mtime_high ();
      low = riscv_device_read_mtime_low ();
    }
  while (high != riscv_device_read_mtime_high ());

  return ((uint64_t)high << 32) | low;

#endif // __riscv_xlen == 64
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_device_read_mtime_low (void)
  {
    return *(volatile uint32_t*)(RISCV_MMIO_MTIME_ADDRESS);
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_device_read_mtime_high (void)
  {
    return *(volatile uint32_t*)(RISCV_MMIO_MTIME_ADDRESS + 4);
  }

  /**
   * @details
   * On RV32, clearing the low word first prevents a carry into the
   * high word while it is being written.
   */
  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtime (uint64_t value)
  {
#if __riscv_xlen == 64

    *(volatile uint64_t*)(RISCV_MMIO_MTIME_ADDRESS) = value;

#else // !(__riscv_xlen == 64)

  riscv_device_write_mtime_low (0);
  riscv_device_write_mtime_high ((uint32_t)(value >> 32));
  riscv_device_write_mtime_low ((uint32_t)value);

#endif // __riscv_xlen == 64
  }

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtime_low (uint32_t value)
  {
    *(volatile uint32_t*)(RISCV_MMIO_MTIME_ADDRESS) = value;
  }

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtime_high (uint32_t value)
  {
    *(volatile uint32_t*)(RISCV_MMIO_MTIME_ADDRESS + 4) = value;
  }

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) uint64_t
  riscv_device_read_mtimecmp (void)
  {
    // On RV32 the compiler generates two word accesses.
    return *(volatile uint64_t*)(RISCV_MMIO_MTIMECMP_ADDRESS);
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_device_read_mtimecmp_low (void)
  {
    return *(volatile uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS);
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_device_read_mtimecmp_high (void)
  {
    return *(volatile uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS + 4);
  }

  /**
   * @details
   * On RV32, setting the low word to the maximum value first ensures
   * that no intermediate comparator value can trigger a spurious
   * interrupt.
   */
  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtimecmp (uint64_t value)
  {
#if __riscv_xlen == 64

    *(volatile uint64_t*)(RISCV_MMIO_MTIMECMP_ADDRESS) = value;

#else // !(__riscv_xlen == 64)

  riscv_device_write_mtimecmp_low (UINT32_MAX);
  riscv_device_write_mtimecmp_high ((uint32_t)(value >> 32));
  riscv_device_write_mtimecmp_low ((uint32_t)value);

#endif // __riscv_xlen == 64
  }

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtimecmp_low (uint32_t value)
  {
    *(volatile uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS) = value;
  }

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtimecmp_high (uint32_t value)
  {
    *(volatile uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS + 4) = value;
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
  namespace device
  {
    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) uint64_t
    mtime (void)
    {
      return riscv_device_read_mtime ();
    }

    inline __attribute__ ((always_inline)) uint32_t
    mtime_low (void)
    {
      return riscv_device_read_mtime_low ();
    }

    inline __attribute__ ((always_inline)) uint32_t
    mtime_high (void)
    {
      return riscv_device_read_mtime_high ();
    }

    inline __attribute__ ((always_inline)) void
    mtime (uint64_t value)
    {
      riscv_device_write_mtime (value);
    }

    inline __attribute__ ((always_inline)) void
    mtime_low (uint32_t value)
    {
      riscv_device_write_mtime_low (value);
    }

    inline __attribute__ ((always_inline)) void
    mtime_high (uint32_t value)
    {
      riscv_device_write_mtime_high (value);
    }

    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) uint64_t
    mtimecmp (void)
    {
      return riscv_device_read_mtimecmp ();
    }

    inline __attribute__ ((always_inline)) uint32_t
    mtimecmp_low (void)
    {
      return riscv_device_read_mtimecmp_low ();
    }

    inline __attribute__ ((always_inline)) uint32_t
    mtimecmp_high (void)
    {
      return riscv_device_read_mtimecmp_high ();
    }

    inline __attribute__ ((always_inline)) void
    mtimecmp (uint64_t value)
    {
      riscv_device_write_mtimecmp (value);
    }

    inline __attribute__ ((always_inline)) void
    mtimecmp_low (uint32_t value)
    {
      riscv_device_write_mtimecmp_low (value);
    }

    inline __attribute__ ((always_inline)) void
    mtimecmp_high (uint32_t value)
    {
      riscv_device_write_mtimecmp_high (value);
    }

    // ------------------------------------------------------------------------
  } // namespace device
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_DEVICE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
