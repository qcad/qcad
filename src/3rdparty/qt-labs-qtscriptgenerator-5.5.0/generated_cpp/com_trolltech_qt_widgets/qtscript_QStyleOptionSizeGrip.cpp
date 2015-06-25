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

#include "qtscriptshell_QStyleOptionSizeGrip.h"

static const char * const qtscript_QStyleOptionSizeGrip_function_names[] = {
    "QStyleOptionSizeGrip"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionSizeGrip_function_signatures[] = {
    "\nQStyleOptionSizeGrip other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionSizeGrip_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionSizeGrip_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionSizeGrip::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionSizeGrip)
Q_DECLARE_METATYPE(QStyleOptionSizeGrip*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionSizeGrip)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionSizeGrip*)
Q_DECLARE_METATYPE(QStyleOptionSizeGrip::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionSizeGrip::StyleOptionVersion)
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
// QStyleOptionSizeGrip::StyleOptionType
//

static const QStyleOptionSizeGrip::StyleOptionType qtscript_QStyleOptionSizeGrip_StyleOptionType_values[] = {
    QStyleOptionSizeGrip::Type
};

static const char * const qtscript_QStyleOptionSizeGrip_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionSizeGrip_StyleOptionType_toStringHelper(QStyleOptionSizeGrip::StyleOptionType value)
{
    if ((value >= QStyleOptionSizeGrip::Type) && (value <= QStyleOptionSizeGrip::Type))
        return qtscript_QStyleOptionSizeGrip_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionSizeGrip::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionSizeGrip_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionSizeGrip::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionSizeGrip"));
    return clazz.property(qtscript_QStyleOptionSizeGrip_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionSizeGrip_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionSizeGrip::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionSizeGrip::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionSizeGrip_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionSizeGrip::Type) && (arg <= QStyleOptionSizeGrip::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionSizeGrip::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionSizeGrip_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSizeGrip::StyleOptionType value = qscriptvalue_cast<QStyleOptionSizeGrip::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionSizeGrip_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSizeGrip::StyleOptionType value = qscriptvalue_cast<QStyleOptionSizeGrip::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionSizeGrip_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionSizeGrip_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionSizeGrip_StyleOptionType,
        qtscript_QStyleOptionSizeGrip_StyleOptionType_valueOf, qtscript_QStyleOptionSizeGrip_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionSizeGrip::StyleOptionType>(engine, qtscript_QStyleOptionSizeGrip_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionSizeGrip_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionSizeGrip_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionSizeGrip_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionSizeGrip::StyleOptionVersion
//

static const QStyleOptionSizeGrip::StyleOptionVersion qtscript_QStyleOptionSizeGrip_StyleOptionVersion_values[] = {
    QStyleOptionSizeGrip::Version
};

static const char * const qtscript_QStyleOptionSizeGrip_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toStringHelper(QStyleOptionSizeGrip::StyleOptionVersion value)
{
    if ((value >= QStyleOptionSizeGrip::Version) && (value <= QStyleOptionSizeGrip::Version))
        return qtscript_QStyleOptionSizeGrip_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionSizeGrip::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionSizeGrip::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionSizeGrip"));
    return clazz.property(qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionSizeGrip_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionSizeGrip::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionSizeGrip::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionSizeGrip_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionSizeGrip::Version) && (arg <= QStyleOptionSizeGrip::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionSizeGrip::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionSizeGrip_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSizeGrip::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionSizeGrip::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSizeGrip::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionSizeGrip::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionSizeGrip_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionSizeGrip_StyleOptionVersion,
        qtscript_QStyleOptionSizeGrip_StyleOptionVersion_valueOf, qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionSizeGrip::StyleOptionVersion>(engine, qtscript_QStyleOptionSizeGrip_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionSizeGrip_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionSizeGrip_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionSizeGrip_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionSizeGrip
//

static QScriptValue qtscript_QStyleOptionSizeGrip_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionSizeGrip* _q_self = qscriptvalue_cast<QStyleOptionSizeGrip*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionSizeGrip.%0(): this object is not a QStyleOptionSizeGrip")
            .arg(qtscript_QStyleOptionSizeGrip_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionSizeGrip");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionSizeGrip_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionSizeGrip_function_names[_id+1],
        qtscript_QStyleOptionSizeGrip_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionSizeGrip_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionSizeGrip(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionSizeGrip _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionSizeGrip)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionSizeGrip _q_arg0 = qscriptvalue_cast<QStyleOptionSizeGrip>(context->argument(0));
        QtScriptShell_QStyleOptionSizeGrip _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionSizeGrip)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionSizeGrip_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionSizeGrip_function_names[_id],
        qtscript_QStyleOptionSizeGrip_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionSizeGrip_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSizeGrip*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionSizeGrip*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionComplex*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSizeGrip>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSizeGrip*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionSizeGrip_static_call, proto, qtscript_QStyleOptionSizeGrip_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionSizeGrip_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionSizeGrip_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
