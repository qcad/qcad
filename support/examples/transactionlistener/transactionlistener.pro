CONFIG      += plugin
TARGET      = transactionlistener
include(../../../shared.pri)

TEMPLATE    = lib
HEADERS     = TransactionListenerPlugin.h
SOURCES     = TransactionListenerPlugin.cpp
DESTDIR     = ../../../../qcad/plugins
LIBS += -lqcadcore -lqcadgui
