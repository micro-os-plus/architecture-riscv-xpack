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

if(micro-os-plus-architecture-riscv-platform-included)
  return()
endif()

set(micro-os-plus-architecture-riscv-platform-included TRUE)

message(STATUS "Including micro-os-plus-architecture-riscv/platform...")

# -----------------------------------------------------------------------------
# The current folder.

get_filename_component(xpack_current_folder ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# -----------------------------------------------------------------------------

if(NOT TARGET micro-os-plus-architecture-riscv-platform-interface)

  add_library(micro-os-plus-architecture-riscv-platform-interface INTERFACE EXCLUDE_FROM_ALL)

  # ---------------------------------------------------------------------------
  # Target settings.
  
  target_sources(
    micro-os-plus-architecture-riscv-platform-interface

    INTERFACE
      ${xpack_current_folder}/src/rtos/port/functions.cpp
  )

  target_include_directories(
    micro-os-plus-architecture-riscv-platform-interface

    INTERFACE
      # ${xpack_current_folder}/include
  )

  target_link_libraries(
    micro-os-plus-architecture-riscv-platform-interface

    INTERFACE
      micro-os-plus::device
  )

  # ---------------------------------------------------------------------------
  # Aliases.

  add_library(micro-os-plus::architecture-riscv-platform ALIAS micro-os-plus-architecture-riscv-platform-interface)
  message(STATUS "micro-os-plus::architecture-riscv-platform")

endif()

# -----------------------------------------------------------------------------
