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

include( src/quazip.pri )

LIBS += -lz
