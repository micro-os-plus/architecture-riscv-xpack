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

if(micro-os-plus-architecture-riscv-device-included)
  return()
endif()

set(micro-os-plus-architecture-riscv-device-included TRUE)

message(STATUS "Including micro-os-plus-architecture-riscv/device...")

# -----------------------------------------------------------------------------
# The current folder.

get_filename_component(xpack_current_folder ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# ---------------------------------------------------------------------------

if(NOT TARGET micro-os-plus-architecture-riscv-device-interface)

  add_library(micro-os-plus-architecture-riscv-device-interface INTERFACE EXCLUDE_FROM_ALL)

  # -------------------------------------------------------------------------
  # Target settings.
  
  target_sources(
    micro-os-plus-architecture-riscv-device-interface

    INTERFACE
      ${xpack_current_folder}/src/rtos/port/os-core.cpp
      ${xpack_current_folder}/src/rtos/port/traps.cpp
  )

  target_include_directories(
    micro-os-plus-architecture-riscv-device-interface

    INTERFACE
      ${xpack_current_folder}/include
  )

  target_link_libraries(
    micro-os-plus-architecture-riscv-device-interface

    INTERFACE
      # micro-os-plus::semihosting-static
  )

  # -------------------------------------------------------------------------
  # Aliases.

  add_library(micro-os-plus::architecture-riscv-device ALIAS micro-os-plus-architecture-riscv-device-interface)
  message(STATUS "micro-os-plus::architecture-riscv-device")

endif()

# -----------------------------------------------------------------------------