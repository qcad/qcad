include( ../../../shared.pri )
HEADERS = \
    RDxfImporter.h \
    RDxfServices.h
SOURCES = \
    RDxfImporter.cpp \
    RDxfServices.cpp
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcaddxf
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadentity -ldxflib -lqcadoperations
