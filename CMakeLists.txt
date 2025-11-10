cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the build type (also it is defined in CMakePreset.json file)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME real_time_cpp)

# Enable compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})


enable_language(C ASM CXX)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(cmake/custom_system)

target_link_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
    # add user defined library search path
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # add user sources here
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # add user defined include paths
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # add user defined symbols
)

list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

target_link_libraries(${CMAKE_PROJECT_NAME}
    # CMSIS_lib
    # add user defined libraries ex: stm32cubemx
)

# Post build commands
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
        $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating binary file from ELF"
)
