#include "qtscriptshell_QXmlDTDHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlDTDHandler::QtScriptShell_QXmlDTDHandler()
    : QXmlDTDHandler() {}

QtScriptShell_QXmlDTDHandler::~QtScriptShell_QXmlDTDHandler() {}

QString  QtScriptShell_QXmlDTDHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDTDHandler::errorString() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlDTDHandler::notationDecl(const QString&  name, const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("notationDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notationDecl") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDTDHandler::notationDecl() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

bool  QtScriptShell_QXmlDTDHandler::unparsedEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId, const QString&  notationName)
{
    QScriptValue _q_function = __qtscript_self.property("unparsedEntityDecl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unparsedEntityDecl") & QScriptValue::QObjectMember)) {
        qFatal("QXmlDTDHandler::unparsedEntityDecl() is abstract!");
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

