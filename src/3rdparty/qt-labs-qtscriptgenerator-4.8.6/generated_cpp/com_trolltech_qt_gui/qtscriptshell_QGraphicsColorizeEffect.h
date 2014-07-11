#ifndef QTSCRIPTSHELL_QGRAPHICSCOLORIZEEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSCOLORIZEEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsColorizeEffect : public QGraphicsColorizeEffect
{
public:
    QtScriptShell_QGraphicsColorizeEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsColorizeEffect();

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

#endif // QTSCRIPTSHELL_QGRAPHICSCOLORIZEEFFECT_H
