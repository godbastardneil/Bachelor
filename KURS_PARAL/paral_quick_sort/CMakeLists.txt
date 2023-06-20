cmake_minimum_required(VERSION 3.5)

project(paral_quick_sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(paral_quick_sort main.cpp)

SET(CMAKE_CXX_FLAGS -pthread)
