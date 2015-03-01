include( ../../shared.pri )
SOURCES += \
    RAction.cpp \
    RArcExporter.cpp \
    RBlock.cpp \
    RBlockReferenceData.cpp \
    RBlockReferenceEntity.cpp \
    RColor.cpp \
    RCoordinateEvent.cpp \
    RDebug.cpp \
    RDocument.cpp \
    RDocumentVariables.cpp \
    RDocumentInterface.cpp \
    RDxfServices.cpp \
    REntity.cpp \
    REntityData.cpp \
    REntityPickEvent.cpp \
    RExporter.cpp \
    RFileCache.cpp \
    RFileExporter.cpp \
    RFileExporterRegistry.cpp \
    RFileImporter.cpp \
    RFileImporterRegistry.cpp \
    RFont.cpp \
    RFontList.cpp \
    RGraphicsScene.cpp \
    RGraphicsView.cpp \
    RGrid.cpp \
    RGuiAction.cpp \
    RImporter.cpp \
    RInputEvent.cpp \
    RLayer.cpp \
    RLinetype.cpp \
    RLinetypeList.cpp \
    RLinetypeListImperial.cpp \
    RLinetypeListMetric.cpp \
    RLinetypePattern.cpp \
    RLineweight.cpp \
    RLinkedStorage.cpp \
    RLocalPeer.cpp \
    RLockedFile.cpp \
    RMainWindow.cpp \
    RMemoryStorage.cpp \
    RMouseEvent.cpp \
    RNavigationAction.cpp \
    RObject.cpp \
    RPainterPath.cpp \
    RPainterPathSource.cpp \
    RPainterPathDevice.cpp \
    RPainterPathEngine.cpp \
    RPainterPathExporter.cpp \
    RPattern.cpp \
    RPatternLine.cpp \
    RPatternList.cpp \
    RPatternListImperial.cpp \
    RPatternListMetric.cpp \
    RPluginLoader.cpp \
    RPropertyAttributes.cpp \
    RPropertyChange.cpp \
    RPropertyEditor.cpp \
    RPropertyTypeId.cpp \
    RResourceList.cpp \
    RS.cpp \
    RSPlatform.cpp \
    RScriptAction.cpp \
    RScriptHandler.cpp \
    RScriptHandlerRegistry.cpp \
    RSettings.cpp \
    RShapesExporter.cpp \
    RSingleApplication.cpp \
    RSingleton.cpp \
    RSpatialIndex.cpp \
    RSpatialIndexSimple.cpp \
    RStorage.cpp \
    RTabletEvent.cpp \
    RTextBasedData.cpp \
    RTextBasedEntity.cpp \
    RTextRenderer.cpp \
    RThread.cpp \
    RTransaction.cpp \
    RTransactionStack.cpp \
    RUcs.cpp \
    RUnit.cpp \
    RView.cpp \
    RViewportData.cpp \
    RViewportEntity.cpp \
    RWheelEvent.cpp \
    RWidget.cpp \
    math/RArc.cpp \
    math/RBox.cpp \
    math/RCircle.cpp \
    math/RDirected.cpp \
    math/REllipse.cpp \
    math/RLine.cpp \
    math/RMath.cpp \
    math/RMatrix.cpp \
    math/RPoint.cpp \
    math/RPolyline.cpp \
    math/RRay.cpp \
    math/RShape.cpp \
    math/RSpline.cpp \
    math/RTextLabel.cpp \
    math/RTriangle.cpp \
    math/RVector.cpp \
    math/RXLine.cpp

win32 {
    SOURCES += RLockedFile_win.cpp
}
else {
    SOURCES += RLockedFile_unix.cpp
}

HEADERS = \
    RAction.h \
    RActionAdapter.h \
    RArcExporter.h \
    RBlock.h \
    RBlockListener.h \
    RBlockReferenceData.h \
    RBlockReferenceEntity.h \
    RColor.h \
    RColorCodes.h \
    RCommandEvent.h \
    RCoordinateEvent.h \
    RCoordinateListener.h \
    RDebug.h \
    RDocument.h \
    RDocumentVariables.h \
    RDocumentInterface.h \
    RDxfServices.h \
    REntity.h \
    REntityData.h \
    REntityPickEvent.h \
    RExporter.h \
    RFileCache.h \
    RFileExporter.h \
    RFileExporterFactory.h \
    RFileExporterRegistry.h \
    RFileImporter.h \
    RFileImporterFactory.h \
    RFileImporterRegistry.h \
    RFocusListener.h \
    RFont.h \
    RFontList.h \
    RGlobal.h \
    RGraphicsScene.h \
    RGraphicsView.h \
    RGrid.h \
    RGuiAction.h \
    RImporter.h \
    RExportListener.h \
    RImportListener.h \
    RInterTransactionListener.h \
    RInputEvent.h \
    RLayer.h \
    RLayerListener.h \
    RLinetype.h \
    RLinetypeList.h \
    RLinetypeListImperial.h\
    RLinetypeListMetric.h \
    RLinetypePattern.h \
    RLineweight.h \
    RLinkedStorage.h \
    RLocalPeer.h \
    RLockedFile.h \
    RMainWindow.h \
    RMemoryStorage.h \
    RMetaTypes.h \
    RMessageHandler.h \
    RModifiedListener.h \
    RMouseCoordinateListener.h \
    RMouseEvent.h \
    RNavigationAction.h \
    RNewDocumentListener.h \
    RNonCopyable.h \
    RObject.h \
    ROperation.h \
    RPainterPath.h \
    RPainterPathSource.h \
    RPainterPathDevice.h \
    RPainterPathEngine.h \
    RPainterPathExporter.h \
    RPattern.h \
    RPatternLine.h \
    RPatternList.h \
    RPatternListImperial.h \
    RPatternListMetric.h \
    RPenListener.h \
    RPluginInterface.h \
    RPluginInfo.h \
    RPluginLoader.h \
    RProgressHandler.h \
    RPropertyAttributes.h \
    RPropertyChange.h \
    RPropertyEditor.h \
    RPropertyEvent.h \
    RPropertyListener.h \
    RPropertyTypeId.h \
    RResourceList.h \
    RRequireHeap.h \
    RRuler.h \
    RRunner.h \
    RS.h \
    RScriptAction.h \
    RScriptHandler.h \
    RScriptHandlerRegistry.h \
    RSelectionChangedEvent.h \
    RSelectionListener.h \
    RSettings.h \
    RShapesExporter.h \
    RSingleApplication.h \
    RSingleton.h \
    RSnap.h \
    RSnapRestriction.h \
    RSpatialIndex.h \
    RSpatialIndexSimple.h \
    RSpatialIndexVisitor.h \
    RStorage.h \
    RTabletEvent.h \
    RTerminateEvent.h \
    RTextBasedData.h \
    RTextBasedEntity.h \
    RTextRenderer.h \
    RThread.h \
    RTransaction.h \
    RTransactionEvent.h \
    RTransactionListener.h \
    RTransactionStack.h \
    RUcs.h \
    RUcsListener.h \
    RUnit.h \
    RVersion.h \
    RView.h \
    RViewFocusListener.h \
    RViewListener.h \
    RViewportData.h \
    RViewportEntity.h \
    RWheelEvent.h \
    RWidget.h \
    math/RArc.h \
    math/RBox.h \
    math/RCircle.h \
    math/RDirected.h \
    math/REllipse.h \
    math/RExplodable.h \
    math/RLine.h \
    math/RMath.h \
    math/RMatrix.h \
    math/RPoint.h \
    math/RPolyline.h \
    math/RRay.h \
    math/RShape.h \
    math/RSpline.h \
    math/RSplineProxy.h \
    math/RTextLabel.h \
    math/RTriangle.h \
    math/RVector.h \
    math/RXLine.h
TEMPLATE = lib

r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}

NAME = qcadcore
TARGET = $${NAME}
RESOURCES = resources/core.qrc
OTHER_FILES += core.dox math/math.dox
DEFINES += QCADCORE_LIBRARY

LIBS += -lopennurbs -lzlib

win32 {
    LIBS += -lRpcrt4 -lAdvapi32
}

macx {
    QMAKE_LFLAGS += -framework ApplicationServices
}

linux-g++* {
    # this might or might not be needed under Linux:
    LIBS += -lX11
}

QMAKE_CXXFLAGS += -std=c++11

!win32 {
    include( ../../shared_ts.pri )
}
