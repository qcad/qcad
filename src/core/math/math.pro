include( ../../shared.pri )
SOURCES = \
    RArc.cpp \
    RBox.cpp \
    RCircle.cpp \
    RDirected.cpp \
    REllipse.cpp \
    RLine.cpp \
    RMath.cpp \
    RMatrix.cpp \
    RPoint.cpp \
    RPolyline.cpp \
    RShape.cpp \
    RSpline.cpp \
    RTextLabel.cpp \
    RTriangle.cpp \
    RVector.cpp
HEADERS = \
    RArc.h \
    RBox.h \
    RCircle.h \
    RDirected.h \
    REllipse.h \
    RExplodable.h \
    RLine.h \
    RMath.h \
    RMatrix.h \
    RPoint.h \
    RPolyline.h \
    RShape.h \
    RSpline.h \
    RTextLabel.h \
    RTriangle.h \
    RVector.h

TEMPLATE = lib
#CONFIG += staticlib
CONFIG += shared
LIBS += -L$$PWD/$$ROUTDIR
LIBS += -lopennurbs
