cmake_minimum_required(VERSION 4.0) #setting the required version of CMake. Have to be very first line

set(TARGET stm32f405rgt6) # Specifying Target

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-toolchain.cmake) #Adding toolcahin file which contains all the necessary toolchain information needed to compile the project


set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F405XX_FLASH.ld) # setting linker scripts

project(stm32f446 LANGUAGES C CXX ASM) # Specifying project


#Adding all the Source file
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cc
    ${CMAKE_SOURCE_DIR}/src/*.s
    ${CMAKE_SOURCE_DIR}/src/*.S
)

#adding startup file to the SOURCES variable
list(APPEND SOURCES ${STARTUP_FILE})

#adding executable to the target
add_executable(${TARGET}.elf ${SOURCES})


target_include_directories(${TARGET}.elf PUBLIC 
    "C:/cmsis/STM32F4xx/inc"
    "C:/cmsis/ARM/inc"
    ${CMAKE_SOURCE_DIR}/inc
)

target_compile_definitions(${TARGET}.elf PUBLIC STM32F405xx)

target_compile_options(${TARGET}.elf PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -specs=nano.specs
    -u
    -fno-exceptions
    -fno-tree-loop-distribution
)

target_link_options(${TARGET}.elf PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,--gc-sections
    --specs=nano.specs
)

add_custom_command(
    TARGET ${TARGET}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
            ${CMAKE_BINARY_DIR}/${TARGET}.elf
            ${CMAKE_BINARY_DIR}/${TARGET}.bin
    COMMENT "Converting ELF to BIN after build"
)


add_custom_target(flash
    DEPENDS ${CMAKE_BINARY_DIR}/stm32f405rgt6.bin
    COMMAND ${STLINK_PATH} -P ${CMAKE_BINARY_DIR}/stm32f405rgt6.bin 0x08000000 -Rst
    COMMENT "Flashing binary to STM32 using ST-Link"
)
