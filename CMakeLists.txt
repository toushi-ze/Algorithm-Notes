# CMakeLists.txt for Generic Linked List Library
# Industrial Grade Linked List Library

cmake_minimum_required(VERSION 3.10)
project(GenericLinkedList VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    # MSVC specific flags
    add_compile_options(/W4)
else()
    # GCC/Clang flags
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# ========================================
# Library Target
# ========================================
add_library(list STATIC
    src/list/list.c
)

# Set library properties
set_target_properties(list PROPERTIES
    OUTPUT_NAME "list"
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# ========================================
# Test Executable
# ========================================
add_executable(list_test
    test/list_test.c
)

# Link test executable with list library
target_link_libraries(list_test list)

# Set test output directory
set_target_properties(list_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ========================================
# Algorithms Test Executable
# ========================================
add_executable(algorithms_test
    test/algorithms_test.c
    src/list/list_node.c
    src/list/list_cycle.c
    src/list/list_cycle_ii.c
    src/list/list_reverse.c
    src/list/list_merge.c
    src/list/list_nth_remove.c
    src/list/list_range_reverse.c
    src/list/list_k_group_reverse.c
)

# Set algorithms test output directory
set_target_properties(algorithms_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ========================================
# Installation
# ========================================
# Install headers
install(DIRECTORY inc/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Install library
install(TARGETS list
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# Install executables (optional)
install(TARGETS list_test algorithms_test
    RUNTIME DESTINATION bin
)

# ========================================
# Testing
# ========================================
enable_testing()
add_test(NAME list_test
    COMMAND list_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_test(NAME algorithms_test
    COMMAND algorithms_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# ========================================
# Build Type Configuration
# ========================================
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "Project version: ${PROJECT_VERSION}")
