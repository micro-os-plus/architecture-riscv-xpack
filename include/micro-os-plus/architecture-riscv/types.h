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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_TYPES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_TYPES_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-riscv/defines.h"

#include <stdint.h>

// Register types; they do not need C linkage, and are defined outside
// the `extern "C"` block to keep a consistent formatting.

#if __riscv_xlen == 32
/**
 * @brief Unsigned integer type with the width of a register.
 *
 * @details
 * `uint32_t` on RV32; the type of the CSR accessors and of the
 * values saved in a trap frame.
 */
typedef uint32_t riscv_architecture_register_t;
/**
 * @brief Signed integer type with the width of a register.
 *
 * @details
 * `int32_t` on RV32.
 */
typedef int32_t riscv_architecture_signed_register_t;
#elif __riscv_xlen == 64
/**
 * @brief Unsigned integer type with the width of a register.
 *
 * @details
 * `uint64_t` on RV64; the type of the CSR accessors and of the
 * values saved in a trap frame.
 */
typedef uint64_t riscv_architecture_register_t;
/**
 * @brief Signed integer type with the width of a register.
 *
 * @details
 * `int64_t` on RV64.
 */
typedef int64_t riscv_architecture_signed_register_t;
#else // !(__riscv_xlen == 32) && !(__riscv_xlen == 64)
#error "Unsupported __riscv_xlen"
#endif // __riscv_xlen == 32

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  /**
   * @brief Portable name of the register type.
   *
   * @details
   * Used by architecture independent µOS++ code (for example the
   * semihosting package).
   */
  typedef riscv_architecture_register_t micro_os_plus_architecture_register_t;

  /**
   * @brief Portable name of the signed register type.
   *
   * @details
   * Used by architecture independent µOS++ code.
   */
  typedef riscv_architecture_signed_register_t
      micro_os_plus_architecture_signed_register_t;

  /**
   * @brief Pointer to a trap (interrupt or exception) handler.
   *
   * @details
   * The type of the entries in the interrupt handler tables
   * (`riscv::core::local_interrupt_handlers[]` and
   * `riscv::core::global_interrupt_handlers[]`). The handlers are
   * regular C functions, called by the trap dispatcher after the
   * context was saved.
   */
  typedef void (*riscv_core_trap_handler_ptr_t) (void);

  /**
   * @brief Type of a PLIC global interrupt source id.
   *
   * @details
   * The PLIC registers are 32-bit wide. Device packages may repeat
   * this typedef, but only with the same type.
   */
  typedef uint32_t riscv_plic_source_t;

  /**
   * @brief Type of a PLIC interrupt priority or threshold.
   *
   * @details
   * The PLIC registers are 32-bit wide. Device packages may repeat
   * this typedef, but only with the same type.
   */
  typedef uint32_t riscv_plic_priority_t;

  // --------------------------------------------------------------------------

  /**
   * @brief Synchronous exception codes.
   *
   * @details
   * The values of `mcause` when the interrupt bit
   * (`RISCV_CSR_MCAUSE_INTERRUPT`) is clear, as defined by the RISC-V
   * privileged specification; codes 10 and 14 are reserved.
   */
  typedef enum
  {
    riscv_exception_misaligned_fetch = 0,
    riscv_exception_fault_fetch = 1,
    riscv_exception_illegal_instruction = 2,
    riscv_exception_breakpoint = 3,
    riscv_exception_misaligned_load = 4,
    riscv_exception_fault_load = 5,
    riscv_exception_misaligned_store = 6,
    riscv_exception_fault_store = 7,
    riscv_exception_user_ecall = 8,
    riscv_exception_supervisor_ecall = 9,
    /* 10 */
    riscv_exception_machine_ecall = 11,
    riscv_exception_page_fetch = 12,
    riscv_exception_page_load = 13,
    /* 14 */
    riscv_exception_page_store = 15
  } riscv_exceptions_enum_t;

  /**
   * @brief The highest exception code in `riscv_exceptions_enum_t`.
   *
   * @details
   * Used to size tables indexed by the exception code.
   */
#define RISCV_EXCEPTIONS_LAST_NUMBER (15u)

  // --------------------------------------------------------------------------

  /**
   * @brief Local (core) interrupt codes.
   *
   * @details
   * The values of `mcause` when the interrupt bit
   * (`RISCV_CSR_MCAUSE_INTERRUPT`) is set, which are also the bit
   * positions in `mie` and `mip` (see `RISCV_CSR_MIP_*`), as defined
   * by the RISC-V privileged specification.
   */
  typedef enum
  {
    riscv_interrupt_local_user_software = 0,
    riscv_interrupt_local_supervisor_software = 1,
    /* 2 reserved */
    riscv_interrupt_local_machine_software = 3,
    riscv_interrupt_local_user_timer = 4,
    riscv_interrupt_local_supervisor_timer = 5,
    /* 6 reserved */
    riscv_interrupt_local_machine_timer = 7,
    riscv_interrupt_local_user_ext = 8,
    riscv_interrupt_local_supervisor_ext = 9,
    /* 10 reserved */
    riscv_interrupt_local_machine_ext = 11,
    /* 12 reserved */
    /* 13 reserved */
    /* 14 reserved */
    /* 15 reserved */
  } riscv_interrupts_local_enum_t;

  // Ensure the `RISCV_CSR_MIP_*` bit masks, which use literal bit
  // numbers to be usable in assembly, match the enumeration values.
  // These are compile time checks, not part of the API.
#if !defined(__DOXYGEN__)

#if defined(__cplusplus)
#define RISCV_STATIC_ASSERT static_assert
#else // !defined(__cplusplus)
#define RISCV_STATIC_ASSERT _Static_assert
#endif // defined(__cplusplus)

  RISCV_STATIC_ASSERT (RISCV_CSR_MIP_SSIP
                           == (1ul
                               << riscv_interrupt_local_supervisor_software),
                       "RISCV_CSR_MIP_SSIP mismatch");
  RISCV_STATIC_ASSERT (RISCV_CSR_MIP_MSIP
                           == (1ul << riscv_interrupt_local_machine_software),
                       "RISCV_CSR_MIP_MSIP mismatch");
  RISCV_STATIC_ASSERT (RISCV_CSR_MIP_STIP
                           == (1ul << riscv_interrupt_local_supervisor_timer),
                       "RISCV_CSR_MIP_STIP mismatch");
  RISCV_STATIC_ASSERT (RISCV_CSR_MIP_MTIP
                           == (1ul << riscv_interrupt_local_machine_timer),
                       "RISCV_CSR_MIP_MTIP mismatch");
  RISCV_STATIC_ASSERT (RISCV_CSR_MIP_SEIP
                           == (1ul << riscv_interrupt_local_supervisor_ext),
                       "RISCV_CSR_MIP_SEIP mismatch");
  RISCV_STATIC_ASSERT (RISCV_CSR_MIP_MEIP
                           == (1ul << riscv_interrupt_local_machine_ext),
                       "RISCV_CSR_MIP_MEIP mismatch");

#undef RISCV_STATIC_ASSERT

#endif // !defined(__DOXYGEN__)

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace riscv::architecture
{
  // --------------------------------------------------------------------------

  /**
   * @brief Unsigned integer type with the width of a register.
   *
   * @details
   * The C++ name of `riscv_architecture_register_t`.
   */
  using register_t = riscv_architecture_register_t;

  /**
   * @brief Signed integer type with the width of a register.
   *
   * @details
   * The C++ name of `riscv_architecture_signed_register_t`.
   */
  using signed_register_t = riscv_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace riscv::architecture

namespace riscv::core
{
  // --------------------------------------------------------------------------

  /**
   * @brief Pointer to a trap (interrupt or exception) handler.
   *
   * @details
   * The C++ name of `riscv_core_trap_handler_ptr_t`.
   */
  using trap_handler_ptr_t = riscv_core_trap_handler_ptr_t;

  // --------------------------------------------------------------------------
} // namespace riscv::core

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  /**
   * @brief Portable C++ name of the register type.
   *
   * @details
   * Used by architecture independent µOS++ C++ code.
   */
  using register_t = riscv_architecture_register_t;

  /**
   * @brief Portable C++ name of the signed register type.
   *
   * @details
   * Used by architecture independent µOS++ C++ code.
   */
  using signed_register_t = riscv_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_TYPES_H_

// ----------------------------------------------------------------------------
