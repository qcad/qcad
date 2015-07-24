#include "qtscriptshell_QXmlSerializer.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qabstractxmlreceiver.h>
#include <qiodevice.h>
#include <qtextcodec.h>
#include <qxmlname.h>
#include <qxmlquery.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QStringRef)

QtScriptShell_QXmlSerializer::QtScriptShell_QXmlSerializer(const QXmlQuery&  query, QIODevice*  outputDevice)
    : QXmlSerializer(query, outputDevice) {}

QtScriptShell_QXmlSerializer::~QtScriptShell_QXmlSerializer() {}

void QtScriptShell_QXmlSerializer::atomicValue(const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("atomicValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atomicValue") & QScriptValue::QObjectMember)) {
        QXmlSerializer::atomicValue(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlSerializer::attribute(const QXmlName&  name, const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attribute");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attribute") & QScriptValue::QObjectMember)) {
        QXmlSerializer::attribute(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlSerializer::characters(const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)) {
        QXmlSerializer::characters(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlSerializer::comment(const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("comment");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("comment") & QScriptValue::QObjectMember)) {
        QXmlSerializer::comment(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlSerializer::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)) {
        QXmlSerializer::endDocument();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlSerializer::endElement()
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)) {
        QXmlSerializer::endElement();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlSerializer::endOfSequence()
{
    QScriptValue _q_function = __qtscript_self.property("endOfSequence");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endOfSequence") & QScriptValue::QObjectMember)) {
        QXmlSerializer::endOfSequence();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlSerializer::namespaceBinding(const QXmlName&  nb)
{
    QScriptValue _q_function = __qtscript_self.property("namespaceBinding");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("namespaceBinding") & QScriptValue::QObjectMember)) {
        QXmlSerializer::namespaceBinding(nb);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, nb));
    }
}

void QtScriptShell_QXmlSerializer::processingInstruction(const QXmlName&  name, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)) {
        QXmlSerializer::processingInstruction(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlSerializer::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)) {
        QXmlSerializer::startDocument();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlSerializer::startElement(const QXmlName&  name)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)) {
        QXmlSerializer::startElement(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name));
    }
}

void QtScriptShell_QXmlSerializer::startOfSequence()
{
    QScriptValue _q_function = __qtscript_self.property("startOfSequence");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startOfSequence") & QScriptValue::QObjectMember)) {
        QXmlSerializer::startOfSequence();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlSerializer::whitespaceOnly(const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("whitespaceOnly");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("whitespaceOnly") & QScriptValue::QObjectMember)) {
        QXmlSerializer::whitespaceOnly(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

