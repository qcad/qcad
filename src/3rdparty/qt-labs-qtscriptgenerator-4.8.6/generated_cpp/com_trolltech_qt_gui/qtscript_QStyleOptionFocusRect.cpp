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

#include "qtscriptshell_QStyleOptionFocusRect.h"

static const char * const qtscript_QStyleOptionFocusRect_function_names[] = {
    "QStyleOptionFocusRect"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionFocusRect_function_signatures[] = {
    "\nQStyleOptionFocusRect other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionFocusRect_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionFocusRect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionFocusRect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionFocusRect)
Q_DECLARE_METATYPE(QStyleOptionFocusRect*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionFocusRect)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionFocusRect*)
Q_DECLARE_METATYPE(QStyleOptionFocusRect::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionFocusRect::StyleOptionType)
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
// QStyleOptionFocusRect::StyleOptionVersion
//

static const QStyleOptionFocusRect::StyleOptionVersion qtscript_QStyleOptionFocusRect_StyleOptionVersion_values[] = {
    QStyleOptionFocusRect::Version
};

static const char * const qtscript_QStyleOptionFocusRect_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionFocusRect_StyleOptionVersion_toStringHelper(QStyleOptionFocusRect::StyleOptionVersion value)
{
    if ((value >= QStyleOptionFocusRect::Version) && (value <= QStyleOptionFocusRect::Version))
        return qtscript_QStyleOptionFocusRect_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionFocusRect::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionFocusRect_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionFocusRect::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionFocusRect"));
    return clazz.property(qtscript_QStyleOptionFocusRect_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionFocusRect_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionFocusRect::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionFocusRect::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionFocusRect_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionFocusRect::Version) && (arg <= QStyleOptionFocusRect::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionFocusRect::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionFocusRect_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFocusRect::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionFocusRect::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFocusRect_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFocusRect::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionFocusRect::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionFocusRect_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionFocusRect_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionFocusRect_StyleOptionVersion,
        qtscript_QStyleOptionFocusRect_StyleOptionVersion_valueOf, qtscript_QStyleOptionFocusRect_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionFocusRect::StyleOptionVersion>(engine, qtscript_QStyleOptionFocusRect_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionFocusRect_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionFocusRect_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionFocusRect_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionFocusRect::StyleOptionType
//

static const QStyleOptionFocusRect::StyleOptionType qtscript_QStyleOptionFocusRect_StyleOptionType_values[] = {
    QStyleOptionFocusRect::Type
};

static const char * const qtscript_QStyleOptionFocusRect_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionFocusRect_StyleOptionType_toStringHelper(QStyleOptionFocusRect::StyleOptionType value)
{
    if ((value >= QStyleOptionFocusRect::Type) && (value <= QStyleOptionFocusRect::Type))
        return qtscript_QStyleOptionFocusRect_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionFocusRect::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionFocusRect_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionFocusRect::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionFocusRect"));
    return clazz.property(qtscript_QStyleOptionFocusRect_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionFocusRect_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionFocusRect::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionFocusRect::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionFocusRect_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionFocusRect::Type) && (arg <= QStyleOptionFocusRect::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionFocusRect::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionFocusRect_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFocusRect::StyleOptionType value = qscriptvalue_cast<QStyleOptionFocusRect::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFocusRect_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFocusRect::StyleOptionType value = qscriptvalue_cast<QStyleOptionFocusRect::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionFocusRect_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionFocusRect_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionFocusRect_StyleOptionType,
        qtscript_QStyleOptionFocusRect_StyleOptionType_valueOf, qtscript_QStyleOptionFocusRect_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionFocusRect::StyleOptionType>(engine, qtscript_QStyleOptionFocusRect_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionFocusRect_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionFocusRect_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionFocusRect_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionFocusRect
//

static QScriptValue qtscript_QStyleOptionFocusRect_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionFocusRect* _q_self = qscriptvalue_cast<QStyleOptionFocusRect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionFocusRect.%0(): this object is not a QStyleOptionFocusRect")
            .arg(qtscript_QStyleOptionFocusRect_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionFocusRect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionFocusRect_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionFocusRect_function_names[_id+1],
        qtscript_QStyleOptionFocusRect_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionFocusRect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionFocusRect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionFocusRect _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFocusRect)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionFocusRect _q_arg0 = qscriptvalue_cast<QStyleOptionFocusRect>(context->argument(0));
        QtScriptShell_QStyleOptionFocusRect _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFocusRect)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionFocusRect_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionFocusRect_function_names[_id],
        qtscript_QStyleOptionFocusRect_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionFocusRect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFocusRect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionFocusRect*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFocusRect>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFocusRect*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionFocusRect_static_call, proto, qtscript_QStyleOptionFocusRect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionFocusRect_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionFocusRect_StyleOptionType_class(engine, ctor));
    return ctor;
}
