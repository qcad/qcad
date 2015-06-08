#include "qtscriptshell_QXmlFormatter.h"

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

QtScriptShell_QXmlFormatter::QtScriptShell_QXmlFormatter(const QXmlQuery&  query, QIODevice*  outputDevice)
    : QXmlFormatter(query, outputDevice) {}

QtScriptShell_QXmlFormatter::~QtScriptShell_QXmlFormatter() {}

void QtScriptShell_QXmlFormatter::atomicValue(const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("atomicValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atomicValue") & QScriptValue::QObjectMember)) {
        QXmlFormatter::atomicValue(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlFormatter::attribute(const QXmlName&  name, const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attribute");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attribute") & QScriptValue::QObjectMember)) {
        QXmlFormatter::attribute(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlFormatter::characters(const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)) {
        QXmlFormatter::characters(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlFormatter::comment(const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("comment");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("comment") & QScriptValue::QObjectMember)) {
        QXmlFormatter::comment(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlFormatter::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)) {
        QXmlFormatter::endDocument();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlFormatter::endElement()
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)) {
        QXmlFormatter::endElement();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlFormatter::endOfSequence()
{
    QScriptValue _q_function = __qtscript_self.property("endOfSequence");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endOfSequence") & QScriptValue::QObjectMember)) {
        QXmlFormatter::endOfSequence();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlFormatter::namespaceBinding(const QXmlName&  nb)
{
    QScriptValue _q_function = __qtscript_self.property("namespaceBinding");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("namespaceBinding") & QScriptValue::QObjectMember)) {
        QXmlFormatter::namespaceBinding(nb);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, nb));
    }
}

void QtScriptShell_QXmlFormatter::processingInstruction(const QXmlName&  name, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)) {
        QXmlFormatter::processingInstruction(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlFormatter::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)) {
        QXmlFormatter::startDocument();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlFormatter::startElement(const QXmlName&  name)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)) {
        QXmlFormatter::startElement(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name));
    }
}

void QtScriptShell_QXmlFormatter::startOfSequence()
{
    QScriptValue _q_function = __qtscript_self.property("startOfSequence");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startOfSequence") & QScriptValue::QObjectMember)) {
        QXmlFormatter::startOfSequence();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QXmlFormatter::whitespaceOnly(const QStringRef&  value)
{
    QScriptValue _q_function = __qtscript_self.property("whitespaceOnly");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("whitespaceOnly") & QScriptValue::QObjectMember)) {
        QXmlFormatter::whitespaceOnly(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

