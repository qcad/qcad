TARGET = customwidgets
CONFIG += plugin
include( ../../shared.pri )

SOURCES = RShortcutLineEditPlugin.cpp \
    RCharacterWidgetPlugin.cpp \
    RFontChooserWidgetPlugin.cpp \
    RRulerQtPlugin.cpp \
    RLinetypeComboPlugin.cpp \
    RLineweightComboPlugin.cpp \
    RColorComboPlugin.cpp \
    RCustomWidgets.cpp \
    RCommandLinePlugin.cpp \
    RMdiChildQtPlugin.cpp \
    RTextEditPlugin.cpp \
    RMathComboBoxPlugin.cpp \
    RMathLineEditPlugin.cpp \
    RGraphicsViewQtPlugin.cpp \
    RListViewPlugin.cpp
HEADERS = RShortcutLineEditPlugin.h \
    RCharacterWidgetPlugin.h \
    RFontChooserWidgetPlugin.h \
    RRulerQtPlugin.h \
    RLinetypeComboPlugin.h \
    RLineweightComboPlugin.h \
    RColorComboPlugin.h \
    RCustomWidgets.h \
    RCommandLinePlugin.h \
    RMdiChildQtPlugin.h \
    RTextEditPlugin.h \
    RMathComboBoxPlugin.h \
    RMathLineEditPlugin.h \
    RGraphicsViewQtPlugin.h \
    RListViewPlugin.h
#contains(QT_VERSION, ^5\\.[1-5]\\..*) || contains(QT_VERSION, ^4\\..*\\..*) {
#    # Qt < 5.6:
#    SOURCES += RWebViewPlugin.cpp
#    HEADERS += RWebViewPlugin.h
#}
TEMPLATE = lib
LIBS += -l$${RLIBNAME}gui -l$${RLIBNAME}core
DESTDIR = ../../plugins/designer
OTHER_FILES += customwidgets.dox
RC_FILE = customwidgets.rc
