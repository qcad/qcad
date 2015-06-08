#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qlocalserver.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocalserver.h>
#include <qlocalsocket.h>
#include <qobject.h>

#include "qtscriptshell_QLocalServer.h"

static const char * const qtscript_QLocalServer_function_names[] = {
    "QLocalServer"
    // static
    , "removeServer"
    // prototype
    , "close"
    , "errorString"
    , "fullServerName"
    , "hasPendingConnections"
    , "isListening"
    , "listen"
    , "maxPendingConnections"
    , "nextPendingConnection"
    , "serverError"
    , "serverName"
    , "setMaxPendingConnections"
    , "waitForNewConnection"
    , "toString"
};

static const char * const qtscript_QLocalServer_function_signatures[] = {
    "QObject parent"
    // static
    , "String name"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String name"
    , ""
    , ""
    , ""
    , ""
    , "int numConnections"
    , "int msec"
""
};

static const int qtscript_QLocalServer_function_lengths[] = {
    1
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QLocalServer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLocalServer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLocalServer*)
Q_DECLARE_METATYPE(QtScriptShell_QLocalServer*)
Q_DECLARE_METATYPE(QLocalSocket*)
Q_DECLARE_METATYPE(QAbstractSocket::SocketError)

//
// QLocalServer
//

static QScriptValue qtscript_QLocalServer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QLocalServer* _q_self = qscriptvalue_cast<QLocalServer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLocalServer.%0(): this object is not a QLocalServer")
            .arg(qtscript_QLocalServer_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->close();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fullServerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPendingConnections();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isListening();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->listen(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->maxPendingConnections();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QLocalSocket* _q_result = _q_self->nextPendingConnection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketError _q_result = _q_self->serverError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->serverName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setMaxPendingConnections(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForNewConnection();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForNewConnection(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QLocalServer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocalServer_throw_ambiguity_error_helper(context,
        qtscript_QLocalServer_function_names[_id+2],
        qtscript_QLocalServer_function_signatures[_id+2]);
}

static QScriptValue qtscript_QLocalServer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLocalServer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLocalServer* _q_cpp_result = new QtScriptShell_QLocalServer();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLocalServer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QLocalServer* _q_cpp_result = new QtScriptShell_QLocalServer(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLocalServer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QLocalServer::removeServer(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocalServer_throw_ambiguity_error_helper(context,
        qtscript_QLocalServer_function_names[_id],
        qtscript_QLocalServer_function_signatures[_id]);
}

static QScriptValue qtscript_QLocalServer_toScriptValue(QScriptEngine *engine, QLocalServer* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLocalServer_fromScriptValue(const QScriptValue &value, QLocalServer* &out)
{
    out = qobject_cast<QLocalServer*>(value.toQObject());
}

QScriptValue qtscript_create_QLocalServer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLocalServer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLocalServer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocalServer_prototype_call, qtscript_QLocalServer_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLocalServer_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLocalServer*>(engine, qtscript_QLocalServer_toScriptValue, 
        qtscript_QLocalServer_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLocalServer_static_call, proto, qtscript_QLocalServer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocalServer_static_call,
            qtscript_QLocalServer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLocalServer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
