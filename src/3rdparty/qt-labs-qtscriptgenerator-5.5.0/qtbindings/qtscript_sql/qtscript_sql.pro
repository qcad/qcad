TARGET = qtscript_sql
include(../qtbindingsbase.pri)
QT -= gui
QT += sql
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_sql/com_trolltech_qt_sql.pri)
