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
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
  riscv_device_read_mtime (void)
  {
#if __riscv_xlen == 64

    return *(
        volatile uint64_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS);

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

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtime_low (void)
  {
    return *(
        volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS);
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtime_high (void)
  {
    return *(volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS
                                 + 4);
  }

  /**
   * @details
   * On RV32, clearing the low word first prevents a carry into the
   * high word while it is being written.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtime (uint64_t value)
  {
#if __riscv_xlen == 64

    *(volatile uint64_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS)
        = value;

#else // !(__riscv_xlen == 64)

  riscv_device_write_mtime_low (0);
  riscv_device_write_mtime_high ((uint32_t)(value >> 32));
  riscv_device_write_mtime_low ((uint32_t)value);

#endif // __riscv_xlen == 64
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtime_low (uint32_t value)
  {
    *(volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS)
        = value;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtime_high (uint32_t value)
  {
    *(volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS + 4)
        = value;
  }

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
  riscv_device_read_mtimecmp (void)
  {
    // On RV32 the compiler generates two word accesses.
    return *(
        volatile uint64_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS);
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtimecmp_low (void)
  {
    return *(
        volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS);
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_device_read_mtimecmp_high (void)
  {
    return *(
        volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS
                            + 4);
  }

  /**
   * @details
   * On RV32, setting the low word to the maximum value first ensures
   * that no intermediate comparator value can trigger a spurious
   * interrupt.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtimecmp (uint64_t value)
  {
#if __riscv_xlen == 64

    *(volatile uint64_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS)
        = value;

#else // !(__riscv_xlen == 64)

  riscv_device_write_mtimecmp_low (UINT32_MAX);
  riscv_device_write_mtimecmp_high ((uint32_t)(value >> 32));
  riscv_device_write_mtimecmp_low ((uint32_t)value);

#endif // __riscv_xlen == 64
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtimecmp_low (uint32_t value)
  {
    *(volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS)
        = value;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_device_write_mtimecmp_high (uint32_t value)
  {
    *(volatile uint32_t*)(MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS + 4)
        = value;
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

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
    mtime (void) noexcept
    {
      return riscv_device_read_mtime ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtime_low (void) noexcept
    {
      return riscv_device_read_mtime_low ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtime_high (void) noexcept
    {
      return riscv_device_read_mtime_high ();
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtime (uint64_t value) noexcept
    {
      riscv_device_write_mtime (value);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtime_low (uint32_t value) noexcept
    {
      riscv_device_write_mtime_low (value);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtime_high (uint32_t value) noexcept
    {
      riscv_device_write_mtime_high (value);
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
    mtimecmp (void) noexcept
    {
      return riscv_device_read_mtimecmp ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtimecmp_low (void) noexcept
    {
      return riscv_device_read_mtimecmp_low ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mtimecmp_high (void) noexcept
    {
      return riscv_device_read_mtimecmp_high ();
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtimecmp (uint64_t value) noexcept
    {
      riscv_device_write_mtimecmp (value);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtimecmp_low (uint32_t value) noexcept
    {
      riscv_device_write_mtimecmp_low (value);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtimecmp_high (uint32_t value) noexcept
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
