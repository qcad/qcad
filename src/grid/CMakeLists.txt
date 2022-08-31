cmake_minimum_required(VERSION 3.16)
project(qcadgrid VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_library(qcadgrid
    ROrthoGrid.cpp ROrthoGrid.h
)

target_include_directories(qcadgrid PUBLIC
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/gui
)

target_compile_definitions(qcadgrid PUBLIC
    QCADGRID_LIBRARY
    QCAD_DLL
)

set_target_properties(qcadgrid PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

find_library(
    core
    NAMES qcadcore libqcadcore
    HINTS "../../debug"
    NO_DEFAULT_PATH
)
message(STATUS "QCADCORE: [${core}]")

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
    ${core}
)

if(win32-msvc2010)
    target_compile_definitions(qcadgrid PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

