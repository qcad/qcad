include( ../../../shared.pri )
TEMPLATE = lib
CONFIG += plugin
TARGET = qcadecmaapi
CONFIG -= warn_on
CONFIG += warn_off
CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h
OTHER_FILES += ecmaapi.dox
DEFINES += QCADECMAAPI_LIBRARY
HEADERS += \
    RAutoLoadEcma.h \
    REcmaHelper.h \
    RScriptHandlerEcma.h
SOURCES += \
    RAutoLoadEcma.cpp \
    REcmaHelper.cpp \
    RScriptHandlerEcma.cpp
include(adapters/adapters.pri)
include(generated/generated.pri)
LIBS += \
    -lqcadcore \
    -lqcadentity \
    -lqcadgrid \
    -lqcadgui \
    -lqcadoperations \
    -lqcadsnap \
    -lqcadspatialindex \
    -lqcadstemmer \
    -lqcadzip \
    -lquazip
