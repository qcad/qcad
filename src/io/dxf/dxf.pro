include( ../../../shared.pri )
HEADERS = \
    RDxfExporter.h \
    RDxfExporterFactory.h \
    RDxfImporter.h \
    RDxfImporterFactory.h \
    RDxfServices.h
SOURCES = \
    RDxfExporter.cpp \
    RDxfExporterFactory.cpp \
    RDxfImporter.cpp \
    RDxfImporterFactory.cpp \
    RDxfServices.cpp
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcaddxf
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadentity -ldxflib -lqcadoperations
DEFINES += QCADDXF_LIBRARY
