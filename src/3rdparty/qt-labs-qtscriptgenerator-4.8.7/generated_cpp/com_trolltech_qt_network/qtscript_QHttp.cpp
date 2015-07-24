#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qhttp.h>
#include <QVariant>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhttp.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qsslerror.h>
#include <qtcpsocket.h>

#include "qtscriptshell_QHttp.h"

static const char * const qtscript_QHttp_function_names[] = {
    "QHttp"
    // static
    // prototype
    , "bytesAvailable"
    , "clearPendingRequests"
    , "close"
    , "currentDestinationDevice"
    , "currentId"
    , "currentRequest"
    , "currentSourceDevice"
    , "error"
    , "errorString"
    , "get"
    , "hasPendingRequests"
    , "head"
    , "lastResponse"
    , "post"
    , "read"
    , "readAll"
    , "request"
    , "setHost"
    , "setProxy"
    , "setSocket"
    , "setUser"
    , "state"
    , "toString"
};

static const char * const qtscript_QHttp_function_signatures[] = {
    "QObject parent\nString hostname, ConnectionMode mode, unsigned short port, QObject parent\nString hostname, unsigned short port, QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String path, QIODevice to"
    , ""
    , "String path"
    , ""
    , "String path, QIODevice data, QIODevice to\nString path, QByteArray data, QIODevice to"
    , "char data, qint64 maxlen"
    , ""
    , "QHttpRequestHeader header, QIODevice device, QIODevice to\nQHttpRequestHeader header, QByteArray data, QIODevice to"
    , "String hostname, ConnectionMode mode, unsigned short port\nString hostname, unsigned short port"
    , "QNetworkProxy proxy\nString host, int port, String username, String password"
    , "QTcpSocket socket"
    , "String username, String password"
    , ""
""
};

static const int qtscript_QHttp_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 0
    , 3
    , 2
    , 0
    , 3
    , 3
    , 4
    , 1
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QHttp_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHttp::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QHttp*)
Q_DECLARE_METATYPE(QtScriptShell_QHttp*)
Q_DECLARE_METATYPE(QHttp::Error)
Q_DECLARE_METATYPE(QHttp::ConnectionMode)
Q_DECLARE_METATYPE(QHttp::State)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QHttpRequestHeader)
Q_DECLARE_METATYPE(QHttpResponseHeader)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QNetworkProxy)
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
// QHttp::Error
//

static const QHttp::Error qtscript_QHttp_Error_values[] = {
    QHttp::NoError
    , QHttp::UnknownError
    , QHttp::HostNotFound
    , QHttp::ConnectionRefused
    , QHttp::UnexpectedClose
    , QHttp::InvalidResponseHeader
    , QHttp::WrongContentLength
    , QHttp::Aborted
    , QHttp::AuthenticationRequiredError
    , QHttp::ProxyAuthenticationRequiredError
};

static const char * const qtscript_QHttp_Error_keys[] = {
    "NoError"
    , "UnknownError"
    , "HostNotFound"
    , "ConnectionRefused"
    , "UnexpectedClose"
    , "InvalidResponseHeader"
    , "WrongContentLength"
    , "Aborted"
    , "AuthenticationRequiredError"
    , "ProxyAuthenticationRequiredError"
};

static QString qtscript_QHttp_Error_toStringHelper(QHttp::Error value)
{
    if ((value >= QHttp::NoError) && (value <= QHttp::ProxyAuthenticationRequiredError))
        return qtscript_QHttp_Error_keys[static_cast<int>(value)-static_cast<int>(QHttp::NoError)];
    return QString();
}

static QScriptValue qtscript_QHttp_Error_toScriptValue(QScriptEngine *engine, const QHttp::Error &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QHttp"));
    return clazz.property(qtscript_QHttp_Error_toStringHelper(value));
}

static void qtscript_QHttp_Error_fromScriptValue(const QScriptValue &value, QHttp::Error &out)
{
    out = qvariant_cast<QHttp::Error>(value.toVariant());
}

static QScriptValue qtscript_construct_QHttp_Error(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QHttp::NoError) && (arg <= QHttp::ProxyAuthenticationRequiredError))
        return qScriptValueFromValue(engine,  static_cast<QHttp::Error>(arg));
    return context->throwError(QString::fromLatin1("Error(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QHttp_Error_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QHttp::Error value = qscriptvalue_cast<QHttp::Error>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QHttp_Error_toString(QScriptContext *context, QScriptEngine *engine)
{
    QHttp::Error value = qscriptvalue_cast<QHttp::Error>(context->thisObject());
    return QScriptValue(engine, qtscript_QHttp_Error_toStringHelper(value));
}

static QScriptValue qtscript_create_QHttp_Error_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QHttp_Error,
        qtscript_QHttp_Error_valueOf, qtscript_QHttp_Error_toString);
    qScriptRegisterMetaType<QHttp::Error>(engine, qtscript_QHttp_Error_toScriptValue,
        qtscript_QHttp_Error_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 10; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QHttp_Error_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QHttp_Error_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QHttp::ConnectionMode
//

static const QHttp::ConnectionMode qtscript_QHttp_ConnectionMode_values[] = {
    QHttp::ConnectionModeHttp
    , QHttp::ConnectionModeHttps
};

static const char * const qtscript_QHttp_ConnectionMode_keys[] = {
    "ConnectionModeHttp"
    , "ConnectionModeHttps"
};

static QString qtscript_QHttp_ConnectionMode_toStringHelper(QHttp::ConnectionMode value)
{
    if ((value >= QHttp::ConnectionModeHttp) && (value <= QHttp::ConnectionModeHttps))
        return qtscript_QHttp_ConnectionMode_keys[static_cast<int>(value)-static_cast<int>(QHttp::ConnectionModeHttp)];
    return QString();
}

static QScriptValue qtscript_QHttp_ConnectionMode_toScriptValue(QScriptEngine *engine, const QHttp::ConnectionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QHttp"));
    return clazz.property(qtscript_QHttp_ConnectionMode_toStringHelper(value));
}

static void qtscript_QHttp_ConnectionMode_fromScriptValue(const QScriptValue &value, QHttp::ConnectionMode &out)
{
    out = qvariant_cast<QHttp::ConnectionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QHttp_ConnectionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QHttp::ConnectionModeHttp) && (arg <= QHttp::ConnectionModeHttps))
        return qScriptValueFromValue(engine,  static_cast<QHttp::ConnectionMode>(arg));
    return context->throwError(QString::fromLatin1("ConnectionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QHttp_ConnectionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QHttp::ConnectionMode value = qscriptvalue_cast<QHttp::ConnectionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QHttp_ConnectionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QHttp::ConnectionMode value = qscriptvalue_cast<QHttp::ConnectionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QHttp_ConnectionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QHttp_ConnectionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QHttp_ConnectionMode,
        qtscript_QHttp_ConnectionMode_valueOf, qtscript_QHttp_ConnectionMode_toString);
    qScriptRegisterMetaType<QHttp::ConnectionMode>(engine, qtscript_QHttp_ConnectionMode_toScriptValue,
        qtscript_QHttp_ConnectionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QHttp_ConnectionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QHttp_ConnectionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QHttp::State
//

static const QHttp::State qtscript_QHttp_State_values[] = {
    QHttp::Unconnected
    , QHttp::HostLookup
    , QHttp::Connecting
    , QHttp::Sending
    , QHttp::Reading
    , QHttp::Connected
    , QHttp::Closing
};

static const char * const qtscript_QHttp_State_keys[] = {
    "Unconnected"
    , "HostLookup"
    , "Connecting"
    , "Sending"
    , "Reading"
    , "Connected"
    , "Closing"
};

static QString qtscript_QHttp_State_toStringHelper(QHttp::State value)
{
    if ((value >= QHttp::Unconnected) && (value <= QHttp::Closing))
        return qtscript_QHttp_State_keys[static_cast<int>(value)-static_cast<int>(QHttp::Unconnected)];
    return QString();
}

static QScriptValue qtscript_QHttp_State_toScriptValue(QScriptEngine *engine, const QHttp::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QHttp"));
    return clazz.property(qtscript_QHttp_State_toStringHelper(value));
}

static void qtscript_QHttp_State_fromScriptValue(const QScriptValue &value, QHttp::State &out)
{
    out = qvariant_cast<QHttp::State>(value.toVariant());
}

static QScriptValue qtscript_construct_QHttp_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QHttp::Unconnected) && (arg <= QHttp::Closing))
        return qScriptValueFromValue(engine,  static_cast<QHttp::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QHttp_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QHttp::State value = qscriptvalue_cast<QHttp::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QHttp_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QHttp::State value = qscriptvalue_cast<QHttp::State>(context->thisObject());
    return QScriptValue(engine, qtscript_QHttp_State_toStringHelper(value));
}

static QScriptValue qtscript_create_QHttp_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QHttp_State,
        qtscript_QHttp_State_valueOf, qtscript_QHttp_State_toString);
    qScriptRegisterMetaType<QHttp::State>(engine, qtscript_QHttp_State_toScriptValue,
        qtscript_QHttp_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QHttp_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QHttp_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QHttp
//

static QScriptValue qtscript_QHttp_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 22;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QHttp* _q_self = qscriptvalue_cast<QHttp*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHttp.%0(): this object is not a QHttp")
            .arg(qtscript_QHttp_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->bytesAvailable();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clearPendingRequests();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->close();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->currentDestinationDevice();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QHttpRequestHeader _q_result = _q_self->currentRequest();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->currentSourceDevice();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QHttp::Error _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->get(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
        int _q_result = _q_self->get(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPendingRequests();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->head(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QHttpResponseHeader _q_result = _q_self->lastResponse();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<QIODevice*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            int _q_result = _q_self->post(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            int _q_result = _q_self->post(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<QIODevice*>(context->argument(1))
            && qscriptvalue_cast<QIODevice*>(context->argument(2))) {
            QString _q_arg0 = context->argument(0).toString();
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            QIODevice* _q_arg2 = qscriptvalue_cast<QIODevice*>(context->argument(2));
            int _q_result = _q_self->post(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(2))) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QIODevice* _q_arg2 = qscriptvalue_cast<QIODevice*>(context->argument(2));
            int _q_result = _q_self->post(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        qint64 _q_result = _q_self->read(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->readAll();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QHttpRequestHeader _q_arg0 = qscriptvalue_cast<QHttpRequestHeader>(context->argument(0));
        int _q_result = _q_self->request(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QHttpRequestHeader>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(1))) {
            QHttpRequestHeader _q_arg0 = qscriptvalue_cast<QHttpRequestHeader>(context->argument(0));
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            int _q_result = _q_self->request(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QHttpRequestHeader>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QHttpRequestHeader _q_arg0 = qscriptvalue_cast<QHttpRequestHeader>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            int _q_result = _q_self->request(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QHttpRequestHeader>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(1))
            && qscriptvalue_cast<QIODevice*>(context->argument(2))) {
            QHttpRequestHeader _q_arg0 = qscriptvalue_cast<QHttpRequestHeader>(context->argument(0));
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            QIODevice* _q_arg2 = qscriptvalue_cast<QIODevice*>(context->argument(2));
            int _q_result = _q_self->request(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QHttpRequestHeader>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(2))) {
            QHttpRequestHeader _q_arg0 = qscriptvalue_cast<QHttpRequestHeader>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QIODevice* _q_arg2 = qscriptvalue_cast<QIODevice*>(context->argument(2));
            int _q_result = _q_self->request(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->setHost(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QHttp::ConnectionMode>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QHttp::ConnectionMode _q_arg1 = qscriptvalue_cast<QHttp::ConnectionMode>(context->argument(1));
            int _q_result = _q_self->setHost(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            int _q_result = _q_self->setHost(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QHttp::ConnectionMode _q_arg1 = qscriptvalue_cast<QHttp::ConnectionMode>(context->argument(1));
        unsigned short _q_arg2 = qscriptvalue_cast<unsigned short>(context->argument(2));
        int _q_result = _q_self->setHost(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QNetworkProxy _q_arg0 = qscriptvalue_cast<QNetworkProxy>(context->argument(0));
        int _q_result = _q_self->setProxy(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->setProxy(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_arg2 = context->argument(2).toString();
        int _q_result = _q_self->setProxy(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        int _q_result = _q_self->setProxy(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QTcpSocket* _q_arg0 = qscriptvalue_cast<QTcpSocket*>(context->argument(0));
        int _q_result = _q_self->setSocket(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->setUser(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->setUser(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QHttp::State _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22: {
    QString result = QString::fromLatin1("QHttp");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHttp_throw_ambiguity_error_helper(context,
        qtscript_QHttp_function_names[_id+1],
        qtscript_QHttp_function_signatures[_id+1]);
}

static QScriptValue qtscript_QHttp_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHttp(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QHttp::ConnectionMode>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QHttp::ConnectionMode _q_arg1 = qscriptvalue_cast<QHttp::ConnectionMode>(context->argument(1));
            QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QHttp::ConnectionMode>() == context->argument(1).toVariant().userType())
            && context->argument(2).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            QHttp::ConnectionMode _q_arg1 = qscriptvalue_cast<QHttp::ConnectionMode>(context->argument(1));
            unsigned short _q_arg2 = qscriptvalue_cast<unsigned short>(context->argument(2));
            QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && context->argument(2).isQObject()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QObject* _q_arg2 = context->argument(2).toQObject();
            QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QHttp::ConnectionMode _q_arg1 = qscriptvalue_cast<QHttp::ConnectionMode>(context->argument(1));
        unsigned short _q_arg2 = qscriptvalue_cast<unsigned short>(context->argument(2));
        QObject* _q_arg3 = context->argument(3).toQObject();
        QtScriptShell_QHttp* _q_cpp_result = new QtScriptShell_QHttp(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHttp*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHttp_throw_ambiguity_error_helper(context,
        qtscript_QHttp_function_names[_id],
        qtscript_QHttp_function_signatures[_id]);
}

static QScriptValue qtscript_QHttp_toScriptValue(QScriptEngine *engine, QHttp* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QHttp_fromScriptValue(const QScriptValue &value, QHttp* &out)
{
    out = qobject_cast<QHttp*>(value.toQObject());
}

QScriptValue qtscript_create_QHttp_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHttp*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHttp*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 23; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QHttp_prototype_call, qtscript_QHttp_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QHttp_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QHttp*>(engine, qtscript_QHttp_toScriptValue, 
        qtscript_QHttp_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHttp_static_call, proto, qtscript_QHttp_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Error"),
        qtscript_create_QHttp_Error_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ConnectionMode"),
        qtscript_create_QHttp_ConnectionMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QHttp_State_class(engine, ctor));
    return ctor;
}
