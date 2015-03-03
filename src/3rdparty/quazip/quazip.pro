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
DEFINES += QUAZIP_STATIC

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../src/3rdparty/zlib

include( src/quazip.pri )

!win32-msvc* {
    LIBS += -lz
}
