include(../qtbindingsbase.pri)
TARGET = qtscript_webkitwidgets
QT += network webkitwidgets
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_webkitwidgets/com_trolltech_qt_webkitwidgets.pri)
