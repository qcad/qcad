include( ../../../shared.pri )
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadecmaapi
LIBS += -ldxflib -lopennurbs -lqcadcore -lqcaddxf -lqcadentity -lqcadgrid -lqcadgui -lqcadoperations -lqcadsnap -lqcadspatialindex -lqcadstemmer -lspatialindexnavel -lstemmer
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
LIBS += -L$$PWD/$$ROUTDIR \
    -ldxflib \
    -lopennurbs \
    -lqcadcore \
    -lqcaddxf \
    -lqcadentity \
    -lqcadgrid \
    -lqcadgui \
    -lqcadoperations \
    -lqcadsnap \
    -lqcadspatialindex \
    -lqcadstemmer \
    -lspatialindexnavel \
    -lstemmer
