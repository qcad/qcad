include( ../../../shared.pri )
SOURCES += \
    libstemmer/libstemmer_utf8.c \
    runtime/api.c \
    runtime/utilities.c \
    src_c/stem_UTF_8_danish.c \
    src_c/stem_UTF_8_dutch.c \
    src_c/stem_UTF_8_english.c \
    src_c/stem_UTF_8_finnish.c \
    src_c/stem_UTF_8_french.c \
    src_c/stem_UTF_8_german.c \
    src_c/stem_UTF_8_hungarian.c \
    src_c/stem_UTF_8_italian.c \
    src_c/stem_UTF_8_norwegian.c \
    src_c/stem_UTF_8_porter.c \
    src_c/stem_UTF_8_portuguese.c \
    src_c/stem_UTF_8_romanian.c \
    src_c/stem_UTF_8_russian.c \
    src_c/stem_UTF_8_spanish.c \
    src_c/stem_UTF_8_swedish.c \
    src_c/stem_UTF_8_turkish.c

HEADERS += \
    include/libstemmer.h \
    libstemmer/modules_utf8.h \
    runtime/api.h \
    runtime/header.h \
    src_c/stem_UTF_8_danish.h \
    src_c/stem_UTF_8_dutch.h \
    src_c/stem_UTF_8_english.h \
    src_c/stem_UTF_8_finnish.h \
    src_c/stem_UTF_8_french.h \
    src_c/stem_UTF_8_german.h \
    src_c/stem_UTF_8_hungarian.h \
    src_c/stem_UTF_8_italian.h \
    src_c/stem_UTF_8_norwegian.h \
    src_c/stem_UTF_8_porter.h \
    src_c/stem_UTF_8_portuguese.h \
    src_c/stem_UTF_8_romanian.h \
    src_c/stem_UTF_8_russian.h \
    src_c/stem_UTF_8_spanish.h \
    src_c/stem_UTF_8_swedish.h \
    src_c/stem_UTF_8_turkish.h

TARGET = stemmer
TEMPLATE = lib
CONFIG += staticlib
#CONFIG += plugin
