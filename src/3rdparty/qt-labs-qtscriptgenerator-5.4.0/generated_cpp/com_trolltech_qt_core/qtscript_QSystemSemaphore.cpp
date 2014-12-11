#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsystemsemaphore.h>
#include <QVariant>
#include <qsystemsemaphore.h>

static const char * const qtscript_QSystemSemaphore_function_names[] = {
    "QSystemSemaphore"
    // static
    // prototype
    , "acquire"
    , "error"
    , "errorString"
    , "key"
    , "release"
    , "setKey"
    , "toString"
};

static const char * const qtscript_QSystemSemaphore_function_signatures[] = {
    "String key, int initialValue, AccessMode mode"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int n"
    , "String key, int initialValue, AccessMode mode"
""
};

static const int qtscript_QSystemSemaphore_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 3
    , 0
};

static QScriptValue qtscript_QSystemSemaphore_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSystemSemaphore::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSystemSemaphore*)
Q_DECLARE_METATYPE(QSystemSemaphore::SystemSemaphoreError)
Q_DECLARE_METATYPE(QSystemSemaphore::AccessMode)

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
// QSystemSemaphore::SystemSemaphoreError
//

static const QSystemSemaphore::SystemSemaphoreError qtscript_QSystemSemaphore_SystemSemaphoreError_values[] = {
    QSystemSemaphore::NoError
    , QSystemSemaphore::PermissionDenied
    , QSystemSemaphore::KeyError
    , QSystemSemaphore::AlreadyExists
    , QSystemSemaphore::NotFound
    , QSystemSemaphore::OutOfResources
    , QSystemSemaphore::UnknownError
};

static const char * const qtscript_QSystemSemaphore_SystemSemaphoreError_keys[] = {
    "NoError"
    , "PermissionDenied"
    , "KeyError"
    , "AlreadyExists"
    , "NotFound"
    , "OutOfResources"
    , "UnknownError"
};

static QString qtscript_QSystemSemaphore_SystemSemaphoreError_toStringHelper(QSystemSemaphore::SystemSemaphoreError value)
{
    if ((value >= QSystemSemaphore::NoError) && (value <= QSystemSemaphore::UnknownError))
        return qtscript_QSystemSemaphore_SystemSemaphoreError_keys[static_cast<int>(value)-static_cast<int>(QSystemSemaphore::NoError)];
    return QString();
}

static QScriptValue qtscript_QSystemSemaphore_SystemSemaphoreError_toScriptValue(QScriptEngine *engine, const QSystemSemaphore::SystemSemaphoreError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSystemSemaphore"));
    return clazz.property(qtscript_QSystemSemaphore_SystemSemaphoreError_toStringHelper(value));
}

static void qtscript_QSystemSemaphore_SystemSemaphoreError_fromScriptValue(const QScriptValue &value, QSystemSemaphore::SystemSemaphoreError &out)
{
    out = qvariant_cast<QSystemSemaphore::SystemSemaphoreError>(value.toVariant());
}

static QScriptValue qtscript_construct_QSystemSemaphore_SystemSemaphoreError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSystemSemaphore::NoError) && (arg <= QSystemSemaphore::UnknownError))
        return qScriptValueFromValue(engine,  static_cast<QSystemSemaphore::SystemSemaphoreError>(arg));
    return context->throwError(QString::fromLatin1("SystemSemaphoreError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSystemSemaphore_SystemSemaphoreError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSystemSemaphore::SystemSemaphoreError value = qscriptvalue_cast<QSystemSemaphore::SystemSemaphoreError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSystemSemaphore_SystemSemaphoreError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSystemSemaphore::SystemSemaphoreError value = qscriptvalue_cast<QSystemSemaphore::SystemSemaphoreError>(context->thisObject());
    return QScriptValue(engine, qtscript_QSystemSemaphore_SystemSemaphoreError_toStringHelper(value));
}

static QScriptValue qtscript_create_QSystemSemaphore_SystemSemaphoreError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSystemSemaphore_SystemSemaphoreError,
        qtscript_QSystemSemaphore_SystemSemaphoreError_valueOf, qtscript_QSystemSemaphore_SystemSemaphoreError_toString);
    qScriptRegisterMetaType<QSystemSemaphore::SystemSemaphoreError>(engine, qtscript_QSystemSemaphore_SystemSemaphoreError_toScriptValue,
        qtscript_QSystemSemaphore_SystemSemaphoreError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSystemSemaphore_SystemSemaphoreError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSystemSemaphore_SystemSemaphoreError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSystemSemaphore::AccessMode
//

static const QSystemSemaphore::AccessMode qtscript_QSystemSemaphore_AccessMode_values[] = {
    QSystemSemaphore::Open
    , QSystemSemaphore::Create
};

static const char * const qtscript_QSystemSemaphore_AccessMode_keys[] = {
    "Open"
    , "Create"
};

static QString qtscript_QSystemSemaphore_AccessMode_toStringHelper(QSystemSemaphore::AccessMode value)
{
    if ((value >= QSystemSemaphore::Open) && (value <= QSystemSemaphore::Create))
        return qtscript_QSystemSemaphore_AccessMode_keys[static_cast<int>(value)-static_cast<int>(QSystemSemaphore::Open)];
    return QString();
}

static QScriptValue qtscript_QSystemSemaphore_AccessMode_toScriptValue(QScriptEngine *engine, const QSystemSemaphore::AccessMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSystemSemaphore"));
    return clazz.property(qtscript_QSystemSemaphore_AccessMode_toStringHelper(value));
}

static void qtscript_QSystemSemaphore_AccessMode_fromScriptValue(const QScriptValue &value, QSystemSemaphore::AccessMode &out)
{
    out = qvariant_cast<QSystemSemaphore::AccessMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QSystemSemaphore_AccessMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSystemSemaphore::Open) && (arg <= QSystemSemaphore::Create))
        return qScriptValueFromValue(engine,  static_cast<QSystemSemaphore::AccessMode>(arg));
    return context->throwError(QString::fromLatin1("AccessMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSystemSemaphore_AccessMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSystemSemaphore::AccessMode value = qscriptvalue_cast<QSystemSemaphore::AccessMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSystemSemaphore_AccessMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSystemSemaphore::AccessMode value = qscriptvalue_cast<QSystemSemaphore::AccessMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QSystemSemaphore_AccessMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QSystemSemaphore_AccessMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSystemSemaphore_AccessMode,
        qtscript_QSystemSemaphore_AccessMode_valueOf, qtscript_QSystemSemaphore_AccessMode_toString);
    qScriptRegisterMetaType<QSystemSemaphore::AccessMode>(engine, qtscript_QSystemSemaphore_AccessMode_toScriptValue,
        qtscript_QSystemSemaphore_AccessMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSystemSemaphore_AccessMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSystemSemaphore_AccessMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSystemSemaphore
//

static QScriptValue qtscript_QSystemSemaphore_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSystemSemaphore* _q_self = qscriptvalue_cast<QSystemSemaphore*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSystemSemaphore.%0(): this object is not a QSystemSemaphore")
            .arg(qtscript_QSystemSemaphore_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->acquire();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSystemSemaphore::SystemSemaphoreError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->key();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->release();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->release(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setKey(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setKey(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QSystemSemaphore::AccessMode _q_arg2 = qscriptvalue_cast<QSystemSemaphore::AccessMode>(context->argument(2));
        _q_self->setKey(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QSystemSemaphore");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSystemSemaphore_throw_ambiguity_error_helper(context,
        qtscript_QSystemSemaphore_function_names[_id+1],
        qtscript_QSystemSemaphore_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSystemSemaphore_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSystemSemaphore(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSystemSemaphore* _q_cpp_result = new QSystemSemaphore(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QSystemSemaphore* _q_cpp_result = new QSystemSemaphore(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QSystemSemaphore::AccessMode _q_arg2 = qscriptvalue_cast<QSystemSemaphore::AccessMode>(context->argument(2));
        QSystemSemaphore* _q_cpp_result = new QSystemSemaphore(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSystemSemaphore_throw_ambiguity_error_helper(context,
        qtscript_QSystemSemaphore_function_names[_id],
        qtscript_QSystemSemaphore_function_signatures[_id]);
}

QScriptValue qtscript_create_QSystemSemaphore_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSystemSemaphore*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSystemSemaphore*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSystemSemaphore_prototype_call, qtscript_QSystemSemaphore_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSystemSemaphore_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSystemSemaphore*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSystemSemaphore_static_call, proto, qtscript_QSystemSemaphore_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SystemSemaphoreError"),
        qtscript_create_QSystemSemaphore_SystemSemaphoreError_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AccessMode"),
        qtscript_create_QSystemSemaphore_AccessMode_class(engine, ctor));
    return ctor;
}
