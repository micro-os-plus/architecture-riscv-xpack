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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_INLINES_H_

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

#if __riscv_xlen == 64

  static inline __attribute__ ((always_inline)) uint64_t
  riscv_device_read_mtime (void)
  {
    return *(volatile uint64_t*)(RISCV_MMIO_MTIME_ADDRESS);
  }

#endif // __riscv_xlen == 64

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

#if __riscv_xlen == 64

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtime (uint64_t value)
  {
    *(volatile uint64_t*)(RISCV_MMIO_MTIME_ADDRESS) = value;
  }

#endif // __riscv_xlen == 64

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
    return *(uint64_t*)(RISCV_MMIO_MTIMECMP_ADDRESS);
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_device_read_mtimecmp_low (void)
  {
    return *(uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS);
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_device_read_mtimecmp_high (void)
  {
    return *(uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS + 4);
  }

#if __riscv_xlen == 64

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtimecmp (uint64_t value)
  {
    *(uint64_t*)(RISCV_MMIO_MTIMECMP_ADDRESS) = value;
  }

#endif // __riscv_xlen == 64

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtimecmp_low (uint32_t value)
  {
    *(uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS) = value;
  }

  static inline __attribute__ ((always_inline)) void
  riscv_device_write_mtimecmp_high (uint32_t value)
  {
    *(uint32_t*)(RISCV_MMIO_MTIMECMP_ADDRESS + 4) = value;
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

#if __riscv_xlen == 64

    inline __attribute__ ((always_inline)) uint64_t
    mtime (void)
    {
      return riscv_device_read_mtime ();
    }

#endif // __riscv_xlen == 64

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

#if __riscv_xlen == 64

    inline __attribute__ ((always_inline)) void
    mtime (uint64_t value)
    {
      riscv_device_write_mtime (value);
    }

#endif // __riscv_xlen == 64

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

#if __riscv_xlen == 64

    inline __attribute__ ((always_inline)) void
    mtimecmp (uint64_t value)
    {
      riscv_device_write_mtimecmp (value);
    }

#endif // __riscv_xlen == 64

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

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEVICE_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
