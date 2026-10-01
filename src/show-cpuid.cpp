/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2023-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

// ----------------------------------------------------------------------------

/**
 * @file
 * @brief RISC-V implementation of the CPU identification display.
 *
 * @details
 * Decodes the `misa`, `mvendorid`, `marchid`, `mimpid`, and `mhartid`
 * CSRs and writes a line like
 * `RV32IMAC, vendor SiFive, arch Rocket, impl 0x20181004, hart 0`
 * to the trace output channel.
 *
 * The implementation is kept consistent with the Cortex-M, AArch32,
 * and AArch64 packages.
 */

#include "micro-os-plus/architecture.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED)

// The trace output is optional; without the `diag-trace` package, the
// function is empty.
#if __has_include("micro-os-plus/diag/trace.h")
#include "micro-os-plus/diag/trace.h"

#include <cstdint>

// ----------------------------------------------------------------------------

namespace
{
  /**
   * @brief Get the name of a core vendor.
   *
   * @details
   * The vendor is identified by the JEDEC manufacturer ID, as encoded
   * in `mvendorid` (bank number in bits 31:7, ID without parity in
   * bits 6:0). Only vendors whose cores are known to report their
   * JEDEC ID in `mvendorid` are listed, in numeric order, with their
   * current short names (for example `0x5B7` is registered in JEP106
   * as C-SKY Microsystems, now T-Head).
   *
   * @param vendor_id The value of the `mvendorid` CSR.
   * @return A pointer to a string literal with the vendor name, or
   * `nullptr` if the ID is not known.
   */
  [[nodiscard]] const char*
  get_vendor_name (riscv::architecture::register_t vendor_id) noexcept
  {
    switch (vendor_id)
      {
      case 0x029U:
        return "Microchip";
      case 0x127U:
        return "MIPS";
      case 0x31EU:
        return "Andes";
      case 0x489U:
        return "SiFive";
      case 0x493U:
        return "Raspberry Pi";
      case 0x5B7U:
        return "T-Head";
      case 0x602U:
        return "OpenHW";
      case 0x612U:
        return "Espressif";
      default:
        return nullptr;
      }
  }

  /**
   * @brief Get the name of an open-source core microarchitecture.
   *
   * @details
   * Open-source microarchitectures are identified by `marchid` values
   * with the most significant bit clear, assigned globally by RISC-V
   * International (see `marchid.md` in the `riscv-isa-manual`
   * repository), and are therefore meaningful regardless of
   * `mvendorid`. Commercial microarchitectures have the most
   * significant bit set and are defined by each vendor; they are not
   * decoded.
   *
   * Only the most common cores are listed, in numeric order.
   *
   * @param arch_id The value of the `marchid` CSR.
   * @return A pointer to a string literal with the microarchitecture
   * name, or `nullptr` if the ID is not known.
   */
  [[nodiscard]] const char*
  get_architecture_name (riscv::architecture::register_t arch_id) noexcept
  {
    switch (arch_id)
      {
      case 1U:
        return "Rocket";
      case 2U:
        return "BOOM";
      case 3U:
        return "CVA6";
      case 27U:
        return "Hazard3";
      default:
        return nullptr;
      }
  }

  /**
   * @brief Get the native register width, in bits.
   *
   * @details
   * Decodes the `MXL` field, located in the two most significant bits
   * of `misa`. If `misa` is not implemented (reads as zero), the width
   * the code was compiled for is returned.
   *
   * @param misa The value of the `misa` CSR.
   * @return 32, 64, or 128.
   */
  [[nodiscard]] unsigned int
  get_xlen (riscv::architecture::register_t misa) noexcept
  {
    const auto mxl = static_cast<unsigned int> (
        misa >> (sizeof (riscv::architecture::register_t) * 8 - 2));

    switch (mxl)
      {
      case 1U:
        return 32U;
      case 2U:
        return 64U;
      case 3U:
        return 128U;
      default:
        return __riscv_xlen;
      }
  }
} // namespace

#endif // __has_include("micro-os-plus/diag/trace.h")

// ----------------------------------------------------------------------------

/**
 * @details
 * Reads the identification CSRs of the current hart and writes them to
 * the trace output channel:
 *
 * - the base ISA and the extensions, from `misa`, as `RV32IMAC`; if
 *   `misa` reads as zero (it is allowed not to be implemented), the
 *   width the code was compiled for is shown, followed by `?`;
 * - the vendor, from `mvendorid`, as a name when known (e.g. `SiFive`),
 *   otherwise in hexadecimal;
 * - the open-source microarchitecture, from `marchid`, as a name when
 *   known (e.g. `Hazard3`), otherwise in hexadecimal;
 * - the implementation ID, from `mimpid`, in hexadecimal, since its
 *   encoding is defined by each implementer;
 * - the hart ID, from `mhartid`, in decimal.
 *
 * All these CSRs are mandatory in M-mode and may read as zero, so
 * reading them never traps.
 *
 * When the `diag-trace` package is not available, the function is empty.
 */
void
micro_os_plus_architecture_show_cpuid (void)
{
#if __has_include("micro-os-plus/diag/trace.h")
  using namespace micro_os_plus;

  const auto misa = riscv::csr::misa ();
  const auto vendor_id = riscv::csr::mvendorid ();
  const auto arch_id = riscv::csr::marchid ();
  const auto impl_id = riscv::csr::mimpid ();
  const auto hart_id = riscv::csr::mhartid ();

  trace::printf ("RV%u", get_xlen (misa));
  if (misa != 0)
    {
      // Bits 0 to 25 flag the extensions `A` to `Z`.
      riscv::architecture::register_t mask = 1;
      for (char letter = 'A'; letter <= 'Z'; ++letter, mask <<= 1)
        {
          if ((misa & mask) != 0)
            {
              trace::printf ("%c", letter);
            }
        }
    }
  else
    {
      trace::printf ("?");
    }

  // The CSRs are register wide; on both RV32 and RV64 the register
  // type is `unsigned long`, but an explicit conversion keeps the
  // `%l` formats correct regardless.
  const char* vendor_name = get_vendor_name (vendor_id);
  if (vendor_name != nullptr)
    {
      trace::printf (", vendor %s", vendor_name);
    }
  else
    {
      trace::printf (", vendor 0x%lX", static_cast<unsigned long> (vendor_id));
    }

  const char* arch_name = get_architecture_name (arch_id);
  if (arch_name != nullptr)
    {
      trace::printf (", arch %s", arch_name);
    }
  else
    {
      trace::printf (", arch 0x%lX", static_cast<unsigned long> (arch_id));
    }

  trace::printf (", impl 0x%lX, hart %lu\n",
                 static_cast<unsigned long> (impl_id),
                 static_cast<unsigned long> (hart_id));
#endif // __has_include("micro-os-plus/diag/trace.h")
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURES_RISCV_ENABLED)

// ----------------------------------------------------------------------------
