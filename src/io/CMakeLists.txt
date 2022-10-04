cmake_minimum_required(VERSION 3.16)
project(io VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

if(NOT r_no_dxf)
    add_subdirectory(dxf)
endif()
