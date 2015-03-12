#include "qtscriptshell_QXmlLocator.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlLocator::QtScriptShell_QXmlLocator()
    : QXmlLocator() {}

QtScriptShell_QXmlLocator::~QtScriptShell_QXmlLocator() {}

int  QtScriptShell_QXmlLocator::columnNumber() const
{
    QScriptValue _q_function = __qtscript_self.property("columnNumber");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnNumber") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLocator::columnNumber() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QXmlLocator::lineNumber() const
{
    QScriptValue _q_function = __qtscript_self.property("lineNumber");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lineNumber") & QScriptValue::QObjectMember)) {
        qFatal("QXmlLocator::lineNumber() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

