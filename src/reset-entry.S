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

	.section	.reset_entry,"ax",@progbits
	.align		2 // number of low order zeros, i.e. align to a multiple of 4
	.globl		riscv_reset_entry
	.type		riscv_reset_entry, @function
riscv_reset_entry:

.option push
	// Ensure the instruction is not optimized, since gp is not yet set.
.option norelax
	// __global_pointer$ is a magic symbol, known by the linker.
	// Unless instructed not to do so, the linker optimizes
	// accesses +/- 2KB around this to gp-relative.
	la gp, __global_pointer$
.option pop

	// The linker script usually defines the stack at the end of RAM.
	la sp, __stack

	// Proceed with the standard C _start() routine.
	j _start

// ----------------------------------------------------------------------------

#endif /* __riscv */

// ----------------------------------------------------------------------------
