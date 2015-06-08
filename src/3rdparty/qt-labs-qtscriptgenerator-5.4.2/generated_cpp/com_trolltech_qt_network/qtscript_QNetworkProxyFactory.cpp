#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qnetworkproxy.h>
#include <QVariant>
#include <qlist.h>
#include <qnetworkproxy.h>

#include "qtscriptshell_QNetworkProxyFactory.h"

static const char * const qtscript_QNetworkProxyFactory_function_names[] = {
    "QNetworkProxyFactory"
    // static
    , "proxyForQuery"
    , "setApplicationProxyFactory"
    , "setUseSystemConfiguration"
    , "systemProxyForQuery"
    // prototype
    , "queryProxy"
    , "toString"
};

static const char * const qtscript_QNetworkProxyFactory_function_signatures[] = {
    ""
    // static
    , "QNetworkProxyQuery query"
    , "QNetworkProxyFactory factory"
    , "bool enable"
    , "QNetworkProxyQuery query"
    // prototype
    , "QNetworkProxyQuery query"
""
};

static const int qtscript_QNetworkProxyFactory_function_lengths[] = {
    0
    // static
    , 1
    , 1
    , 1
    , 1
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkProxyFactory_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkProxyFactory::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkProxyFactory*)
Q_DECLARE_METATYPE(QtScriptShell_QNetworkProxyFactory*)
Q_DECLARE_METATYPE(QNetworkProxyQuery)
Q_DECLARE_METATYPE(QList<QNetworkProxy >)

//
// QNetworkProxyFactory
//

static QScriptValue qtscript_QNetworkProxyFactory_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkProxyFactory* _q_self = qscriptvalue_cast<QNetworkProxyFactory*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkProxyFactory.%0(): this object is not a QNetworkProxyFactory")
            .arg(qtscript_QNetworkProxyFactory_function_names[_id+5]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QNetworkProxy > _q_result = _q_self->queryProxy();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QNetworkProxyQuery _q_arg0 = qscriptvalue_cast<QNetworkProxyQuery>(context->argument(0));
        QList<QNetworkProxy > _q_result = _q_self->queryProxy(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QNetworkProxyFactory");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkProxyFactory_throw_ambiguity_error_helper(context,
        qtscript_QNetworkProxyFactory_function_names[_id+5],
        qtscript_QNetworkProxyFactory_function_signatures[_id+5]);
}

static QScriptValue qtscript_QNetworkProxyFactory_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkProxyFactory(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QNetworkProxyFactory* _q_cpp_result = new QtScriptShell_QNetworkProxyFactory();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QNetworkProxyFactory*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QNetworkProxyQuery _q_arg0 = qscriptvalue_cast<QNetworkProxyQuery>(context->argument(0));
        QList<QNetworkProxy > _q_result = QNetworkProxyFactory::proxyForQuery(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QNetworkProxyFactory* _q_arg0 = qscriptvalue_cast<QNetworkProxyFactory*>(context->argument(0));
        QNetworkProxyFactory::setApplicationProxyFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QNetworkProxyFactory::setUseSystemConfiguration(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QList<QNetworkProxy > _q_result = QNetworkProxyFactory::systemProxyForQuery();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QNetworkProxyQuery _q_arg0 = qscriptvalue_cast<QNetworkProxyQuery>(context->argument(0));
        QList<QNetworkProxy > _q_result = QNetworkProxyFactory::systemProxyForQuery(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkProxyFactory_throw_ambiguity_error_helper(context,
        qtscript_QNetworkProxyFactory_function_names[_id],
        qtscript_QNetworkProxyFactory_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkProxyFactory_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkProxyFactory*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkProxyFactory*)0));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkProxyFactory_prototype_call, qtscript_QNetworkProxyFactory_function_lengths[i+5]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkProxyFactory_function_names[i+5]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkProxyFactory*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkProxyFactory_static_call, proto, qtscript_QNetworkProxyFactory_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkProxyFactory_static_call,
            qtscript_QNetworkProxyFactory_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QNetworkProxyFactory_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
