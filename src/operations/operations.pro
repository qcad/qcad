include( ../../shared.pri )
SOURCES += RAddObjectOperation.cpp \
    RAddObjectsOperation.cpp \
    RChangePropertyOperation.cpp \
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
    RPasteOperation.cpp \
    RScaleSelectionOperation.cpp
HEADERS = RAddObjectOperation.h \
    RAddObjectsOperation.h \
    RChangePropertyOperation.h \
    RClipboardOperation.h \
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
    RPasteOperation.h \
    RTransformation.h \
    RTranslation.h
TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}
TARGET = qcadoperations
LIBS += -lqcadcore -lqcadentity
OTHER_FILES += operations.dox
DEFINES += QCADOPERATIONS_LIBRARY
