cmake_minimum_required(VERSION 3.16)
project(qcadoperations VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
qt_standard_project_setup()

qt_add_library(qcadoperations
    RAddObjectOperation.cpp RAddObjectOperation.h
    RAddObjectsOperation.cpp RAddObjectsOperation.h
    RChangePropertyOperation.cpp RChangePropertyOperation.h
    RClickReferencePointOperation.cpp RClickReferencePointOperation.h
    RClipboardOperation.cpp RClipboardOperation.h
    RCopyOperation.cpp RCopyOperation.h
    RDeleteAllEntitiesOperation.cpp RDeleteAllEntitiesOperation.h
    RDeleteObjectOperation.cpp RDeleteObjectOperation.h
    RDeleteObjectsOperation.cpp RDeleteObjectsOperation.h
    RDeleteSelectionOperation.cpp RDeleteSelectionOperation.h
    RMixedOperation.cpp RMixedOperation.h
    RModifyObjectOperation.cpp RModifyObjectOperation.h
    RModifyObjectsOperation.cpp RModifyObjectsOperation.h
    RMoveReferencePointOperation.cpp RMoveReferencePointOperation.h
    RMoveSelectionOperation.cpp RMoveSelectionOperation.h
    ROperationUtils.cpp ROperationUtils.h
    RPasteOperation.cpp RPasteOperation.h
    RScaleSelectionOperation.cpp RScaleSelectionOperation.h
    RTransformation.h
    RTranslation.h
)
target_include_directories(qcadoperations PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/grid
    ../../src/gui
    ../../src/operations
)

target_compile_definitions(qcadoperations PUBLIC
    QCADOPERATIONS_LIBRARY
    QCAD_DLL
)

set_target_properties(qcadoperations PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)

target_link_libraries(qcadoperations PUBLIC
    # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/
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
)

