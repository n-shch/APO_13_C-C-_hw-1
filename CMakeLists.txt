cmake_minimum_required(VERSION 3.1)
project(C_IZ1 C)
enable_language(C CXX ASM)
set(CMAKE_C_FLAGS  "-std=c11")


include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(C_IZ1 ${sources})