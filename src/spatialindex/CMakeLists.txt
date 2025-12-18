cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(qcadspatialindex VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Gui Widgets PrintSupport QmlIntegration)
qt_standard_project_setup()

if(WIN32)
    set(RC spatialindex.rc)
endif()

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    #set(BUILD_SHARED_LIBS TRUE)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadspatialindex SHARED
    RSpatialIndexNavel.cpp RSpatialIndexNavel.h
    ${RC}
)
target_include_directories(qcadspatialindex PUBLIC
    ../../src/3rdparty/spatialindexnavel
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
    set_target_properties(qcadspatialindex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadspatialindex PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../release)
else()
    set_target_properties(qcadspatialindex PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadspatialindex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadspatialindex PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../debug)
endif()

target_link_libraries(qcadspatialindex PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::PrintSupport
    qcadcore
    spatialindexnavel
)

