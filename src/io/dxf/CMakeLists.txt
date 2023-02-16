cmake_minimum_required(VERSION 3.16)
project(qcaddxf VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

IF(WIN32)
    SET(RC dxf.rc)
ENDIF()

add_library(qcaddxf SHARED
    RDxfExporter.cpp RDxfExporter.h
    RDxfExporterFactory.cpp RDxfExporterFactory.h
    RDxfImporter.cpp RDxfImporter.h
    RDxfImporterFactory.cpp RDxfImporterFactory.h
    RDxfPlugin.cpp RDxfPlugin.h
    ${RC}
)

target_include_directories(qcaddxf PRIVATE
    ../../../src/3rdparty
    ../../../src/core
    ../../../src/entity
    ../../../src/operations
    ../../../src/core/math
    ../../../src/io/dxf
)

target_compile_definitions(qcaddxf PRIVATE
    QCADDXF_LIBRARY
    QCAD_DLL
)

set_target_properties(qcaddxf PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../plugins)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(qcaddxf PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../release)
else()
    target_link_libraries(qcaddxf PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/../../../debug)
endif()

target_link_libraries(qcaddxf PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
    qcadentity
    qcadoperations
    dxflib
)

