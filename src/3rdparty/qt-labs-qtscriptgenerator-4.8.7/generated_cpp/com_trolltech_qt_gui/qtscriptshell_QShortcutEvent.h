#ifndef QTSCRIPTSHELL_QSHORTCUTEVENT_H
#define QTSCRIPTSHELL_QSHORTCUTEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QShortcutEvent : public QShortcutEvent
{
public:
    QtScriptShell_QShortcutEvent(const QKeySequence&  key, int  id, bool  ambiguous = false);
    ~QtScriptShell_QShortcutEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSHORTCUTEVENT_H
