CONFIG      += plugin
TARGET      = qcadscripts
include(../../shared.pri)

TEMPLATE    = lib
HEADERS     = RScriptsPlugin.h
SOURCES     = RScriptsPlugin.cpp
DESTDIR     = ../../../qcad/plugins
LIBS        += -lqcadgui -lqcadoperations -lqcadecmaapi -lqcadcore
RESOURCES   = scripts.qrc
