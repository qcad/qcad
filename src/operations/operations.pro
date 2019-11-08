include( ../../shared.pri )
SOURCES += RAddObjectOperation.cpp \
    RAddObjectsOperation.cpp \
    RChangePropertyOperation.cpp \
    RClickReferencePointOperation.cpp \
    RClipboardOperation.cpp \
    RCopyOperation.cpp \
    RDeleteAllEntitiesOperation.cpp \
    RDeleteObjectOperation.cpp \
    RDeleteObjectsOperation.cpp \
    RDeleteSelectionOperation.cpp \
    RMixedOperation.cpp \
    RModifyObjectOperation.cpp \
    RModifyObjectsOperation.cpp \
    RMoveReferencePointOperation.cpp \
    RMoveSelectionOperation.cpp \
    ROperationUtils.cpp \
    RPasteOperation.cpp \
    RScaleSelectionOperation.cpp
HEADERS = RAddObjectOperation.h \
    RAddObjectsOperation.h \
    RChangePropertyOperation.h \
    RClipboardOperation.h \
    RClickReferencePointOperation.h \
    RCopyOperation.h \
    RDeleteAllEntitiesOperation.h \
    RDeleteObjectOperation.h \
    RDeleteObjectsOperation.h \
    RDeleteSelectionOperation.h \
    RMixedOperation.h \
    RModifyObjectOperation.h \
    RModifyObjectsOperation.h \
    RMoveReferencePointOperation.h \
    RMoveSelectionOperation.h \
    RScaleSelectionOperation.h \
    ROperationUtils.h \
    RPasteOperation.h \
    RTransformation.h \
    RTranslation.h
TEMPLATE = lib
#QT += concurrent
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}
TARGET = $${RLIBNAME}operations
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}entity
OTHER_FILES += operations.dox
DEFINES += QCADOPERATIONS_LIBRARY
RC_FILE = operations.rc
