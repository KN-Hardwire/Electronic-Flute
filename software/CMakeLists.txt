cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == VS Code extension integration ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ================================================

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico-sdk/pico_sdk_init.cmake)

project(flute C CXX ASM)

# =====================================================
# Build configuration options
# =====================================================

option(DEBUG_MODE "Enable debug mode" OFF)

set(PROJECT_TYPE "INT" CACHE STRING "Project numeric type: INT or FLOAT")
set_property(CACHE PROJECT_TYPE PROPERTY STRINGS INT FLOAT)

# Initialise SDK
pico_sdk_init()

# Compiler options
add_compile_options(-Wall -Wextra -O2)

# =====================================================
# Add include and source directories
# =====================================================

# Add include/ to header search paths
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Collect all .c files from source/
file(GLOB FLUTE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/source/*.c
)

# Create executable
add_executable(flute
    ${FLUTE_SOURCES}
)

# =====================================================
# Compile definitions
# =====================================================

# Debug mode (0 or 1)
target_compile_definitions(flute PRIVATE
    DEBUG_MODE=$<BOOL:${DEBUG_MODE}>
)

message("${DEBUG_MODE}")

# Link libraries
target_link_libraries(flute
    pico_stdlib
    hardware_adc
    hardware_pwm
)

# Uncomment appropriate debugging option
# pico_enable_stdio_usb(flute 1)
# pico_enable_stdio_uart(flute 0)
pico_enable_stdio_semihosting (flute 1)

# Generate map/bin/hex files
pico_add_extra_outputs(flute)
