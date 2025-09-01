# Force generic embedded cross-compilation
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Only set toolchain if host is Windows
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(TOOLCHAIN_PATH "C:/Program Files (x86)/Arm-gcc/bin")

    set(CMAKE_C_COMPILER   "${TOOLCHAIN_PATH}/arm-none-eabi-gcc.exe")
    set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-g++.exe")
    set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-gcc.exe")

    # Optional post-build tools
    set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/arm-none-eabi-objcopy.exe")
    set(CMAKE_SIZE    "${TOOLCHAIN_PATH}/arm-none-eabi-size.exe")
    set(STLINK_PATH "C:/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe")
endif()





# Flags for Cortex-M4
set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -Wall -nostdlib -g -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-tree-loop-distribution")


# Use static library during try-compile
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_ASM_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_C_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_CXX_EXECUTABLE_SUFFIX ".elf")