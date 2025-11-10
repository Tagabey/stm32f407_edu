cmake_minimum_required(VERSION 3.22)

enable_language(C ASM CXX)

set(MCU_name "STM32F407xx")

set(Defines_Symbols
    ${MCU_name}
    $<$<CONFIG:Debug>:DEBUG>
)

set(Include_Paths
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32F4xx
)

set(Application_Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/startup_stm32f407xx.s
)

set(Driver_Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/system_stm32f4xx.c
)

# static libraries
set(link_libs
    STM32_Drivers
    ${TOOLCHAIN_LIBRARIES}
)

# interface libs for includes and symbols
add_library(CMSIS_lib INTERFACE)
target_include_directories(CMSIS_lib INTERFACE ${Include_Paths})
target_compile_definitions(CMSIS_lib INTERFACE ${Defines_Symbols})

#
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${Driver_Sources})
target_link_libraries(STM32_Drivers PUBLIC CMSIS_lib)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${Application_Sources})

target_link_libraries(${CMAKE_PROJECT_NAME} ${link_libs})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()

