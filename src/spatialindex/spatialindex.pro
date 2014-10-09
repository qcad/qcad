include( ../../shared.pri )

HEADERS = \
    RSpatialIndexNavel.h

SOURCES = \
    RSpatialIndexNavel.cpp

TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    DESTDIR = ../../../plugins
    CONFIG += plugin
}
TARGET = qcadspatialindex
LIBS += -lqcadcore -lspatialindexnavel
OTHER_FILES += spatialindex.dox
DEFINES += QCADSPATIALINDEX_LIBRARY

#POST_TARGETDEPS += ../../$$ROUTDIR/$${RLIBPRE}spatialindexnavel$${RLIBPOSTDLL}
