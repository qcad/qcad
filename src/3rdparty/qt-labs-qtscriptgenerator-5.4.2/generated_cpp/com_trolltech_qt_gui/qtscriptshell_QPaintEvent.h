#ifndef QTSCRIPTSHELL_QPAINTEVENT_H
#define QTSCRIPTSHELL_QPAINTEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPaintEvent : public QPaintEvent
{
public:
    QtScriptShell_QPaintEvent(const QRect&  paintRect);
    QtScriptShell_QPaintEvent(const QRegion&  paintRegion);
    ~QtScriptShell_QPaintEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAINTEVENT_H
