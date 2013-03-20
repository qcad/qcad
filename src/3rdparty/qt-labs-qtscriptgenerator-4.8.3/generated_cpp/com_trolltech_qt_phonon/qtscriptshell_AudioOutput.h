#ifndef QTSCRIPTSHELL_AUDIOOUTPUT_H
#define QTSCRIPTSHELL_AUDIOOUTPUT_H

#include <audiooutput.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AudioOutput : public Phonon::AudioOutput
{
public:
    QtScriptShell_AudioOutput(Phonon::Category  category, QObject*  parent = 0);
    QtScriptShell_AudioOutput(QObject*  parent = 0);
    ~QtScriptShell_AudioOutput();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_AUDIOOUTPUT_H
