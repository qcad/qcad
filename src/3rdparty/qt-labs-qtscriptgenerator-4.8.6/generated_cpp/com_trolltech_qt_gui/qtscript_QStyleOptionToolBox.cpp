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

#include "qtscriptshell_QStyleOptionToolBox.h"

static const char * const qtscript_QStyleOptionToolBox_function_names[] = {
    "QStyleOptionToolBox"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionToolBox_function_signatures[] = {
    "\nQStyleOptionToolBox other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionToolBox_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionToolBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionToolBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionToolBox)
Q_DECLARE_METATYPE(QStyleOptionToolBox*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolBox)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolBox*)
Q_DECLARE_METATYPE(QStyleOptionToolBox::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionToolBox::StyleOptionType)
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
// QStyleOptionToolBox::StyleOptionVersion
//

static const QStyleOptionToolBox::StyleOptionVersion qtscript_QStyleOptionToolBox_StyleOptionVersion_values[] = {
    QStyleOptionToolBox::Version
};

static const char * const qtscript_QStyleOptionToolBox_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionToolBox_StyleOptionVersion_toStringHelper(QStyleOptionToolBox::StyleOptionVersion value)
{
    if ((value >= QStyleOptionToolBox::Version) && (value <= QStyleOptionToolBox::Version))
        return qtscript_QStyleOptionToolBox_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBox::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBox_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBox::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBox"));
    return clazz.property(qtscript_QStyleOptionToolBox_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBox_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionToolBox::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionToolBox::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBox_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBox::Version) && (arg <= QStyleOptionToolBox::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBox::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBox_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBox::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolBox::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBox_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBox::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolBox::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBox_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBox_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBox_StyleOptionVersion,
        qtscript_QStyleOptionToolBox_StyleOptionVersion_valueOf, qtscript_QStyleOptionToolBox_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionToolBox::StyleOptionVersion>(engine, qtscript_QStyleOptionToolBox_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionToolBox_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBox_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBox_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBox::StyleOptionType
//

static const QStyleOptionToolBox::StyleOptionType qtscript_QStyleOptionToolBox_StyleOptionType_values[] = {
    QStyleOptionToolBox::Type
};

static const char * const qtscript_QStyleOptionToolBox_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionToolBox_StyleOptionType_toStringHelper(QStyleOptionToolBox::StyleOptionType value)
{
    if ((value >= QStyleOptionToolBox::Type) && (value <= QStyleOptionToolBox::Type))
        return qtscript_QStyleOptionToolBox_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBox::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBox_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBox::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBox"));
    return clazz.property(qtscript_QStyleOptionToolBox_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBox_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionToolBox::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionToolBox::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBox_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBox::Type) && (arg <= QStyleOptionToolBox::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBox::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBox_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBox::StyleOptionType value = qscriptvalue_cast<QStyleOptionToolBox::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBox_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBox::StyleOptionType value = qscriptvalue_cast<QStyleOptionToolBox::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBox_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBox_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBox_StyleOptionType,
        qtscript_QStyleOptionToolBox_StyleOptionType_valueOf, qtscript_QStyleOptionToolBox_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionToolBox::StyleOptionType>(engine, qtscript_QStyleOptionToolBox_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionToolBox_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBox_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBox_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBox
//

static QScriptValue qtscript_QStyleOptionToolBox_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionToolBox* _q_self = qscriptvalue_cast<QStyleOptionToolBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionToolBox.%0(): this object is not a QStyleOptionToolBox")
            .arg(qtscript_QStyleOptionToolBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionToolBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolBox_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolBox_function_names[_id+1],
        qtscript_QStyleOptionToolBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionToolBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionToolBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionToolBox _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBox)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionToolBox _q_arg0 = qscriptvalue_cast<QStyleOptionToolBox>(context->argument(0));
        QtScriptShell_QStyleOptionToolBox _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBox)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolBox_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolBox_function_names[_id],
        qtscript_QStyleOptionToolBox_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionToolBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionToolBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBox>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBox*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionToolBox_static_call, proto, qtscript_QStyleOptionToolBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionToolBox_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionToolBox_StyleOptionType_class(engine, ctor));
    return ctor;
}
