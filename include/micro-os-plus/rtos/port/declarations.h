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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_DECLARATIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_DECLARATIONS_H_

// ----------------------------------------------------------------------------

/*
 * This file is included in `micro-os-plus/rtos.h` to customise
 * it with Cortex-M specific declarations.
 */

#if defined(MICRO_OS_PLUS_HAS_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // MICRO_OS_PLUS_HAS_CONFIG_H

// ----------------------------------------------------------------------------

#include <micro-os-plus/architecture.h>

#include <micro-os-plus/rtos/port/defines.h>
#include <micro-os-plus/rtos/port/declarations-c.h>
#include <micro-os-plus/startup/defines.h>

// ----------------------------------------------------------------------------

#include <signal.h>
// Platform definitions
#include <sys/time.h>

// ----------------------------------------------------------------------------

#ifdef __cplusplus

// ----------------------------------------------------------------------------

#include <cstdint>
#include <cstddef>

// ----------------------------------------------------------------------------

namespace micro_os_plus
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace stack
      {
        // Stack word.
        using element_t = micro_os_plus_port_thread_stack_element_t;

        // Align stack to 8 bytes.
        using allocation_element_t
            = micro_os_plus_port_thread_stack_allocation_element_t;

        // Initial value for the minimum stack size in bytes.
        constexpr std::size_t min_size_bytes
            = MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES;

        // Initial value for the default stack size in bytes.
        constexpr std::size_t default_size_bytes
            = MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES;

        // Used to fill in the stack.
        constexpr element_t magic
            = MICRO_OS_PLUS_INTEGER_STARTUP_STACK_FILL_MAGIC; // DEADBEEF

      } // namespace stack

      namespace interrupts
      {
        // Type to store the entire processor interrupts mask.
        using state_t = micro_os_plus_port_interrupts_state_t;

        namespace state
        {
          constexpr state_t init = 0;
        } // namespace state

      } // namespace interrupts

      namespace scheduler
      {
        using state_t = micro_os_plus_port_scheduler_state_t;

        namespace state
        {
          constexpr state_t locked = true;
          constexpr state_t unlocked = false;
          constexpr state_t init = unlocked;
        } // namespace state

        extern state_t lock_state;

      } // namespace scheduler

      using thread_context_t = struct context_s
      {
        // On Cortex-M cores the context itself is stored on the stack,
        // only the stack pointer needs to be preserved.
        stack::element_t* stack_ptr;
      };

      // ----------------------------------------------------------------------
    } // namespace port
  } // namespace rtos
} // namespace micro_os_plus

// ----------------------------------------------------------------------------

#endif // __cplusplus

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_RTOS_PORT_DECLARATIONS_H_

// ----------------------------------------------------------------------------
