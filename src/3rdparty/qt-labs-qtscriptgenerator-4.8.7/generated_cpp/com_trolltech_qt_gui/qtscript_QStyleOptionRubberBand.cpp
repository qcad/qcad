#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstyleoption.h>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyleOptionRubberBand.h"

static const char * const qtscript_QStyleOptionRubberBand_function_names[] = {
    "QStyleOptionRubberBand"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionRubberBand_function_signatures[] = {
    "\nQStyleOptionRubberBand other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionRubberBand_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionRubberBand_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionRubberBand::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionRubberBand)
Q_DECLARE_METATYPE(QStyleOptionRubberBand*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionRubberBand)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionRubberBand*)
Q_DECLARE_METATYPE(QStyleOptionRubberBand::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionRubberBand::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOption*)

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
// QStyleOptionRubberBand::StyleOptionVersion
//

static const QStyleOptionRubberBand::StyleOptionVersion qtscript_QStyleOptionRubberBand_StyleOptionVersion_values[] = {
    QStyleOptionRubberBand::Version
};

static const char * const qtscript_QStyleOptionRubberBand_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionRubberBand_StyleOptionVersion_toStringHelper(QStyleOptionRubberBand::StyleOptionVersion value)
{
    if ((value >= QStyleOptionRubberBand::Version) && (value <= QStyleOptionRubberBand::Version))
        return qtscript_QStyleOptionRubberBand_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionRubberBand::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionRubberBand_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionRubberBand::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionRubberBand"));
    return clazz.property(qtscript_QStyleOptionRubberBand_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionRubberBand_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionRubberBand::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionRubberBand::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionRubberBand_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionRubberBand::Version) && (arg <= QStyleOptionRubberBand::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionRubberBand::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionRubberBand_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionRubberBand::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionRubberBand::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionRubberBand_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionRubberBand::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionRubberBand::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionRubberBand_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionRubberBand_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionRubberBand_StyleOptionVersion,
        qtscript_QStyleOptionRubberBand_StyleOptionVersion_valueOf, qtscript_QStyleOptionRubberBand_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionRubberBand::StyleOptionVersion>(engine, qtscript_QStyleOptionRubberBand_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionRubberBand_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionRubberBand_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionRubberBand_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionRubberBand::StyleOptionType
//

static const QStyleOptionRubberBand::StyleOptionType qtscript_QStyleOptionRubberBand_StyleOptionType_values[] = {
    QStyleOptionRubberBand::Type
};

static const char * const qtscript_QStyleOptionRubberBand_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionRubberBand_StyleOptionType_toStringHelper(QStyleOptionRubberBand::StyleOptionType value)
{
    if ((value >= QStyleOptionRubberBand::Type) && (value <= QStyleOptionRubberBand::Type))
        return qtscript_QStyleOptionRubberBand_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionRubberBand::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionRubberBand_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionRubberBand::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionRubberBand"));
    return clazz.property(qtscript_QStyleOptionRubberBand_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionRubberBand_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionRubberBand::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionRubberBand::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionRubberBand_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionRubberBand::Type) && (arg <= QStyleOptionRubberBand::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionRubberBand::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionRubberBand_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionRubberBand::StyleOptionType value = qscriptvalue_cast<QStyleOptionRubberBand::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionRubberBand_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionRubberBand::StyleOptionType value = qscriptvalue_cast<QStyleOptionRubberBand::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionRubberBand_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionRubberBand_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionRubberBand_StyleOptionType,
        qtscript_QStyleOptionRubberBand_StyleOptionType_valueOf, qtscript_QStyleOptionRubberBand_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionRubberBand::StyleOptionType>(engine, qtscript_QStyleOptionRubberBand_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionRubberBand_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionRubberBand_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionRubberBand_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionRubberBand
//

static QScriptValue qtscript_QStyleOptionRubberBand_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionRubberBand* _q_self = qscriptvalue_cast<QStyleOptionRubberBand*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionRubberBand.%0(): this object is not a QStyleOptionRubberBand")
            .arg(qtscript_QStyleOptionRubberBand_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionRubberBand");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionRubberBand_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionRubberBand_function_names[_id+1],
        qtscript_QStyleOptionRubberBand_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionRubberBand_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionRubberBand(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionRubberBand _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionRubberBand)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionRubberBand _q_arg0 = qscriptvalue_cast<QStyleOptionRubberBand>(context->argument(0));
        QtScriptShell_QStyleOptionRubberBand _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionRubberBand)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionRubberBand_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionRubberBand_function_names[_id],
        qtscript_QStyleOptionRubberBand_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionRubberBand_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionRubberBand*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionRubberBand*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionRubberBand>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionRubberBand*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionRubberBand_static_call, proto, qtscript_QStyleOptionRubberBand_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionRubberBand_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionRubberBand_StyleOptionType_class(engine, ctor));
    return ctor;
}
