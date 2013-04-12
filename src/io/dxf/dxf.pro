include( ../../../shared.pri )
HEADERS = \
    RDxfExporter.h \
    RDxfExporterFactory.h \
    RDxfImporter.h \
    RDxfImporterFactory.h \
    RDxfPlugin.h \
    RDxfServices.h
SOURCES = \
    RDxfExporter.cpp \
    RDxfExporterFactory.cpp \
    RDxfImporter.cpp \
    RDxfImporterFactory.cpp \
    RDxfPlugin.cpp \
    RDxfServices.cpp
TEMPLATE = lib
CONFIG += plugin
DEFINES += QCADDXF_LIBRARY
TARGET = qcaddxf
DESTDIR = ../../../qcad/plugins
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadentity -ldxflib -lqcadoperations
