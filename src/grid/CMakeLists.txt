cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(qcadgrid VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

if(WIN32)
    set(RC grid.rc)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadgrid SHARED
    ROrthoGrid.cpp ROrthoGrid.h
    ${RC}
)

target_include_directories(qcadgrid PUBLIC
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/gui
)

target_compile_definitions(qcadgrid PRIVATE
    QCADGRID_LIBRARY
    QCAD_DLL
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(qcadgrid PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadgrid PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadgrid PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../release)
else()
    set_target_properties(qcadgrid PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadgrid PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadgrid PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../debug)
endif()

target_link_libraries(qcadgrid PUBLIC
    # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
)

if(win32-msvc2010)
    target_compile_definitions(qcadgrid PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

