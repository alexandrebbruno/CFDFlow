# Find Armadillo library
find_package(Armadillo REQUIRED)

# Find pybind11 package
find_package(pybind11 REQUIRED)

set(TARGET_NAME CFDFlow)

# Add your library
add_library(${TARGET_NAME} SHARED
    Mesh.cpp
    Solver.cpp
)

# Link Armadillo library to your library
include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${ARMADILLO_LIBRARIES})

# Add include directories for your library
target_include_directories(${TARGET_NAME} PUBLIC
    include
    ${ARMADILLO_INCLUDE_DIRS}
)


# Create the pybind11 module
pybind11_add_module(PyCFDFlow CFDFlow.py.cpp Mesh.py.cpp Solver.py.cpp)

# Link pybind11 module with C++ lib
target_link_libraries(PyCFDFlow PRIVATE ${TARGET_NAME})
