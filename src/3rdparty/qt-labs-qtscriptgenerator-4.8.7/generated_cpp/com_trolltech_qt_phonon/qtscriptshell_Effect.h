#ifndef QTSCRIPTSHELL_EFFECT_H
#define QTSCRIPTSHELL_EFFECT_H

#include <effect.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_Effect : public Phonon::Effect
{
public:
    QtScriptShell_Effect(const Phonon::EffectDescription&  description, QObject*  parent = 0);
    ~QtScriptShell_Effect();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_EFFECT_H
