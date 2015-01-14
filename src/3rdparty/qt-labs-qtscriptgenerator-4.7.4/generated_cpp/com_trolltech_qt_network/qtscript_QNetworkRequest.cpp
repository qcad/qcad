#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qnetworkrequest.h>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qsslconfiguration.h>
#include <qurl.h>

static const char * const qtscript_QNetworkRequest_function_names[] = {
    "QNetworkRequest"
    // static
    // prototype
    , "attribute"
    , "hasRawHeader"
    , "header"
    , "equals"
    , "originatingObject"
    , "priority"
    , "rawHeader"
    , "rawHeaderList"
    , "setAttribute"
    , "setHeader"
    , "setOriginatingObject"
    , "setPriority"
    , "setRawHeader"
    , "setSslConfiguration"
    , "setUrl"
    , "sslConfiguration"
    , "url"
    , "toString"
};

static const char * const qtscript_QNetworkRequest_function_signatures[] = {
    "QNetworkRequest other\nQUrl url"
    // static
    // prototype
    , "Attribute code, Object defaultValue"
    , "QByteArray headerName"
    , "KnownHeaders header"
    , "QNetworkRequest other"
    , ""
    , ""
    , "QByteArray headerName"
    , ""
    , "Attribute code, Object value"
    , "KnownHeaders header, Object value"
    , "QObject object"
    , "Priority priority"
    , "QByteArray headerName, QByteArray value"
    , "QSslConfiguration configuration"
    , "QUrl url"
    , ""
    , ""
""
};

static const int qtscript_QNetworkRequest_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
    , 2
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QNetworkRequest_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkRequest::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkRequest*)
Q_DECLARE_METATYPE(QNetworkRequest::CacheLoadControl)
Q_DECLARE_METATYPE(QNetworkRequest::KnownHeaders)
Q_DECLARE_METATYPE(QNetworkRequest::Priority)
Q_DECLARE_METATYPE(QNetworkRequest::Attribute)
Q_DECLARE_METATYPE(QNetworkRequest::LoadControl)
Q_DECLARE_METATYPE(QList<QByteArray>)
Q_DECLARE_METATYPE(QSslConfiguration)

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
// QNetworkRequest::CacheLoadControl
//

static const QNetworkRequest::CacheLoadControl qtscript_QNetworkRequest_CacheLoadControl_values[] = {
    QNetworkRequest::AlwaysNetwork
    , QNetworkRequest::PreferNetwork
    , QNetworkRequest::PreferCache
    , QNetworkRequest::AlwaysCache
};

static const char * const qtscript_QNetworkRequest_CacheLoadControl_keys[] = {
    "AlwaysNetwork"
    , "PreferNetwork"
    , "PreferCache"
    , "AlwaysCache"
};

static QString qtscript_QNetworkRequest_CacheLoadControl_toStringHelper(QNetworkRequest::CacheLoadControl value)
{
    if ((value >= QNetworkRequest::AlwaysNetwork) && (value <= QNetworkRequest::AlwaysCache))
        return qtscript_QNetworkRequest_CacheLoadControl_keys[static_cast<int>(value)-static_cast<int>(QNetworkRequest::AlwaysNetwork)];
    return QString();
}

static QScriptValue qtscript_QNetworkRequest_CacheLoadControl_toScriptValue(QScriptEngine *engine, const QNetworkRequest::CacheLoadControl &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkRequest"));
    return clazz.property(qtscript_QNetworkRequest_CacheLoadControl_toStringHelper(value));
}

static void qtscript_QNetworkRequest_CacheLoadControl_fromScriptValue(const QScriptValue &value, QNetworkRequest::CacheLoadControl &out)
{
    out = qvariant_cast<QNetworkRequest::CacheLoadControl>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkRequest_CacheLoadControl(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QNetworkRequest::AlwaysNetwork) && (arg <= QNetworkRequest::AlwaysCache))
        return qScriptValueFromValue(engine,  static_cast<QNetworkRequest::CacheLoadControl>(arg));
    return context->throwError(QString::fromLatin1("CacheLoadControl(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkRequest_CacheLoadControl_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::CacheLoadControl value = qscriptvalue_cast<QNetworkRequest::CacheLoadControl>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkRequest_CacheLoadControl_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::CacheLoadControl value = qscriptvalue_cast<QNetworkRequest::CacheLoadControl>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkRequest_CacheLoadControl_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkRequest_CacheLoadControl_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkRequest_CacheLoadControl,
        qtscript_QNetworkRequest_CacheLoadControl_valueOf, qtscript_QNetworkRequest_CacheLoadControl_toString);
    qScriptRegisterMetaType<QNetworkRequest::CacheLoadControl>(engine, qtscript_QNetworkRequest_CacheLoadControl_toScriptValue,
        qtscript_QNetworkRequest_CacheLoadControl_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkRequest_CacheLoadControl_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkRequest_CacheLoadControl_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkRequest::KnownHeaders
//

static const QNetworkRequest::KnownHeaders qtscript_QNetworkRequest_KnownHeaders_values[] = {
    QNetworkRequest::ContentTypeHeader
    , QNetworkRequest::ContentLengthHeader
    , QNetworkRequest::LocationHeader
    , QNetworkRequest::LastModifiedHeader
    , QNetworkRequest::CookieHeader
    , QNetworkRequest::SetCookieHeader
};

static const char * const qtscript_QNetworkRequest_KnownHeaders_keys[] = {
    "ContentTypeHeader"
    , "ContentLengthHeader"
    , "LocationHeader"
    , "LastModifiedHeader"
    , "CookieHeader"
    , "SetCookieHeader"
};

static QString qtscript_QNetworkRequest_KnownHeaders_toStringHelper(QNetworkRequest::KnownHeaders value)
{
    if ((value >= QNetworkRequest::ContentTypeHeader) && (value <= QNetworkRequest::SetCookieHeader))
        return qtscript_QNetworkRequest_KnownHeaders_keys[static_cast<int>(value)-static_cast<int>(QNetworkRequest::ContentTypeHeader)];
    return QString();
}

static QScriptValue qtscript_QNetworkRequest_KnownHeaders_toScriptValue(QScriptEngine *engine, const QNetworkRequest::KnownHeaders &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkRequest"));
    return clazz.property(qtscript_QNetworkRequest_KnownHeaders_toStringHelper(value));
}

static void qtscript_QNetworkRequest_KnownHeaders_fromScriptValue(const QScriptValue &value, QNetworkRequest::KnownHeaders &out)
{
    out = qvariant_cast<QNetworkRequest::KnownHeaders>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkRequest_KnownHeaders(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QNetworkRequest::ContentTypeHeader) && (arg <= QNetworkRequest::SetCookieHeader))
        return qScriptValueFromValue(engine,  static_cast<QNetworkRequest::KnownHeaders>(arg));
    return context->throwError(QString::fromLatin1("KnownHeaders(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkRequest_KnownHeaders_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::KnownHeaders value = qscriptvalue_cast<QNetworkRequest::KnownHeaders>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkRequest_KnownHeaders_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::KnownHeaders value = qscriptvalue_cast<QNetworkRequest::KnownHeaders>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkRequest_KnownHeaders_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkRequest_KnownHeaders_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkRequest_KnownHeaders,
        qtscript_QNetworkRequest_KnownHeaders_valueOf, qtscript_QNetworkRequest_KnownHeaders_toString);
    qScriptRegisterMetaType<QNetworkRequest::KnownHeaders>(engine, qtscript_QNetworkRequest_KnownHeaders_toScriptValue,
        qtscript_QNetworkRequest_KnownHeaders_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkRequest_KnownHeaders_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkRequest_KnownHeaders_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkRequest::Priority
//

static const QNetworkRequest::Priority qtscript_QNetworkRequest_Priority_values[] = {
    QNetworkRequest::HighPriority
    , QNetworkRequest::NormalPriority
    , QNetworkRequest::LowPriority
};

static const char * const qtscript_QNetworkRequest_Priority_keys[] = {
    "HighPriority"
    , "NormalPriority"
    , "LowPriority"
};

static QString qtscript_QNetworkRequest_Priority_toStringHelper(QNetworkRequest::Priority value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QNetworkRequest_Priority_values[i] == value)
            return QString::fromLatin1(qtscript_QNetworkRequest_Priority_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QNetworkRequest_Priority_toScriptValue(QScriptEngine *engine, const QNetworkRequest::Priority &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkRequest"));
    return clazz.property(qtscript_QNetworkRequest_Priority_toStringHelper(value));
}

static void qtscript_QNetworkRequest_Priority_fromScriptValue(const QScriptValue &value, QNetworkRequest::Priority &out)
{
    out = qvariant_cast<QNetworkRequest::Priority>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkRequest_Priority(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QNetworkRequest_Priority_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QNetworkRequest::Priority>(arg));
    }
    return context->throwError(QString::fromLatin1("Priority(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkRequest_Priority_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::Priority value = qscriptvalue_cast<QNetworkRequest::Priority>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkRequest_Priority_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::Priority value = qscriptvalue_cast<QNetworkRequest::Priority>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkRequest_Priority_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkRequest_Priority_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkRequest_Priority,
        qtscript_QNetworkRequest_Priority_valueOf, qtscript_QNetworkRequest_Priority_toString);
    qScriptRegisterMetaType<QNetworkRequest::Priority>(engine, qtscript_QNetworkRequest_Priority_toScriptValue,
        qtscript_QNetworkRequest_Priority_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkRequest_Priority_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkRequest_Priority_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkRequest::Attribute
//

static const QNetworkRequest::Attribute qtscript_QNetworkRequest_Attribute_values[] = {
    QNetworkRequest::HttpStatusCodeAttribute
    , QNetworkRequest::HttpReasonPhraseAttribute
    , QNetworkRequest::RedirectionTargetAttribute
    , QNetworkRequest::ConnectionEncryptedAttribute
    , QNetworkRequest::CacheLoadControlAttribute
    , QNetworkRequest::CacheSaveControlAttribute
    , QNetworkRequest::SourceIsFromCacheAttribute
    , QNetworkRequest::DoNotBufferUploadDataAttribute
    , QNetworkRequest::HttpPipeliningAllowedAttribute
    , QNetworkRequest::HttpPipeliningWasUsedAttribute
    , QNetworkRequest::CustomVerbAttribute
    , QNetworkRequest::CookieLoadControlAttribute
    , QNetworkRequest::AuthenticationReuseAttribute
    , QNetworkRequest::CookieSaveControlAttribute
    , QNetworkRequest::MaximumDownloadBufferSizeAttribute
    , QNetworkRequest::DownloadBufferAttribute
    , QNetworkRequest::User
    , QNetworkRequest::UserMax
};

static const char * const qtscript_QNetworkRequest_Attribute_keys[] = {
    "HttpStatusCodeAttribute"
    , "HttpReasonPhraseAttribute"
    , "RedirectionTargetAttribute"
    , "ConnectionEncryptedAttribute"
    , "CacheLoadControlAttribute"
    , "CacheSaveControlAttribute"
    , "SourceIsFromCacheAttribute"
    , "DoNotBufferUploadDataAttribute"
    , "HttpPipeliningAllowedAttribute"
    , "HttpPipeliningWasUsedAttribute"
    , "CustomVerbAttribute"
    , "CookieLoadControlAttribute"
    , "AuthenticationReuseAttribute"
    , "CookieSaveControlAttribute"
    , "MaximumDownloadBufferSizeAttribute"
    , "DownloadBufferAttribute"
    , "User"
    , "UserMax"
};

static QString qtscript_QNetworkRequest_Attribute_toStringHelper(QNetworkRequest::Attribute value)
{
    for (int i = 0; i < 18; ++i) {
        if (qtscript_QNetworkRequest_Attribute_values[i] == value)
            return QString::fromLatin1(qtscript_QNetworkRequest_Attribute_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QNetworkRequest_Attribute_toScriptValue(QScriptEngine *engine, const QNetworkRequest::Attribute &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkRequest"));
    return clazz.property(qtscript_QNetworkRequest_Attribute_toStringHelper(value));
}

static void qtscript_QNetworkRequest_Attribute_fromScriptValue(const QScriptValue &value, QNetworkRequest::Attribute &out)
{
    out = qvariant_cast<QNetworkRequest::Attribute>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkRequest_Attribute(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 18; ++i) {
        if (qtscript_QNetworkRequest_Attribute_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QNetworkRequest::Attribute>(arg));
    }
    return context->throwError(QString::fromLatin1("Attribute(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkRequest_Attribute_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::Attribute value = qscriptvalue_cast<QNetworkRequest::Attribute>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkRequest_Attribute_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::Attribute value = qscriptvalue_cast<QNetworkRequest::Attribute>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkRequest_Attribute_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkRequest_Attribute_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkRequest_Attribute,
        qtscript_QNetworkRequest_Attribute_valueOf, qtscript_QNetworkRequest_Attribute_toString);
    qScriptRegisterMetaType<QNetworkRequest::Attribute>(engine, qtscript_QNetworkRequest_Attribute_toScriptValue,
        qtscript_QNetworkRequest_Attribute_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 18; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkRequest_Attribute_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkRequest_Attribute_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkRequest::LoadControl
//

static const QNetworkRequest::LoadControl qtscript_QNetworkRequest_LoadControl_values[] = {
    QNetworkRequest::Automatic
    , QNetworkRequest::Manual
};

static const char * const qtscript_QNetworkRequest_LoadControl_keys[] = {
    "Automatic"
    , "Manual"
};

static QString qtscript_QNetworkRequest_LoadControl_toStringHelper(QNetworkRequest::LoadControl value)
{
    if ((value >= QNetworkRequest::Automatic) && (value <= QNetworkRequest::Manual))
        return qtscript_QNetworkRequest_LoadControl_keys[static_cast<int>(value)-static_cast<int>(QNetworkRequest::Automatic)];
    return QString();
}

static QScriptValue qtscript_QNetworkRequest_LoadControl_toScriptValue(QScriptEngine *engine, const QNetworkRequest::LoadControl &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkRequest"));
    return clazz.property(qtscript_QNetworkRequest_LoadControl_toStringHelper(value));
}

static void qtscript_QNetworkRequest_LoadControl_fromScriptValue(const QScriptValue &value, QNetworkRequest::LoadControl &out)
{
    out = qvariant_cast<QNetworkRequest::LoadControl>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkRequest_LoadControl(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QNetworkRequest::Automatic) && (arg <= QNetworkRequest::Manual))
        return qScriptValueFromValue(engine,  static_cast<QNetworkRequest::LoadControl>(arg));
    return context->throwError(QString::fromLatin1("LoadControl(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkRequest_LoadControl_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::LoadControl value = qscriptvalue_cast<QNetworkRequest::LoadControl>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkRequest_LoadControl_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkRequest::LoadControl value = qscriptvalue_cast<QNetworkRequest::LoadControl>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkRequest_LoadControl_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkRequest_LoadControl_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkRequest_LoadControl,
        qtscript_QNetworkRequest_LoadControl_valueOf, qtscript_QNetworkRequest_LoadControl_toString);
    qScriptRegisterMetaType<QNetworkRequest::LoadControl>(engine, qtscript_QNetworkRequest_LoadControl_toScriptValue,
        qtscript_QNetworkRequest_LoadControl_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkRequest_LoadControl_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkRequest_LoadControl_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkRequest
//

static QScriptValue qtscript_QNetworkRequest_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QNetworkRequest* _q_self = qscriptvalue_cast<QNetworkRequest*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkRequest.%0(): this object is not a QNetworkRequest")
            .arg(qtscript_QNetworkRequest_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QNetworkRequest::Attribute _q_arg0 = qscriptvalue_cast<QNetworkRequest::Attribute>(context->argument(0));
        QVariant _q_result = _q_self->attribute(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QNetworkRequest::Attribute _q_arg0 = qscriptvalue_cast<QNetworkRequest::Attribute>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        QVariant _q_result = _q_self->attribute(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->hasRawHeader(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QNetworkRequest::KnownHeaders _q_arg0 = qscriptvalue_cast<QNetworkRequest::KnownHeaders>(context->argument(0));
        QVariant _q_result = _q_self->header(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->originatingObject();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QNetworkRequest::Priority _q_result = _q_self->priority();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->rawHeader(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QList<QByteArray> _q_result = _q_self->rawHeaderList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QNetworkRequest::Attribute _q_arg0 = qscriptvalue_cast<QNetworkRequest::Attribute>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setAttribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QNetworkRequest::KnownHeaders _q_arg0 = qscriptvalue_cast<QNetworkRequest::KnownHeaders>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setHeader(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->setOriginatingObject(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QNetworkRequest::Priority _q_arg0 = qscriptvalue_cast<QNetworkRequest::Priority>(context->argument(0));
        _q_self->setPriority(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        _q_self->setRawHeader(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QSslConfiguration _q_arg0 = qscriptvalue_cast<QSslConfiguration>(context->argument(0));
        _q_self->setSslConfiguration(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->setUrl(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QSslConfiguration _q_result = _q_self->sslConfiguration();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->url();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QNetworkRequest");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkRequest_throw_ambiguity_error_helper(context,
        qtscript_QNetworkRequest_function_names[_id+1],
        qtscript_QNetworkRequest_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkRequest_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkRequest(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QNetworkRequest _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QNetworkRequest>() == context->argument(0).toVariant().userType())) {
            QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
            QNetworkRequest _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            QNetworkRequest _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkRequest_throw_ambiguity_error_helper(context,
        qtscript_QNetworkRequest_function_names[_id],
        qtscript_QNetworkRequest_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkRequest_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkRequest*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkRequest*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkRequest_prototype_call, qtscript_QNetworkRequest_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkRequest_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkRequest>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QNetworkRequest*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkRequest_static_call, proto, qtscript_QNetworkRequest_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("CacheLoadControl"),
        qtscript_create_QNetworkRequest_CacheLoadControl_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("KnownHeaders"),
        qtscript_create_QNetworkRequest_KnownHeaders_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Priority"),
        qtscript_create_QNetworkRequest_Priority_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Attribute"),
        qtscript_create_QNetworkRequest_Attribute_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("LoadControl"),
        qtscript_create_QNetworkRequest_LoadControl_class(engine, ctor));
    return ctor;
}
