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

#if defined(__riscv)

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_INCLUDE_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // MICRO_OS_PLUS_INCLUDE_CONFIG_H

#include <micro-os-plus/device.h>
#include <micro-os-plus/diag/trace.h>

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

// ----------------------------------------------------------------------------

using namespace micro_os_plus;

// ----------------------------------------------------------------------------

extern "C"
{
  void
  riscv_core_handle_unused_trap (void);
}

// ----------------------------------------------------------------------------

// To provide the desired functionality, redefine it in the application.
#if defined(MICRO_OS_PLUS_USE_CPP_INTERRUPTS)

namespace riscv
{
  namespace core
  {
    void __attribute__ ((weak, alias ("riscv_core_handle_unused_trap")))
    handle_exceptions (void);
  } // namespace core
} // namespace riscv

#else /* defined(MICRO_OS_PLUS_USE_CPP_INTERRUPTS) */

void __attribute__ ((weak, alias ("riscv_core_handle_unused_trap")))
riscv_core_handle_exceptions (void);

#endif // defined(MICRO_OS_PLUS_USE_CPP_INTERRUPTS)

// ----------------------------------------------------------------------------

namespace riscv
{
  namespace core
  {
    // ------------------------------------------------------------------------

    void
    handle_trap ();

    void __attribute__ ((section (".traps_handlers"))) handle_trap ()
    {
      riscv::architecture::register_t cause = riscv::csr::mcause ();
      if ((cause & RISCV_CSR_MCAUSE_INTERRUPT) != 0)
        {
          size_t index = (cause & RISCV_CSR_MCAUSE_CAUSE);
          // The `<=` is because the number is the last valid one.
          if (index <= (RISCV_INTERRUPTS_LOCAL_LAST_NUMBER))
            {
              // Call the local device interrupt handler via the pointer.
              riscv::core::local_interrupt_handlers[index]();

              return;
            }
        }
      else
        {
          size_t index = cause;
          if (index < RISCV_EXCEPTIONS_LAST_NUMBER)
            {
              // Call the single handler for all exception.
              // No need to pass the number, the handler can get
              // it again from `mcause()`.
#if defined(MICRO_OS_PLUS_USE_CPP_INTERRUPTS)
              riscv::core::handle_exceptions ();
#else
              riscv_core_handle_exceptions ();
#endif

              return;
            }
        }

#if defined(MICRO_OS_PLUS_DEBUG)
      riscv::architecture::ebreak ();
#endif // defined(MICRO_OS_PLUS_DEBUG)

      while (true)
        {
          riscv::architecture::wfi ();
        }
    }

    // ------------------------------------------------------------------------
  } // namespace core
} // namespace riscv

// Alias function to C, so that the assembly code will reach it.
extern "C" void __attribute__ ((alias ("_ZN5riscv4core11handle_trapEv")))
riscv_core_handle_trap (void);

#if defined(RISCV_INTERRUPTS_GLOBAL_LAST_NUMBER)

namespace riscv
{
  namespace interrupt
  {
    // ------------------------------------------------------------------------

    void
    handle_machine_ext (void)
    {
      // Get the current interrupt number from the PLIC.
      size_t int_num = riscv::plic::claim_interrupt ();

      // The `<=` is because the number is the last valid one.
      if (int_num <= RISCV_INTERRUPTS_GLOBAL_LAST_NUMBER)
        {
          // Call the global interrupt handler via the pointer.
          riscv::core::global_interrupt_handlers[int_num]();

          // Acknowledge the interrupt in the PLIC.
          riscv::plic::complete_interrupt (
              static_cast<riscv::plic::source_t> (int_num));

          return;
        }

#if defined(MICRO_OS_PLUS_DEBUG)
      riscv::architecture::ebreak ();
#endif // defined(MICRO_OS_PLUS_DEBUG)

      while (true)
        {
          riscv::architecture::wfi ();
        }
    }

    // ------------------------------------------------------------------------
  } // namespace interrupt
} // namespace riscv

extern "C" void
    __attribute__ ((alias ("_ZN5riscv9interrupt18handle_machine_extEv")))
    riscv_interrupt_handle_machine_ext (void);

#endif // defined(RISCV_INTERRUPTS_GLOBAL_LAST_NUMBER)

void __attribute__ ((section (".traps_handlers"), weak))
riscv_core_handle_unused_trap (void)
{
  riscv::architecture::register_t mcause = riscv::csr::mcause ();
  trace::printf ("%s() mcause=0x%0" PRIX64 "\n", __func__, mcause);

#if defined(MICRO_OS_PLUS_DEBUG)
  riscv::architecture::ebreak ();
#endif // defined(MICRO_OS_PLUS_DEBUG)

  while (true)
    {
      riscv::architecture::wfi ();
    }
}

// ----------------------------------------------------------------------------

#endif // __riscv

// ----------------------------------------------------------------------------
