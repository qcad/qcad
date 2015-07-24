TARGET = qtscript_xmlpatterns
include(../qtbindingsbase.pri)
QT -= gui
QT += xmlpatterns network
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_xmlpatterns/com_trolltech_qt_xmlpatterns.pri)
