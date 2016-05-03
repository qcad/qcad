include(../../../shared.pri)
CONFIG      += plugin
TARGET      = transactionlistener

TEMPLATE    = lib
HEADERS     = TransactionListenerPlugin.h
SOURCES     = TransactionListenerPlugin.cpp
DESTDIR     = ../../../plugins
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}gui
