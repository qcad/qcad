#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractsocket.h>
#include <QVariant>
#include <qabstractsocket.h>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>

#include "qtscriptshell_QAbstractSocket.h"

static const char * const qtscript_QAbstractSocket_function_names[] = {
    "QAbstractSocket"
    // static
    // prototype
    , "abort"
    , "connectToHost"
    , "disconnectFromHost"
    , "error"
    , "flush"
    , "isValid"
    , "localAddress"
    , "localPort"
    , "peerAddress"
    , "peerName"
    , "peerPort"
    , "proxy"
    , "readBufferSize"
    , "setProxy"
    , "setReadBufferSize"
    , "setSocketDescriptor"
    , "setSocketOption"
    , "socketDescriptor"
    , "socketOption"
    , "socketType"
    , "state"
    , "waitForConnected"
    , "waitForDisconnected"
    , "toString"
};

static const char * const qtscript_QAbstractSocket_function_signatures[] = {
    "SocketType socketType, QObject parent"
    // static
    // prototype
    , ""
    , "QHostAddress address, unsigned short port, OpenMode mode\nString hostName, unsigned short port, OpenMode mode"
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
    , ""
    , "QNetworkProxy networkProxy"
    , "qint64 size"
    , "int socketDescriptor, SocketState state, OpenMode openMode"
    , "SocketOption option, Object value"
    , ""
    , "SocketOption option"
    , ""
    , ""
    , "int msecs"
    , "int msecs"
""
};

static const int qtscript_QAbstractSocket_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 3
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
    , 0
    , 1
    , 1
    , 3
    , 2
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractSocket*)
Q_DECLARE_METATYPE(QAbstractSocket::SocketType)
Q_DECLARE_METATYPE(QAbstractSocket::SocketError)
Q_DECLARE_METATYPE(QAbstractSocket::NetworkLayerProtocol)
Q_DECLARE_METATYPE(QAbstractSocket::SocketOption)
Q_DECLARE_METATYPE(QAbstractSocket::SocketState)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(QNetworkProxy)
Q_DECLARE_METATYPE(QIODevice*)

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
// QAbstractSocket::SocketType
//

static const QAbstractSocket::SocketType qtscript_QAbstractSocket_SocketType_values[] = {
    QAbstractSocket::UnknownSocketType
    , QAbstractSocket::TcpSocket
    , QAbstractSocket::UdpSocket
};

static const char * const qtscript_QAbstractSocket_SocketType_keys[] = {
    "UnknownSocketType"
    , "TcpSocket"
    , "UdpSocket"
};

static QString qtscript_QAbstractSocket_SocketType_toStringHelper(QAbstractSocket::SocketType value)
{
    if ((value >= QAbstractSocket::UnknownSocketType) && (value <= QAbstractSocket::UdpSocket))
        return qtscript_QAbstractSocket_SocketType_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::UnknownSocketType)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_SocketType_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketType_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketType_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketType &out)
{
    out = qvariant_cast<QAbstractSocket::SocketType>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::UnknownSocketType) && (arg <= QAbstractSocket::UdpSocket))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketType>(arg));
    return context->throwError(QString::fromLatin1("SocketType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketType value = qscriptvalue_cast<QAbstractSocket::SocketType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketType value = qscriptvalue_cast<QAbstractSocket::SocketType>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketType_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketType,
        qtscript_QAbstractSocket_SocketType_valueOf, qtscript_QAbstractSocket_SocketType_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketType>(engine, qtscript_QAbstractSocket_SocketType_toScriptValue,
        qtscript_QAbstractSocket_SocketType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::SocketError
//

static const QAbstractSocket::SocketError qtscript_QAbstractSocket_SocketError_values[] = {
    QAbstractSocket::UnknownSocketError
    , QAbstractSocket::ConnectionRefusedError
    , QAbstractSocket::RemoteHostClosedError
    , QAbstractSocket::HostNotFoundError
    , QAbstractSocket::SocketAccessError
    , QAbstractSocket::SocketResourceError
    , QAbstractSocket::SocketTimeoutError
    , QAbstractSocket::DatagramTooLargeError
    , QAbstractSocket::NetworkError
    , QAbstractSocket::AddressInUseError
    , QAbstractSocket::SocketAddressNotAvailableError
    , QAbstractSocket::UnsupportedSocketOperationError
    , QAbstractSocket::UnfinishedSocketOperationError
    , QAbstractSocket::ProxyAuthenticationRequiredError
    , QAbstractSocket::SslHandshakeFailedError
    , QAbstractSocket::ProxyConnectionRefusedError
    , QAbstractSocket::ProxyConnectionClosedError
    , QAbstractSocket::ProxyConnectionTimeoutError
    , QAbstractSocket::ProxyNotFoundError
    , QAbstractSocket::ProxyProtocolError
};

static const char * const qtscript_QAbstractSocket_SocketError_keys[] = {
    "UnknownSocketError"
    , "ConnectionRefusedError"
    , "RemoteHostClosedError"
    , "HostNotFoundError"
    , "SocketAccessError"
    , "SocketResourceError"
    , "SocketTimeoutError"
    , "DatagramTooLargeError"
    , "NetworkError"
    , "AddressInUseError"
    , "SocketAddressNotAvailableError"
    , "UnsupportedSocketOperationError"
    , "UnfinishedSocketOperationError"
    , "ProxyAuthenticationRequiredError"
    , "SslHandshakeFailedError"
    , "ProxyConnectionRefusedError"
    , "ProxyConnectionClosedError"
    , "ProxyConnectionTimeoutError"
    , "ProxyNotFoundError"
    , "ProxyProtocolError"
};

static QString qtscript_QAbstractSocket_SocketError_toStringHelper(QAbstractSocket::SocketError value)
{
    if ((value >= QAbstractSocket::UnknownSocketError) && (value <= QAbstractSocket::ProxyProtocolError))
        return qtscript_QAbstractSocket_SocketError_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::UnknownSocketError)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_SocketError_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketError_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketError_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketError &out)
{
    out = qvariant_cast<QAbstractSocket::SocketError>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::UnknownSocketError) && (arg <= QAbstractSocket::ProxyProtocolError))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketError>(arg));
    return context->throwError(QString::fromLatin1("SocketError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketError value = qscriptvalue_cast<QAbstractSocket::SocketError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketError value = qscriptvalue_cast<QAbstractSocket::SocketError>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketError_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketError,
        qtscript_QAbstractSocket_SocketError_valueOf, qtscript_QAbstractSocket_SocketError_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketError>(engine, qtscript_QAbstractSocket_SocketError_toScriptValue,
        qtscript_QAbstractSocket_SocketError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 20; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::NetworkLayerProtocol
//

static const QAbstractSocket::NetworkLayerProtocol qtscript_QAbstractSocket_NetworkLayerProtocol_values[] = {
    QAbstractSocket::UnknownNetworkLayerProtocol
    , QAbstractSocket::IPv4Protocol
    , QAbstractSocket::IPv6Protocol
};

static const char * const qtscript_QAbstractSocket_NetworkLayerProtocol_keys[] = {
    "UnknownNetworkLayerProtocol"
    , "IPv4Protocol"
    , "IPv6Protocol"
};

static QString qtscript_QAbstractSocket_NetworkLayerProtocol_toStringHelper(QAbstractSocket::NetworkLayerProtocol value)
{
    if ((value >= QAbstractSocket::UnknownNetworkLayerProtocol) && (value <= QAbstractSocket::IPv6Protocol))
        return qtscript_QAbstractSocket_NetworkLayerProtocol_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::UnknownNetworkLayerProtocol)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_NetworkLayerProtocol_toScriptValue(QScriptEngine *engine, const QAbstractSocket::NetworkLayerProtocol &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_NetworkLayerProtocol_toStringHelper(value));
}

static void qtscript_QAbstractSocket_NetworkLayerProtocol_fromScriptValue(const QScriptValue &value, QAbstractSocket::NetworkLayerProtocol &out)
{
    out = qvariant_cast<QAbstractSocket::NetworkLayerProtocol>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_NetworkLayerProtocol(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::UnknownNetworkLayerProtocol) && (arg <= QAbstractSocket::IPv6Protocol))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::NetworkLayerProtocol>(arg));
    return context->throwError(QString::fromLatin1("NetworkLayerProtocol(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_NetworkLayerProtocol_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::NetworkLayerProtocol value = qscriptvalue_cast<QAbstractSocket::NetworkLayerProtocol>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_NetworkLayerProtocol_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::NetworkLayerProtocol value = qscriptvalue_cast<QAbstractSocket::NetworkLayerProtocol>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_NetworkLayerProtocol_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_NetworkLayerProtocol_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_NetworkLayerProtocol,
        qtscript_QAbstractSocket_NetworkLayerProtocol_valueOf, qtscript_QAbstractSocket_NetworkLayerProtocol_toString);
    qScriptRegisterMetaType<QAbstractSocket::NetworkLayerProtocol>(engine, qtscript_QAbstractSocket_NetworkLayerProtocol_toScriptValue,
        qtscript_QAbstractSocket_NetworkLayerProtocol_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_NetworkLayerProtocol_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_NetworkLayerProtocol_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::SocketOption
//

static const QAbstractSocket::SocketOption qtscript_QAbstractSocket_SocketOption_values[] = {
    QAbstractSocket::LowDelayOption
    , QAbstractSocket::KeepAliveOption
};

static const char * const qtscript_QAbstractSocket_SocketOption_keys[] = {
    "LowDelayOption"
    , "KeepAliveOption"
};

static QString qtscript_QAbstractSocket_SocketOption_toStringHelper(QAbstractSocket::SocketOption value)
{
    if ((value >= QAbstractSocket::LowDelayOption) && (value <= QAbstractSocket::KeepAliveOption))
        return qtscript_QAbstractSocket_SocketOption_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::LowDelayOption)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_SocketOption_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketOption_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketOption_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketOption &out)
{
    out = qvariant_cast<QAbstractSocket::SocketOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::LowDelayOption) && (arg <= QAbstractSocket::KeepAliveOption))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketOption>(arg));
    return context->throwError(QString::fromLatin1("SocketOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketOption value = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketOption value = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketOption,
        qtscript_QAbstractSocket_SocketOption_valueOf, qtscript_QAbstractSocket_SocketOption_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketOption>(engine, qtscript_QAbstractSocket_SocketOption_toScriptValue,
        qtscript_QAbstractSocket_SocketOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::SocketState
//

static const QAbstractSocket::SocketState qtscript_QAbstractSocket_SocketState_values[] = {
    QAbstractSocket::UnconnectedState
    , QAbstractSocket::HostLookupState
    , QAbstractSocket::ConnectingState
    , QAbstractSocket::ConnectedState
    , QAbstractSocket::BoundState
    , QAbstractSocket::ListeningState
    , QAbstractSocket::ClosingState
};

static const char * const qtscript_QAbstractSocket_SocketState_keys[] = {
    "UnconnectedState"
    , "HostLookupState"
    , "ConnectingState"
    , "ConnectedState"
    , "BoundState"
    , "ListeningState"
    , "ClosingState"
};

static QString qtscript_QAbstractSocket_SocketState_toStringHelper(QAbstractSocket::SocketState value)
{
    if ((value >= QAbstractSocket::UnconnectedState) && (value <= QAbstractSocket::ClosingState))
        return qtscript_QAbstractSocket_SocketState_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::UnconnectedState)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_SocketState_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketState_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketState_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketState &out)
{
    out = qvariant_cast<QAbstractSocket::SocketState>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::UnconnectedState) && (arg <= QAbstractSocket::ClosingState))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketState>(arg));
    return context->throwError(QString::fromLatin1("SocketState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketState value = qscriptvalue_cast<QAbstractSocket::SocketState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketState_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketState value = qscriptvalue_cast<QAbstractSocket::SocketState>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketState_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketState,
        qtscript_QAbstractSocket_SocketState_valueOf, qtscript_QAbstractSocket_SocketState_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketState>(engine, qtscript_QAbstractSocket_SocketState_toScriptValue,
        qtscript_QAbstractSocket_SocketState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket
//

static QScriptValue qtscript_QAbstractSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 23;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractSocket* _q_self = qscriptvalue_cast<QAbstractSocket*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractSocket.%0(): this object is not a QAbstractSocket")
            .arg(qtscript_QAbstractSocket_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->abort();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            _q_self->connectToHost(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            _q_self->connectToHost(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->disconnectFromHost();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->flush();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->localAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->localPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->peerAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->peerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->peerPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QNetworkProxy _q_result = _q_self->proxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->readBufferSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QNetworkProxy _q_arg0 = qscriptvalue_cast<QNetworkProxy>(context->argument(0));
        _q_self->setProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setReadBufferSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->setSocketDescriptor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractSocket::SocketState _q_arg1 = qscriptvalue_cast<QAbstractSocket::SocketState>(context->argument(1));
        bool _q_result = _q_self->setSocketDescriptor(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractSocket::SocketState _q_arg1 = qscriptvalue_cast<QAbstractSocket::SocketState>(context->argument(1));
        QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
        bool _q_result = _q_self->setSocketDescriptor(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QAbstractSocket::SocketOption _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setSocketOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->socketDescriptor();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QAbstractSocket::SocketOption _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->argument(0));
        QVariant _q_result = _q_self->socketOption(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketType _q_result = _q_self->socketType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketState _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForConnected();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForConnected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForDisconnected();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForDisconnected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23: {
    QString result = QString::fromLatin1("QAbstractSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSocket_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSocket_function_names[_id+1],
        qtscript_QAbstractSocket_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QAbstractSocket::SocketType _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketType>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QAbstractSocket* _q_cpp_result = new QtScriptShell_QAbstractSocket(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSocket_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSocket_function_names[_id],
        qtscript_QAbstractSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractSocket_toScriptValue(QScriptEngine *engine, QAbstractSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractSocket_fromScriptValue(const QScriptValue &value, QAbstractSocket* &out)
{
    out = qobject_cast<QAbstractSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractSocket_prototype_call, qtscript_QAbstractSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractSocket*>(engine, qtscript_QAbstractSocket_toScriptValue, 
        qtscript_QAbstractSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractSocket_static_call, proto, qtscript_QAbstractSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SocketType"),
        qtscript_create_QAbstractSocket_SocketType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketError"),
        qtscript_create_QAbstractSocket_SocketError_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NetworkLayerProtocol"),
        qtscript_create_QAbstractSocket_NetworkLayerProtocol_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketOption"),
        qtscript_create_QAbstractSocket_SocketOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketState"),
        qtscript_create_QAbstractSocket_SocketState_class(engine, ctor));
    return ctor;
}
