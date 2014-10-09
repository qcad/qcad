include( ../../shared.pri )

SOURCES += \
    RShortcutLineEdit.cpp \
    RCharacterWidget.cpp \
    RColorCombo.cpp \
    RCommandLine.cpp \
    RDockWidget.cpp \
    REventFilter.cpp \
    RFileSystemModel.cpp \
    RFocusFrame.cpp \
    RFontChooserWidget.cpp \
    RGraphicsSceneQt.cpp \
    RGraphicsViewImage.cpp \
    RGraphicsViewQt.cpp \
    RLinetypeCombo.cpp \
    RLineweightCombo.cpp \
    RListWidget.cpp \
    RMainWindowQt.cpp \
    RMathLineEdit.cpp \
    RMdiChildQt.cpp \
    RRulerQt.cpp \
    RTextEdit.cpp \
    RTreeWidget.cpp

HEADERS += \
    RShortcutLineEdit.h \
    RCharacterWidget.h \
    RCloseCurrentEvent.h \
    RColorCombo.h \
    RCommandLine.h \
    RDockWidget.h \
    REventFilter.h \
    RFileSystemModel.h \
    RFocusFrame.h \
    RFontChooserWidget.h \
    RGraphicsSceneQt.h \
    RGraphicsViewImage.h \
    RGraphicsViewQt.h \
    RLinetypeCombo.h \
    RLineweightCombo.h \
    RListView.h \
    RListWidget.h \
    RMainWindowQt.h \
    RMathLineEdit.h \
    RMdiChildQt.h \
    RRulerQt.h \
    RTextEdit.h \
    RTreeWidget.h

!r_mobile {
    SOURCES += \
        RWebView.cpp
    HEADERS += \
        RWebView.h
}

TEMPLATE = lib
r_static_libs {
    CONFIG += staticlib
}
else {
    CONFIG += plugin
}

LIBS += -lqcadcore -lqcadentity
NAME = qcadgui
TARGET = $${NAME}
OTHER_FILES += gui.dox
DEFINES += QCADGUI_LIBRARY
!win32:include( ../../shared_ts.pri )
