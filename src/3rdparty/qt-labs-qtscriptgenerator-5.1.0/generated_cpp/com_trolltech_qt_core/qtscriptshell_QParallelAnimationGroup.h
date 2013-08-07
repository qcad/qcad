#ifndef QTSCRIPTSHELL_QPARALLELANIMATIONGROUP_H
#define QTSCRIPTSHELL_QPARALLELANIMATIONGROUP_H

#include <qparallelanimationgroup.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QParallelAnimationGroup : public QParallelAnimationGroup
{
public:
    QtScriptShell_QParallelAnimationGroup(QObject*  parent = 0);
    ~QtScriptShell_QParallelAnimationGroup();

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

#endif // QTSCRIPTSHELL_QPARALLELANIMATIONGROUP_H
