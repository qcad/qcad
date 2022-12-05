cmake_minimum_required(VERSION 3.16)
project(qcadspatialindex VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

IF(WIN32)
    SET(RC spatialindex.rc)
ENDIF()
add_library(qcadspatialindex SHARED
    RSpatialIndexNavel.cpp RSpatialIndexNavel.h
    ${RC}
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

target_link_libraries(qcadspatialindex PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    qcadcore
    spatialindexnavel
)

