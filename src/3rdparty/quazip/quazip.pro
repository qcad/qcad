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

contains(QT_VERSION, ^5\\..*\\..*) {
    INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtZlib
}
else {
    INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../src/3rdparty/zlib
}

include(src/quazip.pri)

!win32-msvc* {
    LIBS += -lz
}
