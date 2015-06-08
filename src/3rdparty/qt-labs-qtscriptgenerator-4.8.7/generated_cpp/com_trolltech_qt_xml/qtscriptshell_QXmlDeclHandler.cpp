#include "qtscriptshell_QXmlDeclHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlDeclHandler::QtScriptShell_QXmlDeclHandler()
    : QXmlDeclHandler() {}

QtScriptShell_QXmlDeclHandler::~QtScriptShell_QXmlDeclHandler() {}

bool  QtScriptShell_QXmlDeclHandler::attributeDecl(const QString&  eName, const QString&  aName, const QString&  type, const QString&  valueDefault, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("attributeDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("attributeDecl") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDeclHandler::attributeDecl() is abstract!");
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

QString  QtScriptShell_QXmlDeclHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDeclHandler::errorString() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDeclHandler::externalEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("externalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("externalEntityDecl") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDeclHandler::externalEntityDecl() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

bool  QtScriptShell_QXmlDeclHandler::internalEntityDecl(const QString&  name, const QString&  value)
{
    QScriptValue _q_function = __qtscript_self.property("internalEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("internalEntityDecl") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDeclHandler::internalEntityDecl() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, value)));
    }
}

