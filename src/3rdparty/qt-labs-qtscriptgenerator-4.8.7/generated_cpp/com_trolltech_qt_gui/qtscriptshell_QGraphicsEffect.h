#ifndef QTSCRIPTSHELL_QGRAPHICSEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsEffect : public QGraphicsEffect
{
public:
    QtScriptShell_QGraphicsEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsEffect();

    QRectF  boundingRectFor(const QRectF&  sourceRect) const;
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void draw(QPainter*  painter);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void sourceChanged(QGraphicsEffect::ChangeFlags  flags);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSEFFECT_H
