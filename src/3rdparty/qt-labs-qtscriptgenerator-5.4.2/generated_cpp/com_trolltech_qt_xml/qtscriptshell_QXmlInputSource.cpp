#include "qtscriptshell_QXmlInputSource.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlInputSource::QtScriptShell_QXmlInputSource()
    : QXmlInputSource() {}

QtScriptShell_QXmlInputSource::QtScriptShell_QXmlInputSource(QIODevice*  dev)
    : QXmlInputSource(dev) {}

QtScriptShell_QXmlInputSource::~QtScriptShell_QXmlInputSource() {}

QString  QtScriptShell_QXmlInputSource::data() const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QXmlInputSource::data();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QXmlInputSource::fetchData()
{
    QScriptValue _q_function = __qtscript_self.property("fetchData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchData") & QScriptValue::QObjectMember)) {
        QXmlInputSource::fetchData();
    } else {
        _q_function.call(__qtscript_self);
    }
}

QString  QtScriptShell_QXmlInputSource::fromRawData(const QByteArray&  data, bool  beginning)
{
    QScriptValue _q_function = __qtscript_self.property("fromRawData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fromRawData") & QScriptValue::QObjectMember)) {
        return QXmlInputSource::fromRawData(data, beginning);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, beginning)));
    }
}

QChar  QtScriptShell_QXmlInputSource::next()
{
    QScriptValue _q_function = __qtscript_self.property("next");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("next") & QScriptValue::QObjectMember)) {
        return QXmlInputSource::next();
    } else {
        return qscriptvalue_cast<QChar >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QXmlInputSource::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        QXmlInputSource::reset();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlInputSource::setData(const QByteArray&  dat)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        QXmlInputSource::setData(dat);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dat));
    }
}

void QtScriptShell_QXmlInputSource::setData(const QString&  dat)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        QXmlInputSource::setData(dat);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dat));
    }
}

