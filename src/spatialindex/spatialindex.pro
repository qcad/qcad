include( ../../shared.pri )

HEADERS = \
    RSpatialIndexNavel.h

SOURCES = \
    RSpatialIndexNavel.cpp

TEMPLATE = lib
CONFIG += plugin
TARGET = qcadspatialindex
LIBS += -lqcadcore -lspatialindexnavel
OTHER_FILES += spatialindex.dox
DEFINES += QCADSPATIALINDEX_LIBRARY

win32 {
    POST_TARGETDEPS += ../../$$ROUTDIR/spatialindexnavel.dll
}
macx {
    POST_TARGETDEPS += ../../$$ROUTDIR/libspatialindexnavel.dylib
}
linux {
    POST_TARGETDEPS += ../../$$ROUTDIR/libspatialindexnavel.so
}
