cmake_minimum_required(VERSION 3.21)
project(hex_grid)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG        v2.6.2
)

if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()



#main.cpp
#src/cpp/wrapper.cpp

set(LIB_SOURCES
#        src/cpp/math/math_common.h
#        src/cpp/math/matrix2.cpp
#        src/cpp/math/matrix2.h
#        src/cpp/math/matrix3.cpp
#        src/cpp/math/matrix3.h
        src/cpp/math/vector2.cpp
        src/cpp/math/vector2.h
        src/cpp/math/vector3.cpp
        src/cpp/math/vector3.h
#        src/cpp/math/quaternion.cpp
#        src/cpp/math/quaternion.h

        src/cpp/planet/grid/corner.cpp
        src/cpp/planet/grid/corner.h
        src/cpp/planet/grid/create_grid.cpp
        src/cpp/planet/grid/create_grid.h
        src/cpp/planet/grid/edge.cpp
        src/cpp/planet/grid/edge.h
        src/cpp/planet/grid/tile.cpp
        src/cpp/planet/grid/tile.h
        src/cpp/planet/grid/grid.cpp
        src/cpp/planet/grid/grid.h
        src/cpp/planet/planet.cpp
        src/cpp/planet/planet.h
        src/cpp/render/globe_renderer.cpp
        src/cpp/render/globe_renderer.h src/cpp/render/Colour.h)

pybind11_add_module(hex_grid
        src/cpp/wrapper.cpp
        ${LIB_SOURCES}
        )

add_executable(hex_grid_exec
        src/cpp/main.cpp
        ${LIB_SOURCES}
)
