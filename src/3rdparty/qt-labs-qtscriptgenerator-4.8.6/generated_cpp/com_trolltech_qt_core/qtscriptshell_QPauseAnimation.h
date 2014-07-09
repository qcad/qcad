#ifndef QTSCRIPTSHELL_QPAUSEANIMATION_H
#define QTSCRIPTSHELL_QPAUSEANIMATION_H

#include <qpauseanimation.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPauseAnimation : public QPauseAnimation
{
public:
    QtScriptShell_QPauseAnimation(QObject*  parent = 0);
    QtScriptShell_QPauseAnimation(int  msecs, QObject*  parent = 0);
    ~QtScriptShell_QPauseAnimation();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    int  duration() const;
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);
    void updateCurrentTime(int  arg__1);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAUSEANIMATION_H
