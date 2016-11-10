CONFIG      += plugin
TARGET      = $${RLIBNAME}example
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = RExamplePlugin.h
SOURCES     = RExamplePlugin.cpp
DESTDIR     = ../../../plugins
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}gui -l$${RLIBNAME}ecmaapi
