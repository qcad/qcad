include( ../../shared.pri )
SOURCES = \
    RStemmer.cpp
HEADERS = \
    RStemmer.h

TEMPLATE = lib
CONFIG += plugin
TARGET = $${RLIBNAME}stemmer
LIBS += -lstemmer
OTHER_FILES += stemmer.dox
DEFINES += QCADSTEMMER_LIBRARY
RC_FILE = stemmer.rc

POST_TARGETDEPS += $$PWD/../../$$ROUTDIR/$${RLIBPRE}stemmer$${RLIBPOST}
