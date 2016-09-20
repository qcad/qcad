include(../qtbindingsbase.pri)
TARGET = qtscript_gui
SOURCES += plugin.cpp
HEADERS += plugin.h
QT += widgets
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_gui/com_trolltech_qt_gui.pri)
