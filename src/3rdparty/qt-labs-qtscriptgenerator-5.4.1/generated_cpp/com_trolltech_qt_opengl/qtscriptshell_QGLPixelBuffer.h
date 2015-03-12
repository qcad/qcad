#ifndef QTSCRIPTSHELL_QGLPIXELBUFFER_H
#define QTSCRIPTSHELL_QGLPIXELBUFFER_H

#include <qglpixelbuffer.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGLPixelBuffer : public QGLPixelBuffer
{
public:
    QtScriptShell_QGLPixelBuffer(const QSize&  size, const QGLFormat&  format = QGLFormat::defaultFormat(), QGLWidget*  shareWidget = 0);
    QtScriptShell_QGLPixelBuffer(int  width, int  height, const QGLFormat&  format = QGLFormat::defaultFormat(), QGLWidget*  shareWidget = 0);
    ~QtScriptShell_QGLPixelBuffer();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLPIXELBUFFER_H
