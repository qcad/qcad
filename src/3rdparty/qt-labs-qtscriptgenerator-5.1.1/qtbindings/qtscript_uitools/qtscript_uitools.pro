TARGET = qtscript_uitools
include(../qtbindingsbase.pri)
QT += uitools
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_uitools/com_trolltech_qt_uitools.pri)
