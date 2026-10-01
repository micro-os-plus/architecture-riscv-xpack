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
 * @param x An integer literal, without suffix.
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

/**
 * @brief Specifiers for the always inlined architecture wrappers.
 *
 * @details
 * Used on both the declarations and the definitions of the functions
 * wrapping architecture instructions, CSRs, and memory-mapped
 * registers, in C and in C++.
 *
 * In C, the functions are `static inline`, since plain `inline` would
 * require an external definition in one translation unit.
 *
 * In C++, the functions are `inline` with external linkage, so that the
 * external linkage C++ wrappers refer to the same entity in all
 * translation units, as required by the One Definition Rule; with
 * `static`, each translation unit would get a distinct function.
 *
 * In both languages, inlining is forced, also in non-optimised builds;
 * in C++ with the standard attribute syntax (`[[gnu::always_inline]]`),
 * in C with `__attribute__ ((always_inline))`, since C11 has no standard
 * attribute syntax.
 *
 * In C++ the macro expands to an attribute, therefore it must be the
 * first element of the declaration, after any other standard attributes
 * such as `[[nodiscard]]`.
 *
 * The same definition is used by the AArch32 and AArch64 architecture
 * packages.
 */
#if defined(__cplusplus)
#define MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE [[gnu::always_inline]] inline
#else // !defined(__cplusplus)
#define MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE \
  static inline __attribute__ ((always_inline))
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#if __riscv_xlen == 32
/**
 * @brief Pattern used to fill unused stack space.
 *
 * @details
 * Used by the RTOS to compute the stack usage. The bytes are in
 * reverse order, so that on the little-endian RISC-V cores a memory
 * dump shows `DE AD BE EF`.
 */
#define MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC (0xEFBEADDE)
#elif __riscv_xlen == 64
/**
 * @brief Pattern used to fill unused stack space.
 *
 * @details
 * Used by the RTOS to compute the stack usage. The bytes are in
 * reverse order, so that on the little-endian RISC-V cores a memory
 * dump shows `DE AD BE EF BA DC 0F EE`.
 */
#define MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC (0xEE0FDCBAEFBEADDE)
#else // !(__riscv_xlen == 32) && !(__riscv_xlen == 64)
#error "Unsupported __riscv_xlen"
#endif // __riscv_xlen == 32

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
#endif // __riscv_xlen == 32

#define RISCV_PGSHIFT 12
#define RISCV_PGSIZE (1 << RISCV_PGSHIFT)

// End of SiFive definitions.
// ----------------------------------------------------------------------------
#endif // 0

// ----------------------------------------------------------------------------
// `mstatus` fields, as defined by the RISC-V Privileged Architecture,
// version 20211203 (privileged ISA 1.12).
//
// The fields of the obsolete 1.9 specification were removed: `UIE`
// and `UPIE` (the N extension was withdrawn), `PUM` (renamed `SUM`
// in 1.10), and `VM` (replaced by the `satp` CSR).

/// @brief Supervisor mode interrupt enable.
#define RISCV_CSR_MSTATUS_SIE RISCV_UL (0x00000002)
/// @brief Machine mode interrupt enable (global interrupt enable).
#define RISCV_CSR_MSTATUS_MIE RISCV_UL (0x00000008)
/// @brief Supervisor previous interrupt enable.
#define RISCV_CSR_MSTATUS_SPIE RISCV_UL (0x00000020)
/// @brief User mode big-endian memory accesses.
#define RISCV_CSR_MSTATUS_UBE RISCV_UL (0x00000040)
/// @brief Machine previous interrupt enable.
#define RISCV_CSR_MSTATUS_MPIE RISCV_UL (0x00000080)
/// @brief Supervisor previous privilege mode.
#define RISCV_CSR_MSTATUS_SPP RISCV_UL (0x00000100)
/// @brief Vector unit state field (2 bits).
#define RISCV_CSR_MSTATUS_VS RISCV_UL (0x00000600)
/// @brief Machine previous privilege mode field (2 bits).
#define RISCV_CSR_MSTATUS_MPP RISCV_UL (0x00001800)
/// @brief Floating-point unit state field (2 bits).
#define RISCV_CSR_MSTATUS_FS RISCV_UL (0x00006000)
/// @brief Additional user extensions state field (2 bits, read-only).
#define RISCV_CSR_MSTATUS_XS RISCV_UL (0x00018000)
/// @brief Modify privilege: loads and stores use the `MPP` mode.
#define RISCV_CSR_MSTATUS_MPRV RISCV_UL (0x00020000)
/// @brief Permit supervisor access to user memory.
#define RISCV_CSR_MSTATUS_SUM RISCV_UL (0x00040000)
/// @brief Make executable pages readable.
#define RISCV_CSR_MSTATUS_MXR RISCV_UL (0x00080000)
/// @brief Trap virtual memory management operations.
#define RISCV_CSR_MSTATUS_TVM RISCV_UL (0x00100000)
/// @brief Timeout wait: trap `wfi` in lower privilege modes.
#define RISCV_CSR_MSTATUS_TW RISCV_UL (0x00200000)
/// @brief Trap the `sret` instruction.
#define RISCV_CSR_MSTATUS_TSR RISCV_UL (0x00400000)
/// @brief State dirty summary bit, on RV32.
#define RISCV_CSR_MSTATUS32_SD RISCV_UL (0x80000000)
/// @brief State dirty summary bit, on RV64.
#define RISCV_CSR_MSTATUS64_SD RISCV_UL (0x8000000000000000)

// Values of the `mstatus.MPP` field (previous privilege mode).
/// @brief `MPP` value for user mode.
#define RISCV_CSR_MSTATUS_MPP_U RISCV_UL (0x00000000)
/// @brief `MPP` value for supervisor mode.
#define RISCV_CSR_MSTATUS_MPP_S RISCV_UL (0x00000800)
/// @brief `MPP` value for machine mode.
#define RISCV_CSR_MSTATUS_MPP_M RISCV_UL (0x00001800)

// Values of the `mstatus.FS` field (floating-point unit state).
/// @brief `FS` value: the FPU is disabled.
#define RISCV_CSR_MSTATUS_FS_OFF RISCV_UL (0x00000000)
/// @brief `FS` value: the FPU state is initial.
#define RISCV_CSR_MSTATUS_FS_INITIAL RISCV_UL (0x00002000)
/// @brief `FS` value: the FPU state is clean.
#define RISCV_CSR_MSTATUS_FS_CLEAN RISCV_UL (0x00004000)
/// @brief `FS` value: the FPU state is dirty.
#define RISCV_CSR_MSTATUS_FS_DIRTY RISCV_UL (0x00006000)

// Values of the `mstatus.VS` field (vector unit state).
/// @brief `VS` value: the vector unit is disabled.
#define RISCV_CSR_MSTATUS_VS_OFF RISCV_UL (0x00000000)
/// @brief `VS` value: the vector state is initial.
#define RISCV_CSR_MSTATUS_VS_INITIAL RISCV_UL (0x00000200)
/// @brief `VS` value: the vector state is clean.
#define RISCV_CSR_MSTATUS_VS_CLEAN RISCV_UL (0x00000400)
/// @brief `VS` value: the vector state is dirty.
#define RISCV_CSR_MSTATUS_VS_DIRTY RISCV_UL (0x00000600)

#if __riscv_xlen == 32
// On RV32, the endianness control bits are in the separate `mstatush`.
/// @brief Supervisor mode big-endian (`mstatush`, RV32 only).
#define RISCV_CSR_MSTATUSH_SBE RISCV_UL (0x00000010)
/// @brief Machine mode big-endian (`mstatush`, RV32 only).
#define RISCV_CSR_MSTATUSH_MBE RISCV_UL (0x00000020)
/// @brief State dirty summary bit, for the current register width.
#define RISCV_CSR_MSTATUS_SD RISCV_CSR_MSTATUS32_SD
#elif __riscv_xlen == 64
/// @brief User mode register width field (2 bits, RV64 only).
#define RISCV_CSR_MSTATUS_UXL RISCV_UL (0x0000000300000000)
/// @brief Supervisor mode register width field (2 bits, RV64 only).
#define RISCV_CSR_MSTATUS_SXL RISCV_UL (0x0000000C00000000)
/// @brief Supervisor mode big-endian (RV64 only).
#define RISCV_CSR_MSTATUS_SBE RISCV_UL (0x0000001000000000)
/// @brief Machine mode big-endian (RV64 only).
#define RISCV_CSR_MSTATUS_MBE RISCV_UL (0x0000002000000000)
/// @brief State dirty summary bit, for the current register width.
#define RISCV_CSR_MSTATUS_SD RISCV_CSR_MSTATUS64_SD
#endif // __riscv_xlen == 32

// ----------------------------------------------------------------------------
// `sstatus` fields (a restricted view of `mstatus`).

/// @brief Supervisor mode interrupt enable.
#define RISCV_CSR_SSTATUS_SIE RISCV_UL (0x00000002)
/// @brief Supervisor previous interrupt enable.
#define RISCV_CSR_SSTATUS_SPIE RISCV_UL (0x00000020)
/// @brief User mode big-endian memory accesses.
#define RISCV_CSR_SSTATUS_UBE RISCV_UL (0x00000040)
/// @brief Supervisor previous privilege mode.
#define RISCV_CSR_SSTATUS_SPP RISCV_UL (0x00000100)
/// @brief Vector unit state field (2 bits).
#define RISCV_CSR_SSTATUS_VS RISCV_UL (0x00000600)
/// @brief Floating-point unit state field (2 bits).
#define RISCV_CSR_SSTATUS_FS RISCV_UL (0x00006000)
/// @brief Additional user extensions state field (2 bits).
#define RISCV_CSR_SSTATUS_XS RISCV_UL (0x00018000)
/// @brief Permit supervisor access to user memory.
#define RISCV_CSR_SSTATUS_SUM RISCV_UL (0x00040000)
/// @brief Make executable pages readable.
#define RISCV_CSR_SSTATUS_MXR RISCV_UL (0x00080000)
/// @brief State dirty summary bit, on RV32.
#define RISCV_CSR_SSTATUS32_SD RISCV_UL (0x80000000)
/// @brief State dirty summary bit, on RV64.
#define RISCV_CSR_SSTATUS64_SD RISCV_UL (0x8000000000000000)

#if __riscv_xlen == 32
/// @brief State dirty summary bit, for the current register width.
#define RISCV_CSR_SSTATUS_SD RISCV_CSR_SSTATUS32_SD
#elif __riscv_xlen == 64
/// @brief User mode register width field (2 bits, RV64 only).
#define RISCV_CSR_SSTATUS_UXL RISCV_UL (0x0000000300000000)
/// @brief State dirty summary bit, for the current register width.
#define RISCV_CSR_SSTATUS_SD RISCV_CSR_SSTATUS64_SD
#endif // __riscv_xlen == 32

// ----------------------------------------------------------------------------

// The bit positions match the `riscv_interrupts_local_enum_t` values;
// literal numbers are used since enums are not available in assembly.
/// @brief Supervisor software interrupt (bit 1 of `mip`/`mie`).
#define RISCV_CSR_MIP_SSIP (RISCV_UL (1) << 1)
/// @brief Machine software interrupt (bit 3 of `mip`/`mie`).
#define RISCV_CSR_MIP_MSIP (RISCV_UL (1) << 3)
/// @brief Supervisor timer interrupt (bit 5 of `mip`/`mie`).
#define RISCV_CSR_MIP_STIP (RISCV_UL (1) << 5)
/// @brief Machine timer interrupt (bit 7 of `mip`/`mie`).
#define RISCV_CSR_MIP_MTIP (RISCV_UL (1) << 7)
/// @brief Supervisor external interrupt (bit 9 of `mip`/`mie`).
#define RISCV_CSR_MIP_SEIP (RISCV_UL (1) << 9)
/// @brief Machine external interrupt (bit 11 of `mip`/`mie`).
#define RISCV_CSR_MIP_MEIP (RISCV_UL (1) << 11)

// ----------------------------------------------------------------------------

#if __riscv_xlen == 32
/// @brief `mcause` bit set when the trap is an interrupt.
#define RISCV_CSR_MCAUSE_INTERRUPT (RISCV_UL (1) << 31)
/// @brief `mcause` mask for the interrupt or exception code.
#define RISCV_CSR_MCAUSE_CAUSE (RISCV_UL (0x7FFFFFFF))
#elif __riscv_xlen == 64
/// @brief `mcause` bit set when the trap is an interrupt.
#define RISCV_CSR_MCAUSE_INTERRUPT (RISCV_UL (1) << 63)
/// @brief `mcause` mask for the interrupt or exception code.
#define RISCV_CSR_MCAUSE_CAUSE (RISCV_UL (0x7FFFFFFFFFFFFFFF))
#else // !(__riscv_xlen == 32) && !(__riscv_xlen == 64)
#error "Unsupported __riscv_xlen"
#endif // __riscv_xlen == 32

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEFINES_H_

// ----------------------------------------------------------------------------
