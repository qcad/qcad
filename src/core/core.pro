include( ../../shared.pri )
SOURCES += \
    RAction.cpp \
    RBlock.cpp \
    RBlockReferenceData.cpp \
    RBlockReferenceEntity.cpp \
    RColor.cpp \
    RCoordinateEvent.cpp \
    RDebug.cpp \
    RDocument.cpp \
    RDocumentInterface.cpp \
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
    RLinetypePattern.cpp \
    RLinetypePatternMap.cpp \
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
    RScriptAction.cpp \
    RScriptHandler.cpp \
    RScriptHandlerRegistry.cpp \
    RSelectionListenerAdapter.cpp \
    RSettings.cpp \
    RSingleApplication.cpp \
    RSingleton.cpp \
    RSpatialIndex.cpp \
    RSpatialIndexSimple.cpp \
    RStorage.cpp \
    RTabletEvent.cpp \
    RThread.cpp \
    RTransaction.cpp \
    RTransactionStack.cpp \
    RUcs.cpp \
    RUnit.cpp \
    RView.cpp \
    RWheelEvent.cpp \
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
    math/RShape.cpp \
    math/RSpline.cpp \
    math/RTextLabel.cpp \
    math/RTriangle.cpp \
    math/RVector.cpp

win32 {
    SOURCES += RLockedFile_win.cpp
}
else {
    SOURCES += RLockedFile_unix.cpp
}

HEADERS = \
    RAction.h \
    RActionAdapter.h \
    RBlock.h \
    RBlockListener.h \
    RBlockListenerAdapter.h \
    RBlockReferenceData.h \
    RBlockReferenceEntity.h \
    RCloseCurrentEvent.h \
    RColor.h \
    RColorCodes.h \
    RCommandEvent.h \
    RCoordinateEvent.h \
    RCoordinateListener.h \
    RCoordinateListenerAdapter.h \
    RDebug.h \
    RDocument.h \
    RDocumentInterface.h \
    REntity.h \
    REntityData.h \
    REntityPickEvent.h \
    RExporter.h \
    RFileCache.h \
    RFileExporter.h \
    RFileExporterAdapter.h \
    RFileExporterFactory.h \
    RFileExporterFactoryAdapter.h \
    RFileExporterRegistry.h \
    RFileImporter.h \
    RFileImporterAdapter.h \
    RFileImporterFactory.h \
    RFileImporterFactoryAdapter.h \
    RFileImporterRegistry.h \
    RFocusListener.h \
    RFocusListenerAdapter.h \
    RFont.h \
    RFontList.h \
    RGlobal.h \
    RGraphicsScene.h \
    RGraphicsView.h \
    RGrid.h \
    RGuiAction.h \
    RImporter.h \
    RInputEvent.h \
    RLayer.h \
    RLayerListener.h \
    RLayerListenerAdapter.h \
    RLinetype.h \
    RLinetypePattern.h \
    RLinetypePatternMap.h \
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
    RPenListenerAdapter.h \
    RPluginInterface.h \
    RPluginLoader.h \
    RPluginInfo.h \
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
    RSelectionListenerAdapter.h \
    RSettings.h \
    RSingleApplication.h \
    RSingleton.h \
    RSnap.h \
    RSnapRestriction.h \
    RSpatialIndex.h \
    RSpatialIndexSimple.h \
    RSpatialIndexVisitor.h \
    RSpatialIndexVisitorAdapter.h \
    RStorage.h \
    RStreamOperators.h \
    RTabletEvent.h \
    RTerminateEvent.h \
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
    RViewFocusListenerAdapter.h \
    RViewListener.h \
    RViewListenerAdapter.h \
    RWheelEvent.h \
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
    math/RShape.h \
    math/RSpline.h \
    math/RTextLabel.h \
    math/RTriangle.h \
    math/RVector.h
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadcore
RESOURCES = resources/core.qrc
OTHER_FILES += core.dox

LIBS += -L$$PWD/$$ROUTDIR -lopennurbs

macx {
    QMAKE_LFLAGS += -framework ApplicationServices
}

!win32 {
    include( ../../shared_ts.pri )
}
