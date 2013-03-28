include( ../../../shared.pri )
SOURCES = \
    RAutoLoadEcma.cpp \
    RScriptHandlerEcma.cpp
HEADERS = \
    RAutoLoadEcma.h \
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
