#ifndef QTSCRIPTSHELL_QPROPERTYANIMATION_H
#define QTSCRIPTSHELL_QPROPERTYANIMATION_H

#include <qpropertyanimation.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPropertyAnimation : public QPropertyAnimation
{
public:
    QtScriptShell_QPropertyAnimation(QObject*  parent = 0);
    QtScriptShell_QPropertyAnimation(QObject*  target, const QByteArray&  propertyName, QObject*  parent = 0);
    ~QtScriptShell_QPropertyAnimation();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QVariant  interpolated(const QVariant&  from, const QVariant&  to, qreal  progress) const;
    void timerEvent(QTimerEvent*  arg__1);
    void updateCurrentTime(int  arg__1);
    void updateCurrentValue(const QVariant&  value);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPROPERTYANIMATION_H
