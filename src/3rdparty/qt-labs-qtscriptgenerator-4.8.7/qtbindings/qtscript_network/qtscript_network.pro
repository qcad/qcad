TARGET = qtscript_network
include(../qtbindingsbase.pri)
QT -= gui
QT += network
SOURCES += $$GENERATEDCPP/com_trolltech_qt_network/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_network/com_trolltech_qt_network.pri)
