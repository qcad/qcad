#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qudpsocket.h>
#include <QVariant>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkinterface.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qudpsocket.h>

#include "qtscriptshell_QUdpSocket.h"

static const char * const qtscript_QUdpSocket_function_names[] = {
    "QUdpSocket"
    // static
    // prototype
    , "hasPendingDatagrams"
    , "joinMulticastGroup"
    , "leaveMulticastGroup"
    , "multicastInterface"
    , "pendingDatagramSize"
    , "readDatagram"
    , "setMulticastInterface"
    , "writeDatagram"
    , "toString"
};

static const char * const qtscript_QUdpSocket_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QHostAddress groupAddress\nQHostAddress groupAddress, QNetworkInterface iface"
    , "QHostAddress groupAddress\nQHostAddress groupAddress, QNetworkInterface iface"
    , ""
    , ""
    , "char data, qint64 maxlen, QHostAddress host, unsigned short port"
    , "QNetworkInterface iface"
    , "QByteArray datagram, QHostAddress host, unsigned short port"
""
};

static const int qtscript_QUdpSocket_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 2
    , 2
    , 0
    , 0
    , 4
    , 1
    , 3
    , 0
};

static QScriptValue qtscript_QUdpSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUdpSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUdpSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QUdpSocket*)
Q_DECLARE_METATYPE(QHostAddress)
#if QT_VERSION < 0x050600
Q_DECLARE_METATYPE(QNetworkInterface)
#endif
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QHostAddress*)
Q_DECLARE_METATYPE(unsigned short*)
Q_DECLARE_METATYPE(QAbstractSocket*)

//
// QUdpSocket
//

static QScriptValue qtscript_QUdpSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUdpSocket* _q_self = qscriptvalue_cast<QUdpSocket*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUdpSocket.%0(): this object is not a QUdpSocket")
            .arg(qtscript_QUdpSocket_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPendingDatagrams();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        bool _q_result = _q_self->joinMulticastGroup(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        QNetworkInterface _q_arg1 = qscriptvalue_cast<QNetworkInterface>(context->argument(1));
        bool _q_result = _q_self->joinMulticastGroup(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        bool _q_result = _q_self->leaveMulticastGroup(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        QNetworkInterface _q_arg1 = qscriptvalue_cast<QNetworkInterface>(context->argument(1));
        bool _q_result = _q_self->leaveMulticastGroup(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QNetworkInterface _q_result = _q_self->multicastInterface();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->pendingDatagramSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        qint64 _q_result = _q_self->readDatagram(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        QHostAddress* _q_arg2 = qscriptvalue_cast<QHostAddress*>(context->argument(2));
        qint64 _q_result = _q_self->readDatagram(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        QHostAddress* _q_arg2 = qscriptvalue_cast<QHostAddress*>(context->argument(2));
        unsigned short* _q_arg3 = qscriptvalue_cast<unsigned short*>(context->argument(3));
        qint64 _q_result = _q_self->readDatagram(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QNetworkInterface _q_arg0 = qscriptvalue_cast<QNetworkInterface>(context->argument(0));
        _q_self->setMulticastInterface(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QHostAddress _q_arg1 = qscriptvalue_cast<QHostAddress>(context->argument(1));
        unsigned short _q_arg2 = qscriptvalue_cast<unsigned short>(context->argument(2));
        qint64 _q_result = _q_self->writeDatagram(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QUdpSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUdpSocket_throw_ambiguity_error_helper(context,
        qtscript_QUdpSocket_function_names[_id+1],
        qtscript_QUdpSocket_function_signatures[_id+1]);
}

static QScriptValue qtscript_QUdpSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUdpSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUdpSocket* _q_cpp_result = new QtScriptShell_QUdpSocket();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUdpSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QUdpSocket* _q_cpp_result = new QtScriptShell_QUdpSocket(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUdpSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUdpSocket_throw_ambiguity_error_helper(context,
        qtscript_QUdpSocket_function_names[_id],
        qtscript_QUdpSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QUdpSocket_toScriptValue(QScriptEngine *engine, QUdpSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QUdpSocket_fromScriptValue(const QScriptValue &value, QUdpSocket* &out)
{
    out = qobject_cast<QUdpSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QUdpSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUdpSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUdpSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractSocket*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUdpSocket_prototype_call, qtscript_QUdpSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUdpSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QUdpSocket*>(engine, qtscript_QUdpSocket_toScriptValue, 
        qtscript_QUdpSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUdpSocket_static_call, proto, qtscript_QUdpSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
