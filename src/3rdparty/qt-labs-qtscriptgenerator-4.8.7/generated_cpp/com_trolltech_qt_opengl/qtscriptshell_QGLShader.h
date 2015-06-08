#ifndef QTSCRIPTSHELL_QGLSHADER_H
#define QTSCRIPTSHELL_QGLSHADER_H

#include <qglshaderprogram.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGLShader : public QGLShader
{
public:
    QtScriptShell_QGLShader(QGLShader::ShaderType  type, QObject*  parent = 0);
    QtScriptShell_QGLShader(QGLShader::ShaderType  type, const QGLContext*  context, QObject*  parent = 0);
    ~QtScriptShell_QGLShader();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLSHADER_H
