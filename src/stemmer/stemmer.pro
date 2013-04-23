include( ../../shared.pri )
SOURCES = \
    RStemmer.cpp
HEADERS = \
    RStemmer.h

TEMPLATE = lib
CONFIG += plugin
TARGET = qcadstemmer
LIBS += -lstemmer
OTHER_FILES += stemmer.dox
DEFINES += QCADSTEMMER_LIBRARY

win32 {
    POST_TARGETDEPS += ../../$$ROUTDIR/stemmer.lib
}
macx {
    POST_TARGETDEPS += ../../$$ROUTDIR/libstemmer.a
}
linux {
    POST_TARGETDEPS += ../../$$ROUTDIR/libstemmer.a
}
