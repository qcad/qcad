#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qssl.h>
#include <QVariant>

#include <qssl.h>

static const char * const qtscript_QSsl_function_names[] = {
    "QSsl"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QSsl_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QSsl_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QSsl_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSsl::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSsl::KeyType)
Q_DECLARE_METATYPE(QSsl::KeyAlgorithm)
Q_DECLARE_METATYPE(QSsl::SslProtocol)
Q_DECLARE_METATYPE(QSsl::AlternateNameEntryType)
Q_DECLARE_METATYPE(QSsl::EncodingFormat)

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
// QSsl::KeyType
//

static const QSsl::KeyType qtscript_QSsl_KeyType_values[] = {
    QSsl::PrivateKey
    , QSsl::PublicKey
};

static const char * const qtscript_QSsl_KeyType_keys[] = {
    "PrivateKey"
    , "PublicKey"
};

static QString qtscript_QSsl_KeyType_toStringHelper(QSsl::KeyType value)
{
    if ((value >= QSsl::PrivateKey) && (value <= QSsl::PublicKey))
        return qtscript_QSsl_KeyType_keys[static_cast<int>(value)-static_cast<int>(QSsl::PrivateKey)];
    return QString();
}

static QScriptValue qtscript_QSsl_KeyType_toScriptValue(QScriptEngine *engine, const QSsl::KeyType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSsl"));
    return clazz.property(qtscript_QSsl_KeyType_toStringHelper(value));
}

static void qtscript_QSsl_KeyType_fromScriptValue(const QScriptValue &value, QSsl::KeyType &out)
{
    out = qvariant_cast<QSsl::KeyType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSsl_KeyType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSsl::PrivateKey) && (arg <= QSsl::PublicKey))
        return qScriptValueFromValue(engine,  static_cast<QSsl::KeyType>(arg));
    return context->throwError(QString::fromLatin1("KeyType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSsl_KeyType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::KeyType value = qscriptvalue_cast<QSsl::KeyType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSsl_KeyType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::KeyType value = qscriptvalue_cast<QSsl::KeyType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSsl_KeyType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSsl_KeyType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSsl_KeyType,
        qtscript_QSsl_KeyType_valueOf, qtscript_QSsl_KeyType_toString);
    qScriptRegisterMetaType<QSsl::KeyType>(engine, qtscript_QSsl_KeyType_toScriptValue,
        qtscript_QSsl_KeyType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSsl_KeyType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSsl_KeyType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSsl::KeyAlgorithm
//

static const QSsl::KeyAlgorithm qtscript_QSsl_KeyAlgorithm_values[] = {
    QSsl::Rsa
    , QSsl::Dsa
};

static const char * const qtscript_QSsl_KeyAlgorithm_keys[] = {
    "Rsa"
    , "Dsa"
};

static QString qtscript_QSsl_KeyAlgorithm_toStringHelper(QSsl::KeyAlgorithm value)
{
    if ((value >= QSsl::Rsa) && (value <= QSsl::Dsa))
        return qtscript_QSsl_KeyAlgorithm_keys[static_cast<int>(value)-static_cast<int>(QSsl::Rsa)];
    return QString();
}

static QScriptValue qtscript_QSsl_KeyAlgorithm_toScriptValue(QScriptEngine *engine, const QSsl::KeyAlgorithm &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSsl"));
    return clazz.property(qtscript_QSsl_KeyAlgorithm_toStringHelper(value));
}

static void qtscript_QSsl_KeyAlgorithm_fromScriptValue(const QScriptValue &value, QSsl::KeyAlgorithm &out)
{
    out = qvariant_cast<QSsl::KeyAlgorithm>(value.toVariant());
}

static QScriptValue qtscript_construct_QSsl_KeyAlgorithm(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSsl::Rsa) && (arg <= QSsl::Dsa))
        return qScriptValueFromValue(engine,  static_cast<QSsl::KeyAlgorithm>(arg));
    return context->throwError(QString::fromLatin1("KeyAlgorithm(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSsl_KeyAlgorithm_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::KeyAlgorithm value = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSsl_KeyAlgorithm_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::KeyAlgorithm value = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->thisObject());
    return QScriptValue(engine, qtscript_QSsl_KeyAlgorithm_toStringHelper(value));
}

static QScriptValue qtscript_create_QSsl_KeyAlgorithm_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSsl_KeyAlgorithm,
        qtscript_QSsl_KeyAlgorithm_valueOf, qtscript_QSsl_KeyAlgorithm_toString);
    qScriptRegisterMetaType<QSsl::KeyAlgorithm>(engine, qtscript_QSsl_KeyAlgorithm_toScriptValue,
        qtscript_QSsl_KeyAlgorithm_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSsl_KeyAlgorithm_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSsl_KeyAlgorithm_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSsl::SslProtocol
//

static const QSsl::SslProtocol qtscript_QSsl_SslProtocol_values[] = {
    QSsl::UnknownProtocol
    , QSsl::SslV3
    , QSsl::SslV2
    , QSsl::TlsV1
    , QSsl::AnyProtocol
};

static const char * const qtscript_QSsl_SslProtocol_keys[] = {
    "UnknownProtocol"
    , "SslV3"
    , "SslV2"
    , "TlsV1"
    , "AnyProtocol"
};

static QString qtscript_QSsl_SslProtocol_toStringHelper(QSsl::SslProtocol value)
{
    if ((value >= QSsl::UnknownProtocol) && (value <= QSsl::AnyProtocol))
        return qtscript_QSsl_SslProtocol_keys[static_cast<int>(value)-static_cast<int>(QSsl::UnknownProtocol)];
    return QString();
}

static QScriptValue qtscript_QSsl_SslProtocol_toScriptValue(QScriptEngine *engine, const QSsl::SslProtocol &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSsl"));
    return clazz.property(qtscript_QSsl_SslProtocol_toStringHelper(value));
}

static void qtscript_QSsl_SslProtocol_fromScriptValue(const QScriptValue &value, QSsl::SslProtocol &out)
{
    out = qvariant_cast<QSsl::SslProtocol>(value.toVariant());
}

static QScriptValue qtscript_construct_QSsl_SslProtocol(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSsl::UnknownProtocol) && (arg <= QSsl::AnyProtocol))
        return qScriptValueFromValue(engine,  static_cast<QSsl::SslProtocol>(arg));
    return context->throwError(QString::fromLatin1("SslProtocol(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSsl_SslProtocol_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::SslProtocol value = qscriptvalue_cast<QSsl::SslProtocol>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSsl_SslProtocol_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::SslProtocol value = qscriptvalue_cast<QSsl::SslProtocol>(context->thisObject());
    return QScriptValue(engine, qtscript_QSsl_SslProtocol_toStringHelper(value));
}

static QScriptValue qtscript_create_QSsl_SslProtocol_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSsl_SslProtocol,
        qtscript_QSsl_SslProtocol_valueOf, qtscript_QSsl_SslProtocol_toString);
    qScriptRegisterMetaType<QSsl::SslProtocol>(engine, qtscript_QSsl_SslProtocol_toScriptValue,
        qtscript_QSsl_SslProtocol_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSsl_SslProtocol_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSsl_SslProtocol_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSsl::AlternateNameEntryType
//

static const QSsl::AlternateNameEntryType qtscript_QSsl_AlternateNameEntryType_values[] = {
    QSsl::EmailEntry
    , QSsl::DnsEntry
};

static const char * const qtscript_QSsl_AlternateNameEntryType_keys[] = {
    "EmailEntry"
    , "DnsEntry"
};

static QString qtscript_QSsl_AlternateNameEntryType_toStringHelper(QSsl::AlternateNameEntryType value)
{
    if ((value >= QSsl::EmailEntry) && (value <= QSsl::DnsEntry))
        return qtscript_QSsl_AlternateNameEntryType_keys[static_cast<int>(value)-static_cast<int>(QSsl::EmailEntry)];
    return QString();
}

static QScriptValue qtscript_QSsl_AlternateNameEntryType_toScriptValue(QScriptEngine *engine, const QSsl::AlternateNameEntryType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSsl"));
    return clazz.property(qtscript_QSsl_AlternateNameEntryType_toStringHelper(value));
}

static void qtscript_QSsl_AlternateNameEntryType_fromScriptValue(const QScriptValue &value, QSsl::AlternateNameEntryType &out)
{
    out = qvariant_cast<QSsl::AlternateNameEntryType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSsl_AlternateNameEntryType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSsl::EmailEntry) && (arg <= QSsl::DnsEntry))
        return qScriptValueFromValue(engine,  static_cast<QSsl::AlternateNameEntryType>(arg));
    return context->throwError(QString::fromLatin1("AlternateNameEntryType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSsl_AlternateNameEntryType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::AlternateNameEntryType value = qscriptvalue_cast<QSsl::AlternateNameEntryType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSsl_AlternateNameEntryType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::AlternateNameEntryType value = qscriptvalue_cast<QSsl::AlternateNameEntryType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSsl_AlternateNameEntryType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSsl_AlternateNameEntryType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSsl_AlternateNameEntryType,
        qtscript_QSsl_AlternateNameEntryType_valueOf, qtscript_QSsl_AlternateNameEntryType_toString);
    qScriptRegisterMetaType<QSsl::AlternateNameEntryType>(engine, qtscript_QSsl_AlternateNameEntryType_toScriptValue,
        qtscript_QSsl_AlternateNameEntryType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSsl_AlternateNameEntryType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSsl_AlternateNameEntryType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSsl::EncodingFormat
//

static const QSsl::EncodingFormat qtscript_QSsl_EncodingFormat_values[] = {
    QSsl::Pem
    , QSsl::Der
};

static const char * const qtscript_QSsl_EncodingFormat_keys[] = {
    "Pem"
    , "Der"
};

static QString qtscript_QSsl_EncodingFormat_toStringHelper(QSsl::EncodingFormat value)
{
    if ((value >= QSsl::Pem) && (value <= QSsl::Der))
        return qtscript_QSsl_EncodingFormat_keys[static_cast<int>(value)-static_cast<int>(QSsl::Pem)];
    return QString();
}

static QScriptValue qtscript_QSsl_EncodingFormat_toScriptValue(QScriptEngine *engine, const QSsl::EncodingFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSsl"));
    return clazz.property(qtscript_QSsl_EncodingFormat_toStringHelper(value));
}

static void qtscript_QSsl_EncodingFormat_fromScriptValue(const QScriptValue &value, QSsl::EncodingFormat &out)
{
    out = qvariant_cast<QSsl::EncodingFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QSsl_EncodingFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSsl::Pem) && (arg <= QSsl::Der))
        return qScriptValueFromValue(engine,  static_cast<QSsl::EncodingFormat>(arg));
    return context->throwError(QString::fromLatin1("EncodingFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSsl_EncodingFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::EncodingFormat value = qscriptvalue_cast<QSsl::EncodingFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSsl_EncodingFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSsl::EncodingFormat value = qscriptvalue_cast<QSsl::EncodingFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QSsl_EncodingFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QSsl_EncodingFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSsl_EncodingFormat,
        qtscript_QSsl_EncodingFormat_valueOf, qtscript_QSsl_EncodingFormat_toString);
    qScriptRegisterMetaType<QSsl::EncodingFormat>(engine, qtscript_QSsl_EncodingFormat_toScriptValue,
        qtscript_QSsl_EncodingFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSsl_EncodingFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSsl_EncodingFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSsl
//

static QScriptValue qtscript_QSsl_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QSsl cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSsl_throw_ambiguity_error_helper(context,
        qtscript_QSsl_function_names[_id],
        qtscript_QSsl_function_signatures[_id]);
}

QScriptValue qtscript_create_QSsl_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_QSsl_static_call, proto, qtscript_QSsl_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("KeyType"),
        qtscript_create_QSsl_KeyType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("KeyAlgorithm"),
        qtscript_create_QSsl_KeyAlgorithm_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SslProtocol"),
        qtscript_create_QSsl_SslProtocol_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AlternateNameEntryType"),
        qtscript_create_QSsl_AlternateNameEntryType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("EncodingFormat"),
        qtscript_create_QSsl_EncodingFormat_class(engine, ctor));
    return ctor;
}
