include( ../../shared.pri )
SOURCES = \
    RArcData.cpp \
    RArcEntity.cpp \
    RAttributeData.cpp \
    RAttributeEntity.cpp \
    RAttributeDefinitionData.cpp \
    RAttributeDefinitionEntity.cpp \
    RCircleData.cpp \
    RCircleEntity.cpp \
    RDimAlignedData.cpp \
    RDimAlignedEntity.cpp \
    RDimAngularData.cpp \
    RDimAngularEntity.cpp \
    RDimDiametricData.cpp \
    RDimDiametricEntity.cpp \
    RDimLinearData.cpp \
    RDimLinearEntity.cpp \
    RDimOrdinateData.cpp \
    RDimOrdinateEntity.cpp \
    RDimRadialData.cpp \
    RDimRadialEntity.cpp \
    RDimRotatedData.cpp \
    RDimRotatedEntity.cpp \
    RDimensionData.cpp \
    RDimensionEntity.cpp \
    REllipseData.cpp \
    REllipseEntity.cpp \
    RHatchData.cpp \
    RHatchEntity.cpp \
    RImageData.cpp \
    RImageEntity.cpp \
    RLeaderData.cpp \
    RLeaderEntity.cpp \
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
    RTextBasedData.cpp \
    RTextBasedEntity.cpp \
    RTextData.cpp \
    RTextEntity.cpp \
    RTextRenderer.cpp

HEADERS = \
    RArcData.h \
    RArcEntity.h \
    RAttributeData.h \
    RAttributeEntity.h \
    RAttributeDefinitionData.h \
    RAttributeDefinitionEntity.h \
    RCircleData.h \
    RCircleEntity.h \
    RDimAlignedData.h \
    RDimAlignedEntity.h \
    RDimAngularData.h \
    RDimAngularEntity.h \
    RDimDiametricData.h \
    RDimDiametricEntity.h \
    RDimLinearData.h \
    RDimLinearEntity.h \
    RDimOrdinateData.h \
    RDimOrdinateEntity.h \
    RDimRadialData.h \
    RDimRadialEntity.h \
    RDimRotatedData.h \
    RDimRotatedEntity.h \
    RDimensionData.h \
    RDimensionEntity.h \
    REllipseData.h \
    REllipseEntity.h \
    RHatchData.h \
    RHatchEntity.h \
    RImageData.h \
    RImageEntity.h \
    RLeaderData.h \
    RLeaderEntity.h \
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
    RTextBasedData.h \
    RTextBasedEntity.h \
    RTextData.h \
    RTextEntity.h \
    RTextRenderer.h

TEMPLATE = lib
CONFIG += plugin
NAME = qcadentity
TARGET = $${NAME}
OTHER_FILES += entity.dox
DEFINES += QCADENTITY_LIBRARY
LIBS += -lqcadcore -lopennurbs
!win32 {
    include( ../../shared_ts.pri )
}
