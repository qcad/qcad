#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qfiledevice.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfiledevice.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QFileDevice.h"

static const char * const qtscript_QFileDevice_function_names[] = {
    "QFileDevice"
    // static
    // prototype
    , "error"
    , "fileName"
    , "flush"
    , "handle"
    , "map"
    , "permissions"
    , "resize"
    , "setPermissions"
    , "unsetError"
    , "toString"
};

static const char * const qtscript_QFileDevice_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "qint64 offset, qint64 size, MemoryMapFlags flags"
    , ""
    , "qint64 sz"
    , "Permissions permissionSpec"
    , ""
""
};

static const int qtscript_QFileDevice_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 3
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QFileDevice_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFileDevice::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFileDevice*)
Q_DECLARE_METATYPE(QtScriptShell_QFileDevice*)
Q_DECLARE_METATYPE(QFileDevice::FileError)
Q_DECLARE_METATYPE(QFileDevice::Permission)
Q_DECLARE_METATYPE(QFlags<QFileDevice::Permission>)
Q_DECLARE_METATYPE(QFileDevice::MemoryMapFlags)
Q_DECLARE_METATYPE(QFileDevice::FileHandleFlag)
Q_DECLARE_METATYPE(QFlags<QFileDevice::FileHandleFlag>)
Q_DECLARE_METATYPE(uchar*)
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
// QFileDevice::FileError
//

static const QFileDevice::FileError qtscript_QFileDevice_FileError_values[] = {
    QFileDevice::NoError
    , QFileDevice::ReadError
    , QFileDevice::WriteError
    , QFileDevice::FatalError
    , QFileDevice::ResourceError
    , QFileDevice::OpenError
    , QFileDevice::AbortError
    , QFileDevice::TimeOutError
    , QFileDevice::UnspecifiedError
    , QFileDevice::RemoveError
    , QFileDevice::RenameError
    , QFileDevice::PositionError
    , QFileDevice::ResizeError
    , QFileDevice::PermissionsError
    , QFileDevice::CopyError
};

static const char * const qtscript_QFileDevice_FileError_keys[] = {
    "NoError"
    , "ReadError"
    , "WriteError"
    , "FatalError"
    , "ResourceError"
    , "OpenError"
    , "AbortError"
    , "TimeOutError"
    , "UnspecifiedError"
    , "RemoveError"
    , "RenameError"
    , "PositionError"
    , "ResizeError"
    , "PermissionsError"
    , "CopyError"
};

static QString qtscript_QFileDevice_FileError_toStringHelper(QFileDevice::FileError value)
{
    if ((value >= QFileDevice::NoError) && (value <= QFileDevice::CopyError))
        return qtscript_QFileDevice_FileError_keys[static_cast<int>(value)-static_cast<int>(QFileDevice::NoError)];
    return QString();
}

static QScriptValue qtscript_QFileDevice_FileError_toScriptValue(QScriptEngine *engine, const QFileDevice::FileError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDevice"));
    return clazz.property(qtscript_QFileDevice_FileError_toStringHelper(value));
}

static void qtscript_QFileDevice_FileError_fromScriptValue(const QScriptValue &value, QFileDevice::FileError &out)
{
    out = qvariant_cast<QFileDevice::FileError>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDevice_FileError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFileDevice::NoError) && (arg <= QFileDevice::CopyError))
        return qScriptValueFromValue(engine,  static_cast<QFileDevice::FileError>(arg));
    return context->throwError(QString::fromLatin1("FileError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDevice_FileError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileError value = qscriptvalue_cast<QFileDevice::FileError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDevice_FileError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileError value = qscriptvalue_cast<QFileDevice::FileError>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDevice_FileError_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDevice_FileError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDevice_FileError,
        qtscript_QFileDevice_FileError_valueOf, qtscript_QFileDevice_FileError_toString);
    qScriptRegisterMetaType<QFileDevice::FileError>(engine, qtscript_QFileDevice_FileError_toScriptValue,
        qtscript_QFileDevice_FileError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDevice_FileError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDevice_FileError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDevice::Permission
//

static const QFileDevice::Permission qtscript_QFileDevice_Permission_values[] = {
    QFileDevice::ExeOther
    , QFileDevice::WriteOther
    , QFileDevice::ReadOther
    , QFileDevice::ExeGroup
    , QFileDevice::WriteGroup
    , QFileDevice::ReadGroup
    , QFileDevice::ExeUser
    , QFileDevice::WriteUser
    , QFileDevice::ReadUser
    , QFileDevice::ExeOwner
    , QFileDevice::WriteOwner
    , QFileDevice::ReadOwner
};

static const char * const qtscript_QFileDevice_Permission_keys[] = {
    "ExeOther"
    , "WriteOther"
    , "ReadOther"
    , "ExeGroup"
    , "WriteGroup"
    , "ReadGroup"
    , "ExeUser"
    , "WriteUser"
    , "ReadUser"
    , "ExeOwner"
    , "WriteOwner"
    , "ReadOwner"
};

static QString qtscript_QFileDevice_Permission_toStringHelper(QFileDevice::Permission value)
{
    for (int i = 0; i < 12; ++i) {
        if (qtscript_QFileDevice_Permission_values[i] == value)
            return QString::fromLatin1(qtscript_QFileDevice_Permission_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QFileDevice_Permission_toScriptValue(QScriptEngine *engine, const QFileDevice::Permission &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDevice"));
    return clazz.property(qtscript_QFileDevice_Permission_toStringHelper(value));
}

static void qtscript_QFileDevice_Permission_fromScriptValue(const QScriptValue &value, QFileDevice::Permission &out)
{
    out = qvariant_cast<QFileDevice::Permission>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDevice_Permission(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 12; ++i) {
        if (qtscript_QFileDevice_Permission_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QFileDevice::Permission>(arg));
    }
    return context->throwError(QString::fromLatin1("Permission(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDevice_Permission_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::Permission value = qscriptvalue_cast<QFileDevice::Permission>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDevice_Permission_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::Permission value = qscriptvalue_cast<QFileDevice::Permission>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDevice_Permission_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDevice_Permission_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDevice_Permission,
        qtscript_QFileDevice_Permission_valueOf, qtscript_QFileDevice_Permission_toString);
    qScriptRegisterMetaType<QFileDevice::Permission>(engine, qtscript_QFileDevice_Permission_toScriptValue,
        qtscript_QFileDevice_Permission_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 12; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDevice_Permission_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDevice_Permission_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDevice::Permissions
//

static QScriptValue qtscript_QFileDevice_Permissions_toScriptValue(QScriptEngine *engine, const QFileDevice::Permissions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QFileDevice_Permissions_fromScriptValue(const QScriptValue &value, QFileDevice::Permissions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QFileDevice::Permissions>())
        out = qvariant_cast<QFileDevice::Permissions>(var);
    else if (var.userType() == qMetaTypeId<QFileDevice::Permission>())
        out = qvariant_cast<QFileDevice::Permission>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QFileDevice_Permissions(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::Permissions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QFileDevice::Permissions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QFileDevice::Permission>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Permissions(): argument %0 is not of type Permission").arg(i));
            }
            result |= qvariant_cast<QFileDevice::Permission>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QFileDevice_Permissions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::Permissions value = qscriptvalue_cast<QFileDevice::Permissions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDevice_Permissions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::Permissions value = qscriptvalue_cast<QFileDevice::Permissions>(context->thisObject());
    QString result;
    for (int i = 0; i < 12; ++i) {
        if ((value & qtscript_QFileDevice_Permission_values[i]) == qtscript_QFileDevice_Permission_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QFileDevice_Permission_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QFileDevice_Permissions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QFileDevice::Permissions>() == otherObj.value<QFileDevice::Permissions>())));
}

static QScriptValue qtscript_create_QFileDevice_Permissions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QFileDevice_Permissions, qtscript_QFileDevice_Permissions_valueOf,
        qtscript_QFileDevice_Permissions_toString, qtscript_QFileDevice_Permissions_equals);
    qScriptRegisterMetaType<QFileDevice::Permissions>(engine, qtscript_QFileDevice_Permissions_toScriptValue,
        qtscript_QFileDevice_Permissions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QFileDevice::MemoryMapFlags
//

static const QFileDevice::MemoryMapFlags qtscript_QFileDevice_MemoryMapFlags_values[] = {
    QFileDevice::NoOptions
};

static const char * const qtscript_QFileDevice_MemoryMapFlags_keys[] = {
    "NoOptions"
};

static QString qtscript_QFileDevice_MemoryMapFlags_toStringHelper(QFileDevice::MemoryMapFlags value)
{
    if ((value >= QFileDevice::NoOptions) && (value <= QFileDevice::NoOptions))
        return qtscript_QFileDevice_MemoryMapFlags_keys[static_cast<int>(value)-static_cast<int>(QFileDevice::NoOptions)];
    return QString();
}

static QScriptValue qtscript_QFileDevice_MemoryMapFlags_toScriptValue(QScriptEngine *engine, const QFileDevice::MemoryMapFlags &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDevice"));
    return clazz.property(qtscript_QFileDevice_MemoryMapFlags_toStringHelper(value));
}

static void qtscript_QFileDevice_MemoryMapFlags_fromScriptValue(const QScriptValue &value, QFileDevice::MemoryMapFlags &out)
{
    out = qvariant_cast<QFileDevice::MemoryMapFlags>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDevice_MemoryMapFlags(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFileDevice::NoOptions) && (arg <= QFileDevice::NoOptions))
        return qScriptValueFromValue(engine,  static_cast<QFileDevice::MemoryMapFlags>(arg));
    return context->throwError(QString::fromLatin1("MemoryMapFlags(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDevice_MemoryMapFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::MemoryMapFlags value = qscriptvalue_cast<QFileDevice::MemoryMapFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDevice_MemoryMapFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::MemoryMapFlags value = qscriptvalue_cast<QFileDevice::MemoryMapFlags>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDevice_MemoryMapFlags_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDevice_MemoryMapFlags_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDevice_MemoryMapFlags,
        qtscript_QFileDevice_MemoryMapFlags_valueOf, qtscript_QFileDevice_MemoryMapFlags_toString);
    qScriptRegisterMetaType<QFileDevice::MemoryMapFlags>(engine, qtscript_QFileDevice_MemoryMapFlags_toScriptValue,
        qtscript_QFileDevice_MemoryMapFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDevice_MemoryMapFlags_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDevice_MemoryMapFlags_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDevice::FileHandleFlag
//

static const QFileDevice::FileHandleFlag qtscript_QFileDevice_FileHandleFlag_values[] = {
    QFileDevice::DontCloseHandle
    , QFileDevice::AutoCloseHandle
};

static const char * const qtscript_QFileDevice_FileHandleFlag_keys[] = {
    "DontCloseHandle"
    , "AutoCloseHandle"
};

static QString qtscript_QFileDevice_FileHandleFlag_toStringHelper(QFileDevice::FileHandleFlag value)
{
    if ((value >= QFileDevice::DontCloseHandle) && (value <= QFileDevice::AutoCloseHandle))
        return qtscript_QFileDevice_FileHandleFlag_keys[static_cast<int>(value)-static_cast<int>(QFileDevice::DontCloseHandle)];
    return QString();
}

static QScriptValue qtscript_QFileDevice_FileHandleFlag_toScriptValue(QScriptEngine *engine, const QFileDevice::FileHandleFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileDevice"));
    return clazz.property(qtscript_QFileDevice_FileHandleFlag_toStringHelper(value));
}

static void qtscript_QFileDevice_FileHandleFlag_fromScriptValue(const QScriptValue &value, QFileDevice::FileHandleFlag &out)
{
    out = qvariant_cast<QFileDevice::FileHandleFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileDevice_FileHandleFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFileDevice::DontCloseHandle) && (arg <= QFileDevice::AutoCloseHandle))
        return qScriptValueFromValue(engine,  static_cast<QFileDevice::FileHandleFlag>(arg));
    return context->throwError(QString::fromLatin1("FileHandleFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileDevice_FileHandleFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileHandleFlag value = qscriptvalue_cast<QFileDevice::FileHandleFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDevice_FileHandleFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileHandleFlag value = qscriptvalue_cast<QFileDevice::FileHandleFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileDevice_FileHandleFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileDevice_FileHandleFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileDevice_FileHandleFlag,
        qtscript_QFileDevice_FileHandleFlag_valueOf, qtscript_QFileDevice_FileHandleFlag_toString);
    qScriptRegisterMetaType<QFileDevice::FileHandleFlag>(engine, qtscript_QFileDevice_FileHandleFlag_toScriptValue,
        qtscript_QFileDevice_FileHandleFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileDevice_FileHandleFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileDevice_FileHandleFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileDevice::FileHandleFlags
//

static QScriptValue qtscript_QFileDevice_FileHandleFlags_toScriptValue(QScriptEngine *engine, const QFileDevice::FileHandleFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QFileDevice_FileHandleFlags_fromScriptValue(const QScriptValue &value, QFileDevice::FileHandleFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QFileDevice::FileHandleFlags>())
        out = qvariant_cast<QFileDevice::FileHandleFlags>(var);
    else if (var.userType() == qMetaTypeId<QFileDevice::FileHandleFlag>())
        out = qvariant_cast<QFileDevice::FileHandleFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QFileDevice_FileHandleFlags(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileHandleFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QFileDevice::FileHandleFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QFileDevice::FileHandleFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("FileHandleFlags(): argument %0 is not of type FileHandleFlag").arg(i));
            }
            result |= qvariant_cast<QFileDevice::FileHandleFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QFileDevice_FileHandleFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileHandleFlags value = qscriptvalue_cast<QFileDevice::FileHandleFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileDevice_FileHandleFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileDevice::FileHandleFlags value = qscriptvalue_cast<QFileDevice::FileHandleFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QFileDevice_FileHandleFlag_values[i]) == qtscript_QFileDevice_FileHandleFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QFileDevice_FileHandleFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QFileDevice_FileHandleFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QFileDevice::FileHandleFlags>() == otherObj.value<QFileDevice::FileHandleFlags>())));
}

static QScriptValue qtscript_create_QFileDevice_FileHandleFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QFileDevice_FileHandleFlags, qtscript_QFileDevice_FileHandleFlags_valueOf,
        qtscript_QFileDevice_FileHandleFlags_toString, qtscript_QFileDevice_FileHandleFlags_equals);
    qScriptRegisterMetaType<QFileDevice::FileHandleFlags>(engine, qtscript_QFileDevice_FileHandleFlags_toScriptValue,
        qtscript_QFileDevice_FileHandleFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QFileDevice
//

static QScriptValue qtscript_QFileDevice_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFileDevice* _q_self = qscriptvalue_cast<QFileDevice*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFileDevice.%0(): this object is not a QFileDevice")
            .arg(qtscript_QFileDevice_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFileDevice::FileError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->flush();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->handle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        uchar* _q_result = _q_self->map(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        QFileDevice::MemoryMapFlags _q_arg2 = qscriptvalue_cast<QFileDevice::MemoryMapFlags>(context->argument(2));
        uchar* _q_result = _q_self->map(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QFlags<QFileDevice::Permission> _q_result = _q_self->permissions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        bool _q_result = _q_self->resize(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QFlags<QFileDevice::Permission> _q_arg0 = qscriptvalue_cast<QFlags<QFileDevice::Permission> >(context->argument(0));
        bool _q_result = _q_self->setPermissions(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->unsetError();
        return context->engine()->undefinedValue();
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QFileDevice");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileDevice_throw_ambiguity_error_helper(context,
        qtscript_QFileDevice_function_names[_id+1],
        qtscript_QFileDevice_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFileDevice_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QFileDevice cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileDevice_throw_ambiguity_error_helper(context,
        qtscript_QFileDevice_function_names[_id],
        qtscript_QFileDevice_function_signatures[_id]);
}

static QScriptValue qtscript_QFileDevice_toScriptValue(QScriptEngine *engine, QFileDevice* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFileDevice_fromScriptValue(const QScriptValue &value, QFileDevice* &out)
{
    out = qobject_cast<QFileDevice*>(value.toQObject());
}

QScriptValue qtscript_create_QFileDevice_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFileDevice*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFileDevice*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFileDevice_prototype_call, qtscript_QFileDevice_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFileDevice_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFileDevice*>(engine, qtscript_QFileDevice_toScriptValue, 
        qtscript_QFileDevice_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFileDevice_static_call, proto, qtscript_QFileDevice_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("FileError"),
        qtscript_create_QFileDevice_FileError_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Permission"),
        qtscript_create_QFileDevice_Permission_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Permissions"),
        qtscript_create_QFileDevice_Permissions_class(engine));
    ctor.setProperty(QString::fromLatin1("MemoryMapFlags"),
        qtscript_create_QFileDevice_MemoryMapFlags_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FileHandleFlag"),
        qtscript_create_QFileDevice_FileHandleFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FileHandleFlags"),
        qtscript_create_QFileDevice_FileHandleFlags_class(engine));
    return ctor;
}
