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

// RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  // The declarations are part of the common design, but each board
  // must implement them in the <xxx/platform-functions.h> file.

  // Redundant, see the inline definitions.

  // static uint32_t
  // riscv_board_get_rtc_frequency_hz (void);

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
    // The declarations are part of the common design, but each board
    // must implement them in the <xxx/platform-functions.h> file.

    // Redundant, see the inline definitions.

    // uint32_t
    // rtc_frequency_hz (void);

    // ------------------------------------------------------------------------
  } // namespace board
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_PLATFORM_FUNCTIONS_H_

// ----------------------------------------------------------------------------
