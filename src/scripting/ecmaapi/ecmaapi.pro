include( ../../../shared.pri )
TEMPLATE = lib
CONFIG += plugin
TARGET = qcadecmaapi
CONFIG -= warn_on
CONFIG += warn_off
OTHER_FILES += ecmaapi.dox
DEFINES += QCADECMAAPI_LIBRARY
include(adapters/adapters.pri)
include(generated/generated.pri)
HEADERS += \
    RAutoLoadEcma.h \
    REcmaHelper.h \
    RScriptHandlerEcma.h
SOURCES += \
    RAutoLoadEcma.cpp \
    REcmaHelper.cpp \
    RScriptHandlerEcma.cpp
LIBS += \
    -lqcadcore \
    -lqcadentity \
    -lqcadgrid \
    -lqcadgui \
    -lqcadoperations \
    -lqcadsnap \
    -lqcadspatialindex \
    -lqcadstemmer
