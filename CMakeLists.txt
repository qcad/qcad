cmake_minimum_required(VERSION 3.16)

include(CMakeInclude.txt)

project(qcad VERSION 1.0 LANGUAGES CXX)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

option(BUILD_QT6 "Building with Qt 6.x" ON)

add_subdirectory(src)
