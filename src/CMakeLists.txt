cmake_minimum_required(VERSION 3.31.6)
project(gto)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-O3 -march=native -flto")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

add_subdirectory(common)
add_subdirectory(test)
