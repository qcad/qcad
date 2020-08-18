CONFIG      += plugin
TARGET      = $${RLIBNAME}example2
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = RExamplePlugin2.h
SOURCES     = RExamplePlugin2.cpp
DESTDIR     = $$PWD/../../../plugins
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}gui -l$${RLIBNAME}ecmaapi
