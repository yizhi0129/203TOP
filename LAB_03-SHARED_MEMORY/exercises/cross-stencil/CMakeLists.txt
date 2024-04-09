cmake_minimum_required(VERSION 3.16)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(LDFLAGS "-L/usr/local/opt/libomp/lib")
set(CPPFLAGS "-I/usr/local/opt/libomp/include")

project(TOP-LAB_02-cross_stencil LANGUAGES CXX)
add_compile_options(-Wall -Wextra -Wconversion)

find_package(fmt REQUIRED)
find_package(OpenMP REQUIRED)

add_compile_options(${CPPFLAGS})
link_directories(${LDFLAGS})

add_library(non-blocked src/non_blocked.cpp)
target_include_directories(non-blocked PUBLIC include ext/mdspan/include/mdspan)
target_link_libraries(non-blocked OpenMP::OpenMP_CXX)

add_library(blocked src/blocked.cpp)
target_include_directories(blocked PUBLIC include ext/mdspan/include/mdspan)
target_link_libraries(blocked OpenMP::OpenMP_CXX)

add_executable(cross-stencil src/main.cpp)
target_include_directories(cross-stencil PUBLIC include ext/mdspan/include/mdspan)
target_link_libraries(cross-stencil non-blocked blocked fmt::fmt OpenMP::OpenMP_CXX)
