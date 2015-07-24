#ifndef QTSCRIPTSHELL_QABSTRACTANIMATION_H
#define QTSCRIPTSHELL_QABSTRACTANIMATION_H

#include <qabstractanimation.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractAnimation : public QAbstractAnimation
{
public:
    QtScriptShell_QAbstractAnimation(QObject*  parent = 0);
    ~QtScriptShell_QAbstractAnimation();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);
    void updateCurrentTime(int  currentTime);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTANIMATION_H
