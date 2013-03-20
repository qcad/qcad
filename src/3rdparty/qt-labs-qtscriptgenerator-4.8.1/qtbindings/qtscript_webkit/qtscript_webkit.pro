TARGET = qtscript_webkit
include(../qtbindingsbase.pri)
QT += network webkit
SOURCES += $$GENERATEDCPP/com_trolltech_qt_webkit/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_webkit/com_trolltech_qt_webkit.pri)
