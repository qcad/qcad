#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtcpserver.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>

#include "qtscriptshell_QTcpServer.h"

static const char * const qtscript_QTcpServer_function_names[] = {
    "QTcpServer"
    // static
    // prototype
    , "close"
    , "errorString"
    , "hasPendingConnections"
    , "isListening"
    , "listen"
    , "maxPendingConnections"
    , "nextPendingConnection"
    , "pauseAccepting"
    , "proxy"
    , "resumeAccepting"
    , "serverAddress"
    , "serverError"
    , "serverPort"
    , "setMaxPendingConnections"
    , "setProxy"
    , "waitForNewConnection"
    , "toString"
};

static const char * const qtscript_QTcpServer_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QHostAddress address, unsigned short port"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int numConnections"
    , "QNetworkProxy networkProxy"
    , "int msec"
""
};

static const int qtscript_QTcpServer_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 2
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
    , 0
};

static QScriptValue qtscript_QTcpServer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTcpServer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTcpServer*)
Q_DECLARE_METATYPE(QtScriptShell_QTcpServer*)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QTcpSocket*)

//
// QTcpServer
//

static QScriptValue qtscript_QTcpServer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 16;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTcpServer* _q_self = qscriptvalue_cast<QTcpServer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTcpServer.%0(): this object is not a QTcpServer")
            .arg(qtscript_QTcpServer_function_names[_id+1]));
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
        bool _q_result = _q_self->hasPendingConnections();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isListening();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->listen();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        bool _q_result = _q_self->listen(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        bool _q_result = _q_self->listen(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->maxPendingConnections();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QTcpSocket* _q_result = _q_self->nextPendingConnection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->pauseAccepting();
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QNetworkProxy _q_result = _q_self->proxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->resumeAccepting();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->serverAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketError _q_result = _q_self->serverError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->serverPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setMaxPendingConnections(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QNetworkProxy _q_arg0 = qscriptvalue_cast<QNetworkProxy>(context->argument(0));
        _q_self->setProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
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

    case 16: {
    QString result = QString::fromLatin1("QTcpServer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTcpServer_throw_ambiguity_error_helper(context,
        qtscript_QTcpServer_function_names[_id+1],
        qtscript_QTcpServer_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTcpServer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTcpServer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTcpServer* _q_cpp_result = new QtScriptShell_QTcpServer();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTcpServer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QTcpServer* _q_cpp_result = new QtScriptShell_QTcpServer(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTcpServer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTcpServer_throw_ambiguity_error_helper(context,
        qtscript_QTcpServer_function_names[_id],
        qtscript_QTcpServer_function_signatures[_id]);
}

static QScriptValue qtscript_QTcpServer_toScriptValue(QScriptEngine *engine, QTcpServer* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTcpServer_fromScriptValue(const QScriptValue &value, QTcpServer* &out)
{
    out = qobject_cast<QTcpServer*>(value.toQObject());
}

QScriptValue qtscript_create_QTcpServer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTcpServer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTcpServer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTcpServer_prototype_call, qtscript_QTcpServer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTcpServer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTcpServer*>(engine, qtscript_QTcpServer_toScriptValue, 
        qtscript_QTcpServer_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTcpServer_static_call, proto, qtscript_QTcpServer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
