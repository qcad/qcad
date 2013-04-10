#ifndef QTSCRIPTSHELL_VOLUMEFADEREFFECT_H
#define QTSCRIPTSHELL_VOLUMEFADEREFFECT_H

#include <volumefadereffect.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_VolumeFaderEffect : public Phonon::VolumeFaderEffect
{
public:
    QtScriptShell_VolumeFaderEffect(QObject*  parent = 0);
    ~QtScriptShell_VolumeFaderEffect();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_VOLUMEFADEREFFECT_H
