#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstyleoption.h>
#include <QVariant>

#include "qtscriptshell_QStyleHintReturnVariant.h"

static const char * const qtscript_QStyleHintReturnVariant_function_names[] = {
    "QStyleHintReturnVariant"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleHintReturnVariant_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QStyleHintReturnVariant_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleHintReturnVariant_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleHintReturnVariant::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleHintReturnVariant*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleHintReturnVariant*)
Q_DECLARE_METATYPE(QStyleHintReturnVariant::StyleOptionType)
Q_DECLARE_METATYPE(QStyleHintReturnVariant::StyleOptionVersion)
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
// QStyleHintReturnVariant::StyleOptionType
//

static const QStyleHintReturnVariant::StyleOptionType qtscript_QStyleHintReturnVariant_StyleOptionType_values[] = {
    QStyleHintReturnVariant::Type
};

static const char * const qtscript_QStyleHintReturnVariant_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleHintReturnVariant_StyleOptionType_toStringHelper(QStyleHintReturnVariant::StyleOptionType value)
{
    if ((value >= QStyleHintReturnVariant::Type) && (value <= QStyleHintReturnVariant::Type))
        return qtscript_QStyleHintReturnVariant_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturnVariant::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturnVariant_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleHintReturnVariant::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturnVariant"));
    return clazz.property(qtscript_QStyleHintReturnVariant_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleHintReturnVariant_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleHintReturnVariant::StyleOptionType &out)
{
    out = qvariant_cast<QStyleHintReturnVariant::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturnVariant_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturnVariant::Type) && (arg <= QStyleHintReturnVariant::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturnVariant::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturnVariant_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnVariant::StyleOptionType value = qscriptvalue_cast<QStyleHintReturnVariant::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturnVariant_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnVariant::StyleOptionType value = qscriptvalue_cast<QStyleHintReturnVariant::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturnVariant_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturnVariant_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturnVariant_StyleOptionType,
        qtscript_QStyleHintReturnVariant_StyleOptionType_valueOf, qtscript_QStyleHintReturnVariant_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleHintReturnVariant::StyleOptionType>(engine, qtscript_QStyleHintReturnVariant_StyleOptionType_toScriptValue,
        qtscript_QStyleHintReturnVariant_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturnVariant_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturnVariant_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturnVariant::StyleOptionVersion
//

static const QStyleHintReturnVariant::StyleOptionVersion qtscript_QStyleHintReturnVariant_StyleOptionVersion_values[] = {
    QStyleHintReturnVariant::Version
};

static const char * const qtscript_QStyleHintReturnVariant_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleHintReturnVariant_StyleOptionVersion_toStringHelper(QStyleHintReturnVariant::StyleOptionVersion value)
{
    if ((value >= QStyleHintReturnVariant::Version) && (value <= QStyleHintReturnVariant::Version))
        return qtscript_QStyleHintReturnVariant_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturnVariant::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturnVariant_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleHintReturnVariant::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturnVariant"));
    return clazz.property(qtscript_QStyleHintReturnVariant_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleHintReturnVariant_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleHintReturnVariant::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleHintReturnVariant::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturnVariant_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturnVariant::Version) && (arg <= QStyleHintReturnVariant::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturnVariant::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturnVariant_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnVariant::StyleOptionVersion value = qscriptvalue_cast<QStyleHintReturnVariant::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturnVariant_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturnVariant::StyleOptionVersion value = qscriptvalue_cast<QStyleHintReturnVariant::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturnVariant_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturnVariant_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturnVariant_StyleOptionVersion,
        qtscript_QStyleHintReturnVariant_StyleOptionVersion_valueOf, qtscript_QStyleHintReturnVariant_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleHintReturnVariant::StyleOptionVersion>(engine, qtscript_QStyleHintReturnVariant_StyleOptionVersion_toScriptValue,
        qtscript_QStyleHintReturnVariant_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturnVariant_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturnVariant_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturnVariant
//

static QScriptValue qtscript_QStyleHintReturnVariant_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleHintReturnVariant* _q_self = qscriptvalue_cast<QStyleHintReturnVariant*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleHintReturnVariant.%0(): this object is not a QStyleHintReturnVariant")
            .arg(qtscript_QStyleHintReturnVariant_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleHintReturnVariant");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleHintReturnVariant_throw_ambiguity_error_helper(context,
        qtscript_QStyleHintReturnVariant_function_names[_id+1],
        qtscript_QStyleHintReturnVariant_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleHintReturnVariant_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleHintReturnVariant(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleHintReturnVariant* _q_cpp_result = new QtScriptShell_QStyleHintReturnVariant();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleHintReturnVariant*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleHintReturnVariant_throw_ambiguity_error_helper(context,
        qtscript_QStyleHintReturnVariant_function_names[_id],
        qtscript_QStyleHintReturnVariant_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleHintReturnVariant_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleHintReturnVariant*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleHintReturnVariant*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleHintReturn*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleHintReturnVariant*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleHintReturnVariant_static_call, proto, qtscript_QStyleHintReturnVariant_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleHintReturnVariant_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleHintReturnVariant_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
