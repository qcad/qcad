#include "qtscriptshell_QHttpResponseHeader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qhttp.h>
#include <qlist.h>
#include <qpair.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QHttpResponseHeader::QtScriptShell_QHttpResponseHeader()
    : QHttpResponseHeader() {}

QtScriptShell_QHttpResponseHeader::QtScriptShell_QHttpResponseHeader(const QHttpResponseHeader&  header)
    : QHttpResponseHeader(header) {}

QtScriptShell_QHttpResponseHeader::QtScriptShell_QHttpResponseHeader(const QString&  str)
    : QHttpResponseHeader(str) {}

QtScriptShell_QHttpResponseHeader::QtScriptShell_QHttpResponseHeader(int  code, const QString&  text, int  majorVer, int  minorVer)
    : QHttpResponseHeader(code, text, majorVer, minorVer) {}

QtScriptShell_QHttpResponseHeader::~QtScriptShell_QHttpResponseHeader() {}

int  QtScriptShell_QHttpResponseHeader::majorVersion() const
{
    QScriptValue _q_function = __qtscript_self.property("majorVersion");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("majorVersion") & QScriptValue::QObjectMember)) {
        return QHttpResponseHeader::majorVersion();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QHttpResponseHeader::minorVersion() const
{
    QScriptValue _q_function = __qtscript_self.property("minorVersion");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minorVersion") & QScriptValue::QObjectMember)) {
        return QHttpResponseHeader::minorVersion();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QHttpResponseHeader::parseLine(const QString&  line, int  number)
{
    QScriptValue _q_function = __qtscript_self.property("parseLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parseLine") & QScriptValue::QObjectMember)) {
        return QHttpResponseHeader::parseLine(line, number);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, line)
            << qScriptValueFromValue(_q_engine, number)));
    }
}

QString  QtScriptShell_QHttpResponseHeader::toString() const
{
    QScriptValue _q_function = __qtscript_self.property("toString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("toString") & QScriptValue::QObjectMember)) {
        return QHttpResponseHeader::toString();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

