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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include <micro-os-plus/architecture-riscv/types.h>

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
   * Write the `mstatus` CSR.
   */
  static void
  riscv_csr_write_mstatus (riscv_architecture_register_t value);

  /**
   * Clear bits in the `mstatus` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_clear_mstatus_bits (riscv_architecture_register_t mask);

  /**
   * Set bits in the `mstatus` CSR.
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
   * Write the `mtvec` CSR.
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
   * Write the `mie` CSR.
   */
  static void
  riscv_csr_write_mie (riscv_architecture_register_t value);

  /**
   * Clear bits in the `mie` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_clear_mie_bits (riscv_architecture_register_t mask);

  /**
   * Set bits in the `mie` CSR.
   */
  static riscv_architecture_register_t
  riscv_csr_set_mie_bits (riscv_architecture_register_t mask);

  // --------------------------------------------------------------------------
  // `mcycle`

  /**
   * Read the `mcycle` CSR.
   */
#if __riscv_xlen == 64
  static
#endif // __riscv_xlen == 64
      uint64_t
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

    void
    clear_mstatus_bits (architecture::register_t mask);

    void
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

    void
    clear_mie_bits (architecture::register_t mask);

    void
    set_mie_bits (architecture::register_t mask);

    // ------------------------------------------------------------------------
    // `mcycle`

    /**
     * Read the mcycle counter.
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
  } // namespace csr
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_H_

// ----------------------------------------------------------------------------
