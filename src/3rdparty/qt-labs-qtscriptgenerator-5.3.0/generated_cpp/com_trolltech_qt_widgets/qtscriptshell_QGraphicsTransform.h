#ifndef QTSCRIPTSHELL_QGRAPHICSTRANSFORM_H
#define QTSCRIPTSHELL_QGRAPHICSTRANSFORM_H

#include <qgraphicstransform.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsTransform : public QGraphicsTransform
{
public:
    QtScriptShell_QGraphicsTransform(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsTransform();

    void applyTo(QMatrix4x4*  matrix) const;
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSTRANSFORM_H
