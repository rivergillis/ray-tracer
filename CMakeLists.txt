cmake_minimum_required(VERSION 3.10)
project(hw6clion)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_definitions(-DMAC -std=c++11 -Wno-deprecated-declarations)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OPENGL -framework GLUT")

add_executable(hw6clion
        constants.h
        hw6.cpp
        phong.cpp
        phong.h
        point3d.cpp
        point3d.h
        ray3d.cpp
        ray3d.h
        rgb.cpp
        rgb.h
        sphere3d.cpp
        sphere3d.h
        vec3d.cpp
        vec3d.h)
