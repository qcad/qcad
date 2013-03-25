include( ../../shared.pri )
SOURCES = RShortcutLineEditPlugin.cpp \
    RCharacterWidgetPlugin.cpp \
    RWebViewPlugin.cpp \
    RFontChooserWidgetPlugin.cpp \
    RRulerQtPlugin.cpp \
    RLinetypeComboPlugin.cpp \
    RLineweightComboPlugin.cpp \
    RColorComboPlugin.cpp \
    RCustomWidgets.cpp \
    RCommandLinePlugin.cpp \
    RMdiChildQtPlugin.cpp \
    RTextEditPlugin.cpp \
    RMathLineEditPlugin.cpp \
    RGraphicsViewGlPlugin.cpp \
    RGraphicsViewQtPlugin.cpp \
    RListViewPlugin.cpp
HEADERS = RShortcutLineEditPlugin.h \
    RCharacterWidgetPlugin.h \
    RWebViewPlugin.h \
    RFontChooserWidgetPlugin.h \
    RRulerQtPlugin.h \
    RLinetypeComboPlugin.h \
    RLineweightComboPlugin.h \
    RColorComboPlugin.h \
    RCustomWidgets.h \
    RCommandLinePlugin.h \
    RMdiChildQtPlugin.h \
    RTextEditPlugin.h \
    RMathLineEditPlugin.h \
    RGraphicsViewGlPlugin.h \
    RGraphicsViewQtPlugin.h \
    RListViewPlugin.h
TEMPLATE = lib
CONFIG += \
    designer \
    plugin
LIBS += -L$$PWD/$$ROUTDIR -lqcadcore -lqcadgui
TARGET = qcadcustomwidgets
DESTDIR = ../../plugins/designer
OTHER_FILES += customwidgets.dox
