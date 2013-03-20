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

#include "qtscriptshell_QStyleOptionProgressBar.h"

static const char * const qtscript_QStyleOptionProgressBar_function_names[] = {
    "QStyleOptionProgressBar"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionProgressBar_function_signatures[] = {
    "\nQStyleOptionProgressBar other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionProgressBar_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionProgressBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionProgressBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionProgressBar)
Q_DECLARE_METATYPE(QStyleOptionProgressBar*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionProgressBar)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionProgressBar*)
Q_DECLARE_METATYPE(QStyleOptionProgressBar::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionProgressBar::StyleOptionType)
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
// QStyleOptionProgressBar::StyleOptionVersion
//

static const QStyleOptionProgressBar::StyleOptionVersion qtscript_QStyleOptionProgressBar_StyleOptionVersion_values[] = {
    QStyleOptionProgressBar::Version
};

static const char * const qtscript_QStyleOptionProgressBar_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionProgressBar_StyleOptionVersion_toStringHelper(QStyleOptionProgressBar::StyleOptionVersion value)
{
    if ((value >= QStyleOptionProgressBar::Version) && (value <= QStyleOptionProgressBar::Version))
        return qtscript_QStyleOptionProgressBar_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionProgressBar::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionProgressBar_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionProgressBar::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionProgressBar"));
    return clazz.property(qtscript_QStyleOptionProgressBar_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionProgressBar_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionProgressBar::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionProgressBar::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionProgressBar_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionProgressBar::Version) && (arg <= QStyleOptionProgressBar::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionProgressBar::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionProgressBar_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionProgressBar::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionProgressBar::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionProgressBar_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionProgressBar::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionProgressBar::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionProgressBar_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionProgressBar_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionProgressBar_StyleOptionVersion,
        qtscript_QStyleOptionProgressBar_StyleOptionVersion_valueOf, qtscript_QStyleOptionProgressBar_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionProgressBar::StyleOptionVersion>(engine, qtscript_QStyleOptionProgressBar_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionProgressBar_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionProgressBar_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionProgressBar_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionProgressBar::StyleOptionType
//

static const QStyleOptionProgressBar::StyleOptionType qtscript_QStyleOptionProgressBar_StyleOptionType_values[] = {
    QStyleOptionProgressBar::Type
};

static const char * const qtscript_QStyleOptionProgressBar_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionProgressBar_StyleOptionType_toStringHelper(QStyleOptionProgressBar::StyleOptionType value)
{
    if ((value >= QStyleOptionProgressBar::Type) && (value <= QStyleOptionProgressBar::Type))
        return qtscript_QStyleOptionProgressBar_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionProgressBar::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionProgressBar_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionProgressBar::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionProgressBar"));
    return clazz.property(qtscript_QStyleOptionProgressBar_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionProgressBar_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionProgressBar::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionProgressBar::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionProgressBar_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionProgressBar::Type) && (arg <= QStyleOptionProgressBar::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionProgressBar::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionProgressBar_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionProgressBar::StyleOptionType value = qscriptvalue_cast<QStyleOptionProgressBar::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionProgressBar_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionProgressBar::StyleOptionType value = qscriptvalue_cast<QStyleOptionProgressBar::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionProgressBar_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionProgressBar_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionProgressBar_StyleOptionType,
        qtscript_QStyleOptionProgressBar_StyleOptionType_valueOf, qtscript_QStyleOptionProgressBar_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionProgressBar::StyleOptionType>(engine, qtscript_QStyleOptionProgressBar_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionProgressBar_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionProgressBar_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionProgressBar_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionProgressBar
//

static QScriptValue qtscript_QStyleOptionProgressBar_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionProgressBar* _q_self = qscriptvalue_cast<QStyleOptionProgressBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionProgressBar.%0(): this object is not a QStyleOptionProgressBar")
            .arg(qtscript_QStyleOptionProgressBar_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionProgressBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionProgressBar_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionProgressBar_function_names[_id+1],
        qtscript_QStyleOptionProgressBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionProgressBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionProgressBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionProgressBar _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionProgressBar)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionProgressBar _q_arg0 = qscriptvalue_cast<QStyleOptionProgressBar>(context->argument(0));
        QtScriptShell_QStyleOptionProgressBar _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionProgressBar)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionProgressBar_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionProgressBar_function_names[_id],
        qtscript_QStyleOptionProgressBar_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionProgressBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionProgressBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionProgressBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionProgressBar>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionProgressBar*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionProgressBar_static_call, proto, qtscript_QStyleOptionProgressBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionProgressBar_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionProgressBar_StyleOptionType_class(engine, ctor));
    return ctor;
}
