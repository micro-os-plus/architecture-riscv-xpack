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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_TYPES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_TYPES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

#if __riscv_xlen == 32
  typedef uint32_t riscv_architecture_register_t;
  typedef int32_t riscv_architecture_signed_register_t;
#elif __riscv_xlen == 64
typedef uint64_t riscv_architecture_register_t;
typedef int64_t riscv_architecture_signed_register_t;
#endif // __riscv_xlen

  typedef riscv_architecture_register_t micro_os_plus_architecture_register_t;
  typedef riscv_architecture_signed_register_t
      micro_os_plus_architecture_signed_register_t;

  typedef void (*riscv_core_trap_handler_ptr_t) (void);

  // --------------------------------------------------------------------------

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

#define RISCV_EXCEPTIONS_LAST_NUMBER (15u)

  // --------------------------------------------------------------------------
  // Values from Table 3.6.

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

  using register_t = riscv_architecture_register_t;
  using signed_register_t = riscv_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace riscv::architecture

namespace riscv::core
{
  // --------------------------------------------------------------------------

  using trap_handler_ptr_t = riscv_core_trap_handler_ptr_t;

  // --------------------------------------------------------------------------
} // namespace riscv::core

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  using register_t = riscv_architecture_register_t;
  using signed_register_t = riscv_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_ARCH_TYPES_H_

// ----------------------------------------------------------------------------
