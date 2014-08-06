#ifndef QTSCRIPTSHELL_QEVENT_H
#define QTSCRIPTSHELL_QEVENT_H

#include <qcoreevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QEvent : public QEvent
{
public:
    QtScriptShell_QEvent(QEvent::Type  type);
    QtScriptShell_QEvent(const QEvent&  other);
    ~QtScriptShell_QEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QEVENT_H
