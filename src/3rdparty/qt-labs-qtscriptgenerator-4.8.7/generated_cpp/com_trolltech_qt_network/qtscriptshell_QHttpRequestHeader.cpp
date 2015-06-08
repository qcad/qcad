#include "qtscriptshell_QHttpRequestHeader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qhttp.h>
#include <qlist.h>
#include <qpair.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QHttpRequestHeader::QtScriptShell_QHttpRequestHeader()
    : QHttpRequestHeader() {}

QtScriptShell_QHttpRequestHeader::QtScriptShell_QHttpRequestHeader(const QHttpRequestHeader&  header)
    : QHttpRequestHeader(header) {}

QtScriptShell_QHttpRequestHeader::QtScriptShell_QHttpRequestHeader(const QString&  method, const QString&  path, int  majorVer, int  minorVer)
    : QHttpRequestHeader(method, path, majorVer, minorVer) {}

QtScriptShell_QHttpRequestHeader::QtScriptShell_QHttpRequestHeader(const QString&  str)
    : QHttpRequestHeader(str) {}

QtScriptShell_QHttpRequestHeader::~QtScriptShell_QHttpRequestHeader() {}

int  QtScriptShell_QHttpRequestHeader::majorVersion() const
{
    QScriptValue _q_function = __qtscript_self.property("majorVersion");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("majorVersion") & QScriptValue::QObjectMember)) {
        return QHttpRequestHeader::majorVersion();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QHttpRequestHeader::minorVersion() const
{
    QScriptValue _q_function = __qtscript_self.property("minorVersion");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minorVersion") & QScriptValue::QObjectMember)) {
        return QHttpRequestHeader::minorVersion();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QHttpRequestHeader::parseLine(const QString&  line, int  number)
{
    QScriptValue _q_function = __qtscript_self.property("parseLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parseLine") & QScriptValue::QObjectMember)) {
        return QHttpRequestHeader::parseLine(line, number);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, line)
            << qScriptValueFromValue(_q_engine, number)));
    }
}

QString  QtScriptShell_QHttpRequestHeader::toString() const
{
    QScriptValue _q_function = __qtscript_self.property("toString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("toString") & QScriptValue::QObjectMember)) {
        return QHttpRequestHeader::toString();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

