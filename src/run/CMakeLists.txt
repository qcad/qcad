cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)
include(CMakeInclude.txt)

if (APPLE)
    project(QCAD)
else()
    project(qcad)
endif()
