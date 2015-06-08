#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qhostinfo.h>
#include <QVariant>
#include <qhostaddress.h>
#include <qhostinfo.h>
#include <qlist.h>
#include <qobject.h>

static const char * const qtscript_QHostInfo_function_names[] = {
    "QHostInfo"
    // static
    , "abortHostLookup"
    , "fromName"
    , "localDomainName"
    , "localHostName"
    , "lookupHost"
    // prototype
    , "addresses"
    , "error"
    , "errorString"
    , "hostName"
    , "lookupId"
    , "setAddresses"
    , "setError"
    , "setErrorString"
    , "setHostName"
    , "setLookupId"
    , "toString"
};

static const char * const qtscript_QHostInfo_function_signatures[] = {
    "QHostInfo d\nint lookupId"
    // static
    , "int lookupId"
    , "String name"
    , ""
    , ""
    , "String name, QObject receiver, char member"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "List addresses"
    , "HostInfoError error"
    , "String errorString"
    , "String name"
    , "int id"
""
};

static const int qtscript_QHostInfo_function_lengths[] = {
    1
    // static
    , 1
    , 1
    , 0
    , 0
    , 3
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QHostInfo_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHostInfo::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QHostInfo)
Q_DECLARE_METATYPE(QHostInfo*)
Q_DECLARE_METATYPE(QHostInfo::HostInfoError)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QList<QHostAddress>)

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
// QHostInfo::HostInfoError
//

static const QHostInfo::HostInfoError qtscript_QHostInfo_HostInfoError_values[] = {
    QHostInfo::NoError
    , QHostInfo::HostNotFound
    , QHostInfo::UnknownError
};

static const char * const qtscript_QHostInfo_HostInfoError_keys[] = {
    "NoError"
    , "HostNotFound"
    , "UnknownError"
};

static QString qtscript_QHostInfo_HostInfoError_toStringHelper(QHostInfo::HostInfoError value)
{
    if ((value >= QHostInfo::NoError) && (value <= QHostInfo::UnknownError))
        return qtscript_QHostInfo_HostInfoError_keys[static_cast<int>(value)-static_cast<int>(QHostInfo::NoError)];
    return QString();
}

static QScriptValue qtscript_QHostInfo_HostInfoError_toScriptValue(QScriptEngine *engine, const QHostInfo::HostInfoError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QHostInfo"));
    return clazz.property(qtscript_QHostInfo_HostInfoError_toStringHelper(value));
}

static void qtscript_QHostInfo_HostInfoError_fromScriptValue(const QScriptValue &value, QHostInfo::HostInfoError &out)
{
    out = qvariant_cast<QHostInfo::HostInfoError>(value.toVariant());
}

static QScriptValue qtscript_construct_QHostInfo_HostInfoError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QHostInfo::NoError) && (arg <= QHostInfo::UnknownError))
        return qScriptValueFromValue(engine,  static_cast<QHostInfo::HostInfoError>(arg));
    return context->throwError(QString::fromLatin1("HostInfoError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QHostInfo_HostInfoError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QHostInfo::HostInfoError value = qscriptvalue_cast<QHostInfo::HostInfoError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QHostInfo_HostInfoError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QHostInfo::HostInfoError value = qscriptvalue_cast<QHostInfo::HostInfoError>(context->thisObject());
    return QScriptValue(engine, qtscript_QHostInfo_HostInfoError_toStringHelper(value));
}

static QScriptValue qtscript_create_QHostInfo_HostInfoError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QHostInfo_HostInfoError,
        qtscript_QHostInfo_HostInfoError_valueOf, qtscript_QHostInfo_HostInfoError_toString);
    qScriptRegisterMetaType<QHostInfo::HostInfoError>(engine, qtscript_QHostInfo_HostInfoError_toScriptValue,
        qtscript_QHostInfo_HostInfoError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QHostInfo_HostInfoError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QHostInfo_HostInfoError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QHostInfo
//

static QScriptValue qtscript_QHostInfo_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QHostInfo* _q_self = qscriptvalue_cast<QHostInfo*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHostInfo.%0(): this object is not a QHostInfo")
            .arg(qtscript_QHostInfo_function_names[_id+6]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QHostAddress> _q_result = _q_self->addresses();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QHostInfo::HostInfoError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->hostName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lookupId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QList<QHostAddress> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setAddresses(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QHostInfo::HostInfoError _q_arg0 = qscriptvalue_cast<QHostInfo::HostInfoError>(context->argument(0));
        _q_self->setError(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setErrorString(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHostName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLookupId(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QHostInfo");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHostInfo_throw_ambiguity_error_helper(context,
        qtscript_QHostInfo_function_names[_id+6],
        qtscript_QHostInfo_function_signatures[_id+6]);
}

static QScriptValue qtscript_QHostInfo_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHostInfo(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QHostInfo _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QHostInfo>() == context->argument(0).toVariant().userType())) {
            QHostInfo _q_arg0 = qscriptvalue_cast<QHostInfo>(context->argument(0));
            QHostInfo _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QHostInfo _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QHostInfo::abortHostLookup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QHostInfo _q_result = QHostInfo::fromName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = QHostInfo::localDomainName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = QHostInfo::localHostName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg2 = context->argument(2).toString().toLatin1();
          const char * _q_arg2 = tmp__q_arg2.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                int _q_result = QHostInfo::lookupHost(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHostInfo_throw_ambiguity_error_helper(context,
        qtscript_QHostInfo_function_names[_id],
        qtscript_QHostInfo_function_signatures[_id]);
}

QScriptValue qtscript_create_QHostInfo_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHostInfo*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHostInfo*)0));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QHostInfo_prototype_call, qtscript_QHostInfo_function_lengths[i+6]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QHostInfo_function_names[i+6]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QHostInfo>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QHostInfo*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHostInfo_static_call, proto, qtscript_QHostInfo_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QHostInfo_static_call,
            qtscript_QHostInfo_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QHostInfo_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("HostInfoError"),
        qtscript_create_QHostInfo_HostInfoError_class(engine, ctor));
    return ctor;
}
