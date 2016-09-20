include(../qtbindingsbase.pri)
TARGET = qtscript_opengl
QT += opengl
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_opengl/com_trolltech_qt_opengl.pri)
