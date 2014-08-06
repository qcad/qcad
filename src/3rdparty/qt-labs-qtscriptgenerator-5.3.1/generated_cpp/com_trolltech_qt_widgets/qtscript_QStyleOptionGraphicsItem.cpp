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
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QStyleOptionGraphicsItem.h"

static const char * const qtscript_QStyleOptionGraphicsItem_function_names[] = {
    "QStyleOptionGraphicsItem"
    // static
    , "levelOfDetailFromTransform"
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionGraphicsItem_function_signatures[] = {
    "\nQStyleOptionGraphicsItem other"
    // static
    , "QTransform worldTransform"
    // prototype
""
};

static const int qtscript_QStyleOptionGraphicsItem_function_lengths[] = {
    1
    // static
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionGraphicsItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionGraphicsItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionGraphicsItem)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionGraphicsItem)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionGraphicsItem*)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem::StyleOptionVersion)
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
// QStyleOptionGraphicsItem::StyleOptionType
//

static const QStyleOptionGraphicsItem::StyleOptionType qtscript_QStyleOptionGraphicsItem_StyleOptionType_values[] = {
    QStyleOptionGraphicsItem::Type
};

static const char * const qtscript_QStyleOptionGraphicsItem_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionGraphicsItem_StyleOptionType_toStringHelper(QStyleOptionGraphicsItem::StyleOptionType value)
{
    if ((value >= QStyleOptionGraphicsItem::Type) && (value <= QStyleOptionGraphicsItem::Type))
        return qtscript_QStyleOptionGraphicsItem_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionGraphicsItem::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionGraphicsItem::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionGraphicsItem"));
    return clazz.property(qtscript_QStyleOptionGraphicsItem_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionGraphicsItem_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionGraphicsItem::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionGraphicsItem::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionGraphicsItem_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionGraphicsItem::Type) && (arg <= QStyleOptionGraphicsItem::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionGraphicsItem::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionGraphicsItem::StyleOptionType value = qscriptvalue_cast<QStyleOptionGraphicsItem::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionGraphicsItem::StyleOptionType value = qscriptvalue_cast<QStyleOptionGraphicsItem::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionGraphicsItem_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionGraphicsItem_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionGraphicsItem_StyleOptionType,
        qtscript_QStyleOptionGraphicsItem_StyleOptionType_valueOf, qtscript_QStyleOptionGraphicsItem_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionGraphicsItem::StyleOptionType>(engine, qtscript_QStyleOptionGraphicsItem_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionGraphicsItem_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionGraphicsItem_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionGraphicsItem_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionGraphicsItem::StyleOptionVersion
//

static const QStyleOptionGraphicsItem::StyleOptionVersion qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_values[] = {
    QStyleOptionGraphicsItem::Version
};

static const char * const qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toStringHelper(QStyleOptionGraphicsItem::StyleOptionVersion value)
{
    if ((value >= QStyleOptionGraphicsItem::Version) && (value <= QStyleOptionGraphicsItem::Version))
        return qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionGraphicsItem::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionGraphicsItem::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionGraphicsItem"));
    return clazz.property(qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionGraphicsItem::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionGraphicsItem::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionGraphicsItem_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionGraphicsItem::Version) && (arg <= QStyleOptionGraphicsItem::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionGraphicsItem::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionGraphicsItem::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionGraphicsItem::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionGraphicsItem::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionGraphicsItem::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionGraphicsItem_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionGraphicsItem_StyleOptionVersion,
        qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_valueOf, qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionGraphicsItem::StyleOptionVersion>(engine, qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionGraphicsItem_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionGraphicsItem
//

static QScriptValue qtscript_QStyleOptionGraphicsItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionGraphicsItem* _q_self = qscriptvalue_cast<QStyleOptionGraphicsItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionGraphicsItem.%0(): this object is not a QStyleOptionGraphicsItem")
            .arg(qtscript_QStyleOptionGraphicsItem_function_names[_id+2]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionGraphicsItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionGraphicsItem_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionGraphicsItem_function_names[_id+2],
        qtscript_QStyleOptionGraphicsItem_function_signatures[_id+2]);
}

static QScriptValue qtscript_QStyleOptionGraphicsItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionGraphicsItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionGraphicsItem _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionGraphicsItem)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionGraphicsItem _q_arg0 = qscriptvalue_cast<QStyleOptionGraphicsItem>(context->argument(0));
        QtScriptShell_QStyleOptionGraphicsItem _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionGraphicsItem)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        qreal _q_result = QStyleOptionGraphicsItem::levelOfDetailFromTransform(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionGraphicsItem_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionGraphicsItem_function_names[_id],
        qtscript_QStyleOptionGraphicsItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionGraphicsItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionGraphicsItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionGraphicsItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionGraphicsItem>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionGraphicsItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionGraphicsItem_static_call, proto, qtscript_QStyleOptionGraphicsItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStyleOptionGraphicsItem_static_call,
            qtscript_QStyleOptionGraphicsItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QStyleOptionGraphicsItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionGraphicsItem_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionGraphicsItem_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
