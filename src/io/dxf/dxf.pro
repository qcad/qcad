include( ../../../shared.pri )
CONFIG += plugin
TARGET = $${RLIBNAME}dxf

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
DEFINES += QCADDXF_LIBRARY
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}entity -ldxflib -l$${RLIBNAME}operations
r_static_libs {
    CONFIG -= plugin
    CONFIG += staticlib
}
else {
    DESTDIR = ../../../plugins
}

POST_TARGETDEPS += ../../../$$ROUTDIR/$${RLIBPRE}dxflib$${RLIBPOST}
