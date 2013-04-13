include( ../../../shared.pri )
HEADERS = \
    RDxfExporter.h \
    RDxfExporterFactory.h \
    RDxfImporter.h \
    RDxfImporterFactory.h \
    RDxfPlugin.h
SOURCES = \
    RDxfExporter.cpp \
    RDxfExporterFactory.cpp \
    RDxfImporter.cpp \
    RDxfImporterFactory.cpp \
    RDxfPlugin.cpp
TEMPLATE = lib
CONFIG += plugin
DEFINES += QCADDXF_LIBRARY
TARGET = qcaddxf
DESTDIR = ../../../plugins
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadentity -ldxflib -lqcadoperations
