#ifndef QTSCRIPTSHELL_MEDIAOBJECT_H
#define QTSCRIPTSHELL_MEDIAOBJECT_H

#include <mediaobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_MediaObject : public Phonon::MediaObject
{
public:
    QtScriptShell_MediaObject(QObject*  parent = 0);
    ~QtScriptShell_MediaObject();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_MEDIAOBJECT_H
