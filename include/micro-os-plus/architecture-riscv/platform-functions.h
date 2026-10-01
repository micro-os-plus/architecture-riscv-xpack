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
 * The functions are defined inline in
 * `micro-os-plus/architecture-riscv/inlines/platform-functions-inlines.h`,
 * which the platform package must include after defining:
 * - `RISCV_PLATFORM_RTC_FREQUENCY_HZ`, the frequency of the clock that
 *   drives `mtime` (for example `platform-sifive-hifive1`, in its
 *   `defines.h`).
 *
 * The C function is `riscv_board_get_rtc_frequency_hz()`; the C++
 * equivalent is `riscv::board::rtc_frequency_hz()`. They are not
 * declared here, since a `static` declaration without a definition in
 * the same translation unit triggers `-Wunused-function` warnings.
 */

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

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
    // `rtc_frequency_hz()` is defined inline in
    // `inlines/platform-functions-inlines.h`; see the file comment above.

    // ------------------------------------------------------------------------
  } // namespace board
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_H_

// ----------------------------------------------------------------------------
