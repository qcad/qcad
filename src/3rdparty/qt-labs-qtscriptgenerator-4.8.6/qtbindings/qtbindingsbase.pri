include($$PWD/../../../../shared.pri)
TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = $$PWD/../../../../plugins/script
QT += script
CONFIG += debug_and_release
GENERATEDCPP = $$PWD/../generated_cpp
TARGET=$$qtLibraryTarget($$TARGET)
