cmake_minimum_required(VERSION 3.16)
project(qcadcore VERSION 1.0 LANGUAGES CXX)

include(../../CMakeInclude.txt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${QT_VER} REQUIRED COMPONENTS Core Widgets Concurrent Gui Network OpenGL Sql Svg Xml PrintSupport Qml)
IF(NOT BUILD_QT6)
    find_package(${QT_VER} REQUIRED COMPONENTS Script XmlPatterns)
ENDIF()

qt_standard_project_setup()

if(WIN32)
    set(RC core.rc)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../release)
else()
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../debug)
endif()

add_library(qcadcore SHARED
    RAction.cpp RAction.h
    RActionAdapter.h
    RArcExporter.cpp RArcExporter.h
    RBlock.cpp RBlock.h
    RBlockListener.h
    RKeyListener.h
    RMainWindowProxy.h
    RBlockReferenceData.cpp RBlockReferenceData.h
    RBlockReferenceEntity.cpp RBlockReferenceEntity.h
    RColor.cpp RColor.h
    RColorCodes.h
    RCommandEvent.h
    RCoordinateEvent.cpp RCoordinateEvent.h
    RCoordinateListener.h
    RDebug.cpp RDebug.h
    RDimStyle.cpp RDimStyle.h
    RDimStyleData.cpp RDimStyleData.h
    RDimStyleProxy.h
    RDocument.cpp RDocument.h
    RDocumentInterface.cpp RDocumentInterface.h
    RDocumentVariables.cpp RDocumentVariables.h
    RDxfServices.cpp RDxfServices.h
    REntity.cpp REntity.h
    REntityData.cpp REntityData.h
    REntityExportListener.h
    REntityPickEvent.cpp REntityPickEvent.h
    RExportListener.h
    RExporter.cpp RExporter.h
    RFileCache.cpp RFileCache.h
    RFileExporter.cpp RFileExporter.h
    RFileExporterFactory.h
    RFileExporterRegistry.cpp RFileExporterRegistry.h
    RFileImporter.cpp RFileImporter.h
    RFileImporterFactory.h
    RFileImporterRegistry.cpp RFileImporterRegistry.h
    RFocusListener.h
    RFont.cpp RFont.h
    RFontList.cpp RFontList.h
    RGlobal.h
    RGraphicsScene.cpp RGraphicsScene.h
    RGraphicsView.cpp RGraphicsView.h
    RGrid.cpp RGrid.h
    RGuiAction.cpp RGuiAction.h
    RImportListener.h
    RImporter.cpp RImporter.h
    RInputEvent.cpp RInputEvent.h
    RInterTransactionListener.h
    RLayer.cpp RLayer.h
    RLayerListener.h
    RLayerState.cpp RLayerState.h
    RLayout.cpp RLayout.h
    RLinetype.cpp RLinetype.h
    RLinetypeList.cpp RLinetypeList.h
    RLinetypeListImperial.cpp RLinetypeListImperial.h
    RLinetypeListMetric.cpp RLinetypeListMetric.h
    RLinetypePattern.cpp RLinetypePattern.h
    RLineweight.cpp RLineweight.h
    RLinkedStorage.cpp RLinkedStorage.h
    RLocalPeer.cpp RLocalPeer.h
    RLockedFile.cpp RLockedFile.h
    RMainWindow.cpp RMainWindow.h
    RMemoryStorage.cpp RMemoryStorage.h
    RMessageHandler.h
    RMetaTypes.h
    RModifiedListener.h
    RMouseCoordinateListener.h
    RMouseEvent.cpp RMouseEvent.h
    RNavigationAction.cpp RNavigationAction.h
    RNewDocumentListener.h
    RNonCopyable.h
    RObject.cpp RObject.h
    ROperation.h
    RPainterPath.cpp RPainterPath.h
    RPainterPathDevice.cpp RPainterPathDevice.h
    RPainterPathEngine.cpp RPainterPathEngine.h
    RPainterPathExporter.cpp RPainterPathExporter.h
    RPainterPathSource.cpp RPainterPathSource.h
    RPaletteListener.h
    RPattern.cpp RPattern.h
    RPatternLine.cpp RPatternLine.h
    RPatternList.cpp RPatternList.h
    RPatternListImperial.cpp RPatternListImperial.h
    RPatternListMetric.cpp RPatternListMetric.h
    RPenListener.h
    RPluginInfo.h
    RPluginInterface.h
    RPluginLoader.cpp RPluginLoader.h
    RPreferencesListener.h
    RProgressHandler.h
    RProperty.h
    RPropertyAttributes.cpp RPropertyAttributes.h
    RPropertyChange.cpp RPropertyChange.h
    RPropertyEditor.cpp RPropertyEditor.h
    RPropertyEvent.h
    RPropertyListener.h
    RPropertyTypeId.cpp RPropertyTypeId.h
    RRequireHeap.h
    RResourceList.cpp RResourceList.h
    RRuler.h
    RRunner.h
    RSEnums.h
    RS.cpp RS.h
    RSPlatform.cpp
    RScriptAction.cpp RScriptAction.h
    RScriptHandler.cpp RScriptHandler.h
    RScriptHandlerRegistry.cpp RScriptHandlerRegistry.h
    RSelectionChangedEvent.h
    RSelectionListener.h
    RSettings.cpp RSettings.h
    RShapesExporter.cpp RShapesExporter.h
    RSingleApplication.cpp RSingleApplication.h
    RSingleton.cpp RSingleton.h
    RSnap.h
    RSnapRestriction.h
    RSpatialIndex.cpp RSpatialIndex.h
    RSpatialIndexSimple.cpp RSpatialIndexSimple.h
    RSpatialIndexVisitor.h
    RStorage.cpp RStorage.h
    RStorageBlockSort.cpp RStorageBlockSort.h
    RStorageLayerSort.cpp RStorageLayerSort.h
    RTabletEvent.cpp RTabletEvent.h
    RTerminateEvent.h
    RTextBasedData.cpp RTextBasedData.h
    RTextBasedEntity.cpp RTextBasedEntity.h
    RTextLayout.cpp RTextLayout.h
    RTextRenderer.cpp RTextRenderer.h
    RThread.cpp RThread.h
    RTransaction.cpp RTransaction.h
    RTransactionEvent.h
    RTransactionListener.h
    RTransactionStack.cpp RTransactionStack.h
    RUcs.cpp RUcs.h
    RUcsListener.h
    RUnit.cpp RUnit.h
    RVersion.h
    RView.cpp RView.h
    RViewFocusListener.h
    RViewListener.h
    RViewportData.cpp RViewportData.h
    RViewportEntity.cpp RViewportEntity.h
    RWheelEvent.cpp RWheelEvent.h
    RWidget.cpp RWidget.h
    math/RArc.cpp math/RArc.h
    math/RBox.cpp math/RBox.h
    math/RCircle.cpp math/RCircle.h
    math/RDirected.cpp math/RDirected.h
    math/REllipse.cpp math/REllipse.h
    math/REllipseProxy.h
    math/RExplodable.h
    math/RLine.cpp math/RLine.h
    math/RMath.cpp math/RMath.h
    math/RMatrix.cpp math/RMatrix.h
    math/RPoint.cpp math/RPoint.h
    math/RPolyline.cpp math/RPolyline.h
    math/RPolylineProxy.h
    math/RRay.cpp math/RRay.h
    math/RRefPoint.cpp math/RRefPoint.h
    math/RShape.cpp math/RShape.h
    math/RShapeProxy.h
    math/RSpline.cpp math/RSpline.h
    math/RSplineProxy.h
    math/RTextLabel.cpp math/RTextLabel.h
    math/RTransform.cpp math/RTransform.h
    math/RTransformOp.h
    math/RTriangle.cpp math/RTriangle.h
    math/RVector.cpp math/RVector.h
    math/RXLine.cpp math/RXLine.h
    resources/core.qrc
    ${RC}
)

target_include_directories(qcadcore PUBLIC
    ../../src/3rdparty
    ../../src/core
    ../../src/core/math
    ../../src/entity
    ../../src/grid
    ../../src/gui
    ../../src/io/dxf
    ../../src/operations
    ../../src/scripting
    ../../src/scripting/ecmaapi
    ../../src/scripting/ecmaapi/adapters
    ../../src/scripting/ecmaapi/generated
    ../../src/snap
    ../../src/spatialindex
    ../../src/stemmer
    ../../src/zip
)

target_compile_definitions(qcadcore PRIVATE
    QCADCORE_LIBRARY
    QCAD_DLL
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(qcadcore PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadcore PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../release)
    set_target_properties(qcadcore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../release)
else()
    set_target_properties(qcadcore PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadcore PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../debug)
    set_target_properties(qcadcore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../debug)
endif()


target_link_libraries(qcadcore PUBLIC
    Qt::Concurrent
    Qt::Core
    Qt::Widgets
    Qt::PrintSupport
    Qt::Gui
    Qt::Network
    Qt::OpenGL
    Qt::Sql
    Qt::Svg
    Qt::Xml
    Qt::Qml
    zlib
    opennurbs
)


# Resources:
set(qcadcore_resource_files
    "resources/linetype_border.svg"
    "resources/linetype_border2.svg"
    "resources/linetype_borderx2.svg"
    "resources/linetype_byblock.svg"
    "resources/linetype_bylayer.svg"
    "resources/linetype_center.svg"
    "resources/linetype_center2.svg"
    "resources/linetype_centerx2.svg"
    "resources/linetype_continuous.svg"
    "resources/linetype_dashdot.svg"
    "resources/linetype_dashdot2.svg"
    "resources/linetype_dashdotx2.svg"
    "resources/linetype_dashed.svg"
    "resources/linetype_dashed2.svg"
    "resources/linetype_dashedx2.svg"
    "resources/linetype_divide.svg"
    "resources/linetype_divide2.svg"
    "resources/linetype_dividex2.svg"
    "resources/linetype_dot.svg"
    "resources/linetype_dot2.svg"
    "resources/linetype_dotx2.svg"
)

IF(BUILD_QT6)
    qt_add_resources(qcadcore "qcadcore"
        PREFIX
            "/qcad"
        BASE
            "resources"
        FILES
            ${qcadcore_resource_files}
)
ELSE()
    target_link_libraries(qcadcore PUBLIC
        Qt::Script
        Qt::XmlPatterns)
ENDIF()

if(WIN32)
    target_sources(qcadcore PRIVATE
        RLockedFile_win.cpp
    )

    target_link_libraries(qcadcore PUBLIC
        Advapi32
        Rpcrt4
        gdi32
        user32
    )
endif()

if(UNIX)
    target_sources(qcadcore PRIVATE
        RLockedFile_unix.cpp
    )
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_sources(qcadcore PRIVATE
        detectmacdarkmode.h detectmacdarkmode.mm
    )
endif()

#if(_x_ + linux-g)
#    target_link_libraries(qcadcore PUBLIC
#        X11
#    )
#endif()

#if((QT_VERSION_MAJOR GREATER 4))
#    target_compile_definitions(qcadcore PUBLIC
#        QT_DISABLE_DEPRECATED_BEFORE=0x000000
#    )
#
#    target_link_libraries(qcadcore PUBLIC
#        Qt::Help
#        Qt::PrintSupport
#        Qt::UiTools
#    )
#endif()

#if((((QT_VERSION_MAJOR GREATER 4)) AND ((QT_VERSION_MAJOR LESS 6))) AND (MACOS))
#    target_link_libraries(qcadcore PUBLIC
#        Qt::MacExtras
#    )
#endif()

#if(NOT ((QT_VERSION_MAJOR GREATER 4)))
#    target_link_libraries(qcadcore PUBLIC
#        webkit
#    )
#endif()

#if((QT_VERSION_MAJOR GREATER 5))
#    target_link_libraries(qcadcore PUBLIC
#        Qt::Qml
#    )
#endif()

#if(r_no_opennurbs)
#    target_compile_definitions(qcadcore PUBLIC
#        R_NO_OPENNURBS
#    )
#endif()

#if(win32-msvc2010)
#    target_compile_definitions(qcadcore PUBLIC
#        _CRT_SECURE_NO_WARNINGS
#    )
#endif()

#if((win32-msvc2015) AND (QMAKE_TARGET.arch___contains___x86_64))
#    target_link_libraries(qcadcore PUBLIC
#        # Remove: L"C:\Program
#        (
#        )
#        Files
#        Kits\8.1\lib\winv6.3\um\x64"
#        \Windows
#        x86
#    )
#endif()

#if((QT_VERSION_MAJOR LESS 6))
#    target_link_libraries(qcadcore PUBLIC
#        Qt::Core
#        Qt::Script
#        Qt::ScriptTools
#        Qt::XmlPatterns
#    )
#endif()

#if(((QT_VERSION_MAJOR GREATER 4)) AND (NOT r_mobile))
#    target_link_libraries(qcadcore PUBLIC
#        Qt::Designer
#    )
#endif()

#install(TARGETS qcadcore
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
