#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstyleoption.h>
#include <QVariant>

#include "qtscriptshell_QStyleHintReturn.h"

static const char * const qtscript_QStyleHintReturn_function_names[] = {
    "QStyleHintReturn"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleHintReturn_function_signatures[] = {
    "int version, int type"
    // static
    // prototype
""
};

static const int qtscript_QStyleHintReturn_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleHintReturn_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleHintReturn::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleHintReturn*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleHintReturn*)
Q_DECLARE_METATYPE(QStyleHintReturn::HintReturnType)
Q_DECLARE_METATYPE(QStyleHintReturn::StyleOptionType)
Q_DECLARE_METATYPE(QStyleHintReturn::StyleOptionVersion)

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
// QStyleHintReturn::HintReturnType
//

static const QStyleHintReturn::HintReturnType qtscript_QStyleHintReturn_HintReturnType_values[] = {
    QStyleHintReturn::SH_Default
    , QStyleHintReturn::SH_Mask
    , QStyleHintReturn::SH_Variant
};

static const char * const qtscript_QStyleHintReturn_HintReturnType_keys[] = {
    "SH_Default"
    , "SH_Mask"
    , "SH_Variant"
};

static QString qtscript_QStyleHintReturn_HintReturnType_toStringHelper(QStyleHintReturn::HintReturnType value)
{
    if ((value >= QStyleHintReturn::SH_Default) && (value <= QStyleHintReturn::SH_Variant))
        return qtscript_QStyleHintReturn_HintReturnType_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturn::SH_Default)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturn_HintReturnType_toScriptValue(QScriptEngine *engine, const QStyleHintReturn::HintReturnType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturn"));
    return clazz.property(qtscript_QStyleHintReturn_HintReturnType_toStringHelper(value));
}

static void qtscript_QStyleHintReturn_HintReturnType_fromScriptValue(const QScriptValue &value, QStyleHintReturn::HintReturnType &out)
{
    out = qvariant_cast<QStyleHintReturn::HintReturnType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturn_HintReturnType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturn::SH_Default) && (arg <= QStyleHintReturn::SH_Variant))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturn::HintReturnType>(arg));
    return context->throwError(QString::fromLatin1("HintReturnType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturn_HintReturnType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturn::HintReturnType value = qscriptvalue_cast<QStyleHintReturn::HintReturnType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturn_HintReturnType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturn::HintReturnType value = qscriptvalue_cast<QStyleHintReturn::HintReturnType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturn_HintReturnType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturn_HintReturnType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturn_HintReturnType,
        qtscript_QStyleHintReturn_HintReturnType_valueOf, qtscript_QStyleHintReturn_HintReturnType_toString);
    qScriptRegisterMetaType<QStyleHintReturn::HintReturnType>(engine, qtscript_QStyleHintReturn_HintReturnType_toScriptValue,
        qtscript_QStyleHintReturn_HintReturnType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturn_HintReturnType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturn_HintReturnType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturn::StyleOptionType
//

static const QStyleHintReturn::StyleOptionType qtscript_QStyleHintReturn_StyleOptionType_values[] = {
    QStyleHintReturn::Type
};

static const char * const qtscript_QStyleHintReturn_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleHintReturn_StyleOptionType_toStringHelper(QStyleHintReturn::StyleOptionType value)
{
    if ((value >= QStyleHintReturn::Type) && (value <= QStyleHintReturn::Type))
        return qtscript_QStyleHintReturn_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturn::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturn_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleHintReturn::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturn"));
    return clazz.property(qtscript_QStyleHintReturn_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleHintReturn_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleHintReturn::StyleOptionType &out)
{
    out = qvariant_cast<QStyleHintReturn::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturn_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturn::Type) && (arg <= QStyleHintReturn::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturn::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturn_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturn::StyleOptionType value = qscriptvalue_cast<QStyleHintReturn::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturn_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturn::StyleOptionType value = qscriptvalue_cast<QStyleHintReturn::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturn_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturn_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturn_StyleOptionType,
        qtscript_QStyleHintReturn_StyleOptionType_valueOf, qtscript_QStyleHintReturn_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleHintReturn::StyleOptionType>(engine, qtscript_QStyleHintReturn_StyleOptionType_toScriptValue,
        qtscript_QStyleHintReturn_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturn_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturn_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturn::StyleOptionVersion
//

static const QStyleHintReturn::StyleOptionVersion qtscript_QStyleHintReturn_StyleOptionVersion_values[] = {
    QStyleHintReturn::Version
};

static const char * const qtscript_QStyleHintReturn_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleHintReturn_StyleOptionVersion_toStringHelper(QStyleHintReturn::StyleOptionVersion value)
{
    if ((value >= QStyleHintReturn::Version) && (value <= QStyleHintReturn::Version))
        return qtscript_QStyleHintReturn_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleHintReturn::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleHintReturn_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleHintReturn::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleHintReturn"));
    return clazz.property(qtscript_QStyleHintReturn_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleHintReturn_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleHintReturn::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleHintReturn::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleHintReturn_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleHintReturn::Version) && (arg <= QStyleHintReturn::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleHintReturn::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleHintReturn_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturn::StyleOptionVersion value = qscriptvalue_cast<QStyleHintReturn::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleHintReturn_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleHintReturn::StyleOptionVersion value = qscriptvalue_cast<QStyleHintReturn::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleHintReturn_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleHintReturn_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleHintReturn_StyleOptionVersion,
        qtscript_QStyleHintReturn_StyleOptionVersion_valueOf, qtscript_QStyleHintReturn_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleHintReturn::StyleOptionVersion>(engine, qtscript_QStyleHintReturn_StyleOptionVersion_toScriptValue,
        qtscript_QStyleHintReturn_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleHintReturn_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleHintReturn_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleHintReturn
//

static QScriptValue qtscript_QStyleHintReturn_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleHintReturn* _q_self = qscriptvalue_cast<QStyleHintReturn*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleHintReturn.%0(): this object is not a QStyleHintReturn")
            .arg(qtscript_QStyleHintReturn_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleHintReturn");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleHintReturn_throw_ambiguity_error_helper(context,
        qtscript_QStyleHintReturn_function_names[_id+1],
        qtscript_QStyleHintReturn_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleHintReturn_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleHintReturn(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleHintReturn* _q_cpp_result = new QtScriptShell_QStyleHintReturn();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleHintReturn*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QtScriptShell_QStyleHintReturn* _q_cpp_result = new QtScriptShell_QStyleHintReturn(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleHintReturn*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QStyleHintReturn* _q_cpp_result = new QtScriptShell_QStyleHintReturn(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleHintReturn*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleHintReturn_throw_ambiguity_error_helper(context,
        qtscript_QStyleHintReturn_function_names[_id],
        qtscript_QStyleHintReturn_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleHintReturn_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleHintReturn*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleHintReturn*)0));

    engine->setDefaultPrototype(qMetaTypeId<QStyleHintReturn*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleHintReturn_static_call, proto, qtscript_QStyleHintReturn_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("HintReturnType"),
        qtscript_create_QStyleHintReturn_HintReturnType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleHintReturn_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleHintReturn_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
