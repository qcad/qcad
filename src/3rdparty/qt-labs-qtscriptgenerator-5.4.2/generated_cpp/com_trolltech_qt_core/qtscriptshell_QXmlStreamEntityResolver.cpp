#include "qtscriptshell_QXmlStreamEntityResolver.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlStreamEntityResolver::QtScriptShell_QXmlStreamEntityResolver()
    : QXmlStreamEntityResolver() {}

QtScriptShell_QXmlStreamEntityResolver::~QtScriptShell_QXmlStreamEntityResolver() {}

QString  QtScriptShell_QXmlStreamEntityResolver::resolveEntity(const QString&  publicId, const QString&  systemId)
{
    QScriptValue _q_function = __qtscript_self.property("resolveEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveEntity") & QScriptValue::QObjectMember)) {
        return QXmlStreamEntityResolver::resolveEntity(publicId, systemId);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, publicId)
            << qScriptValueFromValue(_q_engine, systemId)));
    }
}

QString  QtScriptShell_QXmlStreamEntityResolver::resolveUndeclaredEntity(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("resolveUndeclaredEntity");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resolveUndeclaredEntity") & QScriptValue::QObjectMember)) {
        return QXmlStreamEntityResolver::resolveUndeclaredEntity(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

