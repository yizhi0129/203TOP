cmake_minimum_required(VERSION 3.16)
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(TOP-LAB01-vector LANGUAGES C)

add_library(vec SHARED vector.c)
add_library(compute SHARED compute.c)

add_executable(main main.c)
target_link_libraries(main vec compute)
target_compile_options(main PUBLIC -Wall -Wextra -Werror -O3)