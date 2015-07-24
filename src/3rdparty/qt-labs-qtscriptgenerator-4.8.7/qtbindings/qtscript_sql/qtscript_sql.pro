TARGET = qtscript_sql
include(../qtbindingsbase.pri)
QT -= gui
QT += sql
SOURCES += $$GENERATEDCPP/com_trolltech_qt_sql/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_sql/com_trolltech_qt_sql.pri)
