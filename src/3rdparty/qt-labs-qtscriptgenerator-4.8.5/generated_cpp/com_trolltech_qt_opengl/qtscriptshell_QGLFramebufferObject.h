#ifndef QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H
#define QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H

#include <qglframebufferobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGLFramebufferObject : public QGLFramebufferObject
{
public:
    QtScriptShell_QGLFramebufferObject(const QSize&  size, const QGLFramebufferObjectFormat&  format);
    QtScriptShell_QGLFramebufferObject(int  width, int  height, const QGLFramebufferObjectFormat&  format);
    ~QtScriptShell_QGLFramebufferObject();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H
