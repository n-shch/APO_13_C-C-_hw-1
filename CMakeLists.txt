cmake_minimum_required(VERSION 3.1)
project(hw-1)
enable_language(C CXX ASM)
set(CMAKE_C_FLAGS  "-std=c11")


include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(vector STATIC src/vector.c)
add_library(parser STATIC src/parser.c)


add_executable(hw-1 src/main.c)
target_link_libraries(hw-1 vector parser)