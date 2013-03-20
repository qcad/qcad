#ifndef QTSCRIPTSHELL_MEDIACONTROLLER_H
#define QTSCRIPTSHELL_MEDIACONTROLLER_H

#include <mediacontroller.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_MediaController : public Phonon::MediaController
{
public:
    QtScriptShell_MediaController(Phonon::MediaObject*  parent);
    ~QtScriptShell_MediaController();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_MEDIACONTROLLER_H
