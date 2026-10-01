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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

/*
 * RISC-V platform (board) support functions.
 *
 * The declarations are part of the common design, but the values are
 * board specific. Each platform package must define the following
 * before including this header:
 * - `RISCV_PLATFORM_RTC_FREQUENCY_HZ`, the frequency of the clock that
 *   drives `mtime` (for example `platform-sifive-hifive1`, in its
 *   `defines.h`); it cannot be derived from the architecture, since
 *   no CSR reports it.
 *
 * The inline definitions are then included automatically at the end.
 */

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  /**
   * @brief Get the frequency of the `mtime` clock.
   * @par Parameters
   *  None.
   * @return The frequency in Hz.
   *
   * @details
   * Returns `RISCV_PLATFORM_RTC_FREQUENCY_HZ`, as defined by the
   * platform package. The value is needed to convert `mtime` ticks
   * to time units, and to measure the core clock frequency.
   */
  static uint32_t
  riscv_board_get_rtc_frequency_hz (void);

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace board
  {
    // ------------------------------------------------------------------------

    /**
     * @brief Get the frequency of the `mtime` clock.
     * @par Parameters
     *  None.
     * @return The frequency in Hz.
     *
     * @details
     * The C++ equivalent of `riscv_board_get_rtc_frequency_hz()`.
     */
    uint32_t
    rtc_frequency_hz (void);

    // ------------------------------------------------------------------------
  } // namespace board
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

// The inline definitions need the platform specific frequency; they are
// included only if the platform defined it before including this header.
#if defined(RISCV_PLATFORM_RTC_FREQUENCY_HZ)
#include "inlines/platform-functions-inlines.h"
#endif // defined(RISCV_PLATFORM_RTC_FREQUENCY_HZ)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_H_

// ----------------------------------------------------------------------------
