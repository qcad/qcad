#include "qtscriptshell_QXmlContentHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlLocator*)
Q_DECLARE_METATYPE(QXmlAttributes)

QtScriptShell_QXmlContentHandler::QtScriptShell_QXmlContentHandler()
    : QXmlContentHandler() {}

QtScriptShell_QXmlContentHandler::~QtScriptShell_QXmlContentHandler() {}

bool  QtScriptShell_QXmlContentHandler::characters(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::characters() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
    }
}

bool  QtScriptShell_QXmlContentHandler::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::endDocument() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlContentHandler::endElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName)
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::endElement() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, namespaceURI)
            << qScriptValueFromValue(_q_engine, localName)
            << qScriptValueFromValue(_q_engine, qName)));
    }
}

bool  QtScriptShell_QXmlContentHandler::endPrefixMapping(const QString&  prefix)
{
    QScriptValue _q_function = __qtscript_self.property("endPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endPrefixMapping") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::endPrefixMapping() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, prefix)));
    }
}

QString  QtScriptShell_QXmlContentHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::errorString() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlContentHandler::ignorableWhitespace(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("ignorableWhitespace");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("ignorableWhitespace") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::ignorableWhitespace() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
    }
}

bool  QtScriptShell_QXmlContentHandler::processingInstruction(const QString&  target, const QString&  data)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::processingInstruction() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, target)
            << qScriptValueFromValue(_q_engine, data)));
    }
}

void QtScriptShell_QXmlContentHandler::setDocumentLocator(QXmlLocator*  locator)
{
    QScriptValue _q_function = __qtscript_self.property("setDocumentLocator");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDocumentLocator") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::setDocumentLocator() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, locator));
    }
}

bool  QtScriptShell_QXmlContentHandler::skippedEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("skippedEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("skippedEntity") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::skippedEntity() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_QXmlContentHandler::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::startDocument() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlContentHandler::startElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName, const QXmlAttributes&  atts)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::startElement() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, namespaceURI)
            << qScriptValueFromValue(_q_engine, localName)
            << qScriptValueFromValue(_q_engine, qName)
            << qScriptValueFromValue(_q_engine, atts)));
    }
}

bool  QtScriptShell_QXmlContentHandler::startPrefixMapping(const QString&  prefix, const QString&  uri)
{
    QScriptValue _q_function = __qtscript_self.property("startPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startPrefixMapping") & QScriptValue::QObjectMember)) {
        qFatal("QXmlContentHandler::startPrefixMapping() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, prefix)
            << qScriptValueFromValue(_q_engine, uri)));
    }
}

