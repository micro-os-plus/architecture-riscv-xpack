/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2015-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_SEMIHOSTING_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_SEMIHOSTING_INLINES_H_

// ----------------------------------------------------------------------------

/**
 * @brief Immediate of the `srai` instruction that marks a semihosting
 *  call.
 *
 * @details
 * A semihosting call is the sequence `slli x0, x0, 0x1f`, `ebreak`,
 * `srai x0, x0, 7`; the surrounding instructions distinguish it from
 * a regular breakpoint.
 */
#define RISCV_SEMIHOSTING_CALL_NUMBER 7

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  /**
   * @brief Type of each entry in the semihosting structures.
   *
   * @details
   * Register wide, as required by the semihosting specification.
   */
  typedef micro_os_plus_architecture_register_t
      micro_os_plus_semihosting_register_t;

  /**
   * @brief Type of each entry in a semihosting parameter block.
   *
   * @details
   * Register wide; the address of the block is passed in `a1`.
   */
  typedef micro_os_plus_architecture_register_t
      micro_os_plus_semihosting_param_block_t;

  /**
   * @brief Type of the result of a semihosting call.
   *
   * @details
   * Signed and register wide; returned by the host in `a0`.
   */
  typedef micro_os_plus_architecture_signed_register_t
      micro_os_plus_semihosting_response_t;

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_INLINES_SEMIHOSTING_INLINES_H_

// ----------------------------------------------------------------------------
