cmake_minimum_required(VERSION 3.16)

include(../../CMakeInclude.txt)

project(qcadsnap VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

if(WIN32)
    set(RC snap.rc)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadsnap SHARED
    RRestrictAngleLength.cpp RRestrictAngleLength.h
    RRestrictHorizontal.cpp RRestrictHorizontal.h
    RRestrictOff.cpp RRestrictOff.h
    RRestrictOrthogonal.cpp RRestrictOrthogonal.h
    RRestrictVertical.cpp RRestrictVertical.h
    RSnapAuto.cpp RSnapAuto.h
    RSnapCenter.cpp RSnapCenter.h
    RSnapDistance.cpp RSnapDistance.h
    RSnapEnd.cpp RSnapEnd.h
    RSnapEntityBase.cpp RSnapEntityBase.h
    RSnapFree.cpp RSnapFree.h
    RSnapGrid.cpp RSnapGrid.h
    RSnapIntersection.cpp RSnapIntersection.h
    RSnapMiddle.cpp RSnapMiddle.h
    RSnapOnEntity.cpp RSnapOnEntity.h
    RSnapPerpendicular.cpp RSnapPerpendicular.h
    RSnapReference.cpp RSnapReference.h
    RSnapTangential.cpp RSnapTangential.h
    ${RC}
)

target_include_directories(qcadsnap PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/snap
    ../../src/grid
)

target_compile_definitions(qcadsnap PRIVATE
    QCADSNAP_LIBRARY
    QCAD_DLL
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(qcadsnap PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadsnap PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadsnap PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../release)
else()
    set_target_properties(qcadsnap PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadsnap PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadsnap PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../debug)
endif()

target_link_libraries(qcadsnap PUBLIC
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
    qcadgrid
)

