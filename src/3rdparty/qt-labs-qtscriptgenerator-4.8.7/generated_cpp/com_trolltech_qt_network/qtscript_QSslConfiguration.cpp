#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsslconfiguration.h>
#include <QVariant>
#include <qlist.h>
#include <qsslcertificate.h>
#include <qsslcipher.h>
#include <qsslconfiguration.h>
#include <qsslkey.h>

static const char * const qtscript_QSslConfiguration_function_names[] = {
    "QSslConfiguration"
    // static
    , "defaultConfiguration"
    , "setDefaultConfiguration"
    // prototype
    , "caCertificates"
    , "ciphers"
    , "isNull"
    , "localCertificate"
    , "operator_assign"
    , "equals"
    , "peerCertificate"
    , "peerCertificateChain"
    , "peerVerifyDepth"
    , "peerVerifyMode"
    , "privateKey"
    , "protocol"
    , "sessionCipher"
    , "setCaCertificates"
    , "setCiphers"
    , "setLocalCertificate"
    , "setPeerVerifyDepth"
    , "setPeerVerifyMode"
    , "setPrivateKey"
    , "setProtocol"
    , "toString"
};

static const char * const qtscript_QSslConfiguration_function_signatures[] = {
    "\nQSslConfiguration other"
    // static
    , ""
    , "QSslConfiguration configuration"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QSslConfiguration other"
    , "QSslConfiguration other"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "List certificates"
    , "List ciphers"
    , "QSslCertificate certificate"
    , "int depth"
    , "PeerVerifyMode mode"
    , "QSslKey key"
    , "SslProtocol protocol"
""
};

static const int qtscript_QSslConfiguration_function_lengths[] = {
    1
    // static
    , 0
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
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
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QSslConfiguration_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSslConfiguration::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSslConfiguration)
Q_DECLARE_METATYPE(QSslConfiguration*)
Q_DECLARE_METATYPE(QSslCertificate)
Q_DECLARE_METATYPE(QList<QSslCertificate>)
Q_DECLARE_METATYPE(QSslCipher)
Q_DECLARE_METATYPE(QList<QSslCipher>)
Q_DECLARE_METATYPE(QSslSocket::PeerVerifyMode)
Q_DECLARE_METATYPE(QSslKey)
Q_DECLARE_METATYPE(QSsl::SslProtocol)

//
// QSslConfiguration
//

static QScriptValue qtscript_QSslConfiguration_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSslConfiguration* _q_self = qscriptvalue_cast<QSslConfiguration*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSslConfiguration.%0(): this object is not a QSslConfiguration")
            .arg(qtscript_QSslConfiguration_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QSslCertificate> _q_result = _q_self->caCertificates();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QSslCipher> _q_result = _q_self->ciphers();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSslCertificate _q_result = _q_self->localCertificate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QSslConfiguration _q_arg0 = qscriptvalue_cast<QSslConfiguration>(context->argument(0));
        QSslConfiguration _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QSslConfiguration _q_arg0 = qscriptvalue_cast<QSslConfiguration>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QSslCertificate _q_result = _q_self->peerCertificate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QList<QSslCertificate> _q_result = _q_self->peerCertificateChain();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->peerVerifyDepth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QSslSocket::PeerVerifyMode _q_result = _q_self->peerVerifyMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QSslKey _q_result = _q_self->privateKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QSsl::SslProtocol _q_result = _q_self->protocol();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QSslCipher _q_result = _q_self->sessionCipher();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QList<QSslCertificate> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setCaCertificates(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QList<QSslCipher> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setCiphers(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
        _q_self->setLocalCertificate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPeerVerifyDepth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QSslSocket::PeerVerifyMode _q_arg0 = qscriptvalue_cast<QSslSocket::PeerVerifyMode>(context->argument(0));
        _q_self->setPeerVerifyMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QSslKey _q_arg0 = qscriptvalue_cast<QSslKey>(context->argument(0));
        _q_self->setPrivateKey(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QSsl::SslProtocol _q_arg0 = qscriptvalue_cast<QSsl::SslProtocol>(context->argument(0));
        _q_self->setProtocol(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20: {
    QString result = QString::fromLatin1("QSslConfiguration");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslConfiguration_throw_ambiguity_error_helper(context,
        qtscript_QSslConfiguration_function_names[_id+3],
        qtscript_QSslConfiguration_function_signatures[_id+3]);
}

static QScriptValue qtscript_QSslConfiguration_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSslConfiguration(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSslConfiguration _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QSslConfiguration _q_arg0 = qscriptvalue_cast<QSslConfiguration>(context->argument(0));
        QSslConfiguration _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSslConfiguration _q_result = QSslConfiguration::defaultConfiguration();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QSslConfiguration _q_arg0 = qscriptvalue_cast<QSslConfiguration>(context->argument(0));
        QSslConfiguration::setDefaultConfiguration(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslConfiguration_throw_ambiguity_error_helper(context,
        qtscript_QSslConfiguration_function_names[_id],
        qtscript_QSslConfiguration_function_signatures[_id]);
}

QScriptValue qtscript_create_QSslConfiguration_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSslConfiguration*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSslConfiguration*)0));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslConfiguration_prototype_call, qtscript_QSslConfiguration_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSslConfiguration_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSslConfiguration>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSslConfiguration*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSslConfiguration_static_call, proto, qtscript_QSslConfiguration_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslConfiguration_static_call,
            qtscript_QSslConfiguration_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSslConfiguration_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
