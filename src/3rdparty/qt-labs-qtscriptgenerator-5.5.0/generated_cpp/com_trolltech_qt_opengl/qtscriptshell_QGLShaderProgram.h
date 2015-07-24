#ifndef QTSCRIPTSHELL_QGLSHADERPROGRAM_H
#define QTSCRIPTSHELL_QGLSHADERPROGRAM_H

#include <qglshaderprogram.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGLShaderProgram : public QGLShaderProgram
{
public:
    QtScriptShell_QGLShaderProgram(QObject*  parent = 0);
    QtScriptShell_QGLShaderProgram(const QGLContext*  context, QObject*  parent = 0);
    ~QtScriptShell_QGLShaderProgram();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  link();
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLSHADERPROGRAM_H
