TARGET = qtscript_widgets
include(../qtbindingsbase.pri)
SOURCES += plugin.cpp
HEADERS += plugin.h
QT += widgets gui
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_widgets/com_trolltech_qt_widgets.pri)
