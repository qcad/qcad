cmake_minimum_required(VERSION 3.16)
project(qcadscripts VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}/Debug/plugins)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}/Release/plugins)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${LIBRARY_OUTPUT_PATH}/MinSizeRel/plugins)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIBRARY_OUTPUT_PATH}/RelWithDebInfo/plugins)

qt_standard_project_setup()

#qt_add_resources(SOURCES scripts.qrc)
IF(WIN32)
    SET(RC scripts.rc)
ENDIF()

add_library(qcadscripts SHARED
    RScriptsPlugin.cpp RScriptsPlugin.h
    scripts.qrc
    ${SOURCES}
    ${RC}
)
target_include_directories(qcadscripts PRIVATE
    ../../src/core
    ../../src/core/math
)

target_compile_definitions(qcadscripts PRIVATE
    QCAD_DLL
)

target_link_libraries(qcadscripts PRIVATE
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


