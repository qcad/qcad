include($$PWD/../../../../shared.pri)
TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .
 
Release:DESTDIR = $$PWD/../../../../plugins/script
Debug:  DESTDIR = $$PWD/../../../../plugins/script_debug

QT += script
CONFIG += plugin debug_and_release build_all
GENERATEDCPP = $$PWD/../generated_cpp
TARGET=$$qtLibraryTarget($$TARGET)
