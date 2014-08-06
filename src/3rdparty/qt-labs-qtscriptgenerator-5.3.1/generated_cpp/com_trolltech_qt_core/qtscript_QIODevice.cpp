#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qiodevice.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QIODevice.h"

static const char * const qtscript_QIODevice_function_names[] = {
    "QIODevice"
    // static
    // prototype
    , "atEnd"
    , "bytesAvailable"
    , "bytesToWrite"
    , "canReadLine"
    , "close"
    , "errorString"
    , "getChar"
    , "isOpen"
    , "isReadable"
    , "isSequential"
    , "isTextModeEnabled"
    , "isWritable"
    , "open"
    , "openMode"
    , "peek"
    , "pos"
    , "putChar"
    , "read"
    , "readAll"
    , "readLine"
    , "reset"
    , "seek"
    , "setTextModeEnabled"
    , "size"
    , "ungetChar"
    , "waitForBytesWritten"
    , "waitForReadyRead"
    , "write"
    , "toString"
};

static const char * const qtscript_QIODevice_function_signatures[] = {
    "\nQObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "char c"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "OpenMode mode"
    , ""
    , "qint64 maxlen"
    , ""
    , "char c"
    , "qint64 maxlen"
    , ""
    , "qint64 maxlen"
    , ""
    , "qint64 pos"
    , "bool enabled"
    , ""
    , "char c"
    , "int msecs"
    , "int msecs"
    , "QByteArray data\nchar data"
""
};

static const int qtscript_QIODevice_function_lengths[] = {
    1
    // static
    // prototype
    , 0
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
    , 0
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QIODevice_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QIODevice::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QtScriptShell_QIODevice*)
Q_DECLARE_METATYPE(QIODevice::OpenModeFlag)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(const char*)

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
// QIODevice::OpenModeFlag
//

static const QIODevice::OpenModeFlag qtscript_QIODevice_OpenModeFlag_values[] = {
    QIODevice::NotOpen
    , QIODevice::ReadOnly
    , QIODevice::WriteOnly
    , QIODevice::ReadWrite
    , QIODevice::Append
    , QIODevice::Truncate
    , QIODevice::Text
    , QIODevice::Unbuffered
};

static const char * const qtscript_QIODevice_OpenModeFlag_keys[] = {
    "NotOpen"
    , "ReadOnly"
    , "WriteOnly"
    , "ReadWrite"
    , "Append"
    , "Truncate"
    , "Text"
    , "Unbuffered"
};

static QString qtscript_QIODevice_OpenModeFlag_toStringHelper(QIODevice::OpenModeFlag value)
{
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QIODevice_OpenModeFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QIODevice_OpenModeFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QIODevice_OpenModeFlag_toScriptValue(QScriptEngine *engine, const QIODevice::OpenModeFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QIODevice"));
    return clazz.property(qtscript_QIODevice_OpenModeFlag_toStringHelper(value));
}

static void qtscript_QIODevice_OpenModeFlag_fromScriptValue(const QScriptValue &value, QIODevice::OpenModeFlag &out)
{
    out = qvariant_cast<QIODevice::OpenModeFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QIODevice_OpenModeFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QIODevice_OpenModeFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QIODevice::OpenModeFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("OpenModeFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QIODevice_OpenModeFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QIODevice::OpenModeFlag value = qscriptvalue_cast<QIODevice::OpenModeFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QIODevice_OpenModeFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QIODevice::OpenModeFlag value = qscriptvalue_cast<QIODevice::OpenModeFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QIODevice_OpenModeFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QIODevice_OpenModeFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QIODevice_OpenModeFlag,
        qtscript_QIODevice_OpenModeFlag_valueOf, qtscript_QIODevice_OpenModeFlag_toString);
    qScriptRegisterMetaType<QIODevice::OpenModeFlag>(engine, qtscript_QIODevice_OpenModeFlag_toScriptValue,
        qtscript_QIODevice_OpenModeFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QIODevice_OpenModeFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QIODevice_OpenModeFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QIODevice::OpenMode
//

static QScriptValue qtscript_QIODevice_OpenMode_toScriptValue(QScriptEngine *engine, const QIODevice::OpenMode &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QIODevice_OpenMode_fromScriptValue(const QScriptValue &value, QIODevice::OpenMode &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QIODevice::OpenMode>())
        out = qvariant_cast<QIODevice::OpenMode>(var);
    else if (var.userType() == qMetaTypeId<QIODevice::OpenModeFlag>())
        out = qvariant_cast<QIODevice::OpenModeFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QIODevice_OpenMode(QScriptContext *context, QScriptEngine *engine)
{
    QIODevice::OpenMode result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QIODevice::OpenMode>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QIODevice::OpenModeFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("OpenMode(): argument %0 is not of type OpenModeFlag").arg(i));
            }
            result |= qvariant_cast<QIODevice::OpenModeFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QIODevice_OpenMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QIODevice::OpenMode value = qscriptvalue_cast<QIODevice::OpenMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QIODevice_OpenMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QIODevice::OpenMode value = qscriptvalue_cast<QIODevice::OpenMode>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_QIODevice_OpenModeFlag_values[i]) == qtscript_QIODevice_OpenModeFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QIODevice_OpenModeFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QIODevice_OpenMode_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QIODevice::OpenMode>() == otherObj.value<QIODevice::OpenMode>())));
}

static QScriptValue qtscript_create_QIODevice_OpenMode_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QIODevice_OpenMode, qtscript_QIODevice_OpenMode_valueOf,
        qtscript_QIODevice_OpenMode_toString, qtscript_QIODevice_OpenMode_equals);
    qScriptRegisterMetaType<QIODevice::OpenMode>(engine, qtscript_QIODevice_OpenMode_toScriptValue,
        qtscript_QIODevice_OpenMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QIODevice
//

static QScriptValue qtscript_QIODevice_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 28;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QIODevice* _q_self = qscriptvalue_cast<QIODevice*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QIODevice.%0(): this object is not a QIODevice")
            .arg(qtscript_QIODevice_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atEnd();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->bytesAvailable();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->bytesToWrite();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canReadLine();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->close();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        bool _q_result = _q_self->getChar(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isOpen();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isReadable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSequential();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTextModeEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWritable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QFlags<QIODevice::OpenModeFlag> _q_arg0 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(0));
        bool _q_result = _q_self->open(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QFlags<QIODevice::OpenModeFlag> _q_result = _q_self->openMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QByteArray _q_result = _q_self->peek(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        bool _q_result = _q_self->putChar(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QByteArray _q_result = _q_self->read(_q_arg0);
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
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->readLine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QByteArray _q_result = _q_self->readLine(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->reset();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        bool _q_result = _q_self->seek(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setTextModeEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        _q_self->ungetChar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForBytesWritten(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForReadyRead(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            qint64 _q_result = _q_self->write(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            qint64 _q_result = _q_self->write(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 28: {
    QString result = QString::fromLatin1("QIODevice");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIODevice_throw_ambiguity_error_helper(context,
        qtscript_QIODevice_function_names[_id+1],
        qtscript_QIODevice_function_signatures[_id+1]);
}

static QScriptValue qtscript_QIODevice_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QIODevice(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QIODevice* _q_cpp_result = new QtScriptShell_QIODevice();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIODevice*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QIODevice* _q_cpp_result = new QtScriptShell_QIODevice(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIODevice*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIODevice_throw_ambiguity_error_helper(context,
        qtscript_QIODevice_function_names[_id],
        qtscript_QIODevice_function_signatures[_id]);
}

static QScriptValue qtscript_QIODevice_toScriptValue(QScriptEngine *engine, QIODevice* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QIODevice_fromScriptValue(const QScriptValue &value, QIODevice* &out)
{
    out = qobject_cast<QIODevice*>(value.toQObject());
}

QScriptValue qtscript_create_QIODevice_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QIODevice*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QIODevice*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 29; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QIODevice_prototype_call, qtscript_QIODevice_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QIODevice_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QIODevice*>(engine, qtscript_QIODevice_toScriptValue, 
        qtscript_QIODevice_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QIODevice_static_call, proto, qtscript_QIODevice_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("OpenModeFlag"),
        qtscript_create_QIODevice_OpenModeFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("OpenMode"),
        qtscript_create_QIODevice_OpenMode_class(engine));
    return ctor;
}
