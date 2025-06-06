include( ../../../../shared.pri )

SOURCES += \
    adler32.c \
    compress.c \
    crc32.c \
    deflate.c \
    infback.c \
    inffast.c \
    inflate.c \
    inftrees.c \
    trees.c \
    uncompr.c \
    zutil.c

HEADERS += \
    crc32.h \
    deflate.h \
    inffast.h \
    inffixed.h \
    inflate.h \
    inftrees.h \
    trees.h \
    zconf.h \
    zlib.h \
    zutil.h

TARGET = zlib
TEMPLATE = lib
CONFIG += staticlib
#win32 {
#    LIBS += -lRpcrt4 -lAdvapi32
#}

CONFIG(release, debug|release) {
    DEFINES += NDEBUG
    #DESTDIR = release
}
else {
    #DESTDIR = debug
}
#DEFINES += ZLIB_DLL
