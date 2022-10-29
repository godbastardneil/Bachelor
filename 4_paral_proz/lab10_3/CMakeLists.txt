cmake_minimum_required(VERSION 3.5)

project(lab10_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab10_3 main.cpp)

SET(CMAKE_CXX_FLAGS -pthread)
