#ifndef QTSCRIPTSHELL_QSEQUENTIALANIMATIONGROUP_H
#define QTSCRIPTSHELL_QSEQUENTIALANIMATIONGROUP_H

#include <qsequentialanimationgroup.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSequentialAnimationGroup : public QSequentialAnimationGroup
{
public:
    QtScriptShell_QSequentialAnimationGroup(QObject*  parent = 0);
    ~QtScriptShell_QSequentialAnimationGroup();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);
    void updateCurrentTime(int  arg__1);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSEQUENTIALANIMATIONGROUP_H
