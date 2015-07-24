#ifndef QTSCRIPTSHELL_QGRAPHICSBLUREFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSBLUREFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsBlurEffect : public QGraphicsBlurEffect
{
public:
    QtScriptShell_QGraphicsBlurEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsBlurEffect();

    QRectF  boundingRectFor(const QRectF&  rect) const;
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void draw(QPainter*  painter);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void sourceChanged(QGraphicsEffect::ChangeFlags  flags);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSBLUREFFECT_H
