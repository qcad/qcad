#include "qtscriptshell_AbstractStream.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <mediasource.h>
#include <qbytearray.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_AbstractStream::QtScriptShell_AbstractStream()
    : Phonon::StreamInterface() {}

QtScriptShell_AbstractStream::~QtScriptShell_AbstractStream() {}

void QtScriptShell_AbstractStream::endOfData()
{
    QScriptValue _q_function = __qtscript_self.property("endOfData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endOfData") & QScriptValue::QObjectMember)) {
        qFatal("AbstractStream::endOfData() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_AbstractStream::setStreamSeekable(bool  s)
{
    QScriptValue _q_function = __qtscript_self.property("setStreamSeekable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setStreamSeekable") & QScriptValue::QObjectMember)) {
        qFatal("AbstractStream::setStreamSeekable() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, s));
    }
}

void QtScriptShell_AbstractStream::setStreamSize(qint64  newSize)
{
    QScriptValue _q_function = __qtscript_self.property("setStreamSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setStreamSize") & QScriptValue::QObjectMember)) {
        qFatal("AbstractStream::setStreamSize() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, newSize));
    }
}

void QtScriptShell_AbstractStream::writeData(const QByteArray&  data)
{
    QScriptValue _q_function = __qtscript_self.property("writeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("writeData") & QScriptValue::QObjectMember)) {
        qFatal("AbstractStream::writeData() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data));
    }
}

