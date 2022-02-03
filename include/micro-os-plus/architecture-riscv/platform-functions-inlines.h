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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

/*
 * Board support functions.
 *
 * Inline functions are first defined in C (prefixed with `riscv_board_`),
 * then, for convenience, are redefined in C++ in the `riscv::board::`
 * namespace.
 *
 * Regular functions are first defined in C++ then aliased to C.
 */

// ----------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_board_get_rtc_frequency_hz (void)
  {
    return RISCV_PLATFORM_RTC_FREQUENCY_HZ;
  }

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace board
  {
    // ------------------------------------------------------------------------

    /**
     * Get the board RTC frequency.
     */
    inline __attribute__ ((always_inline)) uint32_t
    rtc_frequency_hz (void)
    {
      return riscv_board_get_rtc_frequency_hz ();
    }

    // ------------------------------------------------------------------------
  } // namespace board
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
