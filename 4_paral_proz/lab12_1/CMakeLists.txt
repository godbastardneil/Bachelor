cmake_minimum_required(VERSION 3.5)

project(lab12_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab12_1 main.cpp)

target_link_libraries(lab12_1 rt pthread)
