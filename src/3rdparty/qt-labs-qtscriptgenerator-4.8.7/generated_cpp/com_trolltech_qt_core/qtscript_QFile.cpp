#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfile.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfile.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QFile.h"

static const char * const qtscript_QFile_function_names[] = {
    "QFile"
    // static
    , "copy"
    , "decodeName"
    , "encodeName"
    , "exists"
    , "link"
    , "permissions"
    , "remove"
    , "rename"
    , "resize"
    , "setPermissions"
    , "symLinkTarget"
    // prototype
    , "copy"
    , "error"
    , "exists"
    , "fileEngine"
    , "fileName"
    , "flush"
    , "handle"
    , "link"
    , "permissions"
    , "remove"
    , "rename"
    , "resize"
    , "setFileName"
    , "setPermissions"
    , "symLinkTarget"
    , "unsetError"
    , "toString"
};

static const char * const qtscript_QFile_function_signatures[] = {
    "\nQObject parent\nString name\nString name, QObject parent"
    // static
    , "String fileName, String newName"
    , "QByteArray localFileName"
    , "String fileName"
    , "String fileName"
    , "String oldname, String newName"
    , "String filename"
    , "String fileName"
    , "String oldName, String newName"
    , "String filename, qint64 sz"
    , "String filename, Permissions permissionSpec"
    , "String fileName"
    // prototype
    , "String newName"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String newName"
    , ""
    , ""
    , "String newName"
    , "qint64 sz"
    , "String name"
    , "Permissions permissionSpec"
    , ""
    , ""
""
};

static const int qtscript_QFile_function_lengths[] = {
    2
    // static
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 2
    , 2
    , 1
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QFile_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFile::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFile*)
Q_DECLARE_METATYPE(QtScriptShell_QFile*)
Q_DECLARE_METATYPE(QFile::FileError)
Q_DECLARE_METATYPE(QFile::MemoryMapFlags)
Q_DECLARE_METATYPE(QFile::Permission)
Q_DECLARE_METATYPE(QFlags<QFile::Permission>)
Q_DECLARE_METATYPE(QAbstractFileEngine*)
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
// QFile::FileError
//

static const QFile::FileError qtscript_QFile_FileError_values[] = {
    QFile::NoError
    , QFile::ReadError
    , QFile::WriteError
    , QFile::FatalError
    , QFile::ResourceError
    , QFile::OpenError
    , QFile::AbortError
    , QFile::TimeOutError
    , QFile::UnspecifiedError
    , QFile::RemoveError
    , QFile::RenameError
    , QFile::PositionError
    , QFile::ResizeError
    , QFile::PermissionsError
    , QFile::CopyError
};

static const char * const qtscript_QFile_FileError_keys[] = {
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

static QString qtscript_QFile_FileError_toStringHelper(QFile::FileError value)
{
    if ((value >= QFile::NoError) && (value <= QFile::CopyError))
        return qtscript_QFile_FileError_keys[static_cast<int>(value)-static_cast<int>(QFile::NoError)];
    return QString();
}

static QScriptValue qtscript_QFile_FileError_toScriptValue(QScriptEngine *engine, const QFile::FileError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFile"));
    return clazz.property(qtscript_QFile_FileError_toStringHelper(value));
}

static void qtscript_QFile_FileError_fromScriptValue(const QScriptValue &value, QFile::FileError &out)
{
    out = qvariant_cast<QFile::FileError>(value.toVariant());
}

static QScriptValue qtscript_construct_QFile_FileError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFile::NoError) && (arg <= QFile::CopyError))
        return qScriptValueFromValue(engine,  static_cast<QFile::FileError>(arg));
    return context->throwError(QString::fromLatin1("FileError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFile_FileError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFile::FileError value = qscriptvalue_cast<QFile::FileError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFile_FileError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFile::FileError value = qscriptvalue_cast<QFile::FileError>(context->thisObject());
    return QScriptValue(engine, qtscript_QFile_FileError_toStringHelper(value));
}

static QScriptValue qtscript_create_QFile_FileError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFile_FileError,
        qtscript_QFile_FileError_valueOf, qtscript_QFile_FileError_toString);
    qScriptRegisterMetaType<QFile::FileError>(engine, qtscript_QFile_FileError_toScriptValue,
        qtscript_QFile_FileError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFile_FileError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFile_FileError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFile::MemoryMapFlags
//

static const QFile::MemoryMapFlags qtscript_QFile_MemoryMapFlags_values[] = {
    QFile::NoOptions
};

static const char * const qtscript_QFile_MemoryMapFlags_keys[] = {
    "NoOptions"
};

static QString qtscript_QFile_MemoryMapFlags_toStringHelper(QFile::MemoryMapFlags value)
{
    if ((value >= QFile::NoOptions) && (value <= QFile::NoOptions))
        return qtscript_QFile_MemoryMapFlags_keys[static_cast<int>(value)-static_cast<int>(QFile::NoOptions)];
    return QString();
}

static QScriptValue qtscript_QFile_MemoryMapFlags_toScriptValue(QScriptEngine *engine, const QFile::MemoryMapFlags &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFile"));
    return clazz.property(qtscript_QFile_MemoryMapFlags_toStringHelper(value));
}

static void qtscript_QFile_MemoryMapFlags_fromScriptValue(const QScriptValue &value, QFile::MemoryMapFlags &out)
{
    out = qvariant_cast<QFile::MemoryMapFlags>(value.toVariant());
}

static QScriptValue qtscript_construct_QFile_MemoryMapFlags(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFile::NoOptions) && (arg <= QFile::NoOptions))
        return qScriptValueFromValue(engine,  static_cast<QFile::MemoryMapFlags>(arg));
    return context->throwError(QString::fromLatin1("MemoryMapFlags(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFile_MemoryMapFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFile::MemoryMapFlags value = qscriptvalue_cast<QFile::MemoryMapFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFile_MemoryMapFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFile::MemoryMapFlags value = qscriptvalue_cast<QFile::MemoryMapFlags>(context->thisObject());
    return QScriptValue(engine, qtscript_QFile_MemoryMapFlags_toStringHelper(value));
}

static QScriptValue qtscript_create_QFile_MemoryMapFlags_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFile_MemoryMapFlags,
        qtscript_QFile_MemoryMapFlags_valueOf, qtscript_QFile_MemoryMapFlags_toString);
    qScriptRegisterMetaType<QFile::MemoryMapFlags>(engine, qtscript_QFile_MemoryMapFlags_toScriptValue,
        qtscript_QFile_MemoryMapFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFile_MemoryMapFlags_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFile_MemoryMapFlags_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFile::Permission
//

static const QFile::Permission qtscript_QFile_Permission_values[] = {
    QFile::ExeOther
    , QFile::WriteOther
    , QFile::ReadOther
    , QFile::ExeGroup
    , QFile::WriteGroup
    , QFile::ReadGroup
    , QFile::ExeUser
    , QFile::WriteUser
    , QFile::ReadUser
    , QFile::ExeOwner
    , QFile::WriteOwner
    , QFile::ReadOwner
};

static const char * const qtscript_QFile_Permission_keys[] = {
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

static QString qtscript_QFile_Permission_toStringHelper(QFile::Permission value)
{
    for (int i = 0; i < 12; ++i) {
        if (qtscript_QFile_Permission_values[i] == value)
            return QString::fromLatin1(qtscript_QFile_Permission_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QFile_Permission_toScriptValue(QScriptEngine *engine, const QFile::Permission &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFile"));
    return clazz.property(qtscript_QFile_Permission_toStringHelper(value));
}

static void qtscript_QFile_Permission_fromScriptValue(const QScriptValue &value, QFile::Permission &out)
{
    out = qvariant_cast<QFile::Permission>(value.toVariant());
}

static QScriptValue qtscript_construct_QFile_Permission(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 12; ++i) {
        if (qtscript_QFile_Permission_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QFile::Permission>(arg));
    }
    return context->throwError(QString::fromLatin1("Permission(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFile_Permission_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFile::Permission value = qscriptvalue_cast<QFile::Permission>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFile_Permission_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFile::Permission value = qscriptvalue_cast<QFile::Permission>(context->thisObject());
    return QScriptValue(engine, qtscript_QFile_Permission_toStringHelper(value));
}

static QScriptValue qtscript_create_QFile_Permission_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFile_Permission,
        qtscript_QFile_Permission_valueOf, qtscript_QFile_Permission_toString);
    qScriptRegisterMetaType<QFile::Permission>(engine, qtscript_QFile_Permission_toScriptValue,
        qtscript_QFile_Permission_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 12; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFile_Permission_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFile_Permission_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFile::Permissions
//

static QScriptValue qtscript_QFile_Permissions_toScriptValue(QScriptEngine *engine, const QFile::Permissions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QFile_Permissions_fromScriptValue(const QScriptValue &value, QFile::Permissions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QFile::Permissions>())
        out = qvariant_cast<QFile::Permissions>(var);
    else if (var.userType() == qMetaTypeId<QFile::Permission>())
        out = qvariant_cast<QFile::Permission>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QFile_Permissions(QScriptContext *context, QScriptEngine *engine)
{
    QFile::Permissions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QFile::Permissions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QFile::Permission>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Permissions(): argument %0 is not of type Permission").arg(i));
            }
            result |= qvariant_cast<QFile::Permission>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QFile_Permissions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFile::Permissions value = qscriptvalue_cast<QFile::Permissions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFile_Permissions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFile::Permissions value = qscriptvalue_cast<QFile::Permissions>(context->thisObject());
    QString result;
    for (int i = 0; i < 12; ++i) {
        if ((value & qtscript_QFile_Permission_values[i]) == qtscript_QFile_Permission_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QFile_Permission_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QFile_Permissions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QFile::Permissions>() == otherObj.value<QFile::Permissions>())));
}

static QScriptValue qtscript_create_QFile_Permissions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QFile_Permissions, qtscript_QFile_Permissions_valueOf,
        qtscript_QFile_Permissions_toString, qtscript_QFile_Permissions_equals);
    qScriptRegisterMetaType<QFile::Permissions>(engine, qtscript_QFile_Permissions_toScriptValue,
        qtscript_QFile_Permissions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QFile
//

static QScriptValue qtscript_QFile_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFile* _q_self = qscriptvalue_cast<QFile*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFile.%0(): this object is not a QFile")
            .arg(qtscript_QFile_function_names[_id+12]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->copy(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFile::FileError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exists();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QAbstractFileEngine* _q_result = _q_self->fileEngine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->flush();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->handle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->link(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QFlags<QFile::Permission> _q_result = _q_self->permissions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->remove();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->rename(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        bool _q_result = _q_self->resize(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QFlags<QFile::Permission> _q_arg0 = qscriptvalue_cast<QFlags<QFile::Permission> >(context->argument(0));
        bool _q_result = _q_self->setPermissions(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->symLinkTarget();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        _q_self->unsetError();
        return context->engine()->undefinedValue();
    }
    break;

    case 16: {
    QString result = QString::fromLatin1("QFile");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFile_throw_ambiguity_error_helper(context,
        qtscript_QFile_function_names[_id+12],
        qtscript_QFile_function_signatures[_id+12]);
}

static QScriptValue qtscript_QFile_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFile(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = QFile::copy(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_result = QFile::decodeName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = QFile::encodeName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QFile::exists(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = QFile::link(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QFile::Permission> _q_result = QFile::permissions(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QFile::remove(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = QFile::rename(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        bool _q_result = QFile::resize(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QFile::Permission> _q_arg1 = qscriptvalue_cast<QFlags<QFile::Permission> >(context->argument(1));
        bool _q_result = QFile::setPermissions(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QFile::symLinkTarget(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFile_throw_ambiguity_error_helper(context,
        qtscript_QFile_function_names[_id],
        qtscript_QFile_function_signatures[_id]);
}

static QScriptValue qtscript_QFile_toScriptValue(QScriptEngine *engine, QFile* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFile_fromScriptValue(const QScriptValue &value, QFile* &out)
{
    out = qobject_cast<QFile*>(value.toQObject());
}

QScriptValue qtscript_create_QFile_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFile*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFile*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFile_prototype_call, qtscript_QFile_function_lengths[i+12]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFile_function_names[i+12]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFile*>(engine, qtscript_QFile_toScriptValue, 
        qtscript_QFile_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFile_static_call, proto, qtscript_QFile_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFile_static_call,
            qtscript_QFile_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QFile_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("FileError"),
        qtscript_create_QFile_FileError_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MemoryMapFlags"),
        qtscript_create_QFile_MemoryMapFlags_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Permission"),
        qtscript_create_QFile_Permission_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Permissions"),
        qtscript_create_QFile_Permissions_class(engine));
    return ctor;
}
