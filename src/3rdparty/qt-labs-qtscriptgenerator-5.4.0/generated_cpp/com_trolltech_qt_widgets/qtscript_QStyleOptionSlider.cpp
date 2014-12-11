#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstyleoption.h>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyleOptionSlider.h"

static const char * const qtscript_QStyleOptionSlider_function_names[] = {
    "QStyleOptionSlider"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionSlider_function_signatures[] = {
    "\nQStyleOptionSlider other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionSlider_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionSlider_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionSlider::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionSlider)
Q_DECLARE_METATYPE(QStyleOptionSlider*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionSlider)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionSlider*)
Q_DECLARE_METATYPE(QStyleOptionSlider::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionSlider::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionComplex*)

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
// QStyleOptionSlider::StyleOptionType
//

static const QStyleOptionSlider::StyleOptionType qtscript_QStyleOptionSlider_StyleOptionType_values[] = {
    QStyleOptionSlider::Type
};

static const char * const qtscript_QStyleOptionSlider_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionSlider_StyleOptionType_toStringHelper(QStyleOptionSlider::StyleOptionType value)
{
    if ((value >= QStyleOptionSlider::Type) && (value <= QStyleOptionSlider::Type))
        return qtscript_QStyleOptionSlider_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionSlider::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionSlider_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionSlider::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionSlider"));
    return clazz.property(qtscript_QStyleOptionSlider_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionSlider_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionSlider::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionSlider::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionSlider_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionSlider::Type) && (arg <= QStyleOptionSlider::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionSlider::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionSlider_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSlider::StyleOptionType value = qscriptvalue_cast<QStyleOptionSlider::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionSlider_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSlider::StyleOptionType value = qscriptvalue_cast<QStyleOptionSlider::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionSlider_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionSlider_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionSlider_StyleOptionType,
        qtscript_QStyleOptionSlider_StyleOptionType_valueOf, qtscript_QStyleOptionSlider_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionSlider::StyleOptionType>(engine, qtscript_QStyleOptionSlider_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionSlider_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionSlider_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionSlider_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionSlider::StyleOptionVersion
//

static const QStyleOptionSlider::StyleOptionVersion qtscript_QStyleOptionSlider_StyleOptionVersion_values[] = {
    QStyleOptionSlider::Version
};

static const char * const qtscript_QStyleOptionSlider_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionSlider_StyleOptionVersion_toStringHelper(QStyleOptionSlider::StyleOptionVersion value)
{
    if ((value >= QStyleOptionSlider::Version) && (value <= QStyleOptionSlider::Version))
        return qtscript_QStyleOptionSlider_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionSlider::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionSlider_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionSlider::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionSlider"));
    return clazz.property(qtscript_QStyleOptionSlider_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionSlider_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionSlider::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionSlider::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionSlider_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionSlider::Version) && (arg <= QStyleOptionSlider::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionSlider::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionSlider_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSlider::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionSlider::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionSlider_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSlider::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionSlider::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionSlider_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionSlider_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionSlider_StyleOptionVersion,
        qtscript_QStyleOptionSlider_StyleOptionVersion_valueOf, qtscript_QStyleOptionSlider_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionSlider::StyleOptionVersion>(engine, qtscript_QStyleOptionSlider_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionSlider_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionSlider_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionSlider_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionSlider
//

static QScriptValue qtscript_QStyleOptionSlider_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionSlider* _q_self = qscriptvalue_cast<QStyleOptionSlider*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionSlider.%0(): this object is not a QStyleOptionSlider")
            .arg(qtscript_QStyleOptionSlider_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionSlider");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionSlider_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionSlider_function_names[_id+1],
        qtscript_QStyleOptionSlider_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionSlider_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionSlider(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionSlider _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionSlider)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionSlider _q_arg0 = qscriptvalue_cast<QStyleOptionSlider>(context->argument(0));
        QtScriptShell_QStyleOptionSlider _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionSlider)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionSlider_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionSlider_function_names[_id],
        qtscript_QStyleOptionSlider_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionSlider_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSlider*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionSlider*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionComplex*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSlider>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSlider*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionSlider_static_call, proto, qtscript_QStyleOptionSlider_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionSlider_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionSlider_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
