#include "qtscriptshell_QHttpHeader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qlist.h>
#include <qpair.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QHttpHeader::QtScriptShell_QHttpHeader()
    : QHttpHeader() {}

QtScriptShell_QHttpHeader::QtScriptShell_QHttpHeader(const QString&  str)
    : QHttpHeader(str) {}

QtScriptShell_QHttpHeader::~QtScriptShell_QHttpHeader() {}

int  QtScriptShell_QHttpHeader::majorVersion() const
{
    QScriptValue _q_function = __qtscript_self.property("majorVersion");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("majorVersion") & QScriptValue::QObjectMember)) {
        qFatal("QHttpHeader::majorVersion() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QHttpHeader::minorVersion() const
{
    QScriptValue _q_function = __qtscript_self.property("minorVersion");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minorVersion") & QScriptValue::QObjectMember)) {
        qFatal("QHttpHeader::minorVersion() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QHttpHeader::parseLine(const QString&  line, int  number)
{
    QScriptValue _q_function = __qtscript_self.property("parseLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parseLine") & QScriptValue::QObjectMember)) {
        return QHttpHeader::parseLine(line, number);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, line)
            << qScriptValueFromValue(_q_engine, number)));
    }
}

QString  QtScriptShell_QHttpHeader::toString() const
{
    QScriptValue _q_function = __qtscript_self.property("toString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("toString") & QScriptValue::QObjectMember)) {
        return QHttpHeader::toString();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

