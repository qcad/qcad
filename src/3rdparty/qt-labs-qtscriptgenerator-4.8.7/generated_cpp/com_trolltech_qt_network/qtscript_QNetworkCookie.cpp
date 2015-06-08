#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qnetworkcookie.h>
#include <QDateTime>
#include <QVariant>
#include <qbytearray.h>
#include <qdatetime.h>
#include <qlist.h>
#include <qnetworkcookie.h>

static const char * const qtscript_QNetworkCookie_function_names[] = {
    "QNetworkCookie"
    // static
    , "parseCookies"
    // prototype
    , "domain"
    , "expirationDate"
    , "isHttpOnly"
    , "isSecure"
    , "isSessionCookie"
    , "name"
    , "equals"
    , "path"
    , "setDomain"
    , "setExpirationDate"
    , "setHttpOnly"
    , "setName"
    , "setPath"
    , "setSecure"
    , "setValue"
    , "toRawForm"
    , "value"
    , "toString"
};

static const char * const qtscript_QNetworkCookie_function_signatures[] = {
    "QByteArray name, QByteArray value\nQNetworkCookie other"
    // static
    , "QByteArray cookieString"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QNetworkCookie other"
    , ""
    , "String domain"
    , "QDateTime date"
    , "bool enable"
    , "QByteArray cookieName"
    , "String path"
    , "bool enable"
    , "QByteArray value"
    , "RawForm form"
    , ""
""
};

static const int qtscript_QNetworkCookie_function_lengths[] = {
    2
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QNetworkCookie_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkCookie::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkCookie*)
Q_DECLARE_METATYPE(QNetworkCookie::RawForm)

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
// QNetworkCookie::RawForm
//

static const QNetworkCookie::RawForm qtscript_QNetworkCookie_RawForm_values[] = {
    QNetworkCookie::NameAndValueOnly
    , QNetworkCookie::Full
};

static const char * const qtscript_QNetworkCookie_RawForm_keys[] = {
    "NameAndValueOnly"
    , "Full"
};

static QString qtscript_QNetworkCookie_RawForm_toStringHelper(QNetworkCookie::RawForm value)
{
    if ((value >= QNetworkCookie::NameAndValueOnly) && (value <= QNetworkCookie::Full))
        return qtscript_QNetworkCookie_RawForm_keys[static_cast<int>(value)-static_cast<int>(QNetworkCookie::NameAndValueOnly)];
    return QString();
}

static QScriptValue qtscript_QNetworkCookie_RawForm_toScriptValue(QScriptEngine *engine, const QNetworkCookie::RawForm &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkCookie"));
    return clazz.property(qtscript_QNetworkCookie_RawForm_toStringHelper(value));
}

static void qtscript_QNetworkCookie_RawForm_fromScriptValue(const QScriptValue &value, QNetworkCookie::RawForm &out)
{
    out = qvariant_cast<QNetworkCookie::RawForm>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkCookie_RawForm(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QNetworkCookie::NameAndValueOnly) && (arg <= QNetworkCookie::Full))
        return qScriptValueFromValue(engine,  static_cast<QNetworkCookie::RawForm>(arg));
    return context->throwError(QString::fromLatin1("RawForm(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkCookie_RawForm_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkCookie::RawForm value = qscriptvalue_cast<QNetworkCookie::RawForm>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkCookie_RawForm_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkCookie::RawForm value = qscriptvalue_cast<QNetworkCookie::RawForm>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkCookie_RawForm_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkCookie_RawForm_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkCookie_RawForm,
        qtscript_QNetworkCookie_RawForm_valueOf, qtscript_QNetworkCookie_RawForm_toString);
    qScriptRegisterMetaType<QNetworkCookie::RawForm>(engine, qtscript_QNetworkCookie_RawForm_toScriptValue,
        qtscript_QNetworkCookie_RawForm_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkCookie_RawForm_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkCookie_RawForm_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkCookie
//

static QScriptValue qtscript_QNetworkCookie_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkCookie* _q_self = qscriptvalue_cast<QNetworkCookie*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkCookie.%0(): this object is not a QNetworkCookie")
            .arg(qtscript_QNetworkCookie_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->domain();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->expirationDate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isHttpOnly();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSecure();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSessionCookie();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->name();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QNetworkCookie _q_arg0 = qscriptvalue_cast<QNetworkCookie>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDomain(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QDateTime _q_arg0 = context->argument(0).toDateTime();
        _q_self->setExpirationDate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setHttpOnly(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSecure(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toRawForm();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QNetworkCookie::RawForm _q_arg0 = qscriptvalue_cast<QNetworkCookie::RawForm>(context->argument(0));
        QByteArray _q_result = _q_self->toRawForm(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->value();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkCookie_throw_ambiguity_error_helper(context,
        qtscript_QNetworkCookie_function_names[_id+2],
        qtscript_QNetworkCookie_function_signatures[_id+2]);
}

static QScriptValue qtscript_QNetworkCookie_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkCookie(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QNetworkCookie _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QNetworkCookie _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QNetworkCookie>() == context->argument(0).toVariant().userType())) {
            QNetworkCookie _q_arg0 = qscriptvalue_cast<QNetworkCookie>(context->argument(0));
            QNetworkCookie _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QNetworkCookie _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QList<QNetworkCookie> _q_result = QNetworkCookie::parseCookies(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkCookie_throw_ambiguity_error_helper(context,
        qtscript_QNetworkCookie_function_names[_id],
        qtscript_QNetworkCookie_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkCookie_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkCookie*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkCookie*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkCookie_prototype_call, qtscript_QNetworkCookie_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkCookie_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkCookie>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QNetworkCookie*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkCookie_static_call, proto, qtscript_QNetworkCookie_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkCookie_static_call,
            qtscript_QNetworkCookie_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QNetworkCookie_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("RawForm"),
        qtscript_create_QNetworkCookie_RawForm_class(engine, ctor));
    return ctor;
}
