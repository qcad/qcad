include( ../../shared.pri )

HEADERS = \
    RSpatialIndexNavel.h

SOURCES = \
    RSpatialIndexNavel.cpp

TEMPLATE = lib
CONFIG += staticlib
TARGET = qcadspatialindex
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lspatialindexnavel
OTHER_FILES += spatialindex.dox
DEFINES += QCADSPATIALINDEX_LIBRARY
