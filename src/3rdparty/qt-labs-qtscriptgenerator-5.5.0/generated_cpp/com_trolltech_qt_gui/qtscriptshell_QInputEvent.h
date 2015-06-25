#ifndef QTSCRIPTSHELL_QINPUTEVENT_H
#define QTSCRIPTSHELL_QINPUTEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QInputEvent : public QInputEvent
{
public:
    QtScriptShell_QInputEvent(QEvent::Type  type, Qt::KeyboardModifiers  modifiers = Qt::NoModifier);
    ~QtScriptShell_QInputEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QINPUTEVENT_H
