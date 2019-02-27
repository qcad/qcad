include( ../../../shared.pri )
TEMPLATE = lib
CONFIG += plugin
TARGET = $${RLIBNAME}ecmaapi
CONFIG -= warn_on
CONFIG += warn_off
CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h
OTHER_FILES += ecmaapi.dox
DEFINES += QCADECMAAPI_LIBRARY
RC_FILE = ecmaapi.rc
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
    -l$${RLIBNAME}core \
    -l$${RLIBNAME}entity \
    -l$${RLIBNAME}grid \
    -l$${RLIBNAME}gui \
    -l$${RLIBNAME}operations \
    -l$${RLIBNAME}snap \
    -l$${RLIBNAME}spatialindex \
    -l$${RLIBNAME}stemmer
