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
    RDimAngular2LData.cpp \
    RDimAngular2LEntity.cpp \
    RDimAngular3PData.cpp \
    RDimAngular3PEntity.cpp \
    RDimArcLengthData.cpp \
    RDimArcLengthEntity.cpp \
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
    RFaceData.cpp \
    RFaceEntity.cpp \
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
    RRayData.cpp \
    RRayEntity.cpp \
    RSolidData.cpp \
    RSolidEntity.cpp \
    RSplineData.cpp \
    RSplineEntity.cpp \
    RTextData.cpp \
    RTextEntity.cpp \
    RToleranceData.cpp \
    RToleranceEntity.cpp \
    RTraceData.cpp \
    RTraceEntity.cpp \
    RXLineData.cpp \
    RXLineEntity.cpp

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
    RDimAngular2LData.h \
    RDimAngular2LEntity.h \
    RDimAngular3PData.h \
    RDimAngular3PEntity.h \
    RDimArcLengthData.h \
    RDimArcLengthEntity.h \
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
    RFaceData.h \
    RFaceEntity.h \
    RHatchData.h \
    RHatchEntity.h \
    RHatchProxy.h \
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
    RRayData.h \
    RRayEntity.h \
    RSolidData.h \
    RSolidEntity.h \
    RSplineData.h \
    RSplineEntity.h \
    RTextData.h \
    RTextEntity.h \
    RToleranceData.h \
    RToleranceEntity.h \
    RTraceData.h \
    RTraceEntity.h \
    RXLineData.h \
    RXLineEntity.h

TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}
NAME = $${RLIBNAME}entity
TARGET = $${NAME}
OTHER_FILES += entity.dox
DEFINES += QCADENTITY_LIBRARY
RC_FILE = entity.rc
LIBS += -l$${RLIBNAME}core -lopennurbs
!win32 {
    include( ../../shared_ts.pri )
}
