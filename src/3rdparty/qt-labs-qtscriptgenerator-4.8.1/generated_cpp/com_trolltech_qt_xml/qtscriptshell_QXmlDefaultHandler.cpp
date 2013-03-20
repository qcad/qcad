#include "qtscriptshell_QXmlDefaultHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlParseException)
Q_DECLARE_METATYPE(QXmlInputSource*)
Q_DECLARE_METATYPE(QXmlLocator*)
Q_DECLARE_METATYPE(QXmlAttributes)

QtScriptShell_QXmlDefaultHandler::QtScriptShell_QXmlDefaultHandler()
    : QXmlDefaultHandler() {}

QtScriptShell_QXmlDefaultHandler::~QtScriptShell_QXmlDefaultHandler() {}

bool  QtScriptShell_QXmlDefaultHandler::attributeDecl(const QString&  eName, const QString&  aName, const QString&  type, const QString&  valueDefault, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attributeDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributeDecl") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::attributeDecl(eName, aName, type, valueDefault, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, eName)
            << qScriptValueFromValue(_q_engine, aName)
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, valueDefault)
            << qScriptValueFromValue(_q_engine, value)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::characters(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("characters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("characters") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::characters(ch);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::comment(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("comment");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("comment") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::comment(ch);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endCDATA()
{
    QScriptValue _q_function = __qtscript_self.property("endCDATA");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endCDATA") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::endCDATA();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endDTD()
{
    QScriptValue _q_function = __qtscript_self.property("endDTD");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDTD") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::endDTD();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endDocument()
{
    QScriptValue _q_function = __qtscript_self.property("endDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDocument") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::endDocument();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName)
{
    QScriptValue _q_function = __qtscript_self.property("endElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endElement") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::endElement(namespaceURI, localName, qName);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, namespaceURI)
            << qScriptValueFromValue(_q_engine, localName)
            << qScriptValueFromValue(_q_engine, qName)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("endEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endEntity") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::endEntity(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::endPrefixMapping(const QString&  prefix)
{
    QScriptValue _q_function = __qtscript_self.property("endPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endPrefixMapping") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::endPrefixMapping(prefix);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, prefix)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::error(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("error");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("error") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::error(exception);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
    }
}

QString  QtScriptShell_QXmlDefaultHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::errorString();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::externalEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("externalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("externalEntityDecl") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::externalEntityDecl(name, publicId, systemId);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::fatalError(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("fatalError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fatalError") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::fatalError(exception);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::ignorableWhitespace(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("ignorableWhitespace");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("ignorableWhitespace") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::ignorableWhitespace(ch);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::internalEntityDecl(const QString&  name, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("internalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("internalEntityDecl") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::internalEntityDecl(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::notationDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("notationDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notationDecl") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::notationDecl(name, publicId, systemId);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::processingInstruction(const QString&  target, const QString&  data)
{
    QScriptValue _q_function = __qtscript_self.property("processingInstruction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("processingInstruction") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::processingInstruction(target, data);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, target)
            << qScriptValueFromValue(_q_engine, data)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::resolveEntity(const QString&  publicId, const QString&  systemId, QXmlInputSource*&  ret)
{
    QScriptValue _q_function = __qtscript_self.property("resolveEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveEntity") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::resolveEntity(publicId, systemId, ret);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)
            << qScriptValueFromValue(_q_engine, ret)));
    }
}

void QtScriptShell_QXmlDefaultHandler::setDocumentLocator(QXmlLocator*  locator)
{
    QScriptValue _q_function = __qtscript_self.property("setDocumentLocator");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDocumentLocator") & QScriptValue::QObjectMember)) {
        QXmlDefaultHandler::setDocumentLocator(locator);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, locator));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::skippedEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("skippedEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("skippedEntity") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::skippedEntity(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startCDATA()
{
    QScriptValue _q_function = __qtscript_self.property("startCDATA");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startCDATA") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::startCDATA();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startDTD(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("startDTD");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDTD") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::startDTD(name, publicId, systemId);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startDocument()
{
    QScriptValue _q_function = __qtscript_self.property("startDocument");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDocument") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::startDocument();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName, const QXmlAttributes&  atts)
{
    QScriptValue _q_function = __qtscript_self.property("startElement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startElement") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::startElement(namespaceURI, localName, qName, atts);
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

bool  QtScriptShell_QXmlDefaultHandler::startEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("startEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startEntity") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::startEntity(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::startPrefixMapping(const QString&  prefix, const QString&  uri)
{
    QScriptValue _q_function = __qtscript_self.property("startPrefixMapping");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startPrefixMapping") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::startPrefixMapping(prefix, uri);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, prefix)
            << qScriptValueFromValue(_q_engine, uri)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::unparsedEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId, const QString&  notationName)
{
    QScriptValue _q_function = __qtscript_self.property("unparsedEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unparsedEntityDecl") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::unparsedEntityDecl(name, publicId, systemId, notationName);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)
            << qScriptValueFromValue(_q_engine, notationName)));
    }
}

bool  QtScriptShell_QXmlDefaultHandler::warning(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("warning");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("warning") & QScriptValue::QObjectMember)) {
        return QXmlDefaultHandler::warning(exception);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
    }
}

