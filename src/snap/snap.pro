include( ../../shared.pri )
SOURCES = \
    RRestrictAngleLength.cpp \
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
    RRestrictAngleLength.h \
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
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}
TARGET = qcadsnap
LIBS += -lqcadcore -lqcadgrid -lqcadentity
OTHER_FILES += snap.dox
DEFINES += QCADSNAP_LIBRARY
