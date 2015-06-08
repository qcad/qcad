TARGET = qtscript_xmlpatterns
include(../qtbindingsbase.pri)
QT -= gui
QT += xmlpatterns network
SOURCES += $$GENERATEDCPP/com_trolltech_qt_xmlpatterns/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_xmlpatterns/com_trolltech_qt_xmlpatterns.pri)
