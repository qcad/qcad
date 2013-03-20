#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstyleoption.h>
#include <QVariant>

#include "qtscriptshell_QStyleHintReturnMask.h"

static const char * const qtscript_QStyleHintReturnMask_function_names[] = {
    "QStyleHintReturnMask"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleHintReturnMask_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QStyleHintReturnMask_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleHintReturnMask_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleHintReturnMask::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleHintReturnMask*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleHintReturnMask*)
Q_DECLARE_METATYPE(QStyleHintReturnMask::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleHintReturnMask::StyleOptionType)
Q_DECLARE_METATYPE(QStyleHintReturn*)

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
// QStyleHintReturnMask::StyleOptionVersion
//

static const QStyleHintReturnMask::StyleOptionVersion qtscript_QStyleHintReturnMask_StyleOptionVersion_values[] = {
    QStyleHintReturnMask::Version
};

static const char * const qtscript_QStyleHintReturnMask_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleHintReturnMask_StyleOptionVersion_toStringHelper(QStyleHintReturnMask::StyleOptionVersion value)
{
    if ((value >= QStyleHintReturnMask::Version) && (value <= QStyleHintReturnMask::Version))
        return qtscript_QStyleHintReturnMask_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturnMask::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturnMask_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleHintReturnMask::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturnMask"));
    return clazz.property(qtscript_QStyleHintReturnMask_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleHintReturnMask_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleHintReturnMask::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleHintReturnMask::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturnMask_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturnMask::Version) && (arg <= QStyleHintReturnMask::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturnMask::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturnMask_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnMask::StyleOptionVersion value = qscriptvalue_cast<QStyleHintReturnMask::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturnMask_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnMask::StyleOptionVersion value = qscriptvalue_cast<QStyleHintReturnMask::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturnMask_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturnMask_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturnMask_StyleOptionVersion,
        qtscript_QStyleHintReturnMask_StyleOptionVersion_valueOf, qtscript_QStyleHintReturnMask_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleHintReturnMask::StyleOptionVersion>(engine, qtscript_QStyleHintReturnMask_StyleOptionVersion_toScriptValue,
        qtscript_QStyleHintReturnMask_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturnMask_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturnMask_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturnMask::StyleOptionType
//

static const QStyleHintReturnMask::StyleOptionType qtscript_QStyleHintReturnMask_StyleOptionType_values[] = {
    QStyleHintReturnMask::Type
};

static const char * const qtscript_QStyleHintReturnMask_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleHintReturnMask_StyleOptionType_toStringHelper(QStyleHintReturnMask::StyleOptionType value)
{
    if ((value >= QStyleHintReturnMask::Type) && (value <= QStyleHintReturnMask::Type))
        return qtscript_QStyleHintReturnMask_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturnMask::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturnMask_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleHintReturnMask::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturnMask"));
    return clazz.property(qtscript_QStyleHintReturnMask_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleHintReturnMask_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleHintReturnMask::StyleOptionType &out)
{
    out = qvariant_cast<QStyleHintReturnMask::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturnMask_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturnMask::Type) && (arg <= QStyleHintReturnMask::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturnMask::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturnMask_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnMask::StyleOptionType value = qscriptvalue_cast<QStyleHintReturnMask::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturnMask_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnMask::StyleOptionType value = qscriptvalue_cast<QStyleHintReturnMask::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturnMask_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturnMask_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturnMask_StyleOptionType,
        qtscript_QStyleHintReturnMask_StyleOptionType_valueOf, qtscript_QStyleHintReturnMask_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleHintReturnMask::StyleOptionType>(engine, qtscript_QStyleHintReturnMask_StyleOptionType_toScriptValue,
        qtscript_QStyleHintReturnMask_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturnMask_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturnMask_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturnMask
//

static QScriptValue qtscript_QStyleHintReturnMask_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStyleHintReturnMask* _q_self = qscriptvalue_cast<QStyleHintReturnMask*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleHintReturnMask.%0(): this object is not a QStyleHintReturnMask")
            .arg(qtscript_QStyleHintReturnMask_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleHintReturnMask");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleHintReturnMask_throw_ambiguity_error_helper(context,
        qtscript_QStyleHintReturnMask_function_names[_id+1],
        qtscript_QStyleHintReturnMask_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleHintReturnMask_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleHintReturnMask(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleHintReturnMask* _q_cpp_result = new QtScriptShell_QStyleHintReturnMask();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleHintReturnMask*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleHintReturnMask_throw_ambiguity_error_helper(context,
        qtscript_QStyleHintReturnMask_function_names[_id],
        qtscript_QStyleHintReturnMask_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleHintReturnMask_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleHintReturnMask*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleHintReturnMask*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleHintReturn*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleHintReturnMask*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleHintReturnMask_static_call, proto, qtscript_QStyleHintReturnMask_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleHintReturnMask_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleHintReturnMask_StyleOptionType_class(engine, ctor));
    return ctor;
}
