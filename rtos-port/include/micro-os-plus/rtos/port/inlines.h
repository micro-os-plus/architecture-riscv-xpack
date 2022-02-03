/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

/*
 * This file is included in all src/os-*.cpp files.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISC_RTOS_PORT_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_INLINES_H_

// ----------------------------------------------------------------------------

#if defined(HAVE_MICRO_OS_PLUS_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // HAVE_MICRO_OS_PLUS_CONFIG_H

// ----------------------------------------------------------------------------

#include <micro-os-plus/rtos/port/declarations-c.h>

// ----------------------------------------------------------------------------

#ifdef __cplusplus

// ----------------------------------------------------------------------------

#include <micro-os-plus/device.h>
#include <micro-os-plus/diag/trace.h>

// ----------------------------------------------------------------------------

namespace micro_os_plus
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace scheduler
      {

        inline __attribute__ ((always_inline)) void
        greeting (void)
        {
          trace::printf ("Scheduler: µOS++ RISC-V");
          trace::printf (", preemptive");
#if defined(MICRO_OS_PLUS_EXCLUDE_RTOS_IDLE_SLEEP)
          trace::printf (", no WFI");
#else
          trace::printf (", WFI");
#endif
          trace::puts (".");

          // At this stage the system clock should have already been configured
          // at high speed by __initialise_hardware().
          // trace::printf ("System clock: %u Hz.\n", SystemCoreClock);
        }

        inline __attribute__ ((always_inline)) port::scheduler::state_t
        lock (void)
        {
          return locked (state::locked);
        }

        inline __attribute__ ((always_inline)) port::scheduler::state_t
        unlock (void)
        {
          return locked (state::unlocked);
        }

        inline __attribute__ ((always_inline)) bool
        locked (void)
        {
          return lock_state != state::unlocked;
        }

        inline __attribute__ ((always_inline)) void
        wait_for_interrupt (void)
        {
#if !defined(MICRO_OS_PLUS_EXCLUDE_RTOS_IDLE_SLEEP)
#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
          trace::printf ("%s() \n", __func__);
#endif
          riscv::architecture::wfi ();
#endif // !defined(MICRO_OS_PLUS_EXCLUDE_RTOS_IDLE_SLEEP)
        }

      } // namespace scheduler

      namespace interrupts
      {
        inline __attribute__ ((always_inline)) bool
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
        inline __attribute__ ((always_inline)) rtos::interrupts::state_t
        critical_section::enter (void)
        {
          return 0;
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

        // Exit an IRQ critical section
        inline __attribute__ ((always_inline)) void
        critical_section::exit (rtos::interrupts::state_t state)
        {
          riscv::architecture::nop ();
        }

#pragma GCC diagnostic pop

        // ====================================================================

        // Enter an IRQ uncritical section
        inline __attribute__ ((always_inline)) rtos::interrupts::state_t
        uncritical_section::enter (void)
        {
          return 0;
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

        // Exit an IRQ critical section
        inline __attribute__ ((always_inline)) void
        uncritical_section::exit (rtos::interrupts::state_t state)
        {
          ;
        }

#pragma GCC diagnostic pop

      } // namespace interrupts

      // ======================================================================

      namespace this_thread
      {
        inline __attribute__ ((always_inline)) void
        prepare_suspend (void)
        {
          ;
        }

      } // namespace this_thread

      // ======================================================================

      inline __attribute__ ((always_inline)) void
      clock_highres::start (void)
      {
        ;
      }

      inline __attribute__ ((always_inline)) uint32_t
      clock_highres::input_clock_frequency_hz (void)
      {
        return 0;
      }

      inline __attribute__ ((always_inline)) uint32_t
      clock_highres::cycles_per_tick (void)
      {
        return 1;
      }

      inline __attribute__ ((always_inline)) uint32_t
      clock_highres::cycles_since_tick (void)
      {
        return 1;
      }

      // ======================================================================

    } // namespace port
  } // namespace rtos
} // namespace micro_os_plus

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#endif // __cplusplus

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_INLINES_H_

// ----------------------------------------------------------------------------
