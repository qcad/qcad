#ifndef QTSCRIPTSHELL_QSVGRENDERER_H
#define QTSCRIPTSHELL_QSVGRENDERER_H

#include <qsvgrenderer.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSvgRenderer : public QSvgRenderer
{
public:
    QtScriptShell_QSvgRenderer(QObject*  parent = 0);
    QtScriptShell_QSvgRenderer(QXmlStreamReader*  contents, QObject*  parent = 0);
    QtScriptShell_QSvgRenderer(const QByteArray&  contents, QObject*  parent = 0);
    QtScriptShell_QSvgRenderer(const QString&  filename, QObject*  parent = 0);
    ~QtScriptShell_QSvgRenderer();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSVGRENDERER_H
