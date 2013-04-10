#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qurlinfo.h>
#include <QVariant>
#include <qdatetime.h>
#include <qurl.h>
#include <qurlinfo.h>

#include "qtscriptshell_QUrlInfo.h"

static const char * const qtscript_QUrlInfo_function_names[] = {
    "QUrlInfo"
    // static
    , "equal"
    , "greaterThan"
    , "lessThan"
    // prototype
    , "group"
    , "isDir"
    , "isExecutable"
    , "isFile"
    , "isReadable"
    , "isSymLink"
    , "isValid"
    , "isWritable"
    , "lastModified"
    , "lastRead"
    , "name"
    , "equals"
    , "owner"
    , "permissions"
    , "setDir"
    , "setFile"
    , "setGroup"
    , "setLastModified"
    , "setLastRead"
    , "setName"
    , "setOwner"
    , "setPermissions"
    , "setReadable"
    , "setSize"
    , "setSymLink"
    , "setWritable"
    , "size"
    , "toString"
};

static const char * const qtscript_QUrlInfo_function_signatures[] = {
    "\nString name, int permissions, String owner, String group, qint64 size, QDateTime lastModified, QDateTime lastRead, bool isDir, bool isFile, bool isSymLink, bool isWritable, bool isReadable, bool isExecutable\nQUrl url, int permissions, String owner, String group, qint64 size, QDateTime lastModified, QDateTime lastRead, bool isDir, bool isFile, bool isSymLink, bool isWritable, bool isReadable, bool isExecutable\nQUrlInfo ui"
    // static
    , "QUrlInfo i1, QUrlInfo i2, int sortBy"
    , "QUrlInfo i1, QUrlInfo i2, int sortBy"
    , "QUrlInfo i1, QUrlInfo i2, int sortBy"
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
    , ""
    , ""
    , "QUrlInfo i"
    , ""
    , ""
    , "bool b"
    , "bool b"
    , "String s"
    , "QDateTime dt"
    , "QDateTime dt"
    , "String name"
    , "String s"
    , "int p"
    , "bool b"
    , "qint64 size"
    , "bool b"
    , "bool b"
    , ""
""
};

static const int qtscript_QUrlInfo_function_lengths[] = {
    13
    // static
    , 3
    , 3
    , 3
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
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QUrlInfo_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUrlInfo::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUrlInfo)
Q_DECLARE_METATYPE(QUrlInfo*)
Q_DECLARE_METATYPE(QtScriptShell_QUrlInfo)
Q_DECLARE_METATYPE(QtScriptShell_QUrlInfo*)
Q_DECLARE_METATYPE(QUrlInfo::PermissionSpec)

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
// QUrlInfo::PermissionSpec
//

static const QUrlInfo::PermissionSpec qtscript_QUrlInfo_PermissionSpec_values[] = {
    QUrlInfo::ExeOther
    , QUrlInfo::WriteOther
    , QUrlInfo::ReadOther
    , QUrlInfo::ExeGroup
    , QUrlInfo::WriteGroup
    , QUrlInfo::ReadGroup
    , QUrlInfo::ExeOwner
    , QUrlInfo::WriteOwner
    , QUrlInfo::ReadOwner
};

static const char * const qtscript_QUrlInfo_PermissionSpec_keys[] = {
    "ExeOther"
    , "WriteOther"
    , "ReadOther"
    , "ExeGroup"
    , "WriteGroup"
    , "ReadGroup"
    , "ExeOwner"
    , "WriteOwner"
    , "ReadOwner"
};

static QString qtscript_QUrlInfo_PermissionSpec_toStringHelper(QUrlInfo::PermissionSpec value)
{
    for (int i = 0; i < 9; ++i) {
        if (qtscript_QUrlInfo_PermissionSpec_values[i] == value)
            return QString::fromLatin1(qtscript_QUrlInfo_PermissionSpec_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QUrlInfo_PermissionSpec_toScriptValue(QScriptEngine *engine, const QUrlInfo::PermissionSpec &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QUrlInfo"));
    return clazz.property(qtscript_QUrlInfo_PermissionSpec_toStringHelper(value));
}

static void qtscript_QUrlInfo_PermissionSpec_fromScriptValue(const QScriptValue &value, QUrlInfo::PermissionSpec &out)
{
    out = qvariant_cast<QUrlInfo::PermissionSpec>(value.toVariant());
}

static QScriptValue qtscript_construct_QUrlInfo_PermissionSpec(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 9; ++i) {
        if (qtscript_QUrlInfo_PermissionSpec_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QUrlInfo::PermissionSpec>(arg));
    }
    return context->throwError(QString::fromLatin1("PermissionSpec(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QUrlInfo_PermissionSpec_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUrlInfo::PermissionSpec value = qscriptvalue_cast<QUrlInfo::PermissionSpec>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUrlInfo_PermissionSpec_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUrlInfo::PermissionSpec value = qscriptvalue_cast<QUrlInfo::PermissionSpec>(context->thisObject());
    return QScriptValue(engine, qtscript_QUrlInfo_PermissionSpec_toStringHelper(value));
}

static QScriptValue qtscript_create_QUrlInfo_PermissionSpec_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QUrlInfo_PermissionSpec,
        qtscript_QUrlInfo_PermissionSpec_valueOf, qtscript_QUrlInfo_PermissionSpec_toString);
    qScriptRegisterMetaType<QUrlInfo::PermissionSpec>(engine, qtscript_QUrlInfo_PermissionSpec_toScriptValue,
        qtscript_QUrlInfo_PermissionSpec_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 9; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUrlInfo_PermissionSpec_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUrlInfo_PermissionSpec_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QUrlInfo
//

static QScriptValue qtscript_QUrlInfo_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 27;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUrlInfo* _q_self = qscriptvalue_cast<QUrlInfo*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUrlInfo.%0(): this object is not a QUrlInfo")
            .arg(qtscript_QUrlInfo_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->group();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDir();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isExecutable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFile();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isReadable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSymLink();
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
        bool _q_result = _q_self->isWritable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->lastModified();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->lastRead();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QUrlInfo _q_arg0 = qscriptvalue_cast<QUrlInfo>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->owner();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->permissions();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setDir(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFile(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setGroup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QDateTime _q_arg0 = context->argument(0).toDateTime();
        _q_self->setLastModified(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QDateTime _q_arg0 = context->argument(0).toDateTime();
        _q_self->setLastRead(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setOwner(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPermissions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setReadable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSymLink(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setWritable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27: {
    QString result = QString::fromLatin1("QUrlInfo");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUrlInfo_throw_ambiguity_error_helper(context,
        qtscript_QUrlInfo_function_names[_id+4],
        qtscript_QUrlInfo_function_signatures[_id+4]);
}

static QScriptValue qtscript_QUrlInfo_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUrlInfo(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUrlInfo _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUrlInfo)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QUrlInfo _q_arg0 = qscriptvalue_cast<QUrlInfo>(context->argument(0));
        QtScriptShell_QUrlInfo _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUrlInfo)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 13) {
        if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && context->argument(2).isString()
            && context->argument(3).isString()
            && (qMetaTypeId<qint64>() == context->argument(4).toVariant().userType())
            && (qMetaTypeId<QDateTime>() == context->argument(5).toVariant().userType())
            && (qMetaTypeId<QDateTime>() == context->argument(6).toVariant().userType())
            && context->argument(7).isBoolean()
            && context->argument(8).isBoolean()
            && context->argument(9).isBoolean()
            && context->argument(10).isBoolean()
            && context->argument(11).isBoolean()
            && context->argument(12).isBoolean()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QString _q_arg3 = context->argument(3).toString();
            qint64 _q_arg4 = qscriptvalue_cast<qint64>(context->argument(4));
            QDateTime _q_arg5 = context->argument(5).toDateTime();
            QDateTime _q_arg6 = context->argument(6).toDateTime();
            bool _q_arg7 = context->argument(7).toBoolean();
            bool _q_arg8 = context->argument(8).toBoolean();
            bool _q_arg9 = context->argument(9).toBoolean();
            bool _q_arg10 = context->argument(10).toBoolean();
            bool _q_arg11 = context->argument(11).toBoolean();
            bool _q_arg12 = context->argument(12).toBoolean();
            QtScriptShell_QUrlInfo _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8, _q_arg9, _q_arg10, _q_arg11, _q_arg12);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUrlInfo)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isString()
            && context->argument(3).isString()
            && (qMetaTypeId<qint64>() == context->argument(4).toVariant().userType())
            && (qMetaTypeId<QDateTime>() == context->argument(5).toVariant().userType())
            && (qMetaTypeId<QDateTime>() == context->argument(6).toVariant().userType())
            && context->argument(7).isBoolean()
            && context->argument(8).isBoolean()
            && context->argument(9).isBoolean()
            && context->argument(10).isBoolean()
            && context->argument(11).isBoolean()
            && context->argument(12).isBoolean()) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QString _q_arg3 = context->argument(3).toString();
            qint64 _q_arg4 = qscriptvalue_cast<qint64>(context->argument(4));
            QDateTime _q_arg5 = context->argument(5).toDateTime();
            QDateTime _q_arg6 = context->argument(6).toDateTime();
            bool _q_arg7 = context->argument(7).toBoolean();
            bool _q_arg8 = context->argument(8).toBoolean();
            bool _q_arg9 = context->argument(9).toBoolean();
            bool _q_arg10 = context->argument(10).toBoolean();
            bool _q_arg11 = context->argument(11).toBoolean();
            bool _q_arg12 = context->argument(12).toBoolean();
            QtScriptShell_QUrlInfo _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8, _q_arg9, _q_arg10, _q_arg11, _q_arg12);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUrlInfo)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QUrlInfo _q_arg0 = qscriptvalue_cast<QUrlInfo>(context->argument(0));
        QUrlInfo _q_arg1 = qscriptvalue_cast<QUrlInfo>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = QUrlInfo::equal(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QUrlInfo _q_arg0 = qscriptvalue_cast<QUrlInfo>(context->argument(0));
        QUrlInfo _q_arg1 = qscriptvalue_cast<QUrlInfo>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = QUrlInfo::greaterThan(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QUrlInfo _q_arg0 = qscriptvalue_cast<QUrlInfo>(context->argument(0));
        QUrlInfo _q_arg1 = qscriptvalue_cast<QUrlInfo>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = QUrlInfo::lessThan(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUrlInfo_throw_ambiguity_error_helper(context,
        qtscript_QUrlInfo_function_names[_id],
        qtscript_QUrlInfo_function_signatures[_id]);
}

QScriptValue qtscript_create_QUrlInfo_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUrlInfo*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUrlInfo*)0));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUrlInfo_prototype_call, qtscript_QUrlInfo_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUrlInfo_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QUrlInfo>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QUrlInfo*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUrlInfo_static_call, proto, qtscript_QUrlInfo_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUrlInfo_static_call,
            qtscript_QUrlInfo_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QUrlInfo_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("PermissionSpec"),
        qtscript_create_QUrlInfo_PermissionSpec_class(engine, ctor));
    return ctor;
}
