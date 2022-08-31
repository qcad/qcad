cmake_minimum_required(VERSION 3.16)
project(qcadentity VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_plugin(qcaddxf
    RDxfExporter.cpp RDxfExporter.h
    RDxfExporterFactory.cpp RDxfExporterFactory.h
    RDxfImporter.cpp RDxfImporter.h
    RDxfImporterFactory.cpp RDxfImporterFactory.h
    RDxfPlugin.cpp RDxfPlugin.h
)

target_include_directories(qcaddxf PRIVATE
    ../../../src/3rdparty
    ../../../src/core
    ../../../src/core/math
    ../../../src/io/dxf
)

target_compile_definitions(qcaddxf PRIVATE
    QCADDXF_LIBRARY
    QCAD_DLL
)

set_target_properties(qcaddxf PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../debug)

find_library(
    core
    NAMES qcadcore libqcadcore
    HINTS "../../../debug"
    NO_DEFAULT_PATH
)
message(STATUS "QCADCORE: [${core}]")

find_library(
    entity
    NAMES qcadentity libqcadentity
    HINTS "../../../debug"
    NO_DEFAULT_PATH
)
message(STATUS "QCADENTITY: [${entity}]")

find_library(
    dxflib
    NAMES dxflib libdxflib
    HINTS "../../../debug"
    NO_DEFAULT_PATH
)
message(STATUS "DXFLIB: [${dxflib}]")

find_library(
    operations
    NAMES qcadoperations libqcadoperations
    HINTS "../../../debug"
    NO_DEFAULT_PATH
)
message(STATUS "QCADOPERATIONS: [${operations}]")

target_link_libraries(qcaddxf PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    ${core}
    ${entity}
    ${operations}
    ${dxflib}
)

