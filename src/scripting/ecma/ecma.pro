include( ../../../shared.pri )
SOURCES = \
    RScriptHandlerEcma.cpp
HEADERS = \
    RScriptHandlerEcma.h
TEMPLATE = lib
CONFIG += staticlib
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
DEFINES += QCADECMA_LIBRARY
