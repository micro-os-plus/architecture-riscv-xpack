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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_INSTRUCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-riscv/defines.h"

#include <stdint.h>

// ----------------------------------------------------------------------------

// Declarations of RISC-V functions to wrap architecture instructions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // Architecture assembly instructions in C.

  /**
   * `nop` instruction.
   */
  static void
  riscv_architecture_nop (void);

  /**
   * `ebreak` instruction.
   */
  static void
  riscv_architecture_ebreak (void);

  /**
   * `wfi` instruction.
   */
  static void
  riscv_architecture_wfi (void);

  /**
   * `fence iorw, iorw` instruction (full memory and I/O fence).
   */
  static void
  riscv_architecture_fence (void);

  /**
   * `fence.i` instruction (Zifencei, instruction fetch fence).
   *
   * @details
   * Emitted via its `.insn` encoding, so it assembles even when
   * `_zifencei` is not part of `-march` (GCC 12 and later require it
   * for the `fence.i` mnemonic). On cores that do not implement
   * Zifencei, executing it raises an illegal instruction exception.
   */
  static void
  riscv_architecture_fence_i (void);

  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C.

  /**
   * `nop` instruction.
   */
  static void
  micro_os_plus_architecture_nop (void);

  /**
   * `break` instruction.
   */
  static void
  micro_os_plus_architecture_brk (void);

  /**
   * `wfi` instruction.
   */
  static void
  micro_os_plus_architecture_wfi (void);

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace architecture
  {
    // ------------------------------------------------------------------------
    // Architecture assembly instructions in C++.

    /**
     * The assembler `nop` instruction.
     */
    void
    nop (void);

    /**
     * The assembler `ebreak` instruction.
     */
    void
    ebreak (void);

    /**
     * The assembler `wfi` instruction.
     */
    void
    wfi (void);

    /**
     * The assembler `fence iorw, iorw` instruction.
     */
    void
    fence (void);

    /**
     * The assembler `fence.i` instruction.
     */
    void
    fence_i (void);

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace riscv

// ----------------------------------------------------------------------------
// Inline functions.
namespace micro_os_plus
{
  namespace architecture
  {
    // ------------------------------------------------------------------------
    // Portable architecture assembly instructions in C++.

    /**
     * The assembler `nop` instruction.
     */
    void
    nop (void);

    /**
     * The assembler `break` instruction.
     */
    void
    brk (void);

    /**
     * The assembler `wfi` instruction.
     */
    void
    wfi (void);

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace micro_os_plus

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/instructions-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------
