#ifndef QTSCRIPTSHELL_QMOVEEVENT_H
#define QTSCRIPTSHELL_QMOVEEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QMoveEvent : public QMoveEvent
{
public:
    QtScriptShell_QMoveEvent(const QPoint&  pos, const QPoint&  oldPos);
    ~QtScriptShell_QMoveEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOVEEVENT_H
