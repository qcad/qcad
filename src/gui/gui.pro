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
    #RGraphicsSceneGl.cpp \
    RGraphicsSceneQt.cpp \
    RGraphicsViewImage.cpp \
    RGraphicsViewGl.cpp \
    RGraphicsViewQt.cpp \
    RHelpBrowser.cpp \
    RLinetypeCombo.cpp \
    RLineweightCombo.cpp \
    RListWidget.cpp \
    RMainWindowQt.cpp \
    RMathLineEdit.cpp \
    RMdiChildQt.cpp \
    RRulerQt.cpp \
    RTextEdit.cpp \
    RWebView.cpp

HEADERS += \
    RShortcutLineEdit.h \
    RCharacterWidget.h \
    RColorCombo.h \
    RCommandLine.h \
    RDockWidget.h \
    REventFilter.h \
    RFileSystemModel.h \
    RFocusFrame.h \
    RFontChooserWidget.h \
    RGraphicsSceneQt.h \
    RGraphicsViewImage.h \
    RGraphicsViewGl.h \
    RGraphicsViewQt.h \
    RHelpBrowser.h \
    RLinetypeCombo.h \
    RLineweightCombo.h \
    RListView.h \
    RListWidget.h \
    RMainWindowQt.h \
    RMathLineEdit.h \
    RMdiChildQt.h \
    RRulerQt.h \
    RTextEdit.h \
    RWebView.h
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += plugin
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadentity
TARGET = qcadgui
OTHER_FILES += gui.dox
!win32:include( ../../shared_ts.pri )
