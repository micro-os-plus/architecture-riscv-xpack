<!-- Issues are numbered globally across sections, for reference. -->
<!-- markdownlint-disable MD029 -->

# Code Review — Architecture: RISC-V

Date: 2026-10-01. Branch: `xpack-development` (commit `8819f02` plus
uncommitted changes).

Scope: `include/` and `src/` (the default scope; there is no `tests/`
folder). All 22 files were read in full.

Verification: every source file was cross-compiled with
`riscv-none-elf-gcc` 15.2.0 for `rv32imac_zicsr/ilp32` and
`rv64imafdc_zicsr/lp64d`, with `-Wall -Wextra -Wpedantic -Wconversion
-Wsign-conversion -Wshadow -Wundef -Wmissing-declarations`. Each header
was also compiled on its own, and small test programs were compiled and
their assembly inspected. Findings marked **[verified]** were confirmed
this way. Doxygen was not run, as the repository has no Doxyfile.

## Summary

The four sources compile without warnings on both RV32 and RV64.
`micro-os-plus/architecture.h` also compiles cleanly as both C and C++.
However, the review found several correctness defects that a
warning-free build does not reveal:

- MMIO accesses to `mtimecmp` are not `volatile`, so the compiler
  eliminates writes to it (#1).
- Several 64-bit accessors are declared for RV32 but never defined,
  which causes link errors when they are used (#2).
- The CSR write, set, and clear helpers, as well as `wfi`, are not
  compiler memory barriers. Critical sections and idle loops built on
  them are therefore not guaranteed to work (#3, #4); the idle-loop
  case was confirmed to hang.
- The `RISCV_CSR_MIP_*` macros live in a header that is included from
  assembly, yet they cannot be used there (#5).
- `core-functions.h` does not compile on its own (#6).
- The reset code may leave the FPU disabled (#7), and it does not
  handle multiple harts (#8).

Doxygen coverage is very low (#29). Conditional-compilation comments
do not follow the project rules in many places (#27, #28). There are no
tests (#35).

Priority order for fixes: #1, #3, #4, #2, #7, #5, #6, #10, then the
rest.

## Open issues

### Correctness and maintainability

1. **[FIXED]** All six accessors now use `volatile` pointers;
   verified that consecutive writes and reads are all emitted on RV32
   and RV64.
   **`mtimecmp` accessors are not `volatile`** **[verified]** —
   `include/micro-os-plus/architecture-riscv/inlines/device-functions-inlines.h:77-116`.
   All six `mtimecmp` functions access MMIO through `uint64_t*` or
   `uint32_t*` instead of `volatile` pointers, unlike the `mtime`
   functions above them. Test: two consecutive
   `riscv_device_write_mtimecmp_low()` calls at `-O2` compile to a
   single store, because the first is eliminated as a dead store.
   Reads can likewise be cached or hoisted out of loops. This breaks
   the timer interrupt protocol, which relies on writing `-1` to the
   low word first. Fix: use `volatile` on all accesses.

2. **[FIXED]** RV32 variants implemented: high/low/high retry loop
   for `mcycle` and `mtime` reads, low=0/high/low for `mtime` writes,
   and low=`UINT32_MAX`/high/low for `mtimecmp` writes. The
   `#if`-split `static` declarations and the RV64-only guards on the
   C++ wrappers were removed. Verified: no undefined symbols on RV32 or
   RV64, and the generated code follows the intended sequences.
   **64-bit accessors declared for RV32 but never defined**
   **[verified]** — `csr-functions.h:125-129` and `:213-214`,
   `device-functions.h:38-54`, `:74-78`, `:108-118`, and `:145`.
   On RV32 the following have declarations but no definitions:
   `riscv_csr_read_mcycle()`, `riscv::csr::mcycle()`,
   `riscv_device_read_mtime()`, `riscv_device_write_mtime()`,
   `riscv_device_write_mtimecmp()`, `riscv::device::mtime()` (read and
   write), and `riscv::device::mtimecmp(uint64_t)`. Calling them
   compiles, then fails at link time with undefined references (seen
   in `nm`). The self-contained build of `device-functions.h` also
   emits `-Wunused-function` warnings ("declared 'static' but never
   defined"). Fix one of two ways:
   - implement the RV32 variants with the standard high/low/high
     retry loop for reads, and the low=`-1`, high, low sequence for
     `mtimecmp` writes; or
   - remove the declarations under `#if __riscv_xlen == 32`, so the
     error appears at compile time.

   The first option is preferable, since a 64-bit cycle or time read
   is the most commonly needed operation.

3. **[FIXED]** `"memory"` added to the clobbers of all seven helpers
   that write `mstatus`, `mie`, or `mtvec`; the barrier semantics are
   documented on their declarations. Verified: the `a = 1` store is no
   longer merged across the section, and a variable read both before
   and inside the section is reloaded after `csrrc`.
   **CSR write, set, and clear helpers are not compiler barriers**
   **[verified]** — `inlines/csr-functions-inlines.h:70-115` and
   `:193-238`. The `asm volatile` statements have no `"memory"`
   clobber. GCC may therefore move memory accesses across them,
   including across `riscv_csr_clear_mstatus_bits(MIE)` and
   `riscv_csr_set_mstatus_bits(MIE)`. Test: a store to a global before
   the clear was merged with a later store after the set, which shows
   the compiler treats these statements as not touching memory. The
   accesses inside the section stayed in place in this test only by
   chance; nothing guarantees it. Critical sections built on these
   helpers are therefore unsound. Fix: add `"memory"` to the clobbers
   of every helper that writes `mstatus`, `mie`, or `mtvec`.

4. **[FIXED]** `"memory"` added to the clobbers of `wfi` and
   `ebreak`; the C declarations document the barrier semantics.
   Verified: the idle loop now reloads `flag` after each `wfi`.
   **`wfi` and `ebreak` lack a memory clobber** **[verified]** —
   `inlines/instructions-inlines.h:43-67`. Test:
   `while (!flag) riscv_architecture_wfi();` compiles to a single load
   of `flag` followed by an infinite `wfi` loop. Interrupt handlers
   that set the flag can never end the loop. The CMSIS equivalents use
   a `"memory"` clobber. Fix: add `"memory"` to `wfi`, and preferably
   to `ebreak` as well.

5. **[FIXED]** Added the `RISCV_UL()` helper to `defines.h`, which
   appends `ul` only outside assembly. All `ul` constants now use it,
   and the `RISCV_CSR_MIP_*` masks use literal bit numbers. `types.h`
   now includes `defines.h` and has static assertions that keep the
   masks consistent with `riscv_interrupts_local_enum_t`. Verified:
   the macros assemble with the correct values on RV32 and RV64, and
   C and C++ builds are clean.
   **`RISCV_CSR_MIP_*` cannot be used in assembly** **[verified]** —
   `defines.h:169-174`. The macros expand to `1ul << <enum constant>`.
   `defines.h` is the only header `architecture.h` includes when
   `__ASSEMBLER__` is defined, yet `li t0, RISCV_CSR_MIP_MEIP` fails
   with "illegal operands", because both the enum and the `ul` suffix
   are C-only. Fix: use numeric bit positions, and do not use `ul`
   suffixes in this header (or use a `RISCV_UL()` helper that adds the
   suffix only outside assembly).

6. **[FIXED]** Update: the remaining C warnings were removed by
   declaring the device and platform C functions only when their
   definitions are available (`MICRO_OS_PLUS_ARCHITECTURE_RISCV_HAS_DEVICE_ADDRESSES`,
   computed from the two MMIO address macros, and
   `RISCV_PLATFORM_RTC_FREQUENCY_HZ`, both also enabled for
   `__DOXYGEN__`). Every header now compiles on its own without
   warnings in C and C++, and a C caller that forgot the macros gets
   an explicit "implicit declaration" error. Original entry: The headers outside `inlines/` are
   now independent of include order:
   - `core-functions.h` includes `defines.h` and `csr-functions.h`;
   - `riscv_plic_source_t` and `riscv_plic_priority_t` are defined
     in `types.h` (as `uint32_t`; identical typedefs in device
     packages remain legal);
   - `plic-functions.h` no longer declares the device-defined
     `static` C functions; their required signatures are listed in a
     comment;
   - `device-functions.h` includes its inlines automatically when both
     `MICRO_OS_PLUS_DEVICE_RISCV_MMIO_*_ADDRESS` macros are defined.

   Verified in C11 and C++20 on RV32 and RV64: every header compiles
   on its own without warnings, except `device-functions.h` without
   the address macros, which still emits `-Wunused-function` warnings
   (the chosen trade-off). The `devices-sifive` include sequence was
   simulated and compiles cleanly. `inlines/semihosting-inlines.h` was
   left out of scope. Note: `devices-sifive` `device.h` includes
   `architecture-riscv/device-functions-inlines.h`, a path that no
   longer exists (the file is in `inlines/`); that line should now be
   removed there.
   **`core-functions.h` is not self-contained** **[verified]** —
   `inlines/core-functions-inlines.h:32` and `:41` use
   `riscv_csr_set_mie_bits`, `riscv_csr_clear_mie_bits`, and
   `RISCV_CSR_MIP_MEIP`, but `core-functions.h` includes neither
   `csr-functions.h` nor `defines.h`. The header compiles only because
   `architecture.h` happens to include those headers first. Fix:
   include the dependencies explicitly. Similarly:
   - `inlines/semihosting-inlines.h` uses
     `micro_os_plus_architecture_register_t` without including
     `types.h`;
   - `plic-functions.h` **[verified]** requires `riscv_plic_source_t`
     and `riscv_plic_priority_t` from a device package, which is
     undocumented.

7. **[FIXED]** The FPU block is now guarded by
   `defined(__riscv_flen)`, does not test `misa`, clears `mstatus.FS`
   and sets it to Initial (named values `RISCV_CSR_MSTATUS_FS_OFF`,
   `_INITIAL`, `_CLEAN`, and `_DIRTY` were added to `defines.h`), then
   clears `fcsr`. Verified on RV32 F, RV64 D, RV32 without an FPU (no
   code emitted), and RV32 F with `-mno-fdiv` (code now emitted).
   7. **The FPU may be left disabled at reset** —
   `src/reset-entry.S:63-78`. FPU initialisation runs only if `misa`
   reports F, D, or Q. The privileged specification allows `misa` to
   read as zero. On such a core, `mstatus.FS` stays Off, and the first
   floating-point instruction in `_start` or a constructor raises an
   illegal-instruction exception. Since the code was compiled for an
   FPU, the hardware is required to have one, so the `misa` test adds
   risk and no protection. Also, the guard `__riscv_fdiv` is
   semantically wrong: it reports whether divide instructions are
   enabled, and is undefined with `-mno-fdiv` even when an FPU is
   present. Fix: guard with `defined(__riscv_flen)` and set `FS`
   unconditionally.

8. **[FIXED]** `reset_entry` now reads `mhartid` first and sends any
    hart with a non-zero id to a `wfi` park loop, so only one hart
    sets up `sp` and reaches `_start`. `mtvec` is set, in direct mode,
    to a local `default_trap_entry` (an infinite loop) immediately
    after the global pointer is set up and before `sp` is touched, so
    a trap during start-up no longer jumps to an undefined address.
    Note: not re-verified by cross-compilation in this session, as no
    RISC-V toolchain is available here; the change was checked by
    inspection only.
    8. **The reset code does not handle multiple harts** —
   `src/reset-entry.S:33-81`. Every hart that reaches `reset_entry`
   loads the same `sp` (`__stack`) and enters `_start`, which corrupts
   the stack and runs C initialisation more than once. Also, `mtvec`
   is not set before `_start`, so any trap during start-up jumps to an
   undefined address. Fix: park harts with a non-zero `mhartid` (or
   document that only single-hart devices are supported), and set
   `mtvec` to a default handler early.

9. **[FIXED]** Resolved by #7: the `lui`/`or` sequence and its
   wrong comment were replaced, and the field is cleared before being
   set, so no assumption about its reset value remains.
   9. **Wrong comment in the FPU set-up** — `src/reset-entry.S:72`.
   `lui t1, 0x2` loads `0x2000` (`1 << 13`), which sets `FS` to
   Initial (1); the comment `t1 = 0x1 << 12` is wrong. Also, the
   instruction ORs in the field instead of replacing it, which is only
   correct because `FS` is Off after reset. State that assumption.

10. **[PARTLY FIXED]** The comment now says to leave
    `MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEBUGGER_ENTRY_POINT_ENABLED`
    undefined and provide `_debugger_entry_point` in the device
    package, instead of telling callers to "reimplement" the strong
    symbol. The `.weak` marking and the jump-range concern below are
    still open.
    10. **`_debugger_entry_point` cannot be "reimplemented"** —
    `src/debugger-entry-point.S:32-43`. The comment tells pico 2 style
    platforms to reimplement the function in the project, but it is a
    strong global symbol, so doing so causes a duplicate-definition
    link error unless the component macro is left undefined. Fix:
    either mark it `.weak`, or reword the comment to say "leave
    `MICRO_OS_PLUS_ARCHITECTURE_RISCV_DEBUGGER_ENTRY_POINT_ENABLED`
    undefined and provide your own". Related: the `j reset_entry`
    (here) and `j _start` (`reset-entry.S:81`) jumps reach only
    ±1 MiB. If the linker script places these sections far apart, for
    example one in RAM and one in flash, linking fails with
    "relocation truncated". Prefer `tail`, or `la` plus `jr`.

11. **[FIXED]** `clear_mstatus_bits()`, `set_mstatus_bits()`,
    `clear_mie_bits()`, and `set_mie_bits()` now return
    `architecture::register_t` (the previous CSR value), and are
    documented. Verified: a save/restore critical section compiles to
    `csrrc` followed by `csrrs` with the saved bits. No uses were found
    in `rtos-riscv`, `devices-sifive`, `devices-qemu-riscv`, or
    `platform-sifive-hifive1`; existing callers that ignore the result
    are unaffected.
    **C++ set and clear wrappers discard the previous value** —
    `csr-functions.h:171-175` and `:201-205`, and
    `inlines/csr-functions-inlines.h:361-371` and `:409-419`. The C
    functions return the previous CSR value, which is needed to
    save and restore interrupt state. The C++ equivalents return
    `void`. Fix: return `architecture::register_t`.

12. **[FIXED]** The three live `"=rm"` constraints (`mcycle`,
    `mcycle` low, and `mcycleh`) are now `"=r"`, like all the other
    accessors. Verified at `-O0` and `-O2`, RV32 and RV64: every
    `csrr` targets a register. The remaining `"=rm"` at line 42 is in
    the `#if 0` block covered by #20.
    **Invalid `"=rm"` output constraint for `csrr`** —
    `inlines/csr-functions-inlines.h:256`, `:276`, and `:300`. `csrr`
    can only write a register; if GCC chose the memory alternative,
    the assembler would reject the code. Current GCC chose a register
    in tests, including at `-O0`, so the defect is latent. Fix: use
    `"=r"`, as all the other accessors do.

13. **[FIXED]** `defines.h` now follows the Privileged Architecture
    20211203 (1.12):
    - removed: `UIE`, `UPIE`, `PUM`, and `VM` (both `mstatus` and
      `sstatus`);
    - added fields: `UBE`, `VS`, `SUM`, `TVM`, `TW`, and `TSR`; on
      RV64 also `UXL`, `SXL`, `SBE`, and `MBE`; on RV32 the `mstatush`
      `SBE` and `MBE`; and the `sstatus` `UBE`, `VS`, `SUM`, `MXR`,
      and (RV64) `UXL`;
    - added values: `MPP_U`, `MPP_S`, `MPP_M`, and `VS_OFF` to
      `VS_DIRTY`;
    - added width-independent `RISCV_CSR_MSTATUS_SD` and
      `RISCV_CSR_SSTATUS_SD`.

    Verified with compile-time checks against the specification's bit
    positions on RV32 and RV64, including that no RV64 `mstatus`
    fields overlap; the macros also assemble correctly. The only
    downstream use (`RISCV_CSR_MSTATUS_MPP` in `rtos-riscv`) is
    unchanged. Removing macros is an API change (see #34).
    **Obsolete `mstatus`/`sstatus` definitions** —
    `defines.h:141-167`. The following refer to the pre-1.10
    privileged specification:
    - `UIE` and `UPIE` (the N extension was withdrawn);
    - `PUM`, renamed `SUM` in 1.10;
    - `VM`, which was removed (replaced by `satp`).

    Commonly needed fields (`SUM`, `MPRV`-related `MPP` values, `TW`,
    `TSR`, `TVM`) are missing. Fix: align with the current ratified
    specification.

14. **[FIXED]** Added `#else #error "Unsupported __riscv_xlen"`, and
    the `#endif` comment now repeats the `#if` expression. Verified
    with the host `clang++` (no `__riscv_xlen`): the header now fails
    with explicit `#error` messages. The odd indentation of the RV64
    typedefs remains (a clang-format artefact, see #23).
    **`types.h` has no fallback for an unsupported `__riscv_xlen`** —
    `types.h:24-30`. Unlike `defines.h`, it has no `#else #error`.
    When the header is included without a RISC-V compiler, as by
    clangd or a host build, the register types are silently missing
    and the errors appear elsewhere. Fix: add
    `#else #error "Unsupported __riscv_xlen"`.

15. **[FIXED]** Implemented following the Cortex-M package: when
    `diag-trace` is available, it prints a line like
    `RV64ACIMU, vendor SiFive, arch 0x1, impl 0x0, hart 0`, decoding
    `misa` (width and extensions; `RV32?` if `misa` reads as zero),
    `mvendorid` (Microchip, MIPS, Andes, SiFive, Raspberry Pi,
    T-Head, OpenHW, and Espressif by name; each ID cross-checked
    against the JEP106 table), `marchid`,
    `mimpid`, and `mhartid`. New read accessors for `misa`,
    `mvendorid`, `marchid`, and `mimpid` were added to
    `csr-functions.h` (C and C++). Verified: no warnings with the real
    `diag-trace` headers on RV32 and RV64; run under QEMU 9.2 `virt`
    (RV32 and RV64) and `sifive_u` (RV64, hart 0 is the E51). QEMU
    reports zero vendor, architecture, and implementation IDs, so the
    vendor-name lookup was not exercised at run time.
    **`micro_os_plus_architecture_show_cpuid()` is an empty stub** —
    `src/show-cpuid.cpp:26-29`. The function does nothing, and the
    `using namespace micro_os_plus;` on line 22 is unused. Either
    implement it (print `misa`, `mvendorid`, `marchid`, `mimpid`, and
    `mhartid`) or document that it is intentionally empty.

16. **[FIXED]** Every externally provided symbol is now documented
    where it is declared, naming the package that provides it (checked
    against the actual definitions):
    - `core-functions.h`: the running-frequency functions (C and C++)
      and `riscv_trap_entry`, provided by `rtos-riscv`;
    - `declarations.h`: `local_interrupt_handlers[]` and
      `global_interrupt_handlers[]`, defined by the device package with
      `RISCV_INTERRUPTS_{LOCAL,GLOBAL}_LAST_NUMBER + 1` entries;
    - `plic-functions.h`: a file comment listing which functions the
      device package must define out of line and which inline;
    - `platform-functions.h`: a file comment describing
      `RISCV_PLATFORM_RTC_FREQUENCY_HZ` and the inline functions,
      replacing the stale comments (this also covers part of #18).

    The MMIO address requirements were already documented in
    `device-functions.h` (#6), now under the
    `MICRO_OS_PLUS_DEVICE_RISCV_MMIO_*` names.
    **Undocumented external dependencies** — several functions and
    objects are declared here but must be defined by other packages:
    - `riscv_core_get_running_frequency_hz`,
      `riscv_core_update_running_frequency`, and the C++
      `running_frequency_hz` / `update_running_frequency`
      (`core-functions.h:30-34` and `:70-78`);
    - `riscv_trap_entry` (`core-functions.h:45`);
    - `riscv::core::local_interrupt_handlers` and
      `global_interrupt_handlers` (`declarations.h:33-34`);
    - all PLIC functions (`plic-functions.h`);
    - `MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIME_ADDRESS`, `MICRO_OS_PLUS_DEVICE_RISCV_MMIO_MTIMECMP_ADDRESS`, and
      `RISCV_PLATFORM_RTC_FREQUENCY_HZ`.

    The address macros must be integer constants, not pointers,
    because `+ 4` is applied to them (`device-functions-inlines.h:50`,
    `:72`, `:93`, and `:115`). Document all of these requirements in
    the headers.

17. **[PARTLY FIXED, rest deferred]** The `RISCV_SEMIHOSTING_CALL_NUMBER`
    `#define` was moved outside the `extern "C"` block. The file name
    and location (`inlines/`, with no inline functions) and the
    missing `#include` of `types.h` are deferred: the same layout is
    used by `architecture-cortexm`, `architecture-aarch32`, and
    `architecture-aarch64`, and the `semihosting` package relies on
    the typedefs, so these will be fixed together across all
    architecture packages.
    **Misplaced content in `semihosting-inlines.h`** —
    `inlines/semihosting-inlines.h`. The file contains typedefs and a
    macro but no inline functions, so it does not belong in `inlines/`.
    The `#define` sits inside an `extern "C"` block, which has no
    effect on it and is misleading.

18. **[FIXED]** `platform-functions.h` now declares
    `riscv_board_get_rtc_frequency_hz()` and
    `riscv::board::rtc_frequency_hz()` (documented), and includes
    `inlines/platform-functions-inlines.h` automatically when
    `RISCV_PLATFORM_RTC_FREQUENCY_HZ` is defined, as
    `device-functions.h` does for the MMIO addresses. The frequency
    itself remains platform data, since no CSR reports it. Verified on
    RV32 and RV64: clean with the macro in C and C++, and with the
    current `platform-sifive-hifive1` sequence (which still includes the
    inlines file explicitly, harmlessly); without the macro, one
    `-Wunused-function` warning (the accepted trade-off). The macro was
    not renamed.
    **`platform-functions.h` is effectively empty** —
    `platform-functions.h:21-60`. It contains only commented-out
    declarations, and its file comment says "RISC-V core support
    functions". Either declare `riscv_board_get_rtc_frequency_hz()` and
    `riscv::board::rtc_frequency_hz()` properly, or remove the header
    and keep only the inline file.

19. **[FIXED]** The clobbers were reduced to `"a0", "a1", "memory"`,
    with a comment explaining why. The extra `a2`–`a5` clobbers had no
    cost (the function is out of line, and callers already treat
    `a0`–`a7` as clobbered; the generated code only used different
    scratch registers), so this is a precision fix. Verified: the
    semihosting call works under QEMU `virt` (RV32, RV64) and
    `sifive_u`.
    **Unexplained semihosting clobbers** — `src/semihosting.cpp:56`.
    The asm clobbers `a2` to `a5`, although the RISC-V semihosting
    convention returns only in `a0`. This is harmless but costs
    register pressure. Either state why it is required (for example a
    known host bug) or reduce it to `a0`, `a1`, and `"memory"`.

20. **[PARTLY FIXED]** The two disabled `riscv_csr_read/write (reg)`
    blocks in `csr-functions.h` and `inlines/csr-functions-inlines.h`
    (including the `"=rm"` left from #12) were replaced by working
    generic CSR access: the C macros `RISCV_CSR_READ (csr)` and
    `RISCV_CSR_WRITE (csr, value)` (CSR name or number, pasted into
    the instruction; GNU statement expressions under `__extension__`)
    and the C++ templates `riscv::csr::read<N> ()` and
    `riscv::csr::write<N> (value)` (`static_assert` on the 12-bit
    range). The writes are compiler memory barriers, as in #3.
    Verified in C and C++, at `-O0` and `-O2`, on RV32 and RV64, with
    `-Wpedantic`; and at run time under QEMU (`mscratch` round trip
    through both forms, immediate write, `read<0x300>()` equal to
    `mstatus()`). Remaining: the `#if 0` block in `defines.h` and the
    `TODO` in `declarations.h`.
    **Dead code and placeholders** — remove or resolve:
    - `defines.h:27-139` (113 lines inside `#if 0`, with a TODO);
    - `csr-functions.h:29-39`;
    - `inlines/csr-functions-inlines.h:29-49`;
    - the `// TODO: add C++ declarations here.` block in
      `declarations.h:39-46`.

    Dead code in public headers makes reviews and searches harder.

### Naming and style

21. **Lines longer than 80 characters**:
    - ~~`src/reset-entry.S:68`, `:71`, and `:75`~~ (fixed by #7);
    - ~~`src/debugger-entry-point.S:48` (87)~~ (superseded by #28:
      the guard lines in both `.S` files and the C++20 check in
      `architecture.h` are now deliberately longer than 80
      characters, following `architecture-cortexm`);
    - `device-functions.h:102` (81; the separator is two characters
      too long for its indentation).

22. **[FIXED]** The originally listed lines had already been cleaned by
    other edits; the three remaining ones (`src/reset-entry.S:60` and
    `device-functions.h:25` and `:27`) were stripped. No trailing
    whitespace remains in `include/` or `src/`.
    **Trailing whitespace** — `src/reset-entry.S:28`, `:55`, and `:85`;
    `src/debugger-entry-point.S:29` and `:32`.

23. **[CLOSED, accepted]** The `types.h` case was fixed in #29
    (typedefs moved out of the `extern "C"` block), and the `#if`-split
    declarations went away in #2 and #32. The six remaining
    in-function RV32/RV64 blocks (`riscv_csr_read_mcycle()`, `_low()`,
    `_high()`, `riscv_device_read_mtime()`, `riscv_device_write_mtime()`,
    and `riscv_device_write_mtimecmp()`) keep the clang-format layout,
    in which the second branch is indented one level less; wrapping
    them in `// clang-format off`/`on` was tried and rejected as less
    readable. This is a known clang-format limitation, with no effect
    on the generated code.
    **Formatting distorted by preprocessor-split declarations** —
    `types.h:28-29` (unindented typedefs), `csr-functions.h:126-129`,
    and `device-functions.h:38-54` and `:74-78`. The `static` keyword
    sits under `#if` and the return type is indented by 6.
    `inlines/csr-functions-inlines.h:284` and `:308` have `return` at
    the wrong indentation. These are artefacts of `clang-format`
    handling `#if` inside declarations. Fix: write a complete
    declaration in each `#if` branch.

24. **[FIXED]** `inlines/core-functions-inlines.h` now has the
    separator after `namespace core {`. A script checked all 32
    namespace bodies in `include/`: each starts with a
    `// ----` separator (or directly with a nested namespace).
    **Missing section separators** —
    `inlines/core-functions-inlines.h:59-60` has no
    `// ----` separator after `namespace core {`, unlike every other
    file.

25. **[FIXED]** "prefered" → "preferred", "optimized"/"optimizes" →
    "optimised"/"optimises" (`reset-entry.S`), "Initialize" →
    "Initialise" in the `plic::initialize()` comment, and "debuggger" →
    "debugger" (`xcdl-package.jsonc`; the typo had not propagated to
    the generated build files). A re-scan of `include/` and `src/`
    found no other US spellings in comments; the `initialize` API
    identifiers were deliberately kept, since `devices-sifive` defines
    them.
    **US spelling and typos in comments** (the project requires
    British English):
    - "prefered" (`reset-entry.S:28`);
    - "optimized" and "optimizes" (`reset-entry.S:37` and `:41`);
    - "Initialize" (`plic-functions.h:39`);
    - "debuggger" (`xcdl-package.jsonc`, outside the review scope but
      noted).

26. **[FIXED]** Renamed to `MICRO_OS_PLUS_ARCHITECTURE_RISCV_TYPES_H_`
    and `MICRO_OS_PLUS_ARCHITECTURE_RISCV_DECLARATIONS_H_`. The old
    names were not referenced anywhere else in the µOS++ packages. A
    script confirmed that all 17 headers now use guards derived from
    their paths.
    **Inconsistent header guard names** — `types.h` uses
    `..._ARCH_TYPES_H_` and `declarations.h` uses
    `..._ARCH_DECLARATIONS_H_`, while all other headers follow the
    file name. Use `MICRO_OS_PLUS_ARCHITECTURE_RISCV_TYPES_H_` and
    `MICRO_OS_PLUS_ARCHITECTURE_RISCV_DECLARATIONS_H_`.

### Conditional compilation

27. **[FIXED]** `src/reset-entry.S` now uses
    `#if defined(__riscv_cmodel_compact)`, with matching `#else` and
    `#endif` comments.
    27. **Bare `#ifdef`** — `src/reset-entry.S:44`
    (`#ifdef __riscv_cmodel_compact`); use
    `#if defined(__riscv_cmodel_compact)`.

28. **[FIXED]** A script that pairs every conditional (excluding
    header guards) now reports no violations in `include/` and `src/`:
    all `#else` lines have a comment, and every `#endif` repeats the
    exact `#if` expression (`// __riscv_xlen == 32`, `// 0`, the C++20
    check in `architecture.h`, and the component guards in both `.S`
    files, now `//` comments instead of `/* */`). As in
    `architecture-cortexm` and `diag-trace`, the C++20 check and the
    two-macro `.S` guards are kept on single lines longer than 80
    characters, since the rule requires the exact expression; see #21.
    28. **`#else` / `#endif` comments missing or not repeating the
    expression**:
    - Missing:
      - `architecture.h:20`;
      - `csr-functions.h:39`;
      - `inlines/csr-functions-inlines.h:49`;
      - `defines.h:23` and `:184` (`#else`);
      - `src/reset-entry.S:52` (`#else`) and `:56`.
    - Not the exact expression:
      - `// __riscv_xlen` at `types.h:30`, `defines.h:25`, `:132`, and
        `:186`, and `inlines/csr-functions-inlines.h:286` and `:310`;
      - `// 0-1` at `defines.h:139`;
      - ~~`// __riscv_fdiv` at `src/reset-entry.S:78`~~ (fixed by
        #7).

### Documentation (Doxygen)

29. **[FIXED]** (the Doxygen limitation noted below was resolved by
    #32) Measured with Doxygen
    1.17 (a filter added `@file` to every file, since none has one, and
    `WARN_NO_PARAMDOC` was enabled): 169 warnings before, 0 in the
    headers after. Every declaration in `csr-functions.h`,
    `core-functions.h`, `device-functions.h`, `instructions.h`,
    `types.h`, `plic-functions.h`, `platform-functions.h`, and
    `inlines/semihosting-inlines.h` now has `@brief` and `@details`,
    plus `@param`/`@return` (or `@par`) for functions. Each macro in
    `defines.h` has a one-line `/// @brief`, under the existing family
    comments. The definition in `src/semihosting.cpp` has `@details`.
    The comments duplicated in `inlines/` were removed; the
    implementation notes (RV32 sequences) were kept. The static
    assertions in `types.h` are hidden from Doxygen with
    `#if !defined(__DOXYGEN__)`. The 44 remaining warnings are all
    `static` C definitions in `inlines/`, which Doxygen treats as
    separate entities from their documented declarations (a `static`
    function belongs to its file); see the note in the summary.
    29. **Most declarations are undocumented, or documented with a single
    line only.** No declaration in `csr-functions.h`,
    `core-functions.h`, `device-functions.h`, `instructions.h`,
    `types.h`, `defines.h`, `declarations.h`, `functions.h`, or
    `inlines/semihosting-inlines.h` has both `@brief` and `@details`,
    except the two barrier functions in `instructions.h`. There are no
    `@param` or `@return` tags outside `plic-functions.h`. The C PLIC
    declarations (`plic-functions.h:233-265`), all enums, typedefs,
    and macros, and the definitions in `src/` have no documentation at
    all. Some definitions in `inlines/` repeat (and may drift from)
    the header comments:
    - `inlines/core-functions-inlines.h:35-37`;
    - `inlines/instructions-inlines.h:103-132`;
    - `inlines/csr-functions-inlines.h:119-121`, `:139-141`, and
      `:244-246`.

    Recommendation: document every declaration with `@brief`,
    `@details`, `@param`, and `@return`, and keep only `@details`
    implementation notes at definitions.

30. **[FIXED]** "`break` instruction" replaced by "Breakpoint"
    (executes `ebreak`) in C and C++; "RTC" replaced by the `mtime` and
    `mtimecmp` register names; `riscv_trap_entry` documented in #16;
    the `STACK_FILL_MAGIC` comments now explain the byte order.
    30. **Inaccurate documentation**:
    - "`break` instruction" (`instructions.h:79` and `:190`,
      `inlines/instructions-inlines.h:104`); RISC-V uses `ebreak`.
    - "Read the RTC current counter" / "RTC comparator"
      (`device-functions.h:106` and `:130`); `mtime` is the machine
      timer, not necessarily an RTC.
    - "Hardware trap entry point (assembly)" (`core-functions.h:43`);
      it is not provided by this package.
    - The `STACK_FILL_MAGIC` comments (`defines.h:18` and `:21`) should
      explain that the values are byte-swapped so that memory dumps on
      little-endian cores read `DEADBEEF`.

31. **[FIXED]** Documented: the set and clear helpers are atomic
    (`csrrs`/`csrrc`) and safe in interrupt handlers, while the plain
    writes are not read-modify-write safe; the RV32 halves of `mcycle`,
    `mtime`, and `mtimecmp` are not atomic (use the 64-bit functions),
    and writing the `mtimecmp` halves separately may cause spurious
    interrupts; the PLIC claim must be completed on the same hart, and
    the threshold update is not atomic.
    31. **Reentrancy and atomicity are not documented.** State that:
    - `csrrs` and `csrrc` are atomic, so the set and clear helpers
      are interrupt-safe;
    - RV32 split accesses to `mtime` and `mtimecmp` are not atomic;
    - PLIC claim and complete must be called on the hart that received
      the interrupt.

### Modern C++

32. **[FIXED]** Aligned with `architecture-aarch32` and
    `architecture-aarch64`: the new `MICRO_OS_PLUS_ALWAYS_INLINE`
    macro (`defines.h`; `[[gnu::always_inline]] inline` in C++,
    `static inline __attribute__ ((always_inline))` in C) is used on all
    declarations and definitions of the inline wrappers, in C and C++;
    in C++ the C functions now have external linkage, as required by
    the One Definition Rule. All C++ functions defined in this package
    are `noexcept`, and those returning a value are `[[nodiscard]]`,
    except the set/clear helpers, whose previous value is optional.
    The functions defined in other packages (`running_frequency_hz()`,
    `update_running_frequency()`, the PLIC functions) were deliberately
    left unchanged, since adding `noexcept` to their declarations
    would break those definitions. `(void)` parameter lists were kept,
    as in the sibling packages. Side effects: in C++ every header now
    compiles standalone without warnings, and Doxygen links the
    declarations to the inline definitions (0 warnings in total,
    which also closes the remaining part of #29). Verified: all
    earlier tests, `-O0` inlining, `noexcept`/`[[nodiscard]]` checks,
    QEMU runs, and `devices-sifive`/`platform-sifive-hifive1` sources
    (through shims for their stale include paths and macro names).
    Note for #34: callers that ignore a getter result now get a
    `-Wunused-result` warning.
    32. **C++ wrappers lack standard attributes** — none of the wrappers
    are marked `noexcept`, although none can throw. Getters such as
    `mstatus()`, `mcause()`, `mhartid()`, `mtime()`, and
    `claim_interrupt()` lack `[[nodiscard]]`. The C++ code uses `(void)`
    parameter lists and `__attribute__ ((always_inline))` where
    `[[gnu::always_inline]]` is available. Low severity, but it
    contradicts the project's C++20 target.

33. **Constants are macros only** — the CSR bit macros could have
    `inline constexpr` equivalents in `riscv::csr` for C++ users, while
    the macros remain for C and assembly (after #5 is fixed).

### Licensing and metadata

34. All 22 files carry the identical MIT licence header, with plausible
    year ranges. No action is needed. When the fixes for #1 to #8 are
    made, add entries to `CHANGELOG.md`. Removing undefined RV32
    declarations (#2) or changing the C++ wrapper return types (#11)
    is an API change that may require a major version bump.

### Tests

35. **No tests.** There is no `tests/` folder, and none of the defects
    above would have been caught by CI. Recommendation: add at least
    the following:
    - compile-only checks that include every header standalone, for
      RV32 and RV64, in C and C++, with `-Werror`;
    - an assembly check for `defines.h`;
    - a semihosted run under `qemu-system-riscv32` and
      `qemu-system-riscv64` (the xPack `qemu-riscv` is available)
      exercising `reset_entry`, the semihosting call, and the counter
      reads.

## Left out or uncertain

- `src/reset-entry.S:44-50`: the `__riscv_cmodel_compact` path
  references `__global_pointer$` (not `__global_pointer$`) and loads
  it indirectly with `ld`. This appears to be copied from newlib's
  `crt0.S`. I could not confirm that the µOS++ linker scripts define
  that symbol, so it is not reported as a defect.
- `riscv::architecture::register_t` and
  `micro_os_plus::architecture::register_t` share their name with
  newlib's global `register_t` (`<sys/types.h>`). A `using namespace`
  directive could cause ambiguous lookups. Not reproduced, so not
  reported.
- Whether the targeted cores can report `misa == 0` (#7) depends on
  the devices supported; the defect is real per the specification,
  but may not be reachable on current boards.
- Doxygen was not run, so unresolved references and signature
  mismatches were not checked mechanically.
- Files outside `include/` and `src/` (build scripts, CI, README) were
  not reviewed; their inconsistencies are noted in `CLAUDE.md`.
