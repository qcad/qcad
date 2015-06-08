#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

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
    , "bind"
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
    , "QHostAddress address, unsigned short port\nQHostAddress address, unsigned short port, BindMode mode\nunsigned short port\nunsigned short port, BindMode mode"
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
    , 3
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
Q_DECLARE_METATYPE(QUdpSocket::BindFlag)
Q_DECLARE_METATYPE(QFlags<QUdpSocket::BindFlag>)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QNetworkInterface)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QHostAddress*)
Q_DECLARE_METATYPE(unsigned short*)
Q_DECLARE_METATYPE(QAbstractSocket*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QUdpSocket::BindFlag
//

static const QUdpSocket::BindFlag qtscript_QUdpSocket_BindFlag_values[] = {
    QUdpSocket::DefaultForPlatform
    , QUdpSocket::ShareAddress
    , QUdpSocket::DontShareAddress
    , QUdpSocket::ReuseAddressHint
};

static const char * const qtscript_QUdpSocket_BindFlag_keys[] = {
    "DefaultForPlatform"
    , "ShareAddress"
    , "DontShareAddress"
    , "ReuseAddressHint"
};

static QString qtscript_QUdpSocket_BindFlag_toStringHelper(QUdpSocket::BindFlag value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QUdpSocket_BindFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QUdpSocket_BindFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QUdpSocket_BindFlag_toScriptValue(QScriptEngine *engine, const QUdpSocket::BindFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QUdpSocket"));
    return clazz.property(qtscript_QUdpSocket_BindFlag_toStringHelper(value));
}

static void qtscript_QUdpSocket_BindFlag_fromScriptValue(const QScriptValue &value, QUdpSocket::BindFlag &out)
{
    out = qvariant_cast<QUdpSocket::BindFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QUdpSocket_BindFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QUdpSocket_BindFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QUdpSocket::BindFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("BindFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QUdpSocket_BindFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUdpSocket::BindFlag value = qscriptvalue_cast<QUdpSocket::BindFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUdpSocket_BindFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUdpSocket::BindFlag value = qscriptvalue_cast<QUdpSocket::BindFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QUdpSocket_BindFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QUdpSocket_BindFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QUdpSocket_BindFlag,
        qtscript_QUdpSocket_BindFlag_valueOf, qtscript_QUdpSocket_BindFlag_toString);
    qScriptRegisterMetaType<QUdpSocket::BindFlag>(engine, qtscript_QUdpSocket_BindFlag_toScriptValue,
        qtscript_QUdpSocket_BindFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUdpSocket_BindFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUdpSocket_BindFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QUdpSocket::BindMode
//

static QScriptValue qtscript_QUdpSocket_BindMode_toScriptValue(QScriptEngine *engine, const QUdpSocket::BindMode &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QUdpSocket_BindMode_fromScriptValue(const QScriptValue &value, QUdpSocket::BindMode &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QUdpSocket::BindMode>())
        out = qvariant_cast<QUdpSocket::BindMode>(var);
    else if (var.userType() == qMetaTypeId<QUdpSocket::BindFlag>())
        out = qvariant_cast<QUdpSocket::BindFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QUdpSocket_BindMode(QScriptContext *context, QScriptEngine *engine)
{
    QUdpSocket::BindMode result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QUdpSocket::BindMode>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QUdpSocket::BindFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("BindMode(): argument %0 is not of type BindFlag").arg(i));
            }
            result |= qvariant_cast<QUdpSocket::BindFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QUdpSocket_BindMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUdpSocket::BindMode value = qscriptvalue_cast<QUdpSocket::BindMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUdpSocket_BindMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUdpSocket::BindMode value = qscriptvalue_cast<QUdpSocket::BindMode>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QUdpSocket_BindFlag_values[i]) == qtscript_QUdpSocket_BindFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QUdpSocket_BindFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QUdpSocket_BindMode_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QUdpSocket::BindMode>() == otherObj.value<QUdpSocket::BindMode>())));
}

static QScriptValue qtscript_create_QUdpSocket_BindMode_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QUdpSocket_BindMode, qtscript_QUdpSocket_BindMode_valueOf,
        qtscript_QUdpSocket_BindMode_toString, qtscript_QUdpSocket_BindMode_equals);
    qScriptRegisterMetaType<QUdpSocket::BindMode>(engine, qtscript_QUdpSocket_BindMode_toScriptValue,
        qtscript_QUdpSocket_BindMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

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
        _id = 0xBABE0000 + 9;
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
        bool _q_result = _q_self->bind();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
        bool _q_result = _q_self->bind(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            bool _q_result = _q_self->bind(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QFlags<QUdpSocket::BindFlag> >() == context->argument(1).toVariant().userType())) {
            unsigned short _q_arg0 = qscriptvalue_cast<unsigned short>(context->argument(0));
            QFlags<QUdpSocket::BindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QUdpSocket::BindFlag> >(context->argument(1));
            bool _q_result = _q_self->bind(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        QFlags<QUdpSocket::BindFlag> _q_arg2 = qscriptvalue_cast<QFlags<QUdpSocket::BindFlag> >(context->argument(2));
        bool _q_result = _q_self->bind(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPendingDatagrams();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
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

    case 3:
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

    case 4:
    if (context->argumentCount() == 0) {
        QNetworkInterface _q_result = _q_self->multicastInterface();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->pendingDatagramSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
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

    case 7:
    if (context->argumentCount() == 1) {
        QNetworkInterface _q_arg0 = qscriptvalue_cast<QNetworkInterface>(context->argument(0));
        _q_self->setMulticastInterface(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 3) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QHostAddress _q_arg1 = qscriptvalue_cast<QHostAddress>(context->argument(1));
        unsigned short _q_arg2 = qscriptvalue_cast<unsigned short>(context->argument(2));
        qint64 _q_result = _q_self->writeDatagram(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
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
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUdpSocket_prototype_call, qtscript_QUdpSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUdpSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QUdpSocket*>(engine, qtscript_QUdpSocket_toScriptValue, 
        qtscript_QUdpSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUdpSocket_static_call, proto, qtscript_QUdpSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("BindFlag"),
        qtscript_create_QUdpSocket_BindFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BindMode"),
        qtscript_create_QUdpSocket_BindMode_class(engine));
    return ctor;
}
