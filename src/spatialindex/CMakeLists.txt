cmake_minimum_required(VERSION 3.16)
project(qcadspatialindex VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

qt_add_library(qcadspatialindex
    RSpatialIndexNavel.cpp RSpatialIndexNavel.h
)
target_include_directories(qcadspatialindex PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/spatialindex
)

target_compile_definitions(qcadspatialindex PUBLIC
    QCADSPATIALINDEX_LIBRARY
    QCAD_DLL
)

set_target_properties(qcadspatialindex PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

target_link_libraries(qcadspatialindex PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug
    qcadcore
    spatialindexnavel
)

