#include "qtscriptshell_QXmlSimpleReader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlDTDHandler*)
Q_DECLARE_METATYPE(QXmlContentHandler*)
Q_DECLARE_METATYPE(QXmlDeclHandler*)
Q_DECLARE_METATYPE(QXmlEntityResolver*)
Q_DECLARE_METATYPE(QXmlErrorHandler*)
Q_DECLARE_METATYPE(QXmlLexicalHandler*)
Q_DECLARE_METATYPE(QXmlInputSource)
Q_DECLARE_METATYPE(const QXmlInputSource*)

QtScriptShell_QXmlSimpleReader::QtScriptShell_QXmlSimpleReader()
    : QXmlSimpleReader() {}

QtScriptShell_QXmlSimpleReader::~QtScriptShell_QXmlSimpleReader() {}

QXmlDTDHandler*  QtScriptShell_QXmlSimpleReader::DTDHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("DTDHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("DTDHandler") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::DTDHandler();
    } else {
        return qscriptvalue_cast<QXmlDTDHandler* >(_q_function.call(__qtscript_self));
    }
}

QXmlContentHandler*  QtScriptShell_QXmlSimpleReader::contentHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("contentHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contentHandler") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::contentHandler();
    } else {
        return qscriptvalue_cast<QXmlContentHandler* >(_q_function.call(__qtscript_self));
    }
}

QXmlDeclHandler*  QtScriptShell_QXmlSimpleReader::declHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("declHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("declHandler") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::declHandler();
    } else {
        return qscriptvalue_cast<QXmlDeclHandler* >(_q_function.call(__qtscript_self));
    }
}

QXmlEntityResolver*  QtScriptShell_QXmlSimpleReader::entityResolver() const
{
    QScriptValue _q_function = __qtscript_self.property("entityResolver");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("entityResolver") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::entityResolver();
    } else {
        return qscriptvalue_cast<QXmlEntityResolver* >(_q_function.call(__qtscript_self));
    }
}

QXmlErrorHandler*  QtScriptShell_QXmlSimpleReader::errorHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("errorHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorHandler") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::errorHandler();
    } else {
        return qscriptvalue_cast<QXmlErrorHandler* >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlSimpleReader::feature(const QString&  name, bool*  ok) const
{
    QScriptValue _q_function = __qtscript_self.property("feature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("feature") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::feature(name, ok);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_QXmlSimpleReader::hasFeature(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("hasFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasFeature") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::hasFeature(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

bool  QtScriptShell_QXmlSimpleReader::hasProperty(const QString&  name) const
{
    QScriptValue _q_function = __qtscript_self.property("hasProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasProperty") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::hasProperty(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

QXmlLexicalHandler*  QtScriptShell_QXmlSimpleReader::lexicalHandler() const
{
    QScriptValue _q_function = __qtscript_self.property("lexicalHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lexicalHandler") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::lexicalHandler();
    } else {
        return qscriptvalue_cast<QXmlLexicalHandler* >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlSimpleReader::parse(const QXmlInputSource&  input)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::parse(input);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, input)));
    }
}

bool  QtScriptShell_QXmlSimpleReader::parse(const QXmlInputSource*  input)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::parse(*input);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QXmlInputSource *>(input))));
    }
}

bool  QtScriptShell_QXmlSimpleReader::parse(const QXmlInputSource*  input, bool  incremental)
{
    QScriptValue _q_function = __qtscript_self.property("parse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parse") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::parse(input, incremental);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QXmlInputSource *>(input))
            << qScriptValueFromValue(_q_engine, incremental)));
    }
}

bool  QtScriptShell_QXmlSimpleReader::parseContinue()
{
    QScriptValue _q_function = __qtscript_self.property("parseContinue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parseContinue") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::parseContinue();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void*  QtScriptShell_QXmlSimpleReader::property(const QString&  name, bool*  ok) const
{
    QScriptValue _q_function = __qtscript_self.property("property");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("property") & QScriptValue::QObjectMember)) {
        return QXmlSimpleReader::property(name, ok);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<void* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

void QtScriptShell_QXmlSimpleReader::setContentHandler(QXmlContentHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setContentHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setContentHandler") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setContentHandler(handler);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
    }
}

void QtScriptShell_QXmlSimpleReader::setDTDHandler(QXmlDTDHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setDTDHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDTDHandler") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setDTDHandler(handler);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
    }
}

void QtScriptShell_QXmlSimpleReader::setDeclHandler(QXmlDeclHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setDeclHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDeclHandler") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setDeclHandler(handler);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
    }
}

void QtScriptShell_QXmlSimpleReader::setEntityResolver(QXmlEntityResolver*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setEntityResolver");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEntityResolver") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setEntityResolver(handler);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
    }
}

void QtScriptShell_QXmlSimpleReader::setErrorHandler(QXmlErrorHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setErrorHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setErrorHandler") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setErrorHandler(handler);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
    }
}

void QtScriptShell_QXmlSimpleReader::setFeature(const QString&  name, bool  value)
{
    QScriptValue _q_function = __qtscript_self.property("setFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFeature") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setFeature(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

void QtScriptShell_QXmlSimpleReader::setLexicalHandler(QXmlLexicalHandler*  handler)
{
    QScriptValue _q_function = __qtscript_self.property("setLexicalHandler");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLexicalHandler") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setLexicalHandler(handler);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, handler));
    }
}

void QtScriptShell_QXmlSimpleReader::setProperty(const QString&  name, void*  value)
{
    QScriptValue _q_function = __qtscript_self.property("setProperty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setProperty") & QScriptValue::QObjectMember)) {
        QXmlSimpleReader::setProperty(name, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value));
    }
}

