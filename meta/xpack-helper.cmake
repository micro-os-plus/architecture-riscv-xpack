#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# This Source Code Form is subject to the terms of the MIT License.
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

message(STATUS "Including micro-os-plus-architecture-riscv...")

# -----------------------------------------------------------------------------

function(target_sources_micro_os_plus_architecture_riscv target)

  get_filename_component(xpack_root_folder ${CMAKE_CURRENT_FUNCTION_LIST_DIR} DIRECTORY)

  target_sources(
    ${target}

    PRIVATE
      ${xpack_root_folder}/src/rtos/port/os-core.cpp
      ${xpack_root_folder}/src/functions.cpp
      ${xpack_root_folder}/src/reset-entry.S
      ${xpack_root_folder}/src/trap-entry.S
      ${xpack_root_folder}/src/traps.cpp
  )

endfunction()

# -----------------------------------------------------------------------------

function(target_include_directories_micro_os_plus_architecture_riscv target)

  get_filename_component(xpack_root_folder ${CMAKE_CURRENT_FUNCTION_LIST_DIR} DIRECTORY)

  target_include_directories(
    ${target}

    PUBLIC
      ${xpack_root_folder}/include
  )

endfunction()

# -----------------------------------------------------------------------------

function(target_compile_definitions_micro_os_plus_architecture_riscv target)

  # None

endfunction()

# -----------------------------------------------------------------------------
