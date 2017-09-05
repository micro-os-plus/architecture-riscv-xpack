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

#include <micro-os-plus/device.h>
#include <micro-os-plus/diag/trace.h>

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

// ----------------------------------------------------------------------------

extern "C"
{
  // Forward declarations.
  void
  riscv_core_handle_trap (void);

  void
  riscv_trap_handle_unused (void);
}

// ----------------------------------------------------------------------------

// To provide the desired functionality, redefine any of these
// functions in the application.

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_misaligned_fetch (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_fault_fetch (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_illegal_instruction (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_breakpoint (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_misaligned_load (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_fault_load (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_misaligned_store (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_fault_store (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_user_ecall (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_supervisor_ecall (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_machine_ecall (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_page_fetch (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_page_load (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_exception_handle_page_store (void);

/*
 * Array of pointers to exception handlers. See Table 3.6 from Volume II.
 */
riscv_trap_handler_ptr_t __attribute__ ((section(".exceptions_array")))
riscv_exceptions_handlers[] =
  { //
    riscv_exception_handle_misaligned_fetch, /* 0 */
    riscv_exception_handle_fault_fetch, /* 1 */
    riscv_exception_handle_illegal_instruction, /* 2 */
    riscv_exception_handle_breakpoint, /* 3 */
    riscv_exception_handle_misaligned_load, /* 4 */
    riscv_exception_handle_fault_load, /* 5 */
    riscv_exception_handle_misaligned_store, /* 6 */
    riscv_exception_handle_fault_store, /* 7 */
    riscv_exception_handle_user_ecall, /* 8 */
    riscv_exception_handle_supervisor_ecall, /* 9 */
    riscv_trap_handle_unused, /* 10 */
    riscv_exception_handle_machine_ecall, /* 11 */
    riscv_exception_handle_page_fetch, /* 12 */
    riscv_exception_handle_page_load, /* 13 */
    riscv_trap_handle_unused, /* 14 */
    riscv_exception_handle_page_store /* 15 */
    };

static_assert(
    sizeof(riscv_exceptions_handlers)/sizeof(riscv_exceptions_handlers[0]) == RISCV_EXCEPTIONS_ARRAY_SIZE,
    "riscv_exceptions_handlers[] size must match RISCV_EXCEPTIONS_ARRAY_SIZE");

// ----------------------------------------------------------------------------

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_user_software (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_supervisor_software (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_machine_software (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_user_timer (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_supervisor_timer (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_machine_timer (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_user_ext (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_supervisor_ext (void);

#if !defined(RISCV_INTERRUPTS_GLOBAL_ARRAY_SIZE)

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_machine_ext (void);

#endif /* defined(RISCV_INTERRUPTS_GLOBAL_ARRAY_SIZE) */

// TODO: where do these two IRQs come from?
void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_cop (void);

void
__attribute__ ((weak, alias ("riscv_trap_handle_unused")))
riscv_interrupt_local_handle_host (void);

/*
 * Array of pointers to architecture specific local interrupt handlers.
 * See Table 3.6 from Volume II.
 * Devices may not implement all of them, see device specific documentation.
 */
riscv_trap_handler_ptr_t __attribute__ ((section(".interrupts_local_arch_array")))
riscv_interrupts_local_arch_handlers[] =
  { //
    riscv_interrupt_local_handle_user_software, /* 0 */
    riscv_interrupt_local_handle_supervisor_software, /* 1 */
    riscv_trap_handle_unused, /* 2 */
    riscv_interrupt_local_handle_machine_software, /* 3 */
    riscv_interrupt_local_handle_user_timer, /* 4 */
    riscv_interrupt_local_handle_supervisor_timer, /* 5 */
    riscv_trap_handle_unused, /* 6 */
    riscv_interrupt_local_handle_machine_timer, /* 7 */
    riscv_interrupt_local_handle_user_ext, /* 8 */
    riscv_interrupt_local_handle_supervisor_ext, /* 9 */
    riscv_trap_handle_unused, /* 10 */
    riscv_interrupt_local_handle_machine_ext, /* 11 */
    /* Warning, not in the specs. */
    /* TODO: check if they should be here. */
    riscv_interrupt_local_handle_cop, /* 12 */
    riscv_interrupt_local_handle_host, /* 13 */
    riscv_trap_handle_unused, /* 14 */
    riscv_trap_handle_unused /* 15 */
    };

// The linker script should place the device specific handlers right
// after this array (by use of the `.interrupts_local_device_array` section).

static_assert(
    sizeof(riscv_interrupts_local_arch_handlers)/sizeof(riscv_interrupts_local_arch_handlers[0])
    == RISCV_INTERRUPTS_LOCAL_ARCH_ARRAY_SIZE,
    "riscv_interrupts_local_arch_handlers[] size must match RISCV_INTERRUPTS_LOCAL_ARCH_ARRAY_SIZE");

// ----------------------------------------------------------------------------

#if !defined(RISCV_INTERRUPTS_LOCAL_DEVICE_ARRAY_SIZE)
#define RISCV_INTERRUPTS_LOCAL_DEVICE_ARRAY_SIZE (0)
#endif /* !defined(RISCV_INTERRUPTS_LOCAL_DEVICE_ARRAY_SIZE) */

extern "C" void
__attribute__ ((section(".trap_handlers")))
riscv_core_handle_trap (void)
{
  riscv::arch::register_t cause = riscv::csr::mcause ();
  if ((cause & MCAUSE_INT) != 0)
    {
      size_t index = (cause & MCAUSE_CAUSE);
      if (index < RISCV_INTERRUPTS_LOCAL_ARCH_ARRAY_SIZE)
        {
          // Call the local architecture interrupt handler via the pointer.
          riscv_interrupts_local_arch_handlers[index] ();
          return;
        }

#if RISCV_INTERRUPTS_LOCAL_DEVICE_ARRAY_SIZE > 0

      extern riscv_trap_handler_ptr_t
      riscv_interrupts_local_device_handlers[];

      index -= RISCV_INTERRUPTS_LOCAL_ARCH_ARRAY_SIZE;
      if (index
          < RISCV_INTERRUPTS_LOCAL_DEVICE_ARRAY_SIZE)
        {
          // Call the local device interrupt handler via the pointer.
          riscv_interrupts_local_device_handlers[index] ();
          return;
        }

#endif /* RISCV_INTERRUPTS_LOCAL_DEVICE_ARRAY_SIZE > 0 */
    }
  else
    {
      size_t index = cause;
      if (index < RISCV_EXCEPTIONS_ARRAY_SIZE)
        {
          // Call the exception handler via the pointer.
          riscv_exceptions_handlers[index] ();
          return;
        }
    }

#if defined(DEBUG)
  riscv::arch::ebreak ();
#endif /* defined(DEBUG) */

  while (true)
    {
      riscv::arch::nop ();
    }
}

#if defined(RISCV_INTERRUPTS_GLOBAL_ARRAY_SIZE)

plic_instance_t g_plic;

void
__attribute__ ((section(".trap_handlers")))
riscv_interrupt_local_handle_machine_ext (void)
  {
    // TODO: redo PLIC API to use static inlines.
    size_t int_num = PLIC_claim_interrupt (&g_plic);
    if (int_num < RISCV_INTERRUPTS_GLOBAL_ARRAY_SIZE)
      {
        // Call the global interrupt handler via the pointer.
        riscv_interrupts_global_handlers[int_num] ();
        PLIC_complete_interrupt (&g_plic, (plic_source) int_num);
        return;
      }

#if defined(DEBUG)
    riscv::arch::ebreak ();
#endif /* defined(DEBUG) */

    while (true)
      {
        riscv::arch::nop ();
      }

  }
#endif /* defined(RISCV_INTERRUPTS_GLOBAL_ARRAY_SIZE) */

void
__attribute__ ((section(".trap_handlers"),weak))
riscv_trap_handle_unused (void)
{
  riscv::arch::register_t mcause = riscv::csr::mcause ();
  os::trace::printf ("%s() mcause=0x%0" PRIX64 "\n", __func__, mcause);

#if defined(DEBUG)
  riscv::arch::ebreak ();
#endif /* defined(DEBUG) */

  while (true)
    {
      riscv::arch::nop ();
    }
}

// ----------------------------------------------------------------------------
