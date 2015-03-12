#ifndef QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H
#define QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H

#include <qglframebufferobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGLFramebufferObject : public QGLFramebufferObject
{
public:
    QtScriptShell_QGLFramebufferObject(const QSize&  size, const QGLFramebufferObjectFormat&  format);
    QtScriptShell_QGLFramebufferObject(int  width, int  height, const QGLFramebufferObjectFormat&  format);
    ~QtScriptShell_QGLFramebufferObject();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLFRAMEBUFFEROBJECT_H
