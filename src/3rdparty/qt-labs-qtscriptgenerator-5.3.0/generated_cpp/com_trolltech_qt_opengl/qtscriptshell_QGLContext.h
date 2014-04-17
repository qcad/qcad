#ifndef QTSCRIPTSHELL_QGLCONTEXT_H
#define QTSCRIPTSHELL_QGLCONTEXT_H

#include <qgl.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGLContext : public QGLContext
{
public:
    QtScriptShell_QGLContext(const QGLFormat&  format);
    QtScriptShell_QGLContext(const QGLFormat&  format, QPaintDevice*  device);
    ~QtScriptShell_QGLContext();

    bool  chooseContext(const QGLContext*  shareContext = 0);
    bool  create(const QGLContext*  shareContext = 0);
    void doneCurrent();
    void makeCurrent();
    void swapBuffers() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLCONTEXT_H
