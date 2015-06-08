#include "qtscriptshell_QXmlErrorHandler.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qxml.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QXmlParseException)

QtScriptShell_QXmlErrorHandler::QtScriptShell_QXmlErrorHandler()
    : QXmlErrorHandler() {}

QtScriptShell_QXmlErrorHandler::~QtScriptShell_QXmlErrorHandler() {}

bool  QtScriptShell_QXmlErrorHandler::error(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("error");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("error") & QScriptValue::QObjectMember)) {
        qFatal("QXmlErrorHandler::error() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
    }
}

QString  QtScriptShell_QXmlErrorHandler::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        qFatal("QXmlErrorHandler::errorString() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QXmlErrorHandler::fatalError(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("fatalError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fatalError") & QScriptValue::QObjectMember)) {
        qFatal("QXmlErrorHandler::fatalError() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
    }
}

bool  QtScriptShell_QXmlErrorHandler::warning(const QXmlParseException&  exception)
{
    QScriptValue _q_function = __qtscript_self.property("warning");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("warning") & QScriptValue::QObjectMember)) {
        qFatal("QXmlErrorHandler::warning() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, exception)));
    }
}

