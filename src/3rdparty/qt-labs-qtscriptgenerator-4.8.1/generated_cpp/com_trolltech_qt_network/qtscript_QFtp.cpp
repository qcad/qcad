#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qftp.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qftp.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qobject.h>
#include <qurlinfo.h>

#include "qtscriptshell_QFtp.h"

static const char * const qtscript_QFtp_function_names[] = {
    "QFtp"
    // static
    // prototype
    , "bytesAvailable"
    , "cd"
    , "clearPendingCommands"
    , "close"
    , "connectToHost"
    , "currentCommand"
    , "currentDevice"
    , "currentId"
    , "error"
    , "errorString"
    , "get"
    , "hasPendingCommands"
    , "list"
    , "login"
    , "mkdir"
    , "put"
    , "rawCommand"
    , "read"
    , "readAll"
    , "remove"
    , "rename"
    , "rmdir"
    , "setProxy"
    , "setTransferMode"
    , "state"
    , "toString"
};

static const char * const qtscript_QFtp_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "String dir"
    , ""
    , ""
    , "String host, unsigned short port"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String file, QIODevice dev, TransferType type"
    , ""
    , "String dir"
    , "String user, String password"
    , "String dir"
    , "QIODevice dev, String file, TransferType type\nQByteArray data, String file, TransferType type"
    , "String command"
    , "char data, qint64 maxlen"
    , ""
    , "String file"
    , "String oldname, String newname"
    , "String dir"
    , "String host, unsigned short port"
    , "TransferMode mode"
    , ""
""
};

static const int qtscript_QFtp_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 3
    , 0
    , 1
    , 2
    , 1
    , 3
    , 1
    , 2
    , 0
    , 1
    , 2
    , 1
    , 2
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QFtp_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFtp::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFtp*)
Q_DECLARE_METATYPE(QtScriptShell_QFtp*)
Q_DECLARE_METATYPE(QFtp::TransferType)
Q_DECLARE_METATYPE(QFtp::Error)
Q_DECLARE_METATYPE(QFtp::Command)
Q_DECLARE_METATYPE(QFtp::TransferMode)
Q_DECLARE_METATYPE(QFtp::State)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(char*)

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
// QFtp::TransferType
//

static const QFtp::TransferType qtscript_QFtp_TransferType_values[] = {
    QFtp::Binary
    , QFtp::Ascii
};

static const char * const qtscript_QFtp_TransferType_keys[] = {
    "Binary"
    , "Ascii"
};

static QString qtscript_QFtp_TransferType_toStringHelper(QFtp::TransferType value)
{
    if ((value >= QFtp::Binary) && (value <= QFtp::Ascii))
        return qtscript_QFtp_TransferType_keys[static_cast<int>(value)-static_cast<int>(QFtp::Binary)];
    return QString();
}

static QScriptValue qtscript_QFtp_TransferType_toScriptValue(QScriptEngine *engine, const QFtp::TransferType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFtp"));
    return clazz.property(qtscript_QFtp_TransferType_toStringHelper(value));
}

static void qtscript_QFtp_TransferType_fromScriptValue(const QScriptValue &value, QFtp::TransferType &out)
{
    out = qvariant_cast<QFtp::TransferType>(value.toVariant());
}

static QScriptValue qtscript_construct_QFtp_TransferType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFtp::Binary) && (arg <= QFtp::Ascii))
        return qScriptValueFromValue(engine,  static_cast<QFtp::TransferType>(arg));
    return context->throwError(QString::fromLatin1("TransferType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFtp_TransferType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::TransferType value = qscriptvalue_cast<QFtp::TransferType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFtp_TransferType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::TransferType value = qscriptvalue_cast<QFtp::TransferType>(context->thisObject());
    return QScriptValue(engine, qtscript_QFtp_TransferType_toStringHelper(value));
}

static QScriptValue qtscript_create_QFtp_TransferType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFtp_TransferType,
        qtscript_QFtp_TransferType_valueOf, qtscript_QFtp_TransferType_toString);
    qScriptRegisterMetaType<QFtp::TransferType>(engine, qtscript_QFtp_TransferType_toScriptValue,
        qtscript_QFtp_TransferType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFtp_TransferType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFtp_TransferType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFtp::Error
//

static const QFtp::Error qtscript_QFtp_Error_values[] = {
    QFtp::NoError
    , QFtp::UnknownError
    , QFtp::HostNotFound
    , QFtp::ConnectionRefused
    , QFtp::NotConnected
};

static const char * const qtscript_QFtp_Error_keys[] = {
    "NoError"
    , "UnknownError"
    , "HostNotFound"
    , "ConnectionRefused"
    , "NotConnected"
};

static QString qtscript_QFtp_Error_toStringHelper(QFtp::Error value)
{
    if ((value >= QFtp::NoError) && (value <= QFtp::NotConnected))
        return qtscript_QFtp_Error_keys[static_cast<int>(value)-static_cast<int>(QFtp::NoError)];
    return QString();
}

static QScriptValue qtscript_QFtp_Error_toScriptValue(QScriptEngine *engine, const QFtp::Error &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFtp"));
    return clazz.property(qtscript_QFtp_Error_toStringHelper(value));
}

static void qtscript_QFtp_Error_fromScriptValue(const QScriptValue &value, QFtp::Error &out)
{
    out = qvariant_cast<QFtp::Error>(value.toVariant());
}

static QScriptValue qtscript_construct_QFtp_Error(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFtp::NoError) && (arg <= QFtp::NotConnected))
        return qScriptValueFromValue(engine,  static_cast<QFtp::Error>(arg));
    return context->throwError(QString::fromLatin1("Error(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFtp_Error_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::Error value = qscriptvalue_cast<QFtp::Error>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFtp_Error_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::Error value = qscriptvalue_cast<QFtp::Error>(context->thisObject());
    return QScriptValue(engine, qtscript_QFtp_Error_toStringHelper(value));
}

static QScriptValue qtscript_create_QFtp_Error_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFtp_Error,
        qtscript_QFtp_Error_valueOf, qtscript_QFtp_Error_toString);
    qScriptRegisterMetaType<QFtp::Error>(engine, qtscript_QFtp_Error_toScriptValue,
        qtscript_QFtp_Error_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFtp_Error_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFtp_Error_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFtp::Command
//

static const QFtp::Command qtscript_QFtp_Command_values[] = {
    QFtp::None
    , QFtp::SetTransferMode
    , QFtp::SetProxy
    , QFtp::ConnectToHost
    , QFtp::Login
    , QFtp::Close
    , QFtp::List
    , QFtp::Cd
    , QFtp::Get
    , QFtp::Put
    , QFtp::Remove
    , QFtp::Mkdir
    , QFtp::Rmdir
    , QFtp::Rename
    , QFtp::RawCommand
};

static const char * const qtscript_QFtp_Command_keys[] = {
    "None"
    , "SetTransferMode"
    , "SetProxy"
    , "ConnectToHost"
    , "Login"
    , "Close"
    , "List"
    , "Cd"
    , "Get"
    , "Put"
    , "Remove"
    , "Mkdir"
    , "Rmdir"
    , "Rename"
    , "RawCommand"
};

static QString qtscript_QFtp_Command_toStringHelper(QFtp::Command value)
{
    if ((value >= QFtp::None) && (value <= QFtp::RawCommand))
        return qtscript_QFtp_Command_keys[static_cast<int>(value)-static_cast<int>(QFtp::None)];
    return QString();
}

static QScriptValue qtscript_QFtp_Command_toScriptValue(QScriptEngine *engine, const QFtp::Command &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFtp"));
    return clazz.property(qtscript_QFtp_Command_toStringHelper(value));
}

static void qtscript_QFtp_Command_fromScriptValue(const QScriptValue &value, QFtp::Command &out)
{
    out = qvariant_cast<QFtp::Command>(value.toVariant());
}

static QScriptValue qtscript_construct_QFtp_Command(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFtp::None) && (arg <= QFtp::RawCommand))
        return qScriptValueFromValue(engine,  static_cast<QFtp::Command>(arg));
    return context->throwError(QString::fromLatin1("Command(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFtp_Command_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::Command value = qscriptvalue_cast<QFtp::Command>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFtp_Command_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::Command value = qscriptvalue_cast<QFtp::Command>(context->thisObject());
    return QScriptValue(engine, qtscript_QFtp_Command_toStringHelper(value));
}

static QScriptValue qtscript_create_QFtp_Command_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFtp_Command,
        qtscript_QFtp_Command_valueOf, qtscript_QFtp_Command_toString);
    qScriptRegisterMetaType<QFtp::Command>(engine, qtscript_QFtp_Command_toScriptValue,
        qtscript_QFtp_Command_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFtp_Command_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFtp_Command_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFtp::TransferMode
//

static const QFtp::TransferMode qtscript_QFtp_TransferMode_values[] = {
    QFtp::Active
    , QFtp::Passive
};

static const char * const qtscript_QFtp_TransferMode_keys[] = {
    "Active"
    , "Passive"
};

static QString qtscript_QFtp_TransferMode_toStringHelper(QFtp::TransferMode value)
{
    if ((value >= QFtp::Active) && (value <= QFtp::Passive))
        return qtscript_QFtp_TransferMode_keys[static_cast<int>(value)-static_cast<int>(QFtp::Active)];
    return QString();
}

static QScriptValue qtscript_QFtp_TransferMode_toScriptValue(QScriptEngine *engine, const QFtp::TransferMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFtp"));
    return clazz.property(qtscript_QFtp_TransferMode_toStringHelper(value));
}

static void qtscript_QFtp_TransferMode_fromScriptValue(const QScriptValue &value, QFtp::TransferMode &out)
{
    out = qvariant_cast<QFtp::TransferMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QFtp_TransferMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFtp::Active) && (arg <= QFtp::Passive))
        return qScriptValueFromValue(engine,  static_cast<QFtp::TransferMode>(arg));
    return context->throwError(QString::fromLatin1("TransferMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFtp_TransferMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::TransferMode value = qscriptvalue_cast<QFtp::TransferMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFtp_TransferMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::TransferMode value = qscriptvalue_cast<QFtp::TransferMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QFtp_TransferMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QFtp_TransferMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFtp_TransferMode,
        qtscript_QFtp_TransferMode_valueOf, qtscript_QFtp_TransferMode_toString);
    qScriptRegisterMetaType<QFtp::TransferMode>(engine, qtscript_QFtp_TransferMode_toScriptValue,
        qtscript_QFtp_TransferMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFtp_TransferMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFtp_TransferMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFtp::State
//

static const QFtp::State qtscript_QFtp_State_values[] = {
    QFtp::Unconnected
    , QFtp::HostLookup
    , QFtp::Connecting
    , QFtp::Connected
    , QFtp::LoggedIn
    , QFtp::Closing
};

static const char * const qtscript_QFtp_State_keys[] = {
    "Unconnected"
    , "HostLookup"
    , "Connecting"
    , "Connected"
    , "LoggedIn"
    , "Closing"
};

static QString qtscript_QFtp_State_toStringHelper(QFtp::State value)
{
    if ((value >= QFtp::Unconnected) && (value <= QFtp::Closing))
        return qtscript_QFtp_State_keys[static_cast<int>(value)-static_cast<int>(QFtp::Unconnected)];
    return QString();
}

static QScriptValue qtscript_QFtp_State_toScriptValue(QScriptEngine *engine, const QFtp::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFtp"));
    return clazz.property(qtscript_QFtp_State_toStringHelper(value));
}

static void qtscript_QFtp_State_fromScriptValue(const QScriptValue &value, QFtp::State &out)
{
    out = qvariant_cast<QFtp::State>(value.toVariant());
}

static QScriptValue qtscript_construct_QFtp_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFtp::Unconnected) && (arg <= QFtp::Closing))
        return qScriptValueFromValue(engine,  static_cast<QFtp::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFtp_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::State value = qscriptvalue_cast<QFtp::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFtp_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFtp::State value = qscriptvalue_cast<QFtp::State>(context->thisObject());
    return QScriptValue(engine, qtscript_QFtp_State_toStringHelper(value));
}

static QScriptValue qtscript_create_QFtp_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFtp_State,
        qtscript_QFtp_State_valueOf, qtscript_QFtp_State_toString);
    qScriptRegisterMetaType<QFtp::State>(engine, qtscript_QFtp_State_toScriptValue,
        qtscript_QFtp_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFtp_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFtp_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFtp
//

static QScriptValue qtscript_QFtp_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 25;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFtp* _q_self = qscriptvalue_cast<QFtp*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFtp.%0(): this object is not a QFtp")
            .arg(qtscript_QFtp_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->bytesAvailable();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->cd(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->clearPendingCommands();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->close();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->connectToHost(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        int _q_result = _q_self->connectToHost(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QFtp::Command _q_result = _q_self->currentCommand();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->currentDevice();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QFtp::Error _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
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
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
        QFtp::TransferType _q_arg2 = qscriptvalue_cast<QFtp::TransferType>(context->argument(2));
        int _q_result = _q_self->get(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPendingCommands();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->list();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->list(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->login();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->login(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->login(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->mkdir(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            int _q_result = _q_self->put(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            int _q_result = _q_self->put(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()
            && (qMetaTypeId<QFtp::TransferType>() == context->argument(2).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QFtp::TransferType _q_arg2 = qscriptvalue_cast<QFtp::TransferType>(context->argument(2));
            int _q_result = _q_self->put(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && (qMetaTypeId<QFtp::TransferType>() == context->argument(2).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QFtp::TransferType _q_arg2 = qscriptvalue_cast<QFtp::TransferType>(context->argument(2));
            int _q_result = _q_self->put(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->rawCommand(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        qint64 _q_result = _q_self->read(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->readAll();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->remove(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->rename(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->rmdir(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        int _q_result = _q_self->setProxy(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QFtp::TransferMode _q_arg0 = qscriptvalue_cast<QFtp::TransferMode>(context->argument(0));
        int _q_result = _q_self->setTransferMode(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QFtp::State _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25: {
    QString result = QString::fromLatin1("QFtp");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFtp_throw_ambiguity_error_helper(context,
        qtscript_QFtp_function_names[_id+1],
        qtscript_QFtp_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFtp_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFtp(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFtp* _q_cpp_result = new QtScriptShell_QFtp();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFtp*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QFtp* _q_cpp_result = new QtScriptShell_QFtp(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFtp*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFtp_throw_ambiguity_error_helper(context,
        qtscript_QFtp_function_names[_id],
        qtscript_QFtp_function_signatures[_id]);
}

static QScriptValue qtscript_QFtp_toScriptValue(QScriptEngine *engine, QFtp* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFtp_fromScriptValue(const QScriptValue &value, QFtp* &out)
{
    out = qobject_cast<QFtp*>(value.toQObject());
}

QScriptValue qtscript_create_QFtp_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFtp*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFtp*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 26; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFtp_prototype_call, qtscript_QFtp_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFtp_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFtp*>(engine, qtscript_QFtp_toScriptValue, 
        qtscript_QFtp_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFtp_static_call, proto, qtscript_QFtp_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("TransferType"),
        qtscript_create_QFtp_TransferType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Error"),
        qtscript_create_QFtp_Error_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Command"),
        qtscript_create_QFtp_Command_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TransferMode"),
        qtscript_create_QFtp_TransferMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QFtp_State_class(engine, ctor));
    return ctor;
}
