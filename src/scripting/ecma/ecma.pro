include( ../../../shared.pri )
SOURCES = \
    RScriptHandlerEcma.cpp
HEADERS = \
    RActionAdapter.h \
    RBlockListenerAdapter.h \
    RCoordinateListenerAdapter.h \
    RFileExporterFactoryAdapter.h \
    RFileImporterAdapter.h \
    RFileImporterFactoryAdapter.h \
    RFocusListenerAdapter.h \
    RLayerListenerAdapter.h \
    RPenListenerAdapter.h \
    RSelectionListenerAdapter.h \
    RSpatialIndexVisitorAdapter.h \
    RViewFocusListenerAdapter.h \
    RViewListenerAdapter.h \
    RScriptHandlerEcma.h \
    RFontDatabase.h
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadecma
LIBS += -L$$PWD/$$ROUTDIR \
    -ldxflib \
    -lopennurbs \
    -lqcadcore \
    -lqcaddxf \
    -lqcadecmaapi \
    -lqcadentity \
    -lqcadgrid \
    -lqcadgui \
    -lqcadoperations \
    -lqcadsnap \
    -lqcadspatialindex \
    -lqcadstemmer \
    -lspatialindexnavel \
    -lstemmer
OTHER_FILES += ecma.dox
