cmake_minimum_required(VERSION 3.16)
project(qcadscripts VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_resources(SOURCES scripts.qrc)

qt_add_library(qcadscripts
    RScriptsPlugin.cpp RScriptsPlugin.h
    ${SOURCES}
)
target_include_directories(qcadscripts PRIVATE
    ../../src/core
    ../../src/core/math
)

target_compile_definitions(qcadscripts PRIVATE
    QCAD_DLL
)

set_target_properties(qcadscripts PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

find_library(
    core
    NAMES qcadcore libqcadcore
    HINTS "../../debug"
    NO_DEFAULT_PATH
)
message(STATUS "QCADCORE: [${core}]")

target_link_libraries(qcadscripts PRIVATE
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


