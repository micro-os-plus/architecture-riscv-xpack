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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEFINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEFINES_H_

// ----------------------------------------------------------------------------

/**
 * @brief Define an unsigned long constant usable in C, C++, and
 *  assembly.
 * @param [in] x An integer literal, without suffix.
 *
 * @details
 * This header is also included in assembly files, where integer
 * suffixes are not accepted by the assembler. In C and C++ the
 * literal gets the `ul` suffix, so that it has the width of a
 * register; in assembly the literal is used as is.
 */
#if defined(__ASSEMBLER__)
#define RISCV_UL(x) x
#else // !defined(__ASSEMBLER__)
#define RISCV_UL(x) x##ul
#endif // defined(__ASSEMBLER__)

// ----------------------------------------------------------------------------

#if __riscv_xlen == 32
// DEADBEEF
#define MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC (0xEFBEADDE)
#elif __riscv_xlen == 64
// DEADBEEFBADC0FEE
#define MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC (0xEE0FDCBAEFBEADDE)
#else
#error "Unsupported __riscv_xlen"
#endif // __riscv_xlen

#if 0
// TODO: check and possibly prefix them.

// ----------------------------------------------------------------------------
// Definitions from SiFive bsp/env/encoding.h.

#define DCSR_XDEBUGVER (3U << 30)
#define DCSR_NDRESET (1 << 29)
#define DCSR_FULLRESET (1 << 28)
#define DCSR_EBREAKM (1 << 15)
#define DCSR_EBREAKH (1 << 14)
#define DCSR_EBREAKS (1 << 13)
#define DCSR_EBREAKU (1 << 12)
#define DCSR_STOPCYCLE (1 << 10)
#define DCSR_STOPTIME (1 << 9)
#define DCSR_CAUSE (7 << 6)
#define DCSR_DEBUGINT (1 << 5)
#define DCSR_HALT (1 << 3)
#define DCSR_STEP (1 << 2)
#define DCSR_PRV (3 << 0)

#define DCSR_CAUSE_NONE 0
#define DCSR_CAUSE_SWBP 1
#define DCSR_CAUSE_HWBP 2
#define DCSR_CAUSE_DEBUGINT 3
#define DCSR_CAUSE_STEP 4
#define DCSR_CAUSE_HALT 5

#define MCONTROL_TYPE(xlen) (0xfULL << ((xlen) - 4))
#define MCONTROL_DMODE(xlen) (1ULL << ((xlen) - 5))
#define MCONTROL_MASKMAX(xlen) (0x3fULL << ((xlen) - 11))

#define MCONTROL_SELECT (1 << 19)
#define MCONTROL_TIMING (1 << 18)
#define MCONTROL_ACTION (0x3f << 12)
#define MCONTROL_CHAIN (1 << 11)
#define MCONTROL_MATCH (0xf << 7)
#define MCONTROL_M (1 << 6)
#define MCONTROL_H (1 << 5)
#define MCONTROL_S (1 << 4)
#define MCONTROL_U (1 << 3)
#define MCONTROL_EXECUTE (1 << 2)
#define MCONTROL_STORE (1 << 1)
#define MCONTROL_LOAD (1 << 0)

#define MCONTROL_TYPE_NONE 0
#define MCONTROL_TYPE_MATCH 2

#define MCONTROL_ACTION_DEBUG_EXCEPTION 0
#define MCONTROL_ACTION_DEBUG_MODE 1
#define MCONTROL_ACTION_TRACE_START 2
#define MCONTROL_ACTION_TRACE_STOP 3
#define MCONTROL_ACTION_TRACE_EMIT 4

#define MCONTROL_MATCH_EQUAL 0
#define MCONTROL_MATCH_NAPOT 1
#define MCONTROL_MATCH_GE 2
#define MCONTROL_MATCH_LT 3
#define MCONTROL_MATCH_MASK_LOW 4
#define MCONTROL_MATCH_MASK_HIGH 5

#define PRV_U 0
#define PRV_S 1
#define PRV_H 2
#define PRV_M 3

#define VM_MBARE 0
#define VM_MBB 1
#define VM_MBBID 2
#define VM_SV32 8
#define VM_SV39 9
#define VM_SV48 10

// ----------------------------------------------------------------------------

#define DEFAULT_RSTVEC 0x00001000
#define DEFAULT_NMIVEC 0x00001004
#define DEFAULT_MTVEC 0x00001010
#define CONFIG_STRING_ADDR 0x0000100C
#define EXT_IO_BASE 0x40000000
#define DRAM_BASE 0x80000000

// page table entry (PTE) fields
#define PTE_V 0x001 // Valid
#define PTE_R 0x002 // Read
#define PTE_W 0x004 // Write
#define PTE_X 0x008 // Execute
#define PTE_U 0x010 // User
#define PTE_G 0x020 // Global
#define PTE_A 0x040 // Accessed
#define PTE_D 0x080 // Dirty
#define PTE_SOFT 0x300 // Reserved for Software

#define PTE_PPN_SHIFT 10

#define PTE_TABLE(PTE) (((PTE) & (PTE_V | PTE_R | PTE_W | PTE_X)) == PTE_V)

#if __riscv_xlen == 32
#define MSTATUS_SD MSTATUS32_SD
#define SSTATUS_SD SSTATUS32_SD
#define RISCV_PGLEVEL_BITS 10
#elif __riscv_xlen == 64
#define MSTATUS_SD MSTATUS64_SD
#define SSTATUS_SD SSTATUS64_SD
#define RISCV_PGLEVEL_BITS 9
#endif // __riscv_xlen

#define RISCV_PGSHIFT 12
#define RISCV_PGSIZE (1 << RISCV_PGSHIFT)

// End of SiFive definitions.
// ----------------------------------------------------------------------------
#endif // 0-1

// ----------------------------------------------------------------------------
// `mstatus` fields, as defined by the RISC-V Privileged Architecture,
// version 20211203 (privileged ISA 1.12).
//
// The fields of the obsolete 1.9 specification were removed: `UIE`
// and `UPIE` (the N extension was withdrawn), `PUM` (renamed `SUM`
// in 1.10), and `VM` (replaced by the `satp` CSR).

#define RISCV_CSR_MSTATUS_SIE RISCV_UL (0x00000002)
#define RISCV_CSR_MSTATUS_MIE RISCV_UL (0x00000008)
#define RISCV_CSR_MSTATUS_SPIE RISCV_UL (0x00000020)
#define RISCV_CSR_MSTATUS_UBE RISCV_UL (0x00000040)
#define RISCV_CSR_MSTATUS_MPIE RISCV_UL (0x00000080)
#define RISCV_CSR_MSTATUS_SPP RISCV_UL (0x00000100)
#define RISCV_CSR_MSTATUS_VS RISCV_UL (0x00000600)
#define RISCV_CSR_MSTATUS_MPP RISCV_UL (0x00001800)
#define RISCV_CSR_MSTATUS_FS RISCV_UL (0x00006000)
#define RISCV_CSR_MSTATUS_XS RISCV_UL (0x00018000)
#define RISCV_CSR_MSTATUS_MPRV RISCV_UL (0x00020000)
#define RISCV_CSR_MSTATUS_SUM RISCV_UL (0x00040000)
#define RISCV_CSR_MSTATUS_MXR RISCV_UL (0x00080000)
#define RISCV_CSR_MSTATUS_TVM RISCV_UL (0x00100000)
#define RISCV_CSR_MSTATUS_TW RISCV_UL (0x00200000)
#define RISCV_CSR_MSTATUS_TSR RISCV_UL (0x00400000)
#define RISCV_CSR_MSTATUS32_SD RISCV_UL (0x80000000)
#define RISCV_CSR_MSTATUS64_SD RISCV_UL (0x8000000000000000)

// Values of the `mstatus.MPP` field (previous privilege mode).
#define RISCV_CSR_MSTATUS_MPP_U RISCV_UL (0x00000000)
#define RISCV_CSR_MSTATUS_MPP_S RISCV_UL (0x00000800)
#define RISCV_CSR_MSTATUS_MPP_M RISCV_UL (0x00001800)

// Values of the `mstatus.FS` field (floating-point unit state).
#define RISCV_CSR_MSTATUS_FS_OFF RISCV_UL (0x00000000)
#define RISCV_CSR_MSTATUS_FS_INITIAL RISCV_UL (0x00002000)
#define RISCV_CSR_MSTATUS_FS_CLEAN RISCV_UL (0x00004000)
#define RISCV_CSR_MSTATUS_FS_DIRTY RISCV_UL (0x00006000)

// Values of the `mstatus.VS` field (vector unit state).
#define RISCV_CSR_MSTATUS_VS_OFF RISCV_UL (0x00000000)
#define RISCV_CSR_MSTATUS_VS_INITIAL RISCV_UL (0x00000200)
#define RISCV_CSR_MSTATUS_VS_CLEAN RISCV_UL (0x00000400)
#define RISCV_CSR_MSTATUS_VS_DIRTY RISCV_UL (0x00000600)

#if __riscv_xlen == 32
// On RV32, the endianness control bits are in the separate `mstatush`.
#define RISCV_CSR_MSTATUSH_SBE RISCV_UL (0x00000010)
#define RISCV_CSR_MSTATUSH_MBE RISCV_UL (0x00000020)
#define RISCV_CSR_MSTATUS_SD RISCV_CSR_MSTATUS32_SD
#elif __riscv_xlen == 64
#define RISCV_CSR_MSTATUS_UXL RISCV_UL (0x0000000300000000)
#define RISCV_CSR_MSTATUS_SXL RISCV_UL (0x0000000C00000000)
#define RISCV_CSR_MSTATUS_SBE RISCV_UL (0x0000001000000000)
#define RISCV_CSR_MSTATUS_MBE RISCV_UL (0x0000002000000000)
#define RISCV_CSR_MSTATUS_SD RISCV_CSR_MSTATUS64_SD
#endif // __riscv_xlen == 32

// ----------------------------------------------------------------------------
// `sstatus` fields (a restricted view of `mstatus`).

#define RISCV_CSR_SSTATUS_SIE RISCV_UL (0x00000002)
#define RISCV_CSR_SSTATUS_SPIE RISCV_UL (0x00000020)
#define RISCV_CSR_SSTATUS_UBE RISCV_UL (0x00000040)
#define RISCV_CSR_SSTATUS_SPP RISCV_UL (0x00000100)
#define RISCV_CSR_SSTATUS_VS RISCV_UL (0x00000600)
#define RISCV_CSR_SSTATUS_FS RISCV_UL (0x00006000)
#define RISCV_CSR_SSTATUS_XS RISCV_UL (0x00018000)
#define RISCV_CSR_SSTATUS_SUM RISCV_UL (0x00040000)
#define RISCV_CSR_SSTATUS_MXR RISCV_UL (0x00080000)
#define RISCV_CSR_SSTATUS32_SD RISCV_UL (0x80000000)
#define RISCV_CSR_SSTATUS64_SD RISCV_UL (0x8000000000000000)

#if __riscv_xlen == 32
#define RISCV_CSR_SSTATUS_SD RISCV_CSR_SSTATUS32_SD
#elif __riscv_xlen == 64
#define RISCV_CSR_SSTATUS_UXL RISCV_UL (0x0000000300000000)
#define RISCV_CSR_SSTATUS_SD RISCV_CSR_SSTATUS64_SD
#endif // __riscv_xlen == 32

// ----------------------------------------------------------------------------

// The bit positions match the `riscv_interrupts_local_enum_t` values;
// literal numbers are used since enums are not available in assembly.
#define RISCV_CSR_MIP_SSIP (RISCV_UL (1) << 1)
#define RISCV_CSR_MIP_MSIP (RISCV_UL (1) << 3)
#define RISCV_CSR_MIP_STIP (RISCV_UL (1) << 5)
#define RISCV_CSR_MIP_MTIP (RISCV_UL (1) << 7)
#define RISCV_CSR_MIP_SEIP (RISCV_UL (1) << 9)
#define RISCV_CSR_MIP_MEIP (RISCV_UL (1) << 11)

// ----------------------------------------------------------------------------

#if __riscv_xlen == 32
#define RISCV_CSR_MCAUSE_INTERRUPT (RISCV_UL (1) << 31)
#define RISCV_CSR_MCAUSE_CAUSE (RISCV_UL (0x7FFFFFFF))
#elif __riscv_xlen == 64
#define RISCV_CSR_MCAUSE_INTERRUPT (RISCV_UL (1) << 63)
#define RISCV_CSR_MCAUSE_CAUSE (RISCV_UL (0x7FFFFFFFFFFFFFFF))
#else
#error "Unsupported __riscv_xlen"
#endif // __riscv_xlen

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEFINES_H_

// ----------------------------------------------------------------------------
