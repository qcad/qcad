cmake_minimum_required(VERSION 3.16)
project(qcad VERSION 1.0 LANGUAGES CXX)

SET(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

option(BUILD_QT6 "Building with Qt 6.x" OFF)

include(CMakeInclude.txt)

add_subdirectory(src)
