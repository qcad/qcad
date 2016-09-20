include(../qtbindingsbase.pri)
TARGET = qtscript_core
SOURCES += plugin.cpp
HEADERS += qtscriptconcurrent.h plugin.h
INCLUDEPATH += ./include/
QT += concurrent widgets
include($$GENERATEDCPP/com_trolltech_qt_core/com_trolltech_qt_core.pri)
