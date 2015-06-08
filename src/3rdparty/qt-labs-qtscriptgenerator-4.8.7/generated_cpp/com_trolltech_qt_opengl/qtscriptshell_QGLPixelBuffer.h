#ifndef QTSCRIPTSHELL_QGLPIXELBUFFER_H
#define QTSCRIPTSHELL_QGLPIXELBUFFER_H

#include <qglpixelbuffer.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGLPixelBuffer : public QGLPixelBuffer
{
public:
    QtScriptShell_QGLPixelBuffer(const QSize&  size, const QGLFormat&  format = QGLFormat::defaultFormat(), QGLWidget*  shareWidget = 0);
    QtScriptShell_QGLPixelBuffer(int  width, int  height, const QGLFormat&  format = QGLFormat::defaultFormat(), QGLWidget*  shareWidget = 0);
    ~QtScriptShell_QGLPixelBuffer();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLPIXELBUFFER_H
