#ifndef QTSCRIPTSHELL_QGRAPHICSITEMANIMATION_H
#define QTSCRIPTSHELL_QGRAPHICSITEMANIMATION_H

#include <qgraphicsitemanimation.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsItemAnimation : public QGraphicsItemAnimation
{
public:
    QtScriptShell_QGraphicsItemAnimation(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsItemAnimation();

    void afterAnimationStep(qreal  step);
    void beforeAnimationStep(qreal  step);
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSITEMANIMATION_H
