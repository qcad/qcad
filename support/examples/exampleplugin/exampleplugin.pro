include(../../../shared.pri)
CONFIG      += plugin
TARGET      = $${RLIBNAME}example

TEMPLATE    = lib
HEADERS     = RExamplePlugin.h
SOURCES     = RExamplePlugin.cpp
DESTDIR     = ../../../plugins
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}gui -l$${RLIBNAME}ecmaapi
