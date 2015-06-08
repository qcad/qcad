TARGET = qtscript_phonon
include(../qtbindingsbase.pri)
QT += phonon
SOURCES += $$GENERATEDCPP/com_trolltech_qt_phonon/plugin.cpp
include($$GENERATEDCPP/com_trolltech_qt_phonon/com_trolltech_qt_phonon.pri)
