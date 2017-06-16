include(../qtbindingsbase.pri)
TARGET = qtscript_sql
QT -= gui
QT += sql
SOURCES += $$GENERATEDCPP/com_trolltech_qt_sql/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_sql/com_trolltech_qt_sql.pri)
