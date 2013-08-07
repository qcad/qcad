#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsslerror.h>
#include <QVariant>
#include <qsslcertificate.h>
#include <qsslerror.h>

static const char * const qtscript_QSslError_function_names[] = {
    "QSslError"
    // static
    // prototype
    , "certificate"
    , "error"
    , "errorString"
    , "operator_assign"
    , "equals"
    , "swap"
    , "toString"
};

static const char * const qtscript_QSslError_function_signatures[] = {
    "\nSslError error\nSslError error, QSslCertificate certificate\nQSslError other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QSslError other"
    , "QSslError other"
    , "QSslError other"
""
};

static const int qtscript_QSslError_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QSslError_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSslError::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSslError)
Q_DECLARE_METATYPE(QSslError*)
Q_DECLARE_METATYPE(QSslError::SslError)

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
// QSslError::SslError
//

static const QSslError::SslError qtscript_QSslError_SslError_values[] = {
    QSslError::UnspecifiedError
    , QSslError::NoError
    , QSslError::UnableToGetIssuerCertificate
    , QSslError::UnableToDecryptCertificateSignature
    , QSslError::UnableToDecodeIssuerPublicKey
    , QSslError::CertificateSignatureFailed
    , QSslError::CertificateNotYetValid
    , QSslError::CertificateExpired
    , QSslError::InvalidNotBeforeField
    , QSslError::InvalidNotAfterField
    , QSslError::SelfSignedCertificate
    , QSslError::SelfSignedCertificateInChain
    , QSslError::UnableToGetLocalIssuerCertificate
    , QSslError::UnableToVerifyFirstCertificate
    , QSslError::CertificateRevoked
    , QSslError::InvalidCaCertificate
    , QSslError::PathLengthExceeded
    , QSslError::InvalidPurpose
    , QSslError::CertificateUntrusted
    , QSslError::CertificateRejected
    , QSslError::SubjectIssuerMismatch
    , QSslError::AuthorityIssuerSerialNumberMismatch
    , QSslError::NoPeerCertificate
    , QSslError::HostNameMismatch
    , QSslError::NoSslSupport
    , QSslError::CertificateBlacklisted
};

static const char * const qtscript_QSslError_SslError_keys[] = {
    "UnspecifiedError"
    , "NoError"
    , "UnableToGetIssuerCertificate"
    , "UnableToDecryptCertificateSignature"
    , "UnableToDecodeIssuerPublicKey"
    , "CertificateSignatureFailed"
    , "CertificateNotYetValid"
    , "CertificateExpired"
    , "InvalidNotBeforeField"
    , "InvalidNotAfterField"
    , "SelfSignedCertificate"
    , "SelfSignedCertificateInChain"
    , "UnableToGetLocalIssuerCertificate"
    , "UnableToVerifyFirstCertificate"
    , "CertificateRevoked"
    , "InvalidCaCertificate"
    , "PathLengthExceeded"
    , "InvalidPurpose"
    , "CertificateUntrusted"
    , "CertificateRejected"
    , "SubjectIssuerMismatch"
    , "AuthorityIssuerSerialNumberMismatch"
    , "NoPeerCertificate"
    , "HostNameMismatch"
    , "NoSslSupport"
    , "CertificateBlacklisted"
};

static QString qtscript_QSslError_SslError_toStringHelper(QSslError::SslError value)
{
    if ((value >= QSslError::UnspecifiedError) && (value <= QSslError::CertificateBlacklisted))
        return qtscript_QSslError_SslError_keys[static_cast<int>(value)-static_cast<int>(QSslError::UnspecifiedError)];
    return QString();
}

static QScriptValue qtscript_QSslError_SslError_toScriptValue(QScriptEngine *engine, const QSslError::SslError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSslError"));
    return clazz.property(qtscript_QSslError_SslError_toStringHelper(value));
}

static void qtscript_QSslError_SslError_fromScriptValue(const QScriptValue &value, QSslError::SslError &out)
{
    out = qvariant_cast<QSslError::SslError>(value.toVariant());
}

static QScriptValue qtscript_construct_QSslError_SslError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSslError::UnspecifiedError) && (arg <= QSslError::CertificateBlacklisted))
        return qScriptValueFromValue(engine,  static_cast<QSslError::SslError>(arg));
    return context->throwError(QString::fromLatin1("SslError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSslError_SslError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSslError::SslError value = qscriptvalue_cast<QSslError::SslError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSslError_SslError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSslError::SslError value = qscriptvalue_cast<QSslError::SslError>(context->thisObject());
    return QScriptValue(engine, qtscript_QSslError_SslError_toStringHelper(value));
}

static QScriptValue qtscript_create_QSslError_SslError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSslError_SslError,
        qtscript_QSslError_SslError_valueOf, qtscript_QSslError_SslError_toString);
    qScriptRegisterMetaType<QSslError::SslError>(engine, qtscript_QSslError_SslError_toScriptValue,
        qtscript_QSslError_SslError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 26; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSslError_SslError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSslError_SslError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSslError
//

static QScriptValue qtscript_QSslError_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSslError* _q_self = qscriptvalue_cast<QSslError*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSslError.%0(): this object is not a QSslError")
            .arg(qtscript_QSslError_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSslCertificate _q_result = _q_self->certificate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSslError::SslError _q_result = _q_self->error();
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
    if (context->argumentCount() == 1) {
        QSslError _q_arg0 = qscriptvalue_cast<QSslError>(context->argument(0));
        QSslError& _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QSslError _q_arg0 = qscriptvalue_cast<QSslError>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QSslError _q_arg0 = qscriptvalue_cast<QSslError>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslError_throw_ambiguity_error_helper(context,
        qtscript_QSslError_function_names[_id+1],
        qtscript_QSslError_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSslError_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSslError(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSslError _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSslError::SslError>() == context->argument(0).toVariant().userType())) {
            QSslError::SslError _q_arg0 = qscriptvalue_cast<QSslError::SslError>(context->argument(0));
            QSslError _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QSslError>() == context->argument(0).toVariant().userType())) {
            QSslError _q_arg0 = qscriptvalue_cast<QSslError>(context->argument(0));
            QSslError _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QSslError::SslError _q_arg0 = qscriptvalue_cast<QSslError::SslError>(context->argument(0));
        QSslCertificate _q_arg1 = qscriptvalue_cast<QSslCertificate>(context->argument(1));
        QSslError _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslError_throw_ambiguity_error_helper(context,
        qtscript_QSslError_function_names[_id],
        qtscript_QSslError_function_signatures[_id]);
}

QScriptValue qtscript_create_QSslError_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSslError*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSslError*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslError_prototype_call, qtscript_QSslError_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSslError_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSslError>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSslError*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSslError_static_call, proto, qtscript_QSslError_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SslError"),
        qtscript_create_QSslError_SslError_class(engine, ctor));
    return ctor;
}
