#include "qtscriptshell_QImage.h"

#include <QtScript/QScriptEngine>
#include <QMatrix>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qimage.h>
#include <qiodevice.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qtransform.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPaintEngine*)

QtScriptShell_QImage::QtScriptShell_QImage()
    : QImage() {}

QtScriptShell_QImage::QtScriptShell_QImage(const QImage&  arg__1)
    : QImage(arg__1) {}

QtScriptShell_QImage::QtScriptShell_QImage(const QSize&  size, QImage::Format  format)
    : QImage(size, format) {}

QtScriptShell_QImage::QtScriptShell_QImage(const QString&  fileName, const char*  format)
    : QImage(fileName, format) {}

QtScriptShell_QImage::QtScriptShell_QImage(int  width, int  height, QImage::Format  format)
    : QImage(width, height, format) {}

QtScriptShell_QImage::~QtScriptShell_QImage() {}

int  QtScriptShell_QImage::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QImage::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QImage::metric(QPaintDevice::PaintDeviceMetric  metric) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QImage::metric(metric);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metric)));
    }
}

QPaintEngine*  QtScriptShell_QImage::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        return QImage::paintEngine();
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

