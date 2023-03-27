cmake_minimum_required(VERSION 3.10)

project(CFDFlow VERSION 1.0)

add_executable(CFdFlow mesh.test.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)