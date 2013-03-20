include( ../../shared.pri )
SOURCES = \
    RArcData.cpp \
    RArcEntity.cpp \
    RCircleData.cpp \
    RCircleEntity.cpp \
    RDimAlignedData.cpp \
    RDimAlignedEntity.cpp \
    RDimDiametricData.cpp \
    RDimDiametricEntity.cpp \
    RDimAngularData.cpp \
    RDimAngularEntity.cpp \
    RDimRadialData.cpp \
    RDimRadialEntity.cpp \
    RLeaderData.cpp \
    RLeaderEntity.cpp \
    RDimLinearData.cpp \
    RDimLinearEntity.cpp \
    RDimOrdinateData.cpp \
    RDimOrdinateEntity.cpp \
    RDimRotatedData.cpp \
    RDimRotatedEntity.cpp \
    RDimensionData.cpp \
    RDimensionEntity.cpp \
    REllipseData.cpp \
    REllipseEntity.cpp \
    RImageData.cpp \
    RImageEntity.cpp \
    RHatchData.cpp \
    RHatchEntity.cpp \
    RLineData.cpp \
    RLineEntity.cpp \
    RPointData.cpp \
    RPointEntity.cpp \
    RPolylineData.cpp \
    RPolylineEntity.cpp \
    RSolidData.cpp \
    RSolidEntity.cpp \
    RSplineData.cpp \
    RSplineEntity.cpp \
    RTextData.cpp \
    RTextEntity.cpp \
    RTextRenderer.cpp

HEADERS = \
    RArcData.h \
    RArcEntity.h \
    RCircleData.h \
    RCircleEntity.h \
    RDimAlignedData.h \
    RDimAlignedEntity.h \
    RDimDiametricData.h \
    RDimDiametricEntity.h \
    RDimAngularData.h \
    RDimAngularEntity.h \
    RDimRadialData.h \
    RDimRadialEntity.h \
    RLeaderData.h \
    RLeaderEntity.h \
    RDimLinearData.h \
    RDimLinearEntity.h \
    RDimOrdinateData.h \
    RDimOrdinateEntity.h \
    RDimRotatedData.h \
    RDimRotatedEntity.h \
    RDimensionData.h \
    RDimensionEntity.h \
    REllipseData.h \
    REllipseEntity.h \
    RImageData.h \
    RImageEntity.h \
    RHatchData.h \
    RHatchEntity.h \
    RLineData.h \
    RLineEntity.h \
    RPointData.h \
    RPointEntity.h \
    RPolylineData.h \
    RPolylineEntity.h \
    RSolidData.h \
    RSolidEntity.h \
    RSplineData.h \
    RSplineEntity.h \
    RTextData.h \
    RTextEntity.h \
    RTextRenderer.h

TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
TARGET = qcadentity
OTHER_FILES += entity.dox
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lopennurbs
!win32 {
    include( ../../shared_ts.pri )
}
