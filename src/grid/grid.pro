include( ../../shared.pri )
SOURCES = \
    ROrthoGrid.cpp
HEADERS = \
    ROrthoGrid.h
TEMPLATE = lib
OTHER_FILES += grid.dox
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadgrid
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore
