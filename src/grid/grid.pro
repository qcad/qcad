include( ../../shared.pri )
SOURCES = \
    ROrthoGrid.cpp
HEADERS = \
    ROrthoGrid.h
TEMPLATE = lib
OTHER_FILES += grid.dox
DEFINES += QCADGRID_LIBRARY
CONFIG += plugin
TARGET = qcadgrid
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore
