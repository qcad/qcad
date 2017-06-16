include(../qtbindingsbase.pri)
TARGET = qtscript_phonon
QT += phonon
SOURCES += $$GENERATEDCPP/com_trolltech_qt_phonon/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_phonon/com_trolltech_qt_phonon.pri)
