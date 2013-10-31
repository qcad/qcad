CONFIG      += plugin
TARGET      = transactionlistener
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = TransactionListenerPlugin.h
SOURCES     = TransactionListenerPlugin.cpp
DESTDIR     = ../../../plugins
LIBS += -lqcadcore -lqcadgui
