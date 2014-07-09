#ifndef QTSCRIPTSHELL_QKEYEVENT_H
#define QTSCRIPTSHELL_QKEYEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QKeyEvent : public QKeyEvent
{
public:
    QtScriptShell_QKeyEvent(QEvent::Type  type, int  key, Qt::KeyboardModifiers  modifiers, const QString&  text = QString(), bool  autorep = false, ushort  count = 1);
    ~QtScriptShell_QKeyEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QKEYEVENT_H
