cmake_minimum_required(VERSION 3.10)
project(ListAlgorithms C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Source files
file(GLOB SOURCES "src/list/*.c")

# Build executable
add_executable(list_algo ${SOURCES} test/main.c)

# clang-format target
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i inc/list/*.h src/list/*.c test/main.c
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting code with clang-format")
endif()
