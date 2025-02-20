# Copyright 2022-2023 NXP

# Set the SoC specific drivers and configuration to build
if(${CONFIG_SOC} STREQUAL "s32z27")
  set(SOC_BASE ${CONFIG_SOC})
  set(DRIVERS_BASE s32ze)
elseif(${CONFIG_SOC} MATCHES "s32k3.*")
  set(SOC_BASE ${CONFIG_SOC})
  set(DRIVERS_BASE s32k3)
else()
  message(FATAL_ERROR "SoC ${CONFIG_SOC} not supported")
endif()

add_subdirectory(drivers/${DRIVERS_BASE})
add_subdirectory(soc/${SOC_BASE})

if(CONFIG_HAS_MCUX)

  # This is an adaptation from hal_nxp/mcux/CMakeLists.txt entry CMake in order
  # to build MCUX drivers together with RTD drivers for NXP S32 devices.
  # MCUX don't have official support for NXP S32 devices but we are leveraging
  # the existing shim drivers in Zephyr for those hardware blocks which are
  # present in both NXP S32 and non NXP S32 devices.
  #
  # Glue code must be added for each device supported to build with MCUX. This
  # can be found in hal_nxp/s32/mcux/devices:
  # - s32/mcux/devices/${MCUX_DEVICE}/${MCUX_DEVICE}_device.h
  #   redefine RTD module's peripheral access layers and its register masks to be
  #   compatible with MCUX drivers for incompatible peripherals
  # - s32/mcux/devices/${MCUX_DEVICE}/${MCUX_DEVICE}_features.h
  #   define SoC module's features
  # - s32/mcux/devices/${MCUX_DEVICE}/${MCUX_DEVICE}_glue_mcux.h
  #   redefine RTD module's base addresses/pointers/interrupts to be compatible
  #   with MCUX drivers
  # - s32/mcux/devices/${MCUX_DEVICE}/fsl_device_registers.h
  #   expose device features to the MCUX drivers
  # - s32/mcux/devices/${MCUX_DEVICE}/drivers/fsl_clock.h
  #   required by mcux/mcux-sdk/drivers/common/fsl_common_arm.h (at least)
  # - s32/mcux/devices/${MCUX_DEVICE}/drivers/driver_reset.cmake
  #   required by mcux/mcux-sdk/drivers/common/drivers_common.cmake
  # - s32/mcux/devices/${MCUX_DEVICE}/device_system.cmake
  #   required by mcux/hal_nxp.cmake
  # - s32/mcux/devices/${MCUX_DEVICE}/device_CMSIS.cmake
  #   required by mcux/mcux-sdk/drivers/common/drivers_common.cmake for non DSP
  #   architectures

  set(MCUX_SDK_PROJECT_NAME ${ZEPHYR_CURRENT_LIBRARY})

  # Translate the SoC name and part number into the MCUX device and CPU
  # name respectively
  string(TOUPPER ${CONFIG_SOC} MCUX_DEVICE)
  set(MCUX_CPU CPU_${CONFIG_SOC_PART_NUMBER})

  # This is normally done in mcux/hal_nxp.cmake, but we need to point to the
  # path on this directory instead
  list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/mcux/devices/${MCUX_DEVICE}
    ${CMAKE_CURRENT_LIST_DIR}/mcux/devices/${MCUX_DEVICE}/drivers
  )

  # MCUX uses the CPU name to expose SoC-specific features of a given peripheral
  zephyr_compile_definitions(${MCUX_CPU})

  # Clock control is supported through RTD, so disable it in the MCUX drivers
  zephyr_compile_definitions(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL=1)

  zephyr_include_directories(mcux/devices/${MCUX_DEVICE})
  zephyr_include_directories(mcux/devices/${MCUX_DEVICE}/drivers)

  zephyr_linker_sources(RWDATA
    ${CMAKE_CURRENT_LIST_DIR}/../mcux/quick_access_data.ld
  )
  zephyr_linker_sources_ifdef(CONFIG_ARCH_HAS_RAMFUNC_SUPPORT
    RAMFUNC_SECTION
    ${CMAKE_CURRENT_LIST_DIR}/../mcux/quick_access_code.ld
  )
  zephyr_linker_sources_ifdef(CONFIG_NOCACHE_MEMORY
    NOCACHE_SECTION
    ${CMAKE_CURRENT_LIST_DIR}/../mcux/nocache.ld
  )

  # Entry CMake component for MCUX
  include(${CMAKE_CURRENT_LIST_DIR}/../mcux/hal_nxp.cmake)

endif()
