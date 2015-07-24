TARGET = qtscript_printsupport
include(../qtbindingsbase.pri)
SOURCES += plugin.cpp
HEADERS += plugin.h
QT += core gui widgets printsupport
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_printsupport/com_trolltech_qt_printsupport.pri)
