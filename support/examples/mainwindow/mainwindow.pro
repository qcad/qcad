include(../../../shared_app.pri)

TEMPLATE = app
TARGET = mainwindow_prototype
DEPENDPATH += .

HEADERS += MainWindow.h
SOURCES += main.cpp MainWindow.cpp
OTHER_FILES += init_viewport.js
