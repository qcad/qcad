CONFIG      += plugin
TARGET      = scripts
include(../../shared.pri)

TEMPLATE    = lib
HEADERS     = RScriptsPlugin.h
SOURCES     = RScriptsPlugin.cpp
DESTDIR     = ../../plugins
RC_FILE     = scripts.rc
LIBS        += -l$${RLIBNAME}core
RESOURCES   = scripts.qrc
