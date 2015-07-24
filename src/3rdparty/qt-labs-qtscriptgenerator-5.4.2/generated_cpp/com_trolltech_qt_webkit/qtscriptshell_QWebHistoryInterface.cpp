#include "qtscriptshell_QWebHistoryInterface.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qwebhistoryinterface.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWebHistoryInterface::QtScriptShell_QWebHistoryInterface(QObject*  parent)
    : QWebHistoryInterface(parent) {}

QtScriptShell_QWebHistoryInterface::~QtScriptShell_QWebHistoryInterface() {}

void QtScriptShell_QWebHistoryInterface::addHistoryEntry(const QString&  url)
{
    QScriptValue _q_function = __qtscript_self.property("addHistoryEntry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addHistoryEntry") & QScriptValue::QObjectMember)) {
        qFatal("QWebHistoryInterface::addHistoryEntry() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url));
    }
}

bool  QtScriptShell_QWebHistoryInterface::historyContains(const QString&  url) const
{
    QScriptValue _q_function = __qtscript_self.property("historyContains");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("historyContains") & QScriptValue::QObjectMember)) {
        qFatal("QWebHistoryInterface::historyContains() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
    }
}

