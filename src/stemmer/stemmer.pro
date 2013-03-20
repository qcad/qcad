include( ../../shared.pri )
SOURCES = \
    RStemmer.cpp
HEADERS = \
    RStemmer.h

TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadstemmer
LIBS += -L$$PWD/$$ROUTDIR -lstemmer
OTHER_FILES += stemmer.dox
