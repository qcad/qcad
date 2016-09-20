include(../qtbindingsbase.pri)
TARGET = qtscript_network
QT -= gui
QT += network
SOURCES += plugin.cpp
HEADERS += plugin.h include/__package_shared.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_network/com_trolltech_qt_network.pri)
