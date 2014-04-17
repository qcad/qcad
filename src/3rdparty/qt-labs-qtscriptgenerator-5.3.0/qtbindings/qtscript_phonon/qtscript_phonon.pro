TARGET = qtscript_phonon
include(../qtbindingsbase.pri)
QT += phonon
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_phonon/com_trolltech_qt_phonon.pri)
