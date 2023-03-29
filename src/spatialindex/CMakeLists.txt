cmake_minimum_required(VERSION 3.16)
project(qcadspatialindex VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Gui Widgets PrintSupport)
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

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(qcadspatialindex PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../release)
    target_link_libraries(qcadspatialindex PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    set_target_properties(qcadspatialindex PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    target_link_libraries(qcadspatialindex PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

target_link_libraries(qcadspatialindex PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::PrintSupport
    qcadcore
    spatialindexnavel
)

