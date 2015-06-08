#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qnetworkproxy.h>
#include <QVariant>
#include <qnetworkproxy.h>
#include <qurl.h>

static const char * const qtscript_QNetworkProxyQuery_function_names[] = {
    "QNetworkProxyQuery"
    // static
    // prototype
    , "localPort"
    , "equals"
    , "peerHostName"
    , "peerPort"
    , "protocolTag"
    , "queryType"
    , "setLocalPort"
    , "setPeerHostName"
    , "setPeerPort"
    , "setProtocolTag"
    , "setQueryType"
    , "setUrl"
    , "url"
    , "toString"
};

static const char * const qtscript_QNetworkProxyQuery_function_signatures[] = {
    "\nQNetworkProxyQuery other\nString hostname, int port, String protocolTag, QueryType queryType\nQUrl requestUrl, QueryType queryType\nunsigned short bindPort, String protocolTag, QueryType queryType"
    // static
    // prototype
    , ""
    , "QNetworkProxyQuery other"
    , ""
    , ""
    , ""
    , ""
    , "int port"
    , "String hostname"
    , "int port"
    , "String protocolTag"
    , "QueryType type"
    , "QUrl url"
    , ""
""
};

static const int qtscript_QNetworkProxyQuery_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QNetworkProxyQuery_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkProxyQuery::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkProxyQuery)
Q_DECLARE_METATYPE(QNetworkProxyQuery*)
Q_DECLARE_METATYPE(QNetworkProxyQuery::QueryType)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QNetworkProxyQuery::QueryType
//

static const QNetworkProxyQuery::QueryType qtscript_QNetworkProxyQuery_QueryType_values[] = {
    QNetworkProxyQuery::TcpSocket
    , QNetworkProxyQuery::UdpSocket
    , QNetworkProxyQuery::TcpServer
    , QNetworkProxyQuery::UrlRequest
};

static const char * const qtscript_QNetworkProxyQuery_QueryType_keys[] = {
    "TcpSocket"
    , "UdpSocket"
    , "TcpServer"
    , "UrlRequest"
};

static QString qtscript_QNetworkProxyQuery_QueryType_toStringHelper(QNetworkProxyQuery::QueryType value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QNetworkProxyQuery_QueryType_values[i] == value)
            return QString::fromLatin1(qtscript_QNetworkProxyQuery_QueryType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QNetworkProxyQuery_QueryType_toScriptValue(QScriptEngine *engine, const QNetworkProxyQuery::QueryType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkProxyQuery"));
    return clazz.property(qtscript_QNetworkProxyQuery_QueryType_toStringHelper(value));
}

static void qtscript_QNetworkProxyQuery_QueryType_fromScriptValue(const QScriptValue &value, QNetworkProxyQuery::QueryType &out)
{
    out = qvariant_cast<QNetworkProxyQuery::QueryType>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkProxyQuery_QueryType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QNetworkProxyQuery_QueryType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QNetworkProxyQuery::QueryType>(arg));
    }
    return context->throwError(QString::fromLatin1("QueryType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkProxyQuery_QueryType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkProxyQuery::QueryType value = qscriptvalue_cast<QNetworkProxyQuery::QueryType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkProxyQuery_QueryType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkProxyQuery::QueryType value = qscriptvalue_cast<QNetworkProxyQuery::QueryType>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkProxyQuery_QueryType_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkProxyQuery_QueryType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkProxyQuery_QueryType,
        qtscript_QNetworkProxyQuery_QueryType_valueOf, qtscript_QNetworkProxyQuery_QueryType_toString);
    qScriptRegisterMetaType<QNetworkProxyQuery::QueryType>(engine, qtscript_QNetworkProxyQuery_QueryType_toScriptValue,
        qtscript_QNetworkProxyQuery_QueryType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkProxyQuery_QueryType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkProxyQuery_QueryType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkProxyQuery
//

static QScriptValue qtscript_QNetworkProxyQuery_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkProxyQuery* _q_self = qscriptvalue_cast<QNetworkProxyQuery*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkProxyQuery.%0(): this object is not a QNetworkProxyQuery")
            .arg(qtscript_QNetworkProxyQuery_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->localPort();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QNetworkProxyQuery _q_arg0 = qscriptvalue_cast<QNetworkProxyQuery>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->peerHostName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->peerPort();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->protocolTag();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QNetworkProxyQuery::QueryType _q_result = _q_self->queryType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLocalPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPeerHostName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPeerPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setProtocolTag(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QNetworkProxyQuery::QueryType _q_arg0 = qscriptvalue_cast<QNetworkProxyQuery::QueryType>(context->argument(0));
        _q_self->setQueryType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->setUrl(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->url();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QNetworkProxyQuery");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkProxyQuery_throw_ambiguity_error_helper(context,
        qtscript_QNetworkProxyQuery_function_names[_id+1],
        qtscript_QNetworkProxyQuery_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkProxyQuery_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkProxyQuery(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QNetworkProxyQuery _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QNetworkProxyQuery>() == context->argument(0).toVariant().userType())) {
            QNetworkProxyQuery _q_arg0 = qscriptvalue_cast<QNetworkProxyQuery>(context->argument(0));
            QNetworkProxyQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            QNetworkProxyQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
            QNetworkProxyQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            QNetworkProxyQuery _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QNetworkProxyQuery::QueryType>() == context->argument(1).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            QNetworkProxyQuery::QueryType _q_arg1 = qscriptvalue_cast<QNetworkProxyQuery::QueryType>(context->argument(1));
            QNetworkProxyQuery _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QNetworkProxyQuery _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && context->argument(2).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QNetworkProxyQuery _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()
            && (qMetaTypeId<QNetworkProxyQuery::QueryType>() == context->argument(2).toVariant().userType())) {
            unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QNetworkProxyQuery::QueryType _q_arg2 = qscriptvalue_cast<QNetworkProxyQuery::QueryType>(context->argument(2));
            QNetworkProxyQuery _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_arg2 = context->argument(2).toString();
        QNetworkProxyQuery::QueryType _q_arg3 = qscriptvalue_cast<QNetworkProxyQuery::QueryType>(context->argument(3));
        QNetworkProxyQuery _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkProxyQuery_throw_ambiguity_error_helper(context,
        qtscript_QNetworkProxyQuery_function_names[_id],
        qtscript_QNetworkProxyQuery_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkProxyQuery_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkProxyQuery*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkProxyQuery*)0));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkProxyQuery_prototype_call, qtscript_QNetworkProxyQuery_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkProxyQuery_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkProxyQuery>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QNetworkProxyQuery*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkProxyQuery_static_call, proto, qtscript_QNetworkProxyQuery_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("QueryType"),
        qtscript_create_QNetworkProxyQuery_QueryType_class(engine, ctor));
    return ctor;
}
