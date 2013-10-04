#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtconcurrentexception.h>
#include <QVariant>
#include <qtconcurrentreducekernel.h>
#include <qtconcurrentthreadengine.h>

#include <qtconcurrentreducekernel.h>
#include <qtconcurrentthreadengine.h>

static const char * const qtscript_QtConcurrent_function_names[] = {
    "QtConcurrent"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QtConcurrent_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QtConcurrent_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QtConcurrent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QtConcurrent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtConcurrent::ReduceOption)
Q_DECLARE_METATYPE(QFlags<QtConcurrent::ReduceOption>)
Q_DECLARE_METATYPE(QtConcurrent::ThreadFunctionResult)

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
// QtConcurrent::ReduceOption
//

static const QtConcurrent::ReduceOption qtscript_QtConcurrent_ReduceOption_values[] = {
    QtConcurrent::UnorderedReduce
    , QtConcurrent::OrderedReduce
    , QtConcurrent::SequentialReduce
};

static const char * const qtscript_QtConcurrent_ReduceOption_keys[] = {
    "UnorderedReduce"
    , "OrderedReduce"
    , "SequentialReduce"
};

static QString qtscript_QtConcurrent_ReduceOption_toStringHelper(QtConcurrent::ReduceOption value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QtConcurrent_ReduceOption_values[i] == value)
            return QString::fromLatin1(qtscript_QtConcurrent_ReduceOption_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QtConcurrent_ReduceOption_toScriptValue(QScriptEngine *engine, const QtConcurrent::ReduceOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QtConcurrent"));
    return clazz.property(qtscript_QtConcurrent_ReduceOption_toStringHelper(value));
}

static void qtscript_QtConcurrent_ReduceOption_fromScriptValue(const QScriptValue &value, QtConcurrent::ReduceOption &out)
{
    out = qvariant_cast<QtConcurrent::ReduceOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QtConcurrent_ReduceOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QtConcurrent_ReduceOption_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QtConcurrent::ReduceOption>(arg));
    }
    return context->throwError(QString::fromLatin1("ReduceOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QtConcurrent_ReduceOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ReduceOption value = qscriptvalue_cast<QtConcurrent::ReduceOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QtConcurrent_ReduceOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ReduceOption value = qscriptvalue_cast<QtConcurrent::ReduceOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QtConcurrent_ReduceOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QtConcurrent_ReduceOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QtConcurrent_ReduceOption,
        qtscript_QtConcurrent_ReduceOption_valueOf, qtscript_QtConcurrent_ReduceOption_toString);
    qScriptRegisterMetaType<QtConcurrent::ReduceOption>(engine, qtscript_QtConcurrent_ReduceOption_toScriptValue,
        qtscript_QtConcurrent_ReduceOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QtConcurrent_ReduceOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QtConcurrent_ReduceOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QtConcurrent::ReduceOptions
//

static QScriptValue qtscript_QtConcurrent_ReduceOptions_toScriptValue(QScriptEngine *engine, const QtConcurrent::ReduceOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QtConcurrent_ReduceOptions_fromScriptValue(const QScriptValue &value, QtConcurrent::ReduceOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QtConcurrent::ReduceOptions>())
        out = qvariant_cast<QtConcurrent::ReduceOptions>(var);
    else if (var.userType() == qMetaTypeId<QtConcurrent::ReduceOption>())
        out = qvariant_cast<QtConcurrent::ReduceOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QtConcurrent_ReduceOptions(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ReduceOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QtConcurrent::ReduceOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QtConcurrent::ReduceOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ReduceOptions(): argument %0 is not of type ReduceOption").arg(i));
            }
            result |= qvariant_cast<QtConcurrent::ReduceOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QtConcurrent_ReduceOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ReduceOptions value = qscriptvalue_cast<QtConcurrent::ReduceOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QtConcurrent_ReduceOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ReduceOptions value = qscriptvalue_cast<QtConcurrent::ReduceOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QtConcurrent_ReduceOption_values[i]) == qtscript_QtConcurrent_ReduceOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QtConcurrent_ReduceOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QtConcurrent_ReduceOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QtConcurrent::ReduceOptions>() == otherObj.value<QtConcurrent::ReduceOptions>())));
}

static QScriptValue qtscript_create_QtConcurrent_ReduceOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QtConcurrent_ReduceOptions, qtscript_QtConcurrent_ReduceOptions_valueOf,
        qtscript_QtConcurrent_ReduceOptions_toString, qtscript_QtConcurrent_ReduceOptions_equals);
    qScriptRegisterMetaType<QtConcurrent::ReduceOptions>(engine, qtscript_QtConcurrent_ReduceOptions_toScriptValue,
        qtscript_QtConcurrent_ReduceOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QtConcurrent::ThreadFunctionResult
//

static const QtConcurrent::ThreadFunctionResult qtscript_QtConcurrent_ThreadFunctionResult_values[] = {
    QtConcurrent::ThrottleThread
    , QtConcurrent::ThreadFinished
};

static const char * const qtscript_QtConcurrent_ThreadFunctionResult_keys[] = {
    "ThrottleThread"
    , "ThreadFinished"
};

static QString qtscript_QtConcurrent_ThreadFunctionResult_toStringHelper(QtConcurrent::ThreadFunctionResult value)
{
    if ((value >= QtConcurrent::ThrottleThread) && (value <= QtConcurrent::ThreadFinished))
        return qtscript_QtConcurrent_ThreadFunctionResult_keys[static_cast<int>(value)-static_cast<int>(QtConcurrent::ThrottleThread)];
    return QString();
}

static QScriptValue qtscript_QtConcurrent_ThreadFunctionResult_toScriptValue(QScriptEngine *engine, const QtConcurrent::ThreadFunctionResult &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QtConcurrent"));
    return clazz.property(qtscript_QtConcurrent_ThreadFunctionResult_toStringHelper(value));
}

static void qtscript_QtConcurrent_ThreadFunctionResult_fromScriptValue(const QScriptValue &value, QtConcurrent::ThreadFunctionResult &out)
{
    out = qvariant_cast<QtConcurrent::ThreadFunctionResult>(value.toVariant());
}

static QScriptValue qtscript_construct_QtConcurrent_ThreadFunctionResult(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QtConcurrent::ThrottleThread) && (arg <= QtConcurrent::ThreadFinished))
        return qScriptValueFromValue(engine,  static_cast<QtConcurrent::ThreadFunctionResult>(arg));
    return context->throwError(QString::fromLatin1("ThreadFunctionResult(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QtConcurrent_ThreadFunctionResult_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ThreadFunctionResult value = qscriptvalue_cast<QtConcurrent::ThreadFunctionResult>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QtConcurrent_ThreadFunctionResult_toString(QScriptContext *context, QScriptEngine *engine)
{
    QtConcurrent::ThreadFunctionResult value = qscriptvalue_cast<QtConcurrent::ThreadFunctionResult>(context->thisObject());
    return QScriptValue(engine, qtscript_QtConcurrent_ThreadFunctionResult_toStringHelper(value));
}

static QScriptValue qtscript_create_QtConcurrent_ThreadFunctionResult_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QtConcurrent_ThreadFunctionResult,
        qtscript_QtConcurrent_ThreadFunctionResult_valueOf, qtscript_QtConcurrent_ThreadFunctionResult_toString);
    qScriptRegisterMetaType<QtConcurrent::ThreadFunctionResult>(engine, qtscript_QtConcurrent_ThreadFunctionResult_toScriptValue,
        qtscript_QtConcurrent_ThreadFunctionResult_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QtConcurrent_ThreadFunctionResult_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QtConcurrent_ThreadFunctionResult_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QtConcurrent
//

static QScriptValue qtscript_QtConcurrent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QtConcurrent cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QtConcurrent_throw_ambiguity_error_helper(context,
        qtscript_QtConcurrent_function_names[_id],
        qtscript_QtConcurrent_function_signatures[_id]);
}

QScriptValue qtscript_create_QtConcurrent_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_QtConcurrent_static_call, proto, qtscript_QtConcurrent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ReduceOption"),
        qtscript_create_QtConcurrent_ReduceOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ReduceOptions"),
        qtscript_create_QtConcurrent_ReduceOptions_class(engine));
    ctor.setProperty(QString::fromLatin1("ThreadFunctionResult"),
        qtscript_create_QtConcurrent_ThreadFunctionResult_class(engine, ctor));
    return ctor;
}
