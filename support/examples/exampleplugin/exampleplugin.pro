CONFIG      += plugin
TARGET      = qcadexample
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = RExamplePlugin.h
SOURCES     = RExamplePlugin.cpp
DESTDIR     = ../../../plugins
LIBS += -lqcadcore -lqcadecmaapi
