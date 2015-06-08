#include "qtscriptshell_QXmlLexicalHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlLexicalHandler::QtScriptShell_QXmlLexicalHandler()
    : QXmlLexicalHandler() {}

QtScriptShell_QXmlLexicalHandler::~QtScriptShell_QXmlLexicalHandler() {}

bool  QtScriptShell_QXmlLexicalHandler::comment(const QString&  ch)
{
    QScriptValue _q_function = __qtscript_self.property("comment");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("comment") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::comment() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ch)));
    }
}

bool  QtScriptShell_QXmlLexicalHandler::endCDATA()
{
    QScriptValue _q_function = __qtscript_self.property("endCDATA");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endCDATA") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::endCDATA() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlLexicalHandler::endDTD()
{
    QScriptValue _q_function = __qtscript_self.property("endDTD");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endDTD") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::endDTD() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlLexicalHandler::endEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("endEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("endEntity") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::endEntity() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

QString  QtScriptShell_QXmlLexicalHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::errorString() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlLexicalHandler::startCDATA()
{
    QScriptValue _q_function = __qtscript_self.property("startCDATA");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startCDATA") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::startCDATA() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlLexicalHandler::startDTD(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("startDTD");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDTD") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::startDTD() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

bool  QtScriptShell_QXmlLexicalHandler::startEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("startEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startEntity") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLexicalHandler::startEntity() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

