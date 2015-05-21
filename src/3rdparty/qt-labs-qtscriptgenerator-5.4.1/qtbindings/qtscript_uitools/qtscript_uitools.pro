TARGET = qtscript_uitools
include(../qtbindingsbase.pri)
QT += uitools widgets
SOURCES += plugin.cpp
HEADERS += plugin.h
macx {
    INCLUDEPATH += ./include/ ${QTDIR}/lib/QtWidgets.framework/Headers
    # might have to be:
    #INCLUDEPATH += ./include/ $(QTDIR)/lib/QtWidgets.framework/Headers
}
INCLUDEPATH += ./include
include($$GENERATEDCPP/com_trolltech_qt_uitools/com_trolltech_qt_uitools.pri)
