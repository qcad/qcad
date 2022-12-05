cmake_minimum_required(VERSION 3.16)
project(qcadecmaapi VERSION 1.0 LANGUAGES CXX)

include(../../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
IF(NOT BUILD_QT6)
find_package(${QT_VER} REQUIRED COMPONENTS Script ScriptTools)
ENDIF()
qt_standard_project_setup()

#qt_add_resources(SOURCES scripts.qrc)

file(GLOB ADAPTERS "adapters/*.h")
file(GLOB GENERATED "generated/*.h" "generated/*.cpp")

IF(WIN32)
    SET(RC ecmaapi.rc)
ENDIF()

add_library(qcadecmaapi SHARED
    RScriptHandlerEcma.cpp
    REcmaHelper.cpp
    RAutoLoadEcma.cpp
    ecmaapi_global.h
    RAutoLoadEcma.h
    RScriptHandlerEcma.h
    REcmaHelper.h
    ${SOURCES}
    ${GENERATED}
    ${ADAPTERS}
    ${RC}
)
target_include_directories(qcadecmaapi PRIVATE
    ../../../src/core
    ../../../src/core/math
)

target_compile_definitions(qcadecmaapi PRIVATE
    QCAD_DLL
    QCADECMAAPI_LIBRARY
)

target_link_libraries(qcadecmaapi PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
    qcadgui
    qcadoperations
    qcadsnap
    qcadspatialindex
    qcadstemmer
)

IF(NOT BUILD_QT6)
target_link_libraries(qcadecmaapi PRIVATE
    Qt::Script Qt::ScriptTools) 
ENDIF()
