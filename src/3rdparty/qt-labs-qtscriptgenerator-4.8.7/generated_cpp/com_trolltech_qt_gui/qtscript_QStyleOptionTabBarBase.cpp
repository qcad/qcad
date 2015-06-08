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

#include "qtscriptshell_QStyleOptionTabBarBase.h"

static const char * const qtscript_QStyleOptionTabBarBase_function_names[] = {
    "QStyleOptionTabBarBase"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionTabBarBase_function_signatures[] = {
    "\nQStyleOptionTabBarBase other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionTabBarBase_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionTabBarBase_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionTabBarBase::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionTabBarBase)
Q_DECLARE_METATYPE(QStyleOptionTabBarBase*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTabBarBase)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTabBarBase*)
Q_DECLARE_METATYPE(QStyleOptionTabBarBase::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionTabBarBase::StyleOptionType)
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
// QStyleOptionTabBarBase::StyleOptionVersion
//

static const QStyleOptionTabBarBase::StyleOptionVersion qtscript_QStyleOptionTabBarBase_StyleOptionVersion_values[] = {
    QStyleOptionTabBarBase::Version
};

static const char * const qtscript_QStyleOptionTabBarBase_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toStringHelper(QStyleOptionTabBarBase::StyleOptionVersion value)
{
    if ((value >= QStyleOptionTabBarBase::Version) && (value <= QStyleOptionTabBarBase::Version))
        return qtscript_QStyleOptionTabBarBase_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTabBarBase::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionTabBarBase::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTabBarBase"));
    return clazz.property(qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionTabBarBase_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionTabBarBase::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionTabBarBase::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTabBarBase_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTabBarBase::Version) && (arg <= QStyleOptionTabBarBase::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTabBarBase::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTabBarBase_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabBarBase::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTabBarBase::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabBarBase::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTabBarBase::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTabBarBase_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTabBarBase_StyleOptionVersion,
        qtscript_QStyleOptionTabBarBase_StyleOptionVersion_valueOf, qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionTabBarBase::StyleOptionVersion>(engine, qtscript_QStyleOptionTabBarBase_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionTabBarBase_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTabBarBase_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTabBarBase_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTabBarBase::StyleOptionType
//

static const QStyleOptionTabBarBase::StyleOptionType qtscript_QStyleOptionTabBarBase_StyleOptionType_values[] = {
    QStyleOptionTabBarBase::Type
};

static const char * const qtscript_QStyleOptionTabBarBase_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionTabBarBase_StyleOptionType_toStringHelper(QStyleOptionTabBarBase::StyleOptionType value)
{
    if ((value >= QStyleOptionTabBarBase::Type) && (value <= QStyleOptionTabBarBase::Type))
        return qtscript_QStyleOptionTabBarBase_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTabBarBase::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTabBarBase_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionTabBarBase::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTabBarBase"));
    return clazz.property(qtscript_QStyleOptionTabBarBase_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionTabBarBase_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionTabBarBase::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionTabBarBase::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTabBarBase_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTabBarBase::Type) && (arg <= QStyleOptionTabBarBase::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTabBarBase::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTabBarBase_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabBarBase::StyleOptionType value = qscriptvalue_cast<QStyleOptionTabBarBase::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTabBarBase_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabBarBase::StyleOptionType value = qscriptvalue_cast<QStyleOptionTabBarBase::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTabBarBase_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTabBarBase_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTabBarBase_StyleOptionType,
        qtscript_QStyleOptionTabBarBase_StyleOptionType_valueOf, qtscript_QStyleOptionTabBarBase_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionTabBarBase::StyleOptionType>(engine, qtscript_QStyleOptionTabBarBase_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionTabBarBase_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTabBarBase_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTabBarBase_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTabBarBase
//

static QScriptValue qtscript_QStyleOptionTabBarBase_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionTabBarBase* _q_self = qscriptvalue_cast<QStyleOptionTabBarBase*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionTabBarBase.%0(): this object is not a QStyleOptionTabBarBase")
            .arg(qtscript_QStyleOptionTabBarBase_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionTabBarBase");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTabBarBase_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTabBarBase_function_names[_id+1],
        qtscript_QStyleOptionTabBarBase_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionTabBarBase_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionTabBarBase(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionTabBarBase _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabBarBase)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionTabBarBase _q_arg0 = qscriptvalue_cast<QStyleOptionTabBarBase>(context->argument(0));
        QtScriptShell_QStyleOptionTabBarBase _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabBarBase)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTabBarBase_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTabBarBase_function_names[_id],
        qtscript_QStyleOptionTabBarBase_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionTabBarBase_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabBarBase*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionTabBarBase*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabBarBase>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabBarBase*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionTabBarBase_static_call, proto, qtscript_QStyleOptionTabBarBase_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionTabBarBase_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionTabBarBase_StyleOptionType_class(engine, ctor));
    return ctor;
}
