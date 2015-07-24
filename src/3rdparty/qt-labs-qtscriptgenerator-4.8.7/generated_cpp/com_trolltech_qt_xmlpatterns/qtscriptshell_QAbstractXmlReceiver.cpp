#include "qtscriptshell_QAbstractXmlReceiver.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qabstractxmlreceiver.h>
#include <qxmlname.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QStringRef)

QtScriptShell_QAbstractXmlReceiver::QtScriptShell_QAbstractXmlReceiver()
    : QAbstractXmlReceiver() {}

QtScriptShell_QAbstractXmlReceiver::~QtScriptShell_QAbstractXmlReceiver() {}

void QtScriptShell_QAbstractXmlReceiver::atomicValue(const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("atomicValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atomicValue") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::atomicValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QAbstractXmlReceiver::attribute(const QXmlName&  name, const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attribute");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attribute") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::attribute() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QAbstractXmlReceiver::characters(const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::characters() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QAbstractXmlReceiver::comment(const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("comment");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("comment") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::comment() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QAbstractXmlReceiver::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::endDocument() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QAbstractXmlReceiver::endElement()
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::endElement() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QAbstractXmlReceiver::endOfSequence()
{
    QScriptValue _q_function = __qtscript_self.property("endOfSequence");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endOfSequence") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::endOfSequence() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QAbstractXmlReceiver::namespaceBinding(const QXmlName&  name)
{
    QScriptValue _q_function = __qtscript_self.property("namespaceBinding");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("namespaceBinding") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::namespaceBinding() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name));
    }
}

void QtScriptShell_QAbstractXmlReceiver::processingInstruction(const QXmlName&  target, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::processingInstruction() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, target)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QAbstractXmlReceiver::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::startDocument() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QAbstractXmlReceiver::startElement(const QXmlName&  name)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::startElement() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name));
    }
}

void QtScriptShell_QAbstractXmlReceiver::startOfSequence()
{
    QScriptValue _q_function = __qtscript_self.property("startOfSequence");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startOfSequence") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractXmlReceiver::startOfSequence() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QAbstractXmlReceiver::whitespaceOnly(const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("whitespaceOnly");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("whitespaceOnly") & QScriptValue::QObjectMember)) {
        QAbstractXmlReceiver::whitespaceOnly(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

