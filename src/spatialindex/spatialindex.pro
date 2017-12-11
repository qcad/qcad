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
    CONFIG += plugin
}
TARGET = $${RLIBNAME}spatialindex
LIBS += -l$${RLIBNAME}core -lspatialindexnavel
OTHER_FILES += spatialindex.dox
DEFINES += QCADSPATIALINDEX_LIBRARY
RC_FILE = spatialindex.rc

#POST_TARGETDEPS += ../../$$ROUTDIR/$${RLIBPRE}spatialindexnavel$${RLIBPOSTDLL}
