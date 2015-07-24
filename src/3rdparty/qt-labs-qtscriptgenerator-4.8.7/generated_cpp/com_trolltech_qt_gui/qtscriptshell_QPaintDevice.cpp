#include "qtscriptshell_QPaintDevice.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qpaintdevice.h>
#include <qpaintengine.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPaintEngine*)

QtScriptShell_QPaintDevice::QtScriptShell_QPaintDevice()
    : QPaintDevice() {}

QtScriptShell_QPaintDevice::~QtScriptShell_QPaintDevice() {}

int  QtScriptShell_QPaintDevice::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QPaintDevice::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QPaintDevice::metric(QPaintDevice::PaintDeviceMetric  metric) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QPaintDevice::metric(metric);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metric)));
    }
}

QPaintEngine*  QtScriptShell_QPaintDevice::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        qFatal("QPaintDevice::paintEngine() is abstract!");
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

