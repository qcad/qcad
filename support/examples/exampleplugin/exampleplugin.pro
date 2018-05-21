CONFIG      += plugin
TARGET      = example
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = RExamplePlugin.h
SOURCES     = RExamplePlugin.cpp
DESTDIR     = ../../../plugins
LIBS += -lqcadcore -lqcadgui -lqcadecmaapi
RESOURCES   = scripts.qrc
