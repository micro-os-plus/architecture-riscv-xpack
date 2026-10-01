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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-riscv/types.h"

// ----------------------------------------------------------------------------
// RISC-V CSR support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

#if 0
  // Not available, due to ISA limitations.
  // The workaround is to use distinct functions
  // for each CSR. There are only 4096 of them.

  riscv_architecture_register_t
  riscv_csr_read (uint32_t reg);

  void
  riscv_csr_write (uint32_t reg, riscv_architecture_register_t value);
#endif

  // --------------------------------------------------------------------------
  // `mstatus`

  /**
   * Read the `mstatus` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mstatus (void);

  /**
   * @brief Write the `mstatus` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses are not moved across it; this is required when the
   * function is used to delimit critical sections.
   */
  static void
  riscv_csr_write_mstatus (riscv_architecture_register_t value);

  /**
   * @brief Clear bits in the `mstatus` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses are not moved across it; this is required when the
   * function is used to delimit critical sections.
   */
  static riscv_architecture_register_t
  riscv_csr_clear_mstatus_bits (riscv_architecture_register_t mask);

  /**
   * @brief Set bits in the `mstatus` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses are not moved across it; this is required when the
   * function is used to delimit critical sections.
   */
  static riscv_architecture_register_t
  riscv_csr_set_mstatus_bits (riscv_architecture_register_t mask);

  // --------------------------------------------------------------------------
  // `mtvec`

  /**
   * Read the `mtvec` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mtvec (void);

  /**
   * @brief Write the `mtvec` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses (for example the initialisation of a vector table) are
   * not moved after the trap vector is changed.
   */
  static void
  riscv_csr_write_mtvec (riscv_architecture_register_t value);

  // --------------------------------------------------------------------------
  // `mcause`

  /**
   * Read the `mcause` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mcause (void);

  // --------------------------------------------------------------------------
  // `mie`

  /**
   * Read the `mie` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mie (void);

  /**
   * @brief Write the `mie` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses are not moved across it; this is required when the
   * function is used to delimit critical sections.
   */
  static void
  riscv_csr_write_mie (riscv_architecture_register_t value);

  /**
   * @brief Clear bits in the `mie` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses are not moved across it; this is required when the
   * function is used to delimit critical sections.
   */
  static riscv_architecture_register_t
  riscv_csr_clear_mie_bits (riscv_architecture_register_t mask);

  /**
   * @brief Set bits in the `mie` CSR.
   *
   * @details
   * The instruction is also a compiler memory barrier, so memory
   * accesses are not moved across it; this is required when the
   * function is used to delimit critical sections.
   */
  static riscv_architecture_register_t
  riscv_csr_set_mie_bits (riscv_architecture_register_t mask);

  // --------------------------------------------------------------------------
  // `mcycle`

  /**
   * @brief Read the 64-bit `mcycle` CSR.
   * @par Parameters
   *  None.
   * @return The number of clock cycles executed by the hart.
   *
   * @details
   * On RV64 the counter is read with a single `csrr` instruction.
   *
   * On RV32 the counter is split between `mcycle` and `mcycleh`, and
   * cannot be read atomically; the high word is read before and after
   * the low word, and the sequence is repeated if the low word
   * overflowed in between, so the result is always consistent.
   */
  static uint64_t
  riscv_csr_read_mcycle (void);

  static uint32_t
  riscv_csr_read_mcycle_low (void);

  static uint32_t
  riscv_csr_read_mcycle_high (void);

  // --------------------------------------------------------------------------
  // `mhartid`

  /**
   * Read the `mhartid` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mhartid (void);

  // --------------------------------------------------------------------------
  // `misa`

  /**
   * @brief Read the `misa` CSR (machine ISA register).
   * @par Parameters
   *  None.
   * @return The value of the CSR.
   *
   * @details
   * The `MXL` field, in the two most significant bits, encodes the
   * native register width (1 = 32, 2 = 64, 3 = 128 bits); bits 0 to
   * 25 flag the supported extensions, one per letter (`A` to `Z`).
   * The register may legally read as zero, if not implemented.
   */
  static riscv_architecture_register_t
  riscv_csr_read_misa (void);

  // --------------------------------------------------------------------------
  // `mvendorid`

  /**
   * @brief Read the `mvendorid` CSR (vendor ID register).
   * @par Parameters
   *  None.
   * @return The value of the CSR.
   *
   * @details
   * The JEDEC manufacturer ID of the core provider: bits 6:0 hold
   * the ID within the bank, without the parity bit, and bits 31:7
   * the number of `0x7F` continuation codes. Zero means that the
   * field is not implemented, or that the core is non-commercial.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mvendorid (void);

  // --------------------------------------------------------------------------
  // `marchid`

  /**
   * @brief Read the `marchid` CSR (architecture ID register).
   * @par Parameters
   *  None.
   * @return The value of the CSR.
   *
   * @details
   * Encodes the base microarchitecture of the hart, together with
   * `mvendorid`. Zero means not implemented.
   */
  static riscv_architecture_register_t
  riscv_csr_read_marchid (void);

  // --------------------------------------------------------------------------
  // `mimpid`

  /**
   * @brief Read the `mimpid` CSR (implementation ID register).
   * @par Parameters
   *  None.
   * @return The value of the CSR.
   *
   * @details
   * Encodes the version of the processor implementation. Zero means
   * not implemented.
   */
  static riscv_architecture_register_t
  riscv_csr_read_mimpid (void);

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace csr
  {
    // ------------------------------------------------------------------------
    // `mstatus`

    architecture::register_t
    mstatus (void);

    void
    mstatus (architecture::register_t value);

    /**
     * @brief Clear bits in the `mstatus` CSR.
     * @param [in] mask The bits to clear.
     * @return The previous value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_clear_mstatus_bits()`. The bits
     * are cleared atomically, with a single `csrrc` instruction; the
     * returned value can be used to restore the previous state (for
     * example the interrupt enable bits, at the end of a critical
     * section).
     */
    architecture::register_t
    clear_mstatus_bits (architecture::register_t mask);

    /**
     * @brief Set bits in the `mstatus` CSR.
     * @param [in] mask The bits to set.
     * @return The previous value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_set_mstatus_bits()`. The bits
     * are set atomically, with a single `csrrs` instruction; the
     * returned value can be used to restore the previous state (for
     * example the interrupt enable bits, at the end of a critical
     * section).
     */
    architecture::register_t
    set_mstatus_bits (architecture::register_t mask);

    // ------------------------------------------------------------------------
    // `mtvec`

    architecture::register_t
    mtvec (void);

    void
    mtvec (architecture::register_t value);

    // ------------------------------------------------------------------------
    // `mcause`

    architecture::register_t
    mcause (void);

    // ------------------------------------------------------------------------
    // `mie`

    architecture::register_t
    mie (void);

    void
    mie (architecture::register_t value);

    /**
     * @brief Clear bits in the `mie` CSR.
     * @param [in] mask The bits to clear.
     * @return The previous value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_clear_mie_bits()`. The bits
     * are cleared atomically, with a single `csrrc` instruction; the
     * returned value can be used to restore the previous state (for
     * example the interrupt enable bits, at the end of a critical
     * section).
     */
    architecture::register_t
    clear_mie_bits (architecture::register_t mask);

    /**
     * @brief Set bits in the `mie` CSR.
     * @param [in] mask The bits to set.
     * @return The previous value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_set_mie_bits()`. The bits
     * are set atomically, with a single `csrrs` instruction; the
     * returned value can be used to restore the previous state (for
     * example the interrupt enable bits, at the end of a critical
     * section).
     */
    architecture::register_t
    set_mie_bits (architecture::register_t mask);

    // ------------------------------------------------------------------------
    // `mcycle`

    /**
     * @brief Read the 64-bit `mcycle` counter.
     * @par Parameters
     *  None.
     * @return The number of clock cycles executed by the hart.
     *
     * @details
     * The C++ equivalent of `riscv_csr_read_mcycle()`; on RV32 the
     * result is consistent even if the low word overflows during
     * the read.
     */
    uint64_t
    mcycle (void);

    uint32_t
    mcycle_low (void);

    uint32_t
    mcycle_high (void);

    // ------------------------------------------------------------------------
    // `mhartid`

    architecture::register_t
    mhartid (void);

    // ------------------------------------------------------------------------
    // `misa`

    /**
     * @brief Read the `misa` CSR (machine ISA register).
     * @par Parameters
     *  None.
     * @return The value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_read_misa()`.
     */
    architecture::register_t
    misa (void);

    // ------------------------------------------------------------------------
    // `mvendorid`

    /**
     * @brief Read the `mvendorid` CSR (vendor ID register).
     * @par Parameters
     *  None.
     * @return The value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_read_mvendorid()`.
     */
    architecture::register_t
    mvendorid (void);

    // ------------------------------------------------------------------------
    // `marchid`

    /**
     * @brief Read the `marchid` CSR (architecture ID register).
     * @par Parameters
     *  None.
     * @return The value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_read_marchid()`.
     */
    architecture::register_t
    marchid (void);

    // ------------------------------------------------------------------------
    // `mimpid`

    /**
     * @brief Read the `mimpid` CSR (implementation ID register).
     * @par Parameters
     *  None.
     * @return The value of the CSR.
     *
     * @details
     * The C++ equivalent of `riscv_csr_read_mimpid()`.
     */
    architecture::register_t
    mimpid (void);

    // ------------------------------------------------------------------------
  } // namespace csr
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/csr-functions-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_H_

// ----------------------------------------------------------------------------
