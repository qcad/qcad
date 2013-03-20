#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsslsocket.h>
#include <QVariant>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qsslcertificate.h>
#include <qsslcipher.h>
#include <qsslconfiguration.h>
#include <qsslerror.h>
#include <qsslkey.h>
#include <qsslsocket.h>

#include "qtscriptshell_QSslSocket.h"

static const char * const qtscript_QSslSocket_function_names[] = {
    "QSslSocket"
    // static
    , "addDefaultCaCertificate"
    , "addDefaultCaCertificates"
    , "defaultCaCertificates"
    , "defaultCiphers"
    , "setDefaultCaCertificates"
    , "setDefaultCiphers"
    , "supportedCiphers"
    , "supportsSsl"
    , "systemCaCertificates"
    // prototype
    , "addCaCertificate"
    , "addCaCertificates"
    , "caCertificates"
    , "ciphers"
    , "connectToHostEncrypted"
    , "encryptedBytesAvailable"
    , "encryptedBytesToWrite"
    , "ignoreSslErrors"
    , "isEncrypted"
    , "localCertificate"
    , "mode"
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
    , "setSslConfiguration"
    , "sslConfiguration"
    , "sslErrors"
    , "waitForEncrypted"
    , "toString"
};

static const char * const qtscript_QSslSocket_function_signatures[] = {
    "QObject parent"
    // static
    , "QSslCertificate certificate"
    , "List certificates\nString path, EncodingFormat format, PatternSyntax syntax"
    , ""
    , ""
    , "List certificates"
    , "List ciphers"
    , ""
    , ""
    , ""
    // prototype
    , "QSslCertificate certificate"
    , "List certificates\nString path, EncodingFormat format, PatternSyntax syntax"
    , ""
    , ""
    , "String hostName, unsigned short port, OpenMode mode\nString hostName, unsigned short port, String sslPeerName, OpenMode mode"
    , ""
    , ""
    , "List errors"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "List certificates"
    , "List ciphers\nString ciphers"
    , "QSslCertificate certificate\nString fileName, EncodingFormat format"
    , "int depth"
    , "PeerVerifyMode mode"
    , "QSslKey key\nString fileName, KeyAlgorithm algorithm, EncodingFormat format, QByteArray passPhrase"
    , "SslProtocol protocol"
    , "QSslConfiguration config"
    , ""
    , ""
    , "int msecs"
""
};

static const int qtscript_QSslSocket_function_lengths[] = {
    1
    // static
    , 1
    , 3
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    // prototype
    , 1
    , 3
    , 0
    , 0
    , 4
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 1
    , 1
    , 4
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QSslSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSslSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSslSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QSslSocket*)
Q_DECLARE_METATYPE(QSslSocket::SslMode)
Q_DECLARE_METATYPE(QSslSocket::PeerVerifyMode)
Q_DECLARE_METATYPE(QSslCertificate)
Q_DECLARE_METATYPE(QList<QSslCertificate>)
Q_DECLARE_METATYPE(QSsl::EncodingFormat)
Q_DECLARE_METATYPE(QRegExp::PatternSyntax)
Q_DECLARE_METATYPE(QSslCipher)
Q_DECLARE_METATYPE(QList<QSslCipher>)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(QSslError)
Q_DECLARE_METATYPE(QSslKey)
Q_DECLARE_METATYPE(QSsl::SslProtocol)
Q_DECLARE_METATYPE(QSsl::KeyAlgorithm)
Q_DECLARE_METATYPE(QSslConfiguration)
Q_DECLARE_METATYPE(QTcpSocket*)

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
// QSslSocket::SslMode
//

static const QSslSocket::SslMode qtscript_QSslSocket_SslMode_values[] = {
    QSslSocket::UnencryptedMode
    , QSslSocket::SslClientMode
    , QSslSocket::SslServerMode
};

static const char * const qtscript_QSslSocket_SslMode_keys[] = {
    "UnencryptedMode"
    , "SslClientMode"
    , "SslServerMode"
};

static QString qtscript_QSslSocket_SslMode_toStringHelper(QSslSocket::SslMode value)
{
    if ((value >= QSslSocket::UnencryptedMode) && (value <= QSslSocket::SslServerMode))
        return qtscript_QSslSocket_SslMode_keys[static_cast<int>(value)-static_cast<int>(QSslSocket::UnencryptedMode)];
    return QString();
}

static QScriptValue qtscript_QSslSocket_SslMode_toScriptValue(QScriptEngine *engine, const QSslSocket::SslMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSslSocket"));
    return clazz.property(qtscript_QSslSocket_SslMode_toStringHelper(value));
}

static void qtscript_QSslSocket_SslMode_fromScriptValue(const QScriptValue &value, QSslSocket::SslMode &out)
{
    out = qvariant_cast<QSslSocket::SslMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QSslSocket_SslMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSslSocket::UnencryptedMode) && (arg <= QSslSocket::SslServerMode))
        return qScriptValueFromValue(engine,  static_cast<QSslSocket::SslMode>(arg));
    return context->throwError(QString::fromLatin1("SslMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSslSocket_SslMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSslSocket::SslMode value = qscriptvalue_cast<QSslSocket::SslMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSslSocket_SslMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSslSocket::SslMode value = qscriptvalue_cast<QSslSocket::SslMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QSslSocket_SslMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QSslSocket_SslMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSslSocket_SslMode,
        qtscript_QSslSocket_SslMode_valueOf, qtscript_QSslSocket_SslMode_toString);
    qScriptRegisterMetaType<QSslSocket::SslMode>(engine, qtscript_QSslSocket_SslMode_toScriptValue,
        qtscript_QSslSocket_SslMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSslSocket_SslMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSslSocket_SslMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSslSocket::PeerVerifyMode
//

static const QSslSocket::PeerVerifyMode qtscript_QSslSocket_PeerVerifyMode_values[] = {
    QSslSocket::VerifyNone
    , QSslSocket::QueryPeer
    , QSslSocket::VerifyPeer
    , QSslSocket::AutoVerifyPeer
};

static const char * const qtscript_QSslSocket_PeerVerifyMode_keys[] = {
    "VerifyNone"
    , "QueryPeer"
    , "VerifyPeer"
    , "AutoVerifyPeer"
};

static QString qtscript_QSslSocket_PeerVerifyMode_toStringHelper(QSslSocket::PeerVerifyMode value)
{
    if ((value >= QSslSocket::VerifyNone) && (value <= QSslSocket::AutoVerifyPeer))
        return qtscript_QSslSocket_PeerVerifyMode_keys[static_cast<int>(value)-static_cast<int>(QSslSocket::VerifyNone)];
    return QString();
}

static QScriptValue qtscript_QSslSocket_PeerVerifyMode_toScriptValue(QScriptEngine *engine, const QSslSocket::PeerVerifyMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSslSocket"));
    return clazz.property(qtscript_QSslSocket_PeerVerifyMode_toStringHelper(value));
}

static void qtscript_QSslSocket_PeerVerifyMode_fromScriptValue(const QScriptValue &value, QSslSocket::PeerVerifyMode &out)
{
    out = qvariant_cast<QSslSocket::PeerVerifyMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QSslSocket_PeerVerifyMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSslSocket::VerifyNone) && (arg <= QSslSocket::AutoVerifyPeer))
        return qScriptValueFromValue(engine,  static_cast<QSslSocket::PeerVerifyMode>(arg));
    return context->throwError(QString::fromLatin1("PeerVerifyMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSslSocket_PeerVerifyMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSslSocket::PeerVerifyMode value = qscriptvalue_cast<QSslSocket::PeerVerifyMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSslSocket_PeerVerifyMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSslSocket::PeerVerifyMode value = qscriptvalue_cast<QSslSocket::PeerVerifyMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QSslSocket_PeerVerifyMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QSslSocket_PeerVerifyMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSslSocket_PeerVerifyMode,
        qtscript_QSslSocket_PeerVerifyMode_valueOf, qtscript_QSslSocket_PeerVerifyMode_toString);
    qScriptRegisterMetaType<QSslSocket::PeerVerifyMode>(engine, qtscript_QSslSocket_PeerVerifyMode_toScriptValue,
        qtscript_QSslSocket_PeerVerifyMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSslSocket_PeerVerifyMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSslSocket_PeerVerifyMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSslSocket
//

static QScriptValue qtscript_QSslSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 29;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSslSocket* _q_self = qscriptvalue_cast<QSslSocket*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSslSocket.%0(): this object is not a QSslSocket")
            .arg(qtscript_QSslSocket_function_names[_id+10]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
        _q_self->addCaCertificate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isArray()) {
            QList<QSslCertificate> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->addCaCertificates(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->addCaCertificates(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        bool _q_result = _q_self->addCaCertificates(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        QRegExp::PatternSyntax _q_arg2 = qscriptvalue_cast<QRegExp::PatternSyntax>(context->argument(2));
        bool _q_result = _q_self->addCaCertificates(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QSslCertificate> _q_result = _q_self->caCertificates();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QSslCipher> _q_result = _q_self->ciphers();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        _q_self->connectToHostEncrypted(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHostEncrypted(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && context->argument(2).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QString _q_arg2 = context->argument(2).toString();
            _q_self->connectToHostEncrypted(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QIODevice::OpenModeFlag> _q_arg3 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(3));
        _q_self->connectToHostEncrypted(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->encryptedBytesAvailable();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->encryptedBytesToWrite();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QList<QSslError> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->ignoreSslErrors(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEncrypted();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QSslCertificate _q_result = _q_self->localCertificate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QSslSocket::SslMode _q_result = _q_self->mode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QSslCertificate _q_result = _q_self->peerCertificate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QList<QSslCertificate> _q_result = _q_self->peerCertificateChain();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->peerVerifyDepth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QSslSocket::PeerVerifyMode _q_result = _q_self->peerVerifyMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QSslKey _q_result = _q_self->privateKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QSsl::SslProtocol _q_result = _q_self->protocol();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QSslCipher _q_result = _q_self->sessionCipher();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QList<QSslCertificate> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setCaCertificates(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isArray()) {
            QList<QSslCipher> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->setCiphers(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setCiphers(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSslCertificate>() == context->argument(0).toVariant().userType())) {
            QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
            _q_self->setLocalCertificate(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setLocalCertificate(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        _q_self->setLocalCertificate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPeerVerifyDepth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QSslSocket::PeerVerifyMode _q_arg0 = qscriptvalue_cast<QSslSocket::PeerVerifyMode>(context->argument(0));
        _q_self->setPeerVerifyMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSslKey>() == context->argument(0).toVariant().userType())) {
            QSslKey _q_arg0 = qscriptvalue_cast<QSslKey>(context->argument(0));
            _q_self->setPrivateKey(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setPrivateKey(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
        _q_self->setPrivateKey(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
        QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
        _q_self->setPrivateKey(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
        QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
        QByteArray _q_arg3 = qscriptvalue_cast<QByteArray>(context->argument(3));
        _q_self->setPrivateKey(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QSsl::SslProtocol _q_arg0 = qscriptvalue_cast<QSsl::SslProtocol>(context->argument(0));
        _q_self->setProtocol(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QSslConfiguration _q_arg0 = qscriptvalue_cast<QSslConfiguration>(context->argument(0));
        _q_self->setSslConfiguration(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QSslConfiguration _q_result = _q_self->sslConfiguration();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QList<QSslError> _q_result = _q_self->sslErrors();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForEncrypted();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForEncrypted(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29: {
    QString result = QString::fromLatin1("QSslSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslSocket_throw_ambiguity_error_helper(context,
        qtscript_QSslSocket_function_names[_id+10],
        qtscript_QSslSocket_function_signatures[_id+10]);
}

static QScriptValue qtscript_QSslSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSslSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSslSocket* _q_cpp_result = new QtScriptShell_QSslSocket();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSslSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSslSocket* _q_cpp_result = new QtScriptShell_QSslSocket(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSslSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
        QSslSocket::addDefaultCaCertificate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isArray()) {
            QList<QSslCertificate> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QSslSocket::addDefaultCaCertificates(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = QSslSocket::addDefaultCaCertificates(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        bool _q_result = QSslSocket::addDefaultCaCertificates(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        QRegExp::PatternSyntax _q_arg2 = qscriptvalue_cast<QRegExp::PatternSyntax>(context->argument(2));
        bool _q_result = QSslSocket::addDefaultCaCertificates(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QSslCertificate> _q_result = QSslSocket::defaultCaCertificates();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QList<QSslCipher> _q_result = QSslSocket::defaultCiphers();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QList<QSslCertificate> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QSslSocket::setDefaultCaCertificates(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QList<QSslCipher> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QSslSocket::setDefaultCiphers(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QList<QSslCipher> _q_result = QSslSocket::supportedCiphers();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = QSslSocket::supportsSsl();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QList<QSslCertificate> _q_result = QSslSocket::systemCaCertificates();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslSocket_throw_ambiguity_error_helper(context,
        qtscript_QSslSocket_function_names[_id],
        qtscript_QSslSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QSslSocket_toScriptValue(QScriptEngine *engine, QSslSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSslSocket_fromScriptValue(const QScriptValue &value, QSslSocket* &out)
{
    out = qobject_cast<QSslSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QSslSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSslSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSslSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTcpSocket*>()));
    for (int i = 0; i < 30; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslSocket_prototype_call, qtscript_QSslSocket_function_lengths[i+10]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSslSocket_function_names[i+10]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSslSocket*>(engine, qtscript_QSslSocket_toScriptValue, 
        qtscript_QSslSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSslSocket_static_call, proto, qtscript_QSslSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslSocket_static_call,
            qtscript_QSslSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSslSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("SslMode"),
        qtscript_create_QSslSocket_SslMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PeerVerifyMode"),
        qtscript_create_QSslSocket_PeerVerifyMode_class(engine, ctor));
    return ctor;
}
