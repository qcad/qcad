TARGET = qtscript_opengl
include(../qtbindingsbase.pri)
QT += opengl
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_opengl/com_trolltech_qt_opengl.pri)
