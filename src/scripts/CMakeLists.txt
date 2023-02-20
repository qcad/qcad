cmake_minimum_required(VERSION 3.16)
project(qcadscripts VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_resources(SOURCES scripts.qrc)
IF(WIN32)
    SET(RC scripts.rc)
ENDIF()

add_library(qcadscripts SHARED
    RScriptsPlugin.cpp RScriptsPlugin.h
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

set_target_properties(qcadscripts PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../plugins)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(qcadscripts PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    target_link_libraries(qcadscripts PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

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


