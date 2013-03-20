#include "qtscriptshell_QNetworkProxyFactory.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qlist.h>
#include <qnetworkproxy.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QNetworkProxyQuery)
Q_DECLARE_METATYPE(QNetworkProxy)
Q_DECLARE_METATYPE(QList<QNetworkProxy>)

QtScriptShell_QNetworkProxyFactory::QtScriptShell_QNetworkProxyFactory()
    : QNetworkProxyFactory() {}

QtScriptShell_QNetworkProxyFactory::~QtScriptShell_QNetworkProxyFactory() {}

QList<QNetworkProxy >  QtScriptShell_QNetworkProxyFactory::queryProxy(const QNetworkProxyQuery&  query)
{
    QScriptValue _q_function = __qtscript_self.property("queryProxy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("queryProxy") & QScriptValue::QObjectMember)) {
        qFatal("QNetworkProxyFactory::queryProxy() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QList<QNetworkProxy > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query)));
    }
}

