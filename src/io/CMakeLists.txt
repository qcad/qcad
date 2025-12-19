cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(io VERSION 1.0 LANGUAGES CXX)

if(NOT r_no_dxf)
    add_subdirectory(dxf)
endif()
