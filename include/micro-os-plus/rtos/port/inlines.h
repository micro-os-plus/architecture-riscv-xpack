/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
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

/*
 * This file is included in all src/os-*.cpp files.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISC_RTOS_PORT_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_INLINES_H_

// ----------------------------------------------------------------------------

#include <micro-os-plus/config.h>
#include <micro-os-plus/rtos/port/declarations-c.h>

// ----------------------------------------------------------------------------

#ifdef  __cplusplus

#include <micro-os-plus/device.h>
#include <micro-os-plus/diag/trace.h>

namespace os
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace scheduler
      {

        inline void
        __attribute__((always_inline))
        greeting (void)
        {
          trace::printf ("Scheduler: µOS++ RISC-V");
          trace::printf (", preemptive");
#if defined(OS_EXCLUDE_RTOS_IDLE_SLEEP)
          trace::printf(", no WFI");
#else
          trace::printf(", WFI");
#endif
          trace::puts (".");

          // At this stage the system clock should have already been configured
          // at high speed by __initialise_hardware().
          // trace::printf ("System clock: %u Hz.\n", SystemCoreClock);
        }

        inline port::scheduler::state_t
        __attribute__((always_inline))
        lock (void)
        {
          return locked (state::locked);
        }

        inline port::scheduler::state_t
        __attribute__((always_inline))
        unlock (void)
        {
          return locked (state::unlocked);
        }

        inline bool
        __attribute__((always_inline))
        locked (void)
        {
          return lock_state != state::unlocked;
        }

        inline void
        __attribute__((always_inline))
        wait_for_interrupt (void)
        {
#if !defined(OS_EXCLUDE_RTOS_IDLE_SLEEP)
#if defined(OS_TRACE_RTOS_THREAD_CONTEXT)
          trace::printf ("%s() \n", __func__);
#endif
          riscv::arch::wfi();
#endif /* !defined(OS_EXCLUDE_RTOS_IDLE_SLEEP) */
        }

      } /* namespace scheduler */

      namespace interrupts
      {
        inline bool
        __attribute__((always_inline))
        in_handler_mode (void)
        {
          return false;
        }

        /**
         * @details
         * TBD
         */
        inline bool
        is_priority_valid (void)
        {
        	return true;
        }

        // Enter an IRQ critical section
        inline rtos::interrupts::state_t
        __attribute__((always_inline))
        critical_section::enter (void)
        {
          return 0;
        }

        // Exit an IRQ critical section
        inline void
        __attribute__((always_inline))
        critical_section::exit (rtos::interrupts::state_t state)
        {
        	riscv::arch::nop();
        }

        // ====================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

        // Enter an IRQ uncritical section
        inline rtos::interrupts::state_t
        __attribute__((always_inline))
        uncritical_section::enter (void)
        {
          return 0;
        }

        // Exit an IRQ critical section
        inline void
        __attribute__((always_inline))
        uncritical_section::exit (rtos::interrupts::state_t state)
        {
          ;
        }

#pragma GCC diagnostic pop

      } /* namespace interrupts */

      // ======================================================================

      namespace this_thread
      {
        inline void
        __attribute__((always_inline))
        prepare_suspend (void)
        {
          ;
        }

      } /* namespace this_thread */

      // ======================================================================

      inline void
      __attribute__((always_inline))
      clock_highres::start (void)
      {
        ;
      }

      inline uint32_t
      __attribute__((always_inline))
      clock_highres::input_clock_frequency_hz (void)
      {
        return 0;
      }

      inline uint32_t
      __attribute__((always_inline))
      clock_highres::cycles_per_tick (void)
      {
        return 1;
      }

      inline uint32_t
      __attribute__((always_inline))
      clock_highres::cycles_since_tick (void)
      {
        return 1;
      }

    // ======================================================================

    } /* namespace port */
  } /* namespace rtos */
} /* namespace os */

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#endif /* __cplusplus */

#endif /* MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_INLINES_H_ */
