CONFIG      += plugin
TARGET      = transactionlistener
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = TransactionListenerPlugin.h
SOURCES     = TransactionListenerPlugin.cpp
DESTDIR     = $$PWD/../../../plugins
LIBS += -l$${RLIBNAME}core -l$${RLIBNAME}gui
