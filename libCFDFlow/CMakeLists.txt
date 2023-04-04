cmake_minimum_required(VERSION 3.18)

set(TARGET_NAME libCFDFlow)

project(${TARGET_NAME} VERSION 1.0)

add_library(${TARGET_NAME} Mesh.cpp Solver.cpp)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${ARMADILLO_LIBRARIES})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)