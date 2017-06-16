include(../qtbindingsbase.pri)
TARGET = qtscript_xml
QT -= gui
QT += xml
SOURCES += $$GENERATEDCPP/com_trolltech_qt_xml/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_xml/com_trolltech_qt_xml.pri)
