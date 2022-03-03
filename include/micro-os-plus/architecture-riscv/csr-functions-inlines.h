/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

#if 0
  // Not available, due to ISA limitations (no 'r' to pass the CSR,
  // mandatory on -O0, even when called with constants).

  inline riscv_architecture_register_t
  __attribute__((always_inline))
  riscv_csr_read (uint32_t reg)
    {
      riscv_architecture_register_t tmp;

      __asm__ volatile (
          "csrr %[r],%[csr]"

          : [r] "=rm"(tmp) /* Outputs */
          : [csr] "ri"(reg) /* Inputs */
          : /* Clobbers */
      );
      return tmp;
    }

#endif

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_read_mstatus (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrr %[r],mstatus"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  static inline __attribute__ ((always_inline)) void
  riscv_csr_write_mstatus (riscv_architecture_register_t value)
  {
    __asm__ volatile(

        "csrw mstatus,%[v]"

        : /* Outputs */
        : [v] "rK"(value) /* Inputs */
        : /* Clobbers */
    );
  }

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_clear_mstatus_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrrc %[r],mstatus,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_set_mstatus_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrrs %[r],mstatus,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  // --------------------------------------------------------------------------

  /**
   * Read `mtvec` CSR.
   */
  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_read_mtvec (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrr %[r],mtvec"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  /**
   * Write `mtvec` CSR.
   */
  static inline __attribute__ ((always_inline)) void
  riscv_csr_write_mtvec (riscv_architecture_register_t value)
  {
    __asm__ volatile(

        "csrw mtvec,%[v]"

        : /* Outputs */
        : [v] "rK"(value) /* Inputs */
        : /* Clobbers */
    );
  }

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_read_mcause (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrr %[r],mcause"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_read_mie (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrr %[r],mie"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  static inline __attribute__ ((always_inline)) void
  riscv_csr_write_mie (riscv_architecture_register_t value)
  {
    __asm__ volatile(

        "csrw mie,%[v]"

        : /* Outputs */
        : [v] "rK"(value) /* Inputs */
        : /* Clobbers */
    );
  }

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_clear_mie_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrrc %[r],mie,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_set_mie_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrrs %[r],mie,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  // --------------------------------------------------------------------------

#if __riscv_xlen == 64

  /**
   * Read `mcycle` CSR.
   */
  static inline __attribute__ ((always_inline)) uint64_t
  riscv_csr_read_mcycle (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrr %[r],mcycle"

        : [r] "=rm"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;
  }

#endif // __riscv_xlen == 64

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_csr_read_mcycle_low (void)
  {
#if __riscv_xlen == 32

    uint32_t tmp;

    __asm__ volatile(

        "csrr %[r],mcycle"

        : [r] "=rm"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;

#elif __riscv_xlen == 64

  return (uint32_t)riscv_csr_read_mcycle ();

#endif // __riscv_xlen
  }

  static inline __attribute__ ((always_inline)) uint32_t
  riscv_csr_read_mcycle_high (void)
  {
#if __riscv_xlen == 32

    uint32_t tmp;

    __asm__ volatile(

        "csrr %[r],mcycleh"

        : [r] "=rm"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;

#elif __riscv_xlen == 64

  return (uint32_t) (riscv_csr_read_mcycle () >> 32);

#endif // __riscv_xlen
  }

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) riscv_architecture_register_t
  riscv_csr_read_mhartid (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile(

        "csrr %[r],mhartid"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;
  }

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

    inline __attribute__ ((always_inline)) architecture::register_t
    mstatus (void)
    {
      return riscv_csr_read_mstatus ();
    }

    inline __attribute__ ((always_inline)) void
    mstatus (architecture::register_t value)
    {
      riscv_csr_write_mstatus (value);
    }

    inline __attribute__ ((always_inline)) void
    clear_mstatus_bits (architecture::register_t mask)
    {
      riscv_csr_clear_mstatus_bits (mask);
    }

    inline __attribute__ ((always_inline)) void
    set_mstatus_bits (architecture::register_t mask)
    {
      riscv_csr_set_mstatus_bits (mask);
    }

    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) architecture::register_t
    mtvec (void)
    {
      return riscv_csr_read_mtvec ();
    }

    inline __attribute__ ((always_inline)) void
    mtvec (architecture::register_t value)
    {
      riscv_csr_write_mtvec (value);
    }

    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) architecture::register_t
    mcause (void)
    {
      return riscv_csr_read_mcause ();
    }

    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) architecture::register_t
    mie (void)
    {
      return riscv_csr_read_mie ();
    }

    inline __attribute__ ((always_inline)) void
    mie (architecture::register_t value)
    {
      riscv_csr_write_mie (value);
    }

    inline __attribute__ ((always_inline)) void
    clear_mie_bits (architecture::register_t mask)
    {
      riscv_csr_clear_mie_bits (mask);
    }

    inline __attribute__ ((always_inline)) void
    set_mie_bits (architecture::register_t mask)
    {
      riscv_csr_set_mie_bits (mask);
    }

    // ------------------------------------------------------------------------

#if __riscv_xlen == 64

    inline __attribute__ ((always_inline)) uint64_t
    mcycle (void)
    {
      return riscv_csr_read_mcycle ();
    }

#endif // __riscv_xlen == 64

    inline __attribute__ ((always_inline)) uint32_t
    mcycle_low (void)
    {
      return riscv_csr_read_mcycle_low ();
    }

    inline __attribute__ ((always_inline)) uint32_t
    mcycle_high (void)
    {
      return riscv_csr_read_mcycle_high ();
    }

    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) architecture::register_t
    mhartid (void)
    {
      return riscv_csr_read_mhartid ();
    }

    // ------------------------------------------------------------------------
  } // namespace csr
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_CSR_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
