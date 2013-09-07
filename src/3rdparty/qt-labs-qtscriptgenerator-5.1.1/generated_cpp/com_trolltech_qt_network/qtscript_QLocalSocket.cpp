#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlocalsocket.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocalsocket.h>
#include <qobject.h>

#include "qtscriptshell_QLocalSocket.h"

static const char * const qtscript_QLocalSocket_function_names[] = {
    "QLocalSocket"
    // static
    // prototype
    , "abort"
    , "connectToServer"
    , "disconnectFromServer"
    , "error"
    , "flush"
    , "fullServerName"
    , "isValid"
    , "readBufferSize"
    , "serverName"
    , "setReadBufferSize"
    , "setServerName"
    , "state"
    , "waitForConnected"
    , "waitForDisconnected"
    , "toString"
};

static const char * const qtscript_QLocalSocket_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "OpenMode openMode\nString name, OpenMode openMode"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qint64 size"
    , "String name"
    , ""
    , "int msecs"
    , "int msecs"
""
};

static const int qtscript_QLocalSocket_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QLocalSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLocalSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLocalSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QLocalSocket*)
Q_DECLARE_METATYPE(QLocalSocket::LocalSocketState)
Q_DECLARE_METATYPE(QLocalSocket::LocalSocketError)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
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
// QLocalSocket::LocalSocketState
//

static const QLocalSocket::LocalSocketState qtscript_QLocalSocket_LocalSocketState_values[] = {
    QLocalSocket::UnconnectedState
    , QLocalSocket::ConnectingState
    , QLocalSocket::ConnectedState
    , QLocalSocket::ClosingState
};

static const char * const qtscript_QLocalSocket_LocalSocketState_keys[] = {
    "UnconnectedState"
    , "ConnectingState"
    , "ConnectedState"
    , "ClosingState"
};

static QString qtscript_QLocalSocket_LocalSocketState_toStringHelper(QLocalSocket::LocalSocketState value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QLocalSocket_LocalSocketState_values[i] == value)
            return QString::fromLatin1(qtscript_QLocalSocket_LocalSocketState_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QLocalSocket_LocalSocketState_toScriptValue(QScriptEngine *engine, const QLocalSocket::LocalSocketState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocalSocket"));
    return clazz.property(qtscript_QLocalSocket_LocalSocketState_toStringHelper(value));
}

static void qtscript_QLocalSocket_LocalSocketState_fromScriptValue(const QScriptValue &value, QLocalSocket::LocalSocketState &out)
{
    out = qvariant_cast<QLocalSocket::LocalSocketState>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocalSocket_LocalSocketState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QLocalSocket_LocalSocketState_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QLocalSocket::LocalSocketState>(arg));
    }
    return context->throwError(QString::fromLatin1("LocalSocketState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocalSocket_LocalSocketState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocalSocket::LocalSocketState value = qscriptvalue_cast<QLocalSocket::LocalSocketState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocalSocket_LocalSocketState_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocalSocket::LocalSocketState value = qscriptvalue_cast<QLocalSocket::LocalSocketState>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocalSocket_LocalSocketState_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocalSocket_LocalSocketState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocalSocket_LocalSocketState,
        qtscript_QLocalSocket_LocalSocketState_valueOf, qtscript_QLocalSocket_LocalSocketState_toString);
    qScriptRegisterMetaType<QLocalSocket::LocalSocketState>(engine, qtscript_QLocalSocket_LocalSocketState_toScriptValue,
        qtscript_QLocalSocket_LocalSocketState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocalSocket_LocalSocketState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocalSocket_LocalSocketState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocalSocket::LocalSocketError
//

static const QLocalSocket::LocalSocketError qtscript_QLocalSocket_LocalSocketError_values[] = {
    QLocalSocket::UnknownSocketError
    , QLocalSocket::ConnectionRefusedError
    , QLocalSocket::PeerClosedError
    , QLocalSocket::ServerNotFoundError
    , QLocalSocket::SocketAccessError
    , QLocalSocket::SocketResourceError
    , QLocalSocket::SocketTimeoutError
    , QLocalSocket::DatagramTooLargeError
    , QLocalSocket::ConnectionError
    , QLocalSocket::UnsupportedSocketOperationError
    , QLocalSocket::OperationError
};

static const char * const qtscript_QLocalSocket_LocalSocketError_keys[] = {
    "UnknownSocketError"
    , "ConnectionRefusedError"
    , "PeerClosedError"
    , "ServerNotFoundError"
    , "SocketAccessError"
    , "SocketResourceError"
    , "SocketTimeoutError"
    , "DatagramTooLargeError"
    , "ConnectionError"
    , "UnsupportedSocketOperationError"
    , "OperationError"
};

static QString qtscript_QLocalSocket_LocalSocketError_toStringHelper(QLocalSocket::LocalSocketError value)
{
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QLocalSocket_LocalSocketError_values[i] == value)
            return QString::fromLatin1(qtscript_QLocalSocket_LocalSocketError_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QLocalSocket_LocalSocketError_toScriptValue(QScriptEngine *engine, const QLocalSocket::LocalSocketError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocalSocket"));
    return clazz.property(qtscript_QLocalSocket_LocalSocketError_toStringHelper(value));
}

static void qtscript_QLocalSocket_LocalSocketError_fromScriptValue(const QScriptValue &value, QLocalSocket::LocalSocketError &out)
{
    out = qvariant_cast<QLocalSocket::LocalSocketError>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocalSocket_LocalSocketError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QLocalSocket_LocalSocketError_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QLocalSocket::LocalSocketError>(arg));
    }
    return context->throwError(QString::fromLatin1("LocalSocketError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocalSocket_LocalSocketError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocalSocket::LocalSocketError value = qscriptvalue_cast<QLocalSocket::LocalSocketError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocalSocket_LocalSocketError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocalSocket::LocalSocketError value = qscriptvalue_cast<QLocalSocket::LocalSocketError>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocalSocket_LocalSocketError_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocalSocket_LocalSocketError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocalSocket_LocalSocketError,
        qtscript_QLocalSocket_LocalSocketError_valueOf, qtscript_QLocalSocket_LocalSocketError_toString);
    qScriptRegisterMetaType<QLocalSocket::LocalSocketError>(engine, qtscript_QLocalSocket_LocalSocketError_toScriptValue,
        qtscript_QLocalSocket_LocalSocketError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocalSocket_LocalSocketError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocalSocket_LocalSocketError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocalSocket
//

static QScriptValue qtscript_QLocalSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QLocalSocket* _q_self = qscriptvalue_cast<QLocalSocket*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLocalSocket.%0(): this object is not a QLocalSocket")
            .arg(qtscript_QLocalSocket_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->abort();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->connectToServer();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(0).toVariant().userType())) {
            QFlags<QIODevice::OpenModeFlag> _q_arg0 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(0));
            _q_self->connectToServer(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->connectToServer(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QIODevice::OpenModeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(1));
        _q_self->connectToServer(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->disconnectFromServer();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QLocalSocket::LocalSocketError _q_result = _q_self->error();
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
        QString _q_result = _q_self->fullServerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->readBufferSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->serverName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setReadBufferSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setServerName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QLocalSocket::LocalSocketState _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
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

    case 13:
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

    case 14: {
    QString result = QString::fromLatin1("QLocalSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocalSocket_throw_ambiguity_error_helper(context,
        qtscript_QLocalSocket_function_names[_id+1],
        qtscript_QLocalSocket_function_signatures[_id+1]);
}

static QScriptValue qtscript_QLocalSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLocalSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLocalSocket* _q_cpp_result = new QtScriptShell_QLocalSocket();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLocalSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QLocalSocket* _q_cpp_result = new QtScriptShell_QLocalSocket(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLocalSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocalSocket_throw_ambiguity_error_helper(context,
        qtscript_QLocalSocket_function_names[_id],
        qtscript_QLocalSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QLocalSocket_toScriptValue(QScriptEngine *engine, QLocalSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLocalSocket_fromScriptValue(const QScriptValue &value, QLocalSocket* &out)
{
    out = qobject_cast<QLocalSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QLocalSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLocalSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLocalSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocalSocket_prototype_call, qtscript_QLocalSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLocalSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLocalSocket*>(engine, qtscript_QLocalSocket_toScriptValue, 
        qtscript_QLocalSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLocalSocket_static_call, proto, qtscript_QLocalSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("LocalSocketState"),
        qtscript_create_QLocalSocket_LocalSocketState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("LocalSocketError"),
        qtscript_create_QLocalSocket_LocalSocketError_class(engine, ctor));
    return ctor;
}
