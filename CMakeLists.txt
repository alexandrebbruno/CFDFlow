cmake_minimum_required(VERSION 3.18)

project(data_structures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(libCFDFlow)

add_executable(CFDFlow
main.cpp
)