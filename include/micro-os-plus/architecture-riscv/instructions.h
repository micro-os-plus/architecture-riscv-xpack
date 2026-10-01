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
   * @brief Execute the `nop` instruction.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * Does nothing; usually used for short delays or as a placeholder.
   * It is not a memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_architecture_nop (void);

  /**
   * @brief Execute the `ebreak` instruction.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * Enters the debugger, if one is attached; otherwise it raises a
   * breakpoint exception (`riscv_exception_breakpoint`).
   *
   * The instruction is also a compiler memory barrier, so all memory
   * writes issued before it are visible to a debugger inspecting the
   * target when the breakpoint is hit.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_architecture_ebreak (void);

  /**
   * @brief Execute the `wfi` (wait for interrupt) instruction.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * Stalls the hart, possibly in a low power state, until an
   * interrupt is pending; the interrupt is taken only if enabled. The
   * instruction may also complete earlier, so it must be used in a
   * loop that checks the wake-up condition.
   *
   * The instruction is also a compiler memory barrier, so variables
   * modified by interrupt handlers are re-read after the core wakes
   * up; without it, loops like `while (!flag) wfi();` may never
   * observe the change.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_architecture_wfi (void);

  /**
   * @brief Execute the `fence iorw, iorw` instruction.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * A full memory and I/O fence: all memory and device accesses issued
   * before it are ordered before those issued after it, as observed
   * by other harts and devices. It is also a compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_architecture_fence (void);

  /**
   * @brief Execute the `fence.i` instruction (Zifencei).
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * Synchronises the instruction fetch of the current hart with the
   * preceding stores, for example after code was written to memory.
   *
   * Emitted via its `.insn` encoding, so it assembles even when
   * `_zifencei` is not part of `-march` (GCC 12 and later require it
   * for the `fence.i` mnemonic). On cores that do not implement
   * Zifencei, executing it raises an illegal instruction exception.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_architecture_fence_i (void);

  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C.

  /**
   * @brief No operation.
   * @par Parameters
   *  None.
   * @par Returns
   *  Nothing.
   *
   * @details
   * The portable µOS++ name; on RISC-V it executes `nop`.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_nop (void);

  /**
   * @brief Breakpoint instruction.
   *
   * @details
   * On RISC-V, it is implemented with the `ebreak` instruction, which
   * is also a compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_brk (void);

  /**
   * @brief Wait for interrupt.
   *
   * @details
   * On RISC-V, it is implemented with the `wfi` instruction, which
   * is also a compiler memory barrier, so variables modified by
   * interrupt handlers are re-read after the core wakes up.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_wfi (void);

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * Ensures that all memory and I/O accesses issued before this call are
   * ordered before any memory or I/O access after it. It also acts as a
   * compiler memory barrier.
   *
   * On RISC-V, it is implemented with the `fence iorw, iorw`
   * instruction. Unlike the Arm `dsb`, a RISC-V fence only orders the
   * accesses, it does not wait for their completion; CSR writes are
   * already serialised by the architecture.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_data_barrier (void);

  /**
   * @brief Instruction synchronisation barrier.
   *
   * @details
   * Ensures that the instructions after this call are fetched only
   * after the preceding stores (for example code written to memory) are
   * visible to the instruction fetch of the current hart. Usually
   * called right after `micro_os_plus_architecture_data_barrier()`.
   *
   * On RISC-V, it is implemented with the `fence.i` instruction, which
   * requires the Zifencei extension.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_instruction_barrier (void);

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
     * @brief Execute the `nop` instruction.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_architecture_nop()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    nop (void) noexcept;

    /**
     * @brief Execute the `ebreak` instruction.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_architecture_ebreak()`; it is also a
     * compiler memory barrier.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    ebreak (void) noexcept;

    /**
     * @brief Execute the `wfi` instruction.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_architecture_wfi()`; it is also a
     * compiler memory barrier, and must be used in a loop.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    wfi (void) noexcept;

    /**
     * @brief Execute the `fence iorw, iorw` instruction.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_architecture_fence()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    fence (void) noexcept;

    /**
     * @brief Execute the `fence.i` instruction.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `riscv_architecture_fence_i()`; it requires
     * the Zifencei extension.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    fence_i (void) noexcept;

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
     * @brief No operation.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_nop()`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    nop (void) noexcept;

    /**
     * @brief Breakpoint.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_brk()`; on
     * RISC-V it executes `ebreak`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    brk (void) noexcept;

    /**
     * @brief Wait for interrupt.
     * @par Parameters
     *  None.
     * @par Returns
     *  Nothing.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_wfi()`; on
     * RISC-V it executes `wfi`.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    wfi (void) noexcept;

    /**
     * @brief Data synchronisation barrier.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_data_barrier()`;
     * on RISC-V, it is implemented with the `fence iorw, iorw`
     * instruction.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    data_barrier (void) noexcept;

    /**
     * @brief Instruction synchronisation barrier.
     *
     * @details
     * The C++ equivalent of
     * `micro_os_plus_architecture_instruction_barrier()`; on RISC-V,
     * it is implemented with the `fence.i` instruction.
     */
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    instruction_barrier (void) noexcept;

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
