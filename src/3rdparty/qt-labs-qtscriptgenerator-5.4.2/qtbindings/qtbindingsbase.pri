include($$PWD/../../../../shared.pri)
TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .

#CONFIG(debug, debug|release) {
#    DESTDIR = $$PWD/../plugins/script_debug
#} else {
#    DESTDIR = $$PWD/../plugins/script
#}
DESTDIR = $$PWD/../../../../plugins/script

QT += script
#CONFIG += plugin release build_all
CONFIG += debug_and_release
GENERATEDCPP = $$PWD/../generated_cpp
TARGET=$$qtLibraryTarget($$TARGET)
