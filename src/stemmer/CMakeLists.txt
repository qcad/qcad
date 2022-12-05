cmake_minimum_required(VERSION 3.16)
project(qcadstemmer VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core)
qt_standard_project_setup()

IF(WIN32)
    SET(RC stemmer.rc)
ENDIF()

add_library(qcadstemmer SHARED
    RStemmer.cpp RStemmer.h
    ${RC}
)

target_include_directories(qcadstemmer PRIVATE
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    .
)

target_compile_definitions(qcadstemmer PRIVATE
    QCADSTEMMER_LIBRARY
    QCAD_DLL
)

target_link_libraries(qcadstemmer PRIVATE
    Qt::Core
    stemmer
)

