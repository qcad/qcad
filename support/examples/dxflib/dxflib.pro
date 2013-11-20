TEMPLATE    = app
TARGET      = dxflib_example
CONFIG      -= app_bundle
SOURCES     = main.cpp
DESTDIR     = .
INCLUDEPATH += ../../../src/3rdparty/dxflib/src
LIBS += -L../../../debug -ldxflib
