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

#ifndef RISCV_ARCH_ARCH_INSTRUCTIONS_INLINES_H_
#define RISCV_ARCH_ARCH_INSTRUCTIONS_INLINES_H_

#include <stdint.h>

/*
 * Inline implementations for the RISC-V architecture instructions.
 */

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

  // --------------------------------------------------------------------------

  static inline void
  __attribute__((always_inline))
  riscv_arch_nop (void)
  {
    asm volatile(
        " nop "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
  }

  static inline void
  __attribute__((always_inline))
  riscv_arch_ebreak (void)
  {
    asm volatile(
        " ebreak "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
  }

  static inline void
  __attribute__((always_inline))
  riscv_arch_wfi (void)
  {
    asm volatile(
        " wfi "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
  }

  static inline void
  __attribute__((always_inline))
  os_arch_nop (void)
  {
    riscv_arch_nop ();
  }

  /**
   * `break` instruction.
   */
  static inline void
  __attribute__((always_inline))
  os_arch_brk (void)
  {
    riscv_arch_ebreak ();
  }

  /**
   * `wfi` instruction.
   */
  static inline void
  __attribute__((always_inline))
  os_arch_wfi (void)
  {
    riscv_arch_wfi ();
  }

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

// ============================================================================

#if defined(__cplusplus)

namespace riscv
{
  namespace arch
  {
    // ------------------------------------------------------------------------

    inline void
    __attribute__((always_inline))
    nop (void)
    {
      riscv_arch_nop ();
    }

    inline void
    __attribute__((always_inline))
    ebreak (void)
    {
      riscv_arch_ebreak ();
    }

    inline void
    __attribute__((always_inline))
    wfi (void)
    {
      riscv_arch_wfi ();
    }

  // --------------------------------------------------------------------------
  } /* namespace arch */

// ----------------------------------------------------------------------------
} /* namespace riscv */

namespace os
{
  namespace arch
  {
    // ------------------------------------------------------------------------

    inline void
    __attribute__((always_inline))
    nop (void)
    {
      riscv::arch::nop ();
    }

    inline void
    __attribute__((always_inline))
    brk (void)
    {
      riscv::arch::ebreak ();
    }

    inline void
    __attribute__((always_inline))
    wfi (void)
    {
      riscv::arch::wfi ();
    }

  // --------------------------------------------------------------------------
  } /* namespace arch */

// ----------------------------------------------------------------------------
} /* namespace os */

#endif /* defined(__cplusplus) */

// ----------------------------------------------------------------------------

#endif /* RISCV_ARCH_ARCH_INSTRUCTIONS_INLINES_H_ */
