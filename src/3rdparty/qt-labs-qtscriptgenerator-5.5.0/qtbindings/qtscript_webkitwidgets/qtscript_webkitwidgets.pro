TARGET = qtscript_webkitwidgets
include(../qtbindingsbase.pri)
QT += network webkitwidgets
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_webkitwidgets/com_trolltech_qt_webkitwidgets.pri)
