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

#if defined(__riscv)

// ----------------------------------------------------------------------------

#if defined(HAVE_MICRO_OS_PLUS_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // HAVE_MICRO_OS_PLUS_CONFIG_H

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_INCLUDE_RTOS)

// ----------------------------------------------------------------------------

#include <string.h>
#include <cassert>

#include <micro-os-plus/rtos.h>

// #include <micro-os-plus/architecture-riscv/exception-handlers.h>

#include <micro-os-plus/device.h>

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_INTEGER_RTOS_CRITICAL_SECTION_INTERRUPT_PRIORITY)
#error \
    "MICRO_OS_PLUS_INTEGER_RTOS_CRITICAL_SECTION_INTERRUPT_PRIORITY should not be used with RISC-V devices."
#endif

// ----------------------------------------------------------------------------

#if defined(__ARM_ARCH_6M__)
extern uint32_t __vectors_start;
#endif

// ----------------------------------------------------------------------------

extern "C"
{
  extern unsigned int __heap_end__;
  extern unsigned int __stack;
}

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

        typedef struct frame_s
        {
          stack::element_t x;
        } frame_t;
      } // namespace stack

      /**
       * @brief Create a new thread context on the stack.
       * @param [in] context Pointer to thread context.
       * @param [in] func Pointer to function to execute in the new context.
       * @param [in] args Function arguments.
       *
       * @details
       * Initialise the stack with a repetitive pattern; create an
       * exception stack frame (at stack top) such that a later
       * PendSV will pass control to the new context.
       */
      void
      context::create (void* context, void* func, void* args)
      {
#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
        trace::printf ("port::context::%s(%p)\n", __func__, context);
#endif
        class rtos::thread::context* th_ctx
            = static_cast<class rtos::thread::context*> (context);

        class rtos::thread::stack& stack = th_ctx->stack ();

        rtos::thread::stack::element_t* p = stack.top ();

        // Be sure the stack is large enough to hold at least
        // two exception frames.
        assert ((p - stack.bottom ()) > (int)(2 * sizeof (stack::frame_t)));

        p -= (sizeof (stack::frame_t)
              / sizeof (rtos::thread::stack::element_t));

        // Align the frame to 8 bytes than leave one more word for the extra
        // stack element, r14_exec_return, which is the 9th.
        // Note: if the thread stack is not aligned at an 8 byte boundary,
        // var_args() will fail (for example printf() does not floats/doubles).
        if ((reinterpret_cast<uintptr_t> (p) & 3) != 0)
          {
            p = (rtos::thread::stack::element_t*)(((int)p) & (~3));
          }

        if ((reinterpret_cast<uintptr_t> (p) & 7) == 0)
          {
            --p;
          }

        // For convenience, use the stack frame structure.
        stack::frame_t* f = reinterpret_cast<stack::frame_t*> (p);

        // The stack as if after a context save.

        // Thread starts in thumb state (T bit set).
        f->x = 0x00000000;

        // Store the current stack pointer in the context.
        th_ctx->port_.stack_ptr = p;

        // Guarantee that the stack is properly aligned.
        // assert((((int )(&f->r0)) & 7) == 0);
      }

      /**
       * @brief Start the SysTick clock.
       *
       * @details
       * Some vendors libraries (like ST HAL) already initialise SysTick
       * during their code, but with a default rate.
       *
       * It is here explicitly to be sure it is always done properly,
       * with the required rate.
       */
      void
      clock_systick::start (void)
      {
#if defined(NDEBUG)
        // SysTick_Config (SystemCoreClock /
        // rtos::clock_systick::frequency_hz);
#else
        // assert(
        //    SysTick_Config (SystemCoreClock /
        //    rtos::clock_systick::frequency_hz)
        //        == 0);
#endif

        // Set SysTick interrupt priority to the lowest level (highest value).
        // NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
      }

      // ----------------------------------------------------------------------

      namespace scheduler
      {
        state_t lock_state;

        result_t
        initialize (void)
        {
          // __disable_irq ();

          return result::ok;
        }

        /**
         * @brief Start the scheduler and pass control to the main thread.
         *
         * @details
         * TBD
         */
        void
#if defined(__ARM_ARCH_6M__)
            __attribute__ ((optimize ("no-delete-null-pointer-checks")))
#endif
            start (void)
        {
#if defined(MICRO_OS_PLUS_TRACE_RTOS_SCHEDULER)
          trace::printf ("port::scheduler::%s() \n", __func__);
#endif

          // TBD

          // One disadvantage of this simple method is that
          // the first context switch will want to save the initial SP
          // somewhere, so prepare a fake thread context.
          // Don't worry for being on the stack, this is used
          // only once and can be overridden later.
          os_thread_t fake_thread;
          memset (&fake_thread, 0, sizeof (os_thread_t));

          fake_thread.name = "fake_thread";
          rtos::thread* pth = (rtos::thread*)&fake_thread;

          // Make the fake thread look like the current thread.
          rtos::scheduler::current_thread_ = pth;

          // Trigger the PendSV; the exception will happen a bit later,
          // after re-enabling the interrupts.
          scheduler::reschedule ();

          lock_state = state::init;

          // Enable all interrupts; allow PendSV to occur.
          // __enable_irq ();

          // The context switch will occur somewhere here.
          for (;;)
            riscv::architecture::nop ();

          /* NOTREACHED */
        }

        // --------------------------------------------------------------------

        state_t
        locked (state_t state)
        {
          os_assert_throw (!interrupts::in_handler_mode (), EPERM);

          state_t tmp;

          {
            rtos::interrupts::critical_section ics;

            tmp = lock_state;
            lock_state = state;
          }

          return tmp;
        }

        // --------------------------------------------------------------------

        /**
         * @brief Reschedule the next thread.
         *
         * @details
         * TBD
         *
         * @note Can be invoked from Interrupt Service Routines.
         */

        void
        reschedule (void)
        {
          if (rtos::scheduler::locked ()
              || (rtos::interrupts::in_handler_mode ()
                  && !rtos::scheduler::preemptive ()))
            {
#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
              trace::printf ("port::scheduler::%s() %s nop\n", __func__,
                             rtos::scheduler::current_thread_->name ());
#endif
              return;
            }

#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
          trace::printf ("port::scheduler::%s()\n", __func__);
#endif
          // TBD
        }

        // --------------------------------------------------------------------

// warning: ISO C++17 does not allow 'register' storage class specifier
// [-Wregister]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wregister"

        /**
         * @brief Save the current thread context on stack.
         * @return The SP after saving the context.
         *
         * @details
         * TBD
         *
         * @warning Any change in this routine must be checked in the
         * generated code, otherwise bad surprises can occur, like
         * adding clobber registers that added more initial pushes.
         */

        inline __attribute__ ((always_inline)) stack::element_t*
        save_on_stack (void)
        {
          register stack::element_t* sp_;

          __asm__ volatile(
              // Get the thread stack
              " nop                       \n"

              : [r] "=r"(sp_) /* out */
              : /* in */
              : /* clobber. DO NOT add anything here! */
          );

          return sp_;
        }

        /**
         * @brief Restore the new thread from the given stack address.
         * @param [in] sp Address where the thread context was saved.
         *
         * @details
         * TBD
         *
         * @warning Any change in this routine must be checked in the
         * generated code, otherwise bad surprises can occur, like
         * adding clobber registers that added more initial pushes.
         */

        inline __attribute__ ((always_inline)) void
        restore_from_stack (stack::element_t* sp)
        {
          // Without enforcing optimisations, an intermediate variable
          // would be needed to avoid using R4, which collides with
          // the R4 in the list of ldmia.

          // register stack::element_t* sp_ asm ("r0") = sp;

          __asm__ volatile(

              " nop                 \n"

              : /* out */
              : [r] "r"(sp) /* in */
              : /* clobber. DO NOT add anything here! */
          );
        }

#pragma GCC diagnostic pop

        /**
         * @brief Switch stacks to perform the rescheduling.
         * @param [in] sp Pointer to the initial thread context.
         * @return Pointer to the new thread context.
         *
         * @details
         * This function is the heart of the scheduler and
         * performs the context switches. It is called from the
         * PendSV_Handler.
         *
         * The main purpose of this function is to:
         * - remember the SP address in the thread context
         * - add the running thread to the ready list
         * - select the next thread
         * - get the new SP from there
         *
         * To protect the internal lists, interrupts are partly
         * disabled by a local critical section.
         */

        stack::element_t*
        switch_stacks (stack::element_t* sp)
        {
          uint32_t pri;

          // Enter a local critical section to protect the lists.

          // TBD

          rtos::thread* old_thread = rtos::scheduler::current_thread_;

          // Save the current SP in the initial context.
          old_thread->context_.port_.stack_ptr = sp;

#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
          trace::printf ("port::scheduler::%s() leave %s\n", __func__,
                         old_thread->name ());
#endif

          rtos::scheduler::internal_switch_threads ();

#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
          trace::printf ("port::scheduler::%s() to %s\n", __func__,
                         rtos::scheduler::current_thread_->name ());
#endif

          // Prepare a local copy of the new thread SP.
          stack::element_t* out_sp
              = rtos::scheduler::current_thread_->context_.port_.stack_ptr;

          // TBD

          // Return the new thread SP. Registers will be
          // restored in the assembly code.
          return out_sp;
        }

        // --------------------------------------------------------------------
      } // namespace scheduler
    } // namespace port
  } // namespace rtos
} // namespace micro_os_plus

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_INCLUDE_RTOS)

// ----------------------------------------------------------------------------

#endif // defined(__riscv)

// ----------------------------------------------------------------------------
