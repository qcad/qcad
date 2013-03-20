#include "qtscriptshell_QGLPixelBuffer.h"

#include <QtScript/QScriptEngine>
#include <QImage>
#include <QVariant>
#include <qgl.h>
#include <qglpixelbuffer.h>
#include <qimage.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qsize.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPaintEngine*)

QtScriptShell_QGLPixelBuffer::QtScriptShell_QGLPixelBuffer(const QSize&  size, const QGLFormat&  format, QGLWidget*  shareWidget)
    : QGLPixelBuffer(size, format, shareWidget) {}

QtScriptShell_QGLPixelBuffer::QtScriptShell_QGLPixelBuffer(int  width, int  height, const QGLFormat&  format, QGLWidget*  shareWidget)
    : QGLPixelBuffer(width, height, format, shareWidget) {}

QtScriptShell_QGLPixelBuffer::~QtScriptShell_QGLPixelBuffer() {}

int  QtScriptShell_QGLPixelBuffer::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QGLPixelBuffer::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QGLPixelBuffer::metric(QPaintDevice::PaintDeviceMetric  metric) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QGLPixelBuffer::metric(metric);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metric)));
    }
}

QPaintEngine*  QtScriptShell_QGLPixelBuffer::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        return QGLPixelBuffer::paintEngine();
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

