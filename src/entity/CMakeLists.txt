cmake_minimum_required(VERSION 3.16)
project(qcadentity VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

if(WIN32)
    set(RC entity.rc)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadentity SHARED
    RArcData.cpp RArcData.h
    RArcEntity.cpp RArcEntity.h
    RAttributeData.cpp RAttributeData.h
    RAttributeDefinitionData.cpp RAttributeDefinitionData.h
    RAttributeDefinitionEntity.cpp RAttributeDefinitionEntity.h
    RAttributeEntity.cpp RAttributeEntity.h
    RCircleData.cpp RCircleData.h
    RCircleEntity.cpp RCircleEntity.h
    RCustomEntity.cpp RCustomEntity.h
    RCustomEntityHandler.h
    RCustomEntityRegistry.cpp RCustomEntityRegistry.h
    RDimAlignedData.cpp RDimAlignedData.h
    RDimAlignedEntity.cpp RDimAlignedEntity.h
    RDimAngular2LData.cpp RDimAngular2LData.h
    RDimAngular2LEntity.cpp RDimAngular2LEntity.h
    RDimAngular3PData.cpp RDimAngular3PData.h
    RDimAngular3PEntity.cpp RDimAngular3PEntity.h
    RDimAngularData.cpp RDimAngularData.h
    RDimAngularEntity.cpp RDimAngularEntity.h
    RDimArcLengthData.cpp RDimArcLengthData.h
    RDimArcLengthEntity.cpp RDimArcLengthEntity.h
    RDimDiametricData.cpp RDimDiametricData.h
    RDimDiametricEntity.cpp RDimDiametricEntity.h
    RDimLinearData.cpp RDimLinearData.h
    RDimLinearEntity.cpp RDimLinearEntity.h
    RDimOrdinateData.cpp RDimOrdinateData.h
    RDimOrdinateEntity.cpp RDimOrdinateEntity.h
    RDimRadialData.cpp RDimRadialData.h
    RDimRadialEntity.cpp RDimRadialEntity.h
    RDimRotatedData.cpp RDimRotatedData.h
    RDimRotatedEntity.cpp RDimRotatedEntity.h
    RDimStyleProxyBasic.cpp RDimStyleProxyBasic.h
    RDimensionData.cpp RDimensionData.h
    RDimensionEntity.cpp RDimensionEntity.h
    REllipseData.cpp REllipseData.h
    REllipseEntity.cpp REllipseEntity.h
    RFaceData.cpp RFaceData.h
    RFaceEntity.cpp RFaceEntity.h
    RHatchData.cpp RHatchData.h
    RHatchEntity.cpp RHatchEntity.h
    RHatchProxy.h
    RImageData.cpp RImageData.h
    RImageEntity.cpp RImageEntity.h
    RLeaderData.cpp RLeaderData.h
    RLeaderEntity.cpp RLeaderEntity.h
    RLineData.cpp RLineData.h
    RLineEntity.cpp RLineEntity.h
    RPointData.cpp RPointData.h
    RPointEntity.cpp RPointEntity.h
    RPolylineData.cpp RPolylineData.h
    RPolylineEntity.cpp RPolylineEntity.h
    RWipeoutData.cpp RWipeoutData.h
    RWipeoutEntity.cpp RWipeoutEntity.h
    RRayData.cpp RRayData.h
    RRayEntity.cpp RRayEntity.h
    RSolidData.cpp RSolidData.h
    RSolidEntity.cpp RSolidEntity.h
    RSplineData.cpp RSplineData.h
    RSplineEntity.cpp RSplineEntity.h
    RTextData.cpp RTextData.h
    RTextEntity.cpp RTextEntity.h
    RToleranceData.cpp RToleranceData.h
    RToleranceEntity.cpp RToleranceEntity.h
    RTraceData.cpp RTraceData.h
    RTraceEntity.cpp RTraceEntity.h
    RXLineData.cpp RXLineData.h
    RXLineEntity.cpp RXLineEntity.h
    ${RC}
)

target_include_directories(qcadentity PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
)

target_compile_definitions(qcadentity PRIVATE
    QCADENTITY_LIBRARY
    QCAD_DLL
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(qcadentity PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadentity PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadentity PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../release)
else()
    set_target_properties(qcadentity PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadentity PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadentity PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../debug)
endif()

target_link_libraries(qcadentity PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::PrintSupport
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    qcadcore
    opennurbs
)

if(win32-msvc2010)
    target_compile_definitions(qcadentity PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()
