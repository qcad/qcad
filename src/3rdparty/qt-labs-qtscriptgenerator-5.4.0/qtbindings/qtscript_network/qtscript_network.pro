TARGET = qtscript_network
include(../qtbindingsbase.pri)
QT -= gui
QT += network
SOURCES += plugin.cpp
HEADERS += plugin.h include/__package_shared.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_network/com_trolltech_qt_network.pri)
