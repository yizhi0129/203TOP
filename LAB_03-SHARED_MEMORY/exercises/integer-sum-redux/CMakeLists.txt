cmake_minimum_required(VERSION 3.16)
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(TOP-LAB_03-integer_sum_redux LANGUAGES CXX)
add_compile_options(-Wall -Wextra -Wconversion -O0)
# add_compile_options(-Wall -Wextra -Wconversion -O3)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

# Check if the compiler is Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Clang needs a different flag to enable OpenMP
    set(OpenMP_CXX_FLAGS "-fopenmp=libomp")
endif()

# Set OpenMP library names for Clang
set(OpenMP_CXX_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY "libomp.so")

find_package(OpenMP REQUIRED)

if(OPENMP_FOUND)
    message(STATUS "OpenMP found")
    message(STATUS "OpenMP_CXX_FLAGS: ${OpenMP_CXX_FLAGS}")
    message(STATUS "OpenMP_CXX_LIB_NAMES: ${OpenMP_CXX_LIB_NAMES}")
endif()

add_library(seq src/sequential.cpp)
target_include_directories(seq PUBLIC include)
target_link_libraries(seq OpenMP::OpenMP_CXX)

add_executable(int-sum-redux src/main.cpp)
target_include_directories(int-sum-redux PUBLIC include)
target_link_libraries(int-sum-redux seq fmt::fmt OpenMP::OpenMP_CXX m)
