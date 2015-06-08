#ifndef QTSCRIPTSHELL_QSOUND_H
#define QTSCRIPTSHELL_QSOUND_H

#include <qsound.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSound : public QSound
{
public:
    QtScriptShell_QSound(const QString&  filename, QObject*  parent = 0);
    ~QtScriptShell_QSound();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSOUND_H
