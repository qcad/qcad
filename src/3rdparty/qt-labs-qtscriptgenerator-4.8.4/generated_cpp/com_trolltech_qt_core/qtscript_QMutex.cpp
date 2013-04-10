#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmutex.h>
#include <QVariant>
#include <qmutex.h>

static const char * const qtscript_QMutex_function_names[] = {
    "QMutex"
    // static
    // prototype
    , "lock"
    , "lockInline"
    , "tryLock"
    , "tryLockInline"
    , "unlock"
    , "unlockInline"
    , "toString"
};

static const char * const qtscript_QMutex_function_signatures[] = {
    "RecursionMode mode"
    // static
    // prototype
    , ""
    , ""
    , "\nint timeout"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QMutex_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QMutex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMutex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMutex*)
Q_DECLARE_METATYPE(QMutex::RecursionMode)

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
// QMutex::RecursionMode
//

static const QMutex::RecursionMode qtscript_QMutex_RecursionMode_values[] = {
    QMutex::NonRecursive
    , QMutex::Recursive
};

static const char * const qtscript_QMutex_RecursionMode_keys[] = {
    "NonRecursive"
    , "Recursive"
};

static QString qtscript_QMutex_RecursionMode_toStringHelper(QMutex::RecursionMode value)
{
    if ((value >= QMutex::NonRecursive) && (value <= QMutex::Recursive))
        return qtscript_QMutex_RecursionMode_keys[static_cast<int>(value)-static_cast<int>(QMutex::NonRecursive)];
    return QString();
}

static QScriptValue qtscript_QMutex_RecursionMode_toScriptValue(QScriptEngine *engine, const QMutex::RecursionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMutex"));
    return clazz.property(qtscript_QMutex_RecursionMode_toStringHelper(value));
}

static void qtscript_QMutex_RecursionMode_fromScriptValue(const QScriptValue &value, QMutex::RecursionMode &out)
{
    out = qvariant_cast<QMutex::RecursionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QMutex_RecursionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QMutex::NonRecursive) && (arg <= QMutex::Recursive))
        return qScriptValueFromValue(engine,  static_cast<QMutex::RecursionMode>(arg));
    return context->throwError(QString::fromLatin1("RecursionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMutex_RecursionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMutex::RecursionMode value = qscriptvalue_cast<QMutex::RecursionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMutex_RecursionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMutex::RecursionMode value = qscriptvalue_cast<QMutex::RecursionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QMutex_RecursionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QMutex_RecursionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMutex_RecursionMode,
        qtscript_QMutex_RecursionMode_valueOf, qtscript_QMutex_RecursionMode_toString);
    qScriptRegisterMetaType<QMutex::RecursionMode>(engine, qtscript_QMutex_RecursionMode_toScriptValue,
        qtscript_QMutex_RecursionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMutex_RecursionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMutex_RecursionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMutex
//

static QScriptValue qtscript_QMutex_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QMutex* _q_self = qscriptvalue_cast<QMutex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMutex.%0(): this object is not a QMutex")
            .arg(qtscript_QMutex_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->lock();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->lockInline();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->tryLock();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->tryLock(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->tryLockInline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->unlock();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->unlockInline();
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QMutex");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMutex_throw_ambiguity_error_helper(context,
        qtscript_QMutex_function_names[_id+1],
        qtscript_QMutex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMutex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMutex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QMutex* _q_cpp_result = new QMutex();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QMutex::RecursionMode _q_arg0 = qscriptvalue_cast<QMutex::RecursionMode>(context->argument(0));
        QMutex* _q_cpp_result = new QMutex(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMutex_throw_ambiguity_error_helper(context,
        qtscript_QMutex_function_names[_id],
        qtscript_QMutex_function_signatures[_id]);
}

QScriptValue qtscript_create_QMutex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMutex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMutex*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMutex_prototype_call, qtscript_QMutex_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMutex_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMutex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMutex_static_call, proto, qtscript_QMutex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("RecursionMode"),
        qtscript_create_QMutex_RecursionMode_class(engine, ctor));
    return ctor;
}
