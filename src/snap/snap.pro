include( ../../shared.pri )
SOURCES = \
    RRestrictHorizontal.cpp \
    RRestrictVertical.cpp \
    RRestrictOrthogonal.cpp \
    RRestrictOff.cpp \
    RSnapAuto.cpp \
    RSnapCenter.cpp \
    RSnapDistance.cpp \
    RSnapEnd.cpp \
    RSnapEntityBase.cpp \
    RSnapFree.cpp \
    RSnapGrid.cpp \
    RSnapIntersection.cpp \
    RSnapMiddle.cpp \
    RSnapOnEntity.cpp \
    RSnapPerpendicular.cpp \
    RSnapReference.cpp
HEADERS = \
    RRestrictHorizontal.h \
    RRestrictVertical.h \
    RRestrictOrthogonal.h \
    RRestrictOff.h \
    RSnapAuto.h \
    RSnapCenter.h \
    RSnapDistance.h \
    RSnapEnd.h \
    RSnapEntityBase.h \
    RSnapFree.h \
    RSnapGrid.h \
    RSnapIntersection.h \
    RSnapMiddle.h \
    RSnapOnEntity.h \
    RSnapPerpendicular.h \
    RSnapReference.h 
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadsnap
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadgrid
OTHER_FILES += snap.dox
DEFINES += QCADSNAP_LIBRARY
