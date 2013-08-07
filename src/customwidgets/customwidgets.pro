TARGET = qcadcustomwidgets
CONFIG += plugin
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
    RGraphicsViewQtPlugin.h \
    RListViewPlugin.h
TEMPLATE = lib
LIBS += -lqcadgui -lqcadcore
DESTDIR = ../../plugins/designer
OTHER_FILES += customwidgets.dox
