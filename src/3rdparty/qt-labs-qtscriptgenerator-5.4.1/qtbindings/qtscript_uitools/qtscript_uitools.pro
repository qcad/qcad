TARGET = qtscript_uitools
include(../qtbindingsbase.pri)
QT += uitools widgets
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/ ${QTDIR}/lib/QtWidgets.framework/Headers
# might have to be:
#INCLUDEPATH += ./include/ $(QTDIR)/lib/QtWidgets.framework/Headers
include($$GENERATEDCPP/com_trolltech_qt_uitools/com_trolltech_qt_uitools.pri)
