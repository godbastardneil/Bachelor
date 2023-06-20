cmake_minimum_required(VERSION 3.5)

project(lab9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab9 main.cpp)

SET(CMAKE_CXX_FLAGS -pthread)
