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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_CSR_FUNCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_CSR_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the RISC-V core support functions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mstatus (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mstatus"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_csr_write_mstatus (riscv_architecture_register_t value)
  {
    __asm__ volatile (

        "csrw mstatus,%[v]"

        : /* Outputs */
        : [v] "rK"(value) /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_clear_mstatus_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrrc %[r],mstatus,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : "memory" /* Clobbers */
    );

    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_set_mstatus_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrrs %[r],mstatus,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : "memory" /* Clobbers */
    );

    return tmp;
  }

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mtvec (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mtvec"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_csr_write_mtvec (riscv_architecture_register_t value)
  {
    __asm__ volatile (

        "csrw mtvec,%[v]"

        : /* Outputs */
        : [v] "rK"(value) /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mcause (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mcause"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mie (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mie"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  riscv_csr_write_mie (riscv_architecture_register_t value)
  {
    __asm__ volatile (

        "csrw mie,%[v]"

        : /* Outputs */
        : [v] "rK"(value) /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_clear_mie_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrrc %[r],mie,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : "memory" /* Clobbers */
    );

    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_set_mie_bits (riscv_architecture_register_t mask)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrrs %[r],mie,%[v]"

        : [r] "=r"(tmp) /* Outputs */
        : [v] "rK"(mask) /* Inputs */
        : "memory" /* Clobbers */
    );

    return tmp;
  }

  // --------------------------------------------------------------------------

  /**
   * @details
   * On RV32, `mcycleh` is read before and after `mcycle`; if the two
   * high values differ, the low word overflowed between the reads and
   * the sequence is repeated.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
  riscv_csr_read_mcycle (void)
  {
#if __riscv_xlen == 64

    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mcycle"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;

#else // !(__riscv_xlen == 64)

  uint32_t high;
  uint32_t low;

  do
    {
      high = riscv_csr_read_mcycle_high ();
      low = riscv_csr_read_mcycle_low ();
    }
  while (high != riscv_csr_read_mcycle_high ());

  return ((uint64_t)high << 32) | low;

#endif // __riscv_xlen == 64
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_csr_read_mcycle_low (void)
  {
#if __riscv_xlen == 32

    uint32_t tmp;

    __asm__ volatile (

        "csrr %[r],mcycle"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;

#elif __riscv_xlen == 64

  return (uint32_t)riscv_csr_read_mcycle ();

#endif // __riscv_xlen == 32
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
  riscv_csr_read_mcycle_high (void)
  {
#if __riscv_xlen == 32

    uint32_t tmp;

    __asm__ volatile (

        "csrr %[r],mcycleh"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;

#elif __riscv_xlen == 64

  return (uint32_t)(riscv_csr_read_mcycle () >> 32);

#endif // __riscv_xlen == 32
  }

  // --------------------------------------------------------------------------

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mhartid (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mhartid"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_misa (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],misa"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mvendorid (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mvendorid"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_marchid (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],marchid"

        : [r] "=r"(tmp) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
    return tmp;
  }

  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE riscv_architecture_register_t
  riscv_csr_read_mimpid (void)
  {
    riscv_architecture_register_t tmp;

    __asm__ volatile (

        "csrr %[r],mimpid"

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

    template <uint32_t csr>
    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        read (void) noexcept
    {
      static_assert (csr < 4096, "CSR numbers are 12-bit");

      architecture::register_t tmp;

      __asm__ volatile (

          "csrr %[r], %[c]"

          : [r] "=r"(tmp) /* Outputs */
          : [c] "i"(csr) /* Inputs */
          : /* Clobbers */
      );

      return tmp;
    }

    template <uint32_t csr>
    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    write (architecture::register_t value) noexcept
    {
      static_assert (csr < 4096, "CSR numbers are 12-bit");

      __asm__ volatile (

          "csrw %[c], %[v]"

          : /* Outputs */
          : [c] "i"(csr), [v] "rK"(value) /* Inputs */
          : "memory" /* Clobbers */
      );
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mstatus (void) noexcept
    {
      return riscv_csr_read_mstatus ();
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mstatus (architecture::register_t value) noexcept
    {
      riscv_csr_write_mstatus (value);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE architecture::register_t
    clear_mstatus_bits (architecture::register_t mask) noexcept
    {
      return riscv_csr_clear_mstatus_bits (mask);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE architecture::register_t
    set_mstatus_bits (architecture::register_t mask) noexcept
    {
      return riscv_csr_set_mstatus_bits (mask);
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mtvec (void) noexcept
    {
      return riscv_csr_read_mtvec ();
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mtvec (architecture::register_t value) noexcept
    {
      riscv_csr_write_mtvec (value);
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mcause (void) noexcept
    {
      return riscv_csr_read_mcause ();
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mie (void) noexcept
    {
      return riscv_csr_read_mie ();
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
    mie (architecture::register_t value) noexcept
    {
      riscv_csr_write_mie (value);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE architecture::register_t
    clear_mie_bits (architecture::register_t mask) noexcept
    {
      return riscv_csr_clear_mie_bits (mask);
    }

    MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE architecture::register_t
    set_mie_bits (architecture::register_t mask) noexcept
    {
      return riscv_csr_set_mie_bits (mask);
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint64_t
    mcycle (void) noexcept
    {
      return riscv_csr_read_mcycle ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mcycle_low (void) noexcept
    {
      return riscv_csr_read_mcycle_low ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE uint32_t
    mcycle_high (void) noexcept
    {
      return riscv_csr_read_mcycle_high ();
    }

    // ------------------------------------------------------------------------

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mhartid (void) noexcept
    {
      return riscv_csr_read_mhartid ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        misa (void) noexcept
    {
      return riscv_csr_read_misa ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mvendorid (void) noexcept
    {
      return riscv_csr_read_mvendorid ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        marchid (void) noexcept
    {
      return riscv_csr_read_marchid ();
    }

    [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
        architecture::register_t
        mimpid (void) noexcept
    {
      return riscv_csr_read_mimpid ();
    }

    // ------------------------------------------------------------------------
  } // namespace csr
} // namespace riscv

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_CSR_FUNCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
