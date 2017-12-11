include( ../../shared.pri )
SOURCES = \
    ROrthoGrid.cpp
HEADERS = \
    ROrthoGrid.h
TEMPLATE = lib
OTHER_FILES += grid.dox
DEFINES += QCADGRID_LIBRARY
RC_FILE = grid.rc
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}
TARGET = $${RLIBNAME}grid
LIBS += -l$${RLIBNAME}core
