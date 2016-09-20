include(../qtbindingsbase.pri)
TARGET = qtscript_widgets
SOURCES += plugin.cpp
HEADERS += plugin.h
QT += widgets gui
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_widgets/com_trolltech_qt_widgets.pri)
