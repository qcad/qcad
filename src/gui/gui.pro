include( ../../shared.pri )

SOURCES += \
    RShortcutLineEdit.cpp \
    RCharacterWidget.cpp \
    RColorCombo.cpp \
    RCommandLine.cpp \
    RDockWidget.cpp \
    REventFilter.cpp \
    RFileSystemModel.cpp \
    RFlowLayout.cpp \
    RFocusFrame.cpp \
    RFontChooserWidget.cpp \
    RGraphicsSceneQt.cpp \
    RGraphicsViewImage.cpp \
    RGraphicsViewQt.cpp \
    RLinetypeCombo.cpp \
    RLinetypeComboDelegate.cpp \
    RLineweightCombo.cpp \
    RListWidget.cpp \
    RMainWindowQt.cpp \
    RMathLineEdit.cpp \
    RMdiArea.cpp \
    RMdiChildQt.cpp \
    RRulerQt.cpp \
    RTextEdit.cpp \
    RToolMatrixItemDelegate.cpp \
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
    RFlowLayout.h \
    RFocusFrame.h \
    RFontChooserWidget.h \
    RGraphicsSceneQt.h \
    RGraphicsViewImage.h \
    RGraphicsViewQt.h \
    RLinetypeCombo.h \
    RLinetypeComboDelegate.h \
    RLineweightCombo.h \
    RListView.h \
    RListWidget.h \
    RMainWindowQt.h \
    RMathLineEdit.h \
    RMdiArea.h \
    RMdiChildQt.h \
    RRulerQt.h \
    RTextEdit.h \
    RToolMatrixItemDelegate.h \
    RTreeWidget.h

!r_mobile {
    contains(QT_VERSION, ^5\\.[1-5]\\..*) || contains(QT_VERSION, ^4\\..*\\..*) {
        # Qt < 5.6:
        SOURCES += \
            RWebView.cpp
        HEADERS += \
            RWebView.h
    }
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
