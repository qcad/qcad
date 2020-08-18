CONFIG += plugin
TARGET = dxf
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
DEFINES += QCADDXF_LIBRARY
RC_FILE = dxf.rc
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}entity -ldxflib -l$${RLIBNAME}operations
r_static_libs {
    CONFIG -= plugin
    CONFIG += staticlib
}
else {
    DESTDIR = $$PWD/../../../plugins
}

POST_TARGETDEPS +=  $$PWD/../../../$$ROUTDIR/$${RLIBPRE}dxflib$${RLIBPOST}
