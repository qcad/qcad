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

#include "qtscriptshell_QStyleOptionViewItem.h"

static const char * const qtscript_QStyleOptionViewItem_function_names[] = {
    "QStyleOptionViewItem"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionViewItem_function_signatures[] = {
    "\nQStyleOptionViewItem other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionViewItem_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionViewItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionViewItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QStyleOptionViewItem*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionViewItem)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionViewItem*)
Q_DECLARE_METATYPE(QStyleOptionViewItem::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionViewItem::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionViewItem::Position)
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
// QStyleOptionViewItem::StyleOptionVersion
//

static const QStyleOptionViewItem::StyleOptionVersion qtscript_QStyleOptionViewItem_StyleOptionVersion_values[] = {
    QStyleOptionViewItem::Version
};

static const char * const qtscript_QStyleOptionViewItem_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionViewItem_StyleOptionVersion_toStringHelper(QStyleOptionViewItem::StyleOptionVersion value)
{
    if ((value >= QStyleOptionViewItem::Version) && (value <= QStyleOptionViewItem::Version))
        return qtscript_QStyleOptionViewItem_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionViewItem::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItem_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItem::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItem"));
    return clazz.property(qtscript_QStyleOptionViewItem_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItem_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionViewItem::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionViewItem::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItem_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionViewItem::Version) && (arg <= QStyleOptionViewItem::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItem::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItem_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItem::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionViewItem::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItem_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItem::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionViewItem::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItem_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItem_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItem_StyleOptionVersion,
        qtscript_QStyleOptionViewItem_StyleOptionVersion_valueOf, qtscript_QStyleOptionViewItem_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionViewItem::StyleOptionVersion>(engine, qtscript_QStyleOptionViewItem_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionViewItem_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItem_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItem_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItem::StyleOptionType
//

static const QStyleOptionViewItem::StyleOptionType qtscript_QStyleOptionViewItem_StyleOptionType_values[] = {
    QStyleOptionViewItem::Type
};

static const char * const qtscript_QStyleOptionViewItem_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionViewItem_StyleOptionType_toStringHelper(QStyleOptionViewItem::StyleOptionType value)
{
    if ((value >= QStyleOptionViewItem::Type) && (value <= QStyleOptionViewItem::Type))
        return qtscript_QStyleOptionViewItem_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionViewItem::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItem_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItem::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItem"));
    return clazz.property(qtscript_QStyleOptionViewItem_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItem_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionViewItem::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionViewItem::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItem_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionViewItem::Type) && (arg <= QStyleOptionViewItem::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItem::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItem_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItem::StyleOptionType value = qscriptvalue_cast<QStyleOptionViewItem::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItem_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItem::StyleOptionType value = qscriptvalue_cast<QStyleOptionViewItem::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItem_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItem_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItem_StyleOptionType,
        qtscript_QStyleOptionViewItem_StyleOptionType_valueOf, qtscript_QStyleOptionViewItem_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionViewItem::StyleOptionType>(engine, qtscript_QStyleOptionViewItem_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionViewItem_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItem_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItem_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItem::Position
//

static const QStyleOptionViewItem::Position qtscript_QStyleOptionViewItem_Position_values[] = {
    QStyleOptionViewItem::Left
    , QStyleOptionViewItem::Right
    , QStyleOptionViewItem::Top
    , QStyleOptionViewItem::Bottom
};

static const char * const qtscript_QStyleOptionViewItem_Position_keys[] = {
    "Left"
    , "Right"
    , "Top"
    , "Bottom"
};

static QString qtscript_QStyleOptionViewItem_Position_toStringHelper(QStyleOptionViewItem::Position value)
{
    if ((value >= QStyleOptionViewItem::Left) && (value <= QStyleOptionViewItem::Bottom))
        return qtscript_QStyleOptionViewItem_Position_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionViewItem::Left)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItem_Position_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItem::Position &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItem"));
    return clazz.property(qtscript_QStyleOptionViewItem_Position_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItem_Position_fromScriptValue(const QScriptValue &value, QStyleOptionViewItem::Position &out)
{
    out = qvariant_cast<QStyleOptionViewItem::Position>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItem_Position(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionViewItem::Left) && (arg <= QStyleOptionViewItem::Bottom))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItem::Position>(arg));
    return context->throwError(QString::fromLatin1("Position(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItem_Position_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItem::Position value = qscriptvalue_cast<QStyleOptionViewItem::Position>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItem_Position_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItem::Position value = qscriptvalue_cast<QStyleOptionViewItem::Position>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItem_Position_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItem_Position_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItem_Position,
        qtscript_QStyleOptionViewItem_Position_valueOf, qtscript_QStyleOptionViewItem_Position_toString);
    qScriptRegisterMetaType<QStyleOptionViewItem::Position>(engine, qtscript_QStyleOptionViewItem_Position_toScriptValue,
        qtscript_QStyleOptionViewItem_Position_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItem_Position_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItem_Position_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItem
//

static QScriptValue qtscript_QStyleOptionViewItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionViewItem* _q_self = qscriptvalue_cast<QStyleOptionViewItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionViewItem.%0(): this object is not a QStyleOptionViewItem")
            .arg(qtscript_QStyleOptionViewItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionViewItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionViewItem_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionViewItem_function_names[_id+1],
        qtscript_QStyleOptionViewItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionViewItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionViewItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionViewItem _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItem)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
        QtScriptShell_QStyleOptionViewItem _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItem)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionViewItem_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionViewItem_function_names[_id],
        qtscript_QStyleOptionViewItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionViewItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionViewItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItem>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionViewItem_static_call, proto, qtscript_QStyleOptionViewItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionViewItem_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionViewItem_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Position"),
        qtscript_create_QStyleOptionViewItem_Position_class(engine, ctor));
    return ctor;
}
