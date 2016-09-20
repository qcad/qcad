include(../qtbindingsbase.pri)
TARGET = qtscript_webkit
QT += network webkit webkitwidgets
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_webkit/com_trolltech_qt_webkit.pri)
