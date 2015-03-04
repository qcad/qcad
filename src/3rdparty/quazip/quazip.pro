include( ../../../shared.pri )

TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}

CONFIG -= warn_on
CONFIG += warn_off

# Handles dllimport/dllexport directives:
DEFINES += QUAZIP_BUILD

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../src/3rdparty/zlib

include(src/quazip.pri)
#include($$[QT_INSTALL_HEADERS]/../src/3rdparty/zlib.pri)

#!win32-msvc* {
#    LIBS += -lz
#}
