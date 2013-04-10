#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qnetworkinterface.h>
#include <QVariant>
#include <qhostaddress.h>
#include <qnetworkinterface.h>

static const char * const qtscript_QNetworkAddressEntry_function_names[] = {
    "QNetworkAddressEntry"
    // static
    // prototype
    , "broadcast"
    , "ip"
    , "netmask"
    , "equals"
    , "prefixLength"
    , "setBroadcast"
    , "setIp"
    , "setNetmask"
    , "setPrefixLength"
    , "toString"
};

static const char * const qtscript_QNetworkAddressEntry_function_signatures[] = {
    "\nQNetworkAddressEntry other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QNetworkAddressEntry other"
    , ""
    , "QHostAddress newBroadcast"
    , "QHostAddress newIp"
    , "QHostAddress newNetmask"
    , "int length"
""
};

static const int qtscript_QNetworkAddressEntry_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkAddressEntry_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkAddressEntry::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkAddressEntry)
Q_DECLARE_METATYPE(QNetworkAddressEntry*)
Q_DECLARE_METATYPE(QHostAddress)

//
// QNetworkAddressEntry
//

static QScriptValue qtscript_QNetworkAddressEntry_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkAddressEntry* _q_self = qscriptvalue_cast<QNetworkAddressEntry*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkAddressEntry.%0(): this object is not a QNetworkAddressEntry")
            .arg(qtscript_QNetworkAddressEntry_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->broadcast();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->ip();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->netmask();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QNetworkAddressEntry _q_arg0 = qscriptvalue_cast<QNetworkAddressEntry>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->prefixLength();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        _q_self->setBroadcast(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        _q_self->setIp(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        _q_self->setNetmask(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPrefixLength(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QNetworkAddressEntry");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkAddressEntry_throw_ambiguity_error_helper(context,
        qtscript_QNetworkAddressEntry_function_names[_id+1],
        qtscript_QNetworkAddressEntry_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkAddressEntry_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkAddressEntry(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QNetworkAddressEntry _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QNetworkAddressEntry _q_arg0 = qscriptvalue_cast<QNetworkAddressEntry>(context->argument(0));
        QNetworkAddressEntry _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkAddressEntry_throw_ambiguity_error_helper(context,
        qtscript_QNetworkAddressEntry_function_names[_id],
        qtscript_QNetworkAddressEntry_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkAddressEntry_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkAddressEntry*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkAddressEntry*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkAddressEntry_prototype_call, qtscript_QNetworkAddressEntry_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkAddressEntry_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkAddressEntry>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QNetworkAddressEntry*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkAddressEntry_static_call, proto, qtscript_QNetworkAddressEntry_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
