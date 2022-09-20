cmake_minimum_required(VERSION 3.16)
project(qcadstemmer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_library(qcadstemmer
    RStemmer.cpp RStemmer.h
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

set_target_properties(qcadstemmer PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

target_link_libraries(qcadstemmer PRIVATE
    Qt::Core
    -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug
    stemmer
)

