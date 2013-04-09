include( ../../shared.pri )

HEADERS = \
    RSpatialIndexNavel.h

SOURCES = \
    RSpatialIndexNavel.cpp

TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadspatialindex
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lspatialindexnavel
OTHER_FILES += spatialindex.dox
DEFINES += QCADSPATIALINDEX_LIBRARY
