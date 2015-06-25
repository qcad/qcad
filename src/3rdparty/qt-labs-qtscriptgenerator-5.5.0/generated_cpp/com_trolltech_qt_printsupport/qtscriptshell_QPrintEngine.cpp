#include "qtscriptshell_QPrintEngine.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPrinter::PrinterState)
Q_DECLARE_METATYPE(QPrintEngine::PrintEnginePropertyKey)

QtScriptShell_QPrintEngine::QtScriptShell_QPrintEngine()
    : QPrintEngine() {}

QtScriptShell_QPrintEngine::~QtScriptShell_QPrintEngine() {}

bool  QtScriptShell_QPrintEngine::abort()
{
    QScriptValue _q_function = __qtscript_self.property("abort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("abort") & QScriptValue::QObjectMember)) {
        qFatal("QPrintEngine::abort() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QPrintEngine::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        qFatal("QPrintEngine::metric() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QPrintEngine::newPage()
{
    QScriptValue _q_function = __qtscript_self.property("newPage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("newPage") & QScriptValue::QObjectMember)) {
        qFatal("QPrintEngine::newPage() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QPrinter::PrinterState  QtScriptShell_QPrintEngine::printerState() const
{
    QScriptValue _q_function = __qtscript_self.property("printerState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("printerState") & QScriptValue::QObjectMember)) {
        qFatal("QPrintEngine::printerState() is abstract!");
    } else {
        return qscriptvalue_cast<QPrinter::PrinterState >(_q_function.call(__qtscript_self));
    }
}

QVariant  QtScriptShell_QPrintEngine::property(QPrintEngine::PrintEnginePropertyKey  key) const
{
    QScriptValue _q_function = __qtscript_self.property("property");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("property") & QScriptValue::QObjectMember)) {
        qFatal("QPrintEngine::property() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, key)));
    }
}

void QtScriptShell_QPrintEngine::setProperty(QPrintEngine::PrintEnginePropertyKey  key, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setProperty") & QScriptValue::QObjectMember)) {
        qFatal("QPrintEngine::setProperty() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, key)
            << qScriptValueFromValue(_q_engine, value));
    }
}

