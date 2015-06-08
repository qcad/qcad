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

#include "qtscriptshell_QStyleOptionMenuItem.h"

static const char * const qtscript_QStyleOptionMenuItem_function_names[] = {
    "QStyleOptionMenuItem"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionMenuItem_function_signatures[] = {
    "\nQStyleOptionMenuItem other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionMenuItem_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionMenuItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionMenuItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionMenuItem)
Q_DECLARE_METATYPE(QStyleOptionMenuItem*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionMenuItem)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionMenuItem*)
Q_DECLARE_METATYPE(QStyleOptionMenuItem::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionMenuItem::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionMenuItem::CheckType)
Q_DECLARE_METATYPE(QStyleOptionMenuItem::MenuItemType)
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
// QStyleOptionMenuItem::StyleOptionVersion
//

static const QStyleOptionMenuItem::StyleOptionVersion qtscript_QStyleOptionMenuItem_StyleOptionVersion_values[] = {
    QStyleOptionMenuItem::Version
};

static const char * const qtscript_QStyleOptionMenuItem_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionMenuItem_StyleOptionVersion_toStringHelper(QStyleOptionMenuItem::StyleOptionVersion value)
{
    if ((value >= QStyleOptionMenuItem::Version) && (value <= QStyleOptionMenuItem::Version))
        return qtscript_QStyleOptionMenuItem_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionMenuItem::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionMenuItem_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionMenuItem::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionMenuItem"));
    return clazz.property(qtscript_QStyleOptionMenuItem_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionMenuItem_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionMenuItem::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionMenuItem::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionMenuItem_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionMenuItem::Version) && (arg <= QStyleOptionMenuItem::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionMenuItem::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionMenuItem_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionMenuItem::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionMenuItem_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionMenuItem::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionMenuItem_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionMenuItem_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionMenuItem_StyleOptionVersion,
        qtscript_QStyleOptionMenuItem_StyleOptionVersion_valueOf, qtscript_QStyleOptionMenuItem_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionMenuItem::StyleOptionVersion>(engine, qtscript_QStyleOptionMenuItem_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionMenuItem_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionMenuItem_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionMenuItem_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionMenuItem::StyleOptionType
//

static const QStyleOptionMenuItem::StyleOptionType qtscript_QStyleOptionMenuItem_StyleOptionType_values[] = {
    QStyleOptionMenuItem::Type
};

static const char * const qtscript_QStyleOptionMenuItem_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionMenuItem_StyleOptionType_toStringHelper(QStyleOptionMenuItem::StyleOptionType value)
{
    if ((value >= QStyleOptionMenuItem::Type) && (value <= QStyleOptionMenuItem::Type))
        return qtscript_QStyleOptionMenuItem_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionMenuItem::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionMenuItem_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionMenuItem::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionMenuItem"));
    return clazz.property(qtscript_QStyleOptionMenuItem_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionMenuItem_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionMenuItem::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionMenuItem::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionMenuItem_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionMenuItem::Type) && (arg <= QStyleOptionMenuItem::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionMenuItem::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionMenuItem_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::StyleOptionType value = qscriptvalue_cast<QStyleOptionMenuItem::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionMenuItem_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::StyleOptionType value = qscriptvalue_cast<QStyleOptionMenuItem::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionMenuItem_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionMenuItem_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionMenuItem_StyleOptionType,
        qtscript_QStyleOptionMenuItem_StyleOptionType_valueOf, qtscript_QStyleOptionMenuItem_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionMenuItem::StyleOptionType>(engine, qtscript_QStyleOptionMenuItem_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionMenuItem_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionMenuItem_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionMenuItem_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionMenuItem::CheckType
//

static const QStyleOptionMenuItem::CheckType qtscript_QStyleOptionMenuItem_CheckType_values[] = {
    QStyleOptionMenuItem::NotCheckable
    , QStyleOptionMenuItem::Exclusive
    , QStyleOptionMenuItem::NonExclusive
};

static const char * const qtscript_QStyleOptionMenuItem_CheckType_keys[] = {
    "NotCheckable"
    , "Exclusive"
    , "NonExclusive"
};

static QString qtscript_QStyleOptionMenuItem_CheckType_toStringHelper(QStyleOptionMenuItem::CheckType value)
{
    if ((value >= QStyleOptionMenuItem::NotCheckable) && (value <= QStyleOptionMenuItem::NonExclusive))
        return qtscript_QStyleOptionMenuItem_CheckType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionMenuItem::NotCheckable)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionMenuItem_CheckType_toScriptValue(QScriptEngine *engine, const QStyleOptionMenuItem::CheckType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionMenuItem"));
    return clazz.property(qtscript_QStyleOptionMenuItem_CheckType_toStringHelper(value));
}

static void qtscript_QStyleOptionMenuItem_CheckType_fromScriptValue(const QScriptValue &value, QStyleOptionMenuItem::CheckType &out)
{
    out = qvariant_cast<QStyleOptionMenuItem::CheckType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionMenuItem_CheckType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionMenuItem::NotCheckable) && (arg <= QStyleOptionMenuItem::NonExclusive))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionMenuItem::CheckType>(arg));
    return context->throwError(QString::fromLatin1("CheckType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionMenuItem_CheckType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::CheckType value = qscriptvalue_cast<QStyleOptionMenuItem::CheckType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionMenuItem_CheckType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::CheckType value = qscriptvalue_cast<QStyleOptionMenuItem::CheckType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionMenuItem_CheckType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionMenuItem_CheckType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionMenuItem_CheckType,
        qtscript_QStyleOptionMenuItem_CheckType_valueOf, qtscript_QStyleOptionMenuItem_CheckType_toString);
    qScriptRegisterMetaType<QStyleOptionMenuItem::CheckType>(engine, qtscript_QStyleOptionMenuItem_CheckType_toScriptValue,
        qtscript_QStyleOptionMenuItem_CheckType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionMenuItem_CheckType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionMenuItem_CheckType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionMenuItem::MenuItemType
//

static const QStyleOptionMenuItem::MenuItemType qtscript_QStyleOptionMenuItem_MenuItemType_values[] = {
    QStyleOptionMenuItem::Normal
    , QStyleOptionMenuItem::DefaultItem
    , QStyleOptionMenuItem::Separator
    , QStyleOptionMenuItem::SubMenu
    , QStyleOptionMenuItem::Scroller
    , QStyleOptionMenuItem::TearOff
    , QStyleOptionMenuItem::Margin
    , QStyleOptionMenuItem::EmptyArea
};

static const char * const qtscript_QStyleOptionMenuItem_MenuItemType_keys[] = {
    "Normal"
    , "DefaultItem"
    , "Separator"
    , "SubMenu"
    , "Scroller"
    , "TearOff"
    , "Margin"
    , "EmptyArea"
};

static QString qtscript_QStyleOptionMenuItem_MenuItemType_toStringHelper(QStyleOptionMenuItem::MenuItemType value)
{
    if ((value >= QStyleOptionMenuItem::Normal) && (value <= QStyleOptionMenuItem::EmptyArea))
        return qtscript_QStyleOptionMenuItem_MenuItemType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionMenuItem::Normal)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionMenuItem_MenuItemType_toScriptValue(QScriptEngine *engine, const QStyleOptionMenuItem::MenuItemType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionMenuItem"));
    return clazz.property(qtscript_QStyleOptionMenuItem_MenuItemType_toStringHelper(value));
}

static void qtscript_QStyleOptionMenuItem_MenuItemType_fromScriptValue(const QScriptValue &value, QStyleOptionMenuItem::MenuItemType &out)
{
    out = qvariant_cast<QStyleOptionMenuItem::MenuItemType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionMenuItem_MenuItemType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionMenuItem::Normal) && (arg <= QStyleOptionMenuItem::EmptyArea))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionMenuItem::MenuItemType>(arg));
    return context->throwError(QString::fromLatin1("MenuItemType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionMenuItem_MenuItemType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::MenuItemType value = qscriptvalue_cast<QStyleOptionMenuItem::MenuItemType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionMenuItem_MenuItemType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionMenuItem::MenuItemType value = qscriptvalue_cast<QStyleOptionMenuItem::MenuItemType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionMenuItem_MenuItemType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionMenuItem_MenuItemType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionMenuItem_MenuItemType,
        qtscript_QStyleOptionMenuItem_MenuItemType_valueOf, qtscript_QStyleOptionMenuItem_MenuItemType_toString);
    qScriptRegisterMetaType<QStyleOptionMenuItem::MenuItemType>(engine, qtscript_QStyleOptionMenuItem_MenuItemType_toScriptValue,
        qtscript_QStyleOptionMenuItem_MenuItemType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionMenuItem_MenuItemType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionMenuItem_MenuItemType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionMenuItem
//

static QScriptValue qtscript_QStyleOptionMenuItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionMenuItem* _q_self = qscriptvalue_cast<QStyleOptionMenuItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionMenuItem.%0(): this object is not a QStyleOptionMenuItem")
            .arg(qtscript_QStyleOptionMenuItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionMenuItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionMenuItem_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionMenuItem_function_names[_id+1],
        qtscript_QStyleOptionMenuItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionMenuItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionMenuItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionMenuItem _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionMenuItem)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionMenuItem _q_arg0 = qscriptvalue_cast<QStyleOptionMenuItem>(context->argument(0));
        QtScriptShell_QStyleOptionMenuItem _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionMenuItem)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionMenuItem_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionMenuItem_function_names[_id],
        qtscript_QStyleOptionMenuItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionMenuItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionMenuItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionMenuItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionMenuItem>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionMenuItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionMenuItem_static_call, proto, qtscript_QStyleOptionMenuItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionMenuItem_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionMenuItem_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CheckType"),
        qtscript_create_QStyleOptionMenuItem_CheckType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MenuItemType"),
        qtscript_create_QStyleOptionMenuItem_MenuItemType_class(engine, ctor));
    return ctor;
}
