cmake_minimum_required(VERSION 3.16)
project(qcadsnap VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_library(qcadsnap
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
)

target_include_directories(qcadsnap PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/snap
    ../../src/grid
)

target_compile_definitions(qcadsnap PUBLIC
    QCADSNAP_LIBRARY
    QCAD_DLL
)

set_target_properties(qcadsnap PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

target_link_libraries(qcadsnap PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    -L${CMAKE_CURRENT_SOURCE_DIR}/../../debug
    qcadcore
    qcadentity
    qcadgrid
)

