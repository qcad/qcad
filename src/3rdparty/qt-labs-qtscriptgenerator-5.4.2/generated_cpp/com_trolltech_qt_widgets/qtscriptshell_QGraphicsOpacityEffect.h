#ifndef QTSCRIPTSHELL_QGRAPHICSOPACITYEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSOPACITYEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsOpacityEffect : public QGraphicsOpacityEffect
{
public:
    QtScriptShell_QGraphicsOpacityEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsOpacityEffect();

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

#endif // QTSCRIPTSHELL_QGRAPHICSOPACITYEFFECT_H
