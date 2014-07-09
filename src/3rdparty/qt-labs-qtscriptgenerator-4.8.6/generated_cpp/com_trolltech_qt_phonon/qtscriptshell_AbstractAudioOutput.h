#ifndef QTSCRIPTSHELL_ABSTRACTAUDIOOUTPUT_H
#define QTSCRIPTSHELL_ABSTRACTAUDIOOUTPUT_H

#include <abstractaudiooutput.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractAudioOutput : public Phonon::AbstractAudioOutput
{
public:
    ~QtScriptShell_AbstractAudioOutput();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTAUDIOOUTPUT_H
