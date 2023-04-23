cmake_minimum_required(VERSION 3.18)

project(CFDFlow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Add libCFDFlow
add_subdirectory(libCFDFlow)