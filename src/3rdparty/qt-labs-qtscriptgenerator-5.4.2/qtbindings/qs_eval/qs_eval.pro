QT = core gui script widgets
win32: CONFIG += console
mac:CONFIG -= app_bundle
SOURCES += main.cpp
TOO_OLD_LIST=$$find(QT_VERSION, ^4\\.[0-4])
count(TOO_OLD_LIST, 0): QT += scripttools
