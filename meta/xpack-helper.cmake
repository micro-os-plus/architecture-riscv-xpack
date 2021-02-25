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

if(micro-os-plus-architecture-riscv-included)
  return()
endif()

set(micro-os-plus-architecture-riscv-included TRUE)

message(STATUS "Including micro-os-plus-architecture-riscv...")

# -----------------------------------------------------------------------------
# Local dependencies.

include("${CMAKE_CURRENT_LIST_DIR}/../device/meta/xpack-helper.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/../platform/meta/xpack-helper.cmake")

# -----------------------------------------------------------------------------

get_filename_component(xpack_current_folder ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# -----------------------------------------------------------------------------

if(NOT TARGET micro-os-plus-architecture-riscv-interface)

  add_library(micro-os-plus-architecture-riscv-interface INTERFACE EXCLUDE_FROM_ALL)

  # ---------------------------------------------------------------------------
  # Target settings.

  target_sources(
    micro-os-plus-architecture-riscv-interface

    INTERFACE
      ${xpack_current_folder}/src/reset-entry.S
      ${xpack_current_folder}/src/trap-entry.S
  )

  target_include_directories(
    micro-os-plus-architecture-riscv-interface

    INTERFACE
      ${xpack_current_folder}/include
  )

  # ---------------------------------------------------------------------------
  # Aliases.

  add_library(micro-os-plus::architecture-riscv ALIAS micro-os-plus-architecture-riscv-interface)
  message(STATUS "micro-os-plus::architecture-riscv")
  add_library(micro-os-plus::architecture ALIAS micro-os-plus-architecture-riscv-interface)
  message(STATUS "micro-os-plus::architecture")

endif()

# -----------------------------------------------------------------------------
