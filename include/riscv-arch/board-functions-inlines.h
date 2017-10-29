/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef RISCV_ARCH_BOARD_FUNCTIONS_INLINES_H_
#define RISCV_ARCH_BOARD_FUNCTIONS_INLINES_H_

#include <stdint.h>

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
#endif /* defined(__cplusplus) */

  static inline uint32_t
  __attribute__((always_inline))
  riscv_board_get_rtc_frequency_hz (void)
  {
    return RISCV_BOARD_RTC_FREQUENCY_HZ;
  }

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

// ----------------------------------------------------------------------------

#if defined(__cplusplus)

namespace riscv
{
  namespace board
  {
    // ------------------------------------------------------------------------

    uint32_t
    inline __attribute__((always_inline))
    rtc_frequency_hz (void)
    {
      return riscv_board_get_rtc_frequency_hz ();
    }

  } /* namespace board */

// ----------------------------------------------------------------------------
} /* namespace riscv */

#endif /* defined(__cplusplus) */

// ----------------------------------------------------------------------------

#endif /* RISCV_ARCH_BOARD_FUNCTIONS_INLINES_H_ */
