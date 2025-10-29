cmake_minimum_required(VERSION 3.15)
project(stm32f407_project C CXX ASM)

# Enable compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-DSTM32F407xx)

# MCU settings
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F407xx)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/STM32F407XX_FLASH.ld)

# Compiler options
set(CMAKE_C_FLAGS "${MCU_FLAGS} -O2 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -O2 -fno-exceptions -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} -Wl,--gc-sections")

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.c"
    "src/*.cpp"
    "src/*.s"
)

# Include paths
include_directories(
    include
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

# Define target
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Post-build commands (size + binary)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND arm-none-eabi-size ${PROJECT_NAME}.elf
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)

# Optional: copy compile_commands.json to root for VS Code IntelliSense
add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)
