#ifndef QTSCRIPTSHELL_QRESIZEEVENT_H
#define QTSCRIPTSHELL_QRESIZEEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QResizeEvent : public QResizeEvent
{
public:
    QtScriptShell_QResizeEvent(const QSize&  size, const QSize&  oldSize);
    ~QtScriptShell_QResizeEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QRESIZEEVENT_H
