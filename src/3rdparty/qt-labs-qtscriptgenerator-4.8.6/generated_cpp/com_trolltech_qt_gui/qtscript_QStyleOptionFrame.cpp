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

#include "qtscriptshell_QStyleOptionFrame.h"

static const char * const qtscript_QStyleOptionFrame_function_names[] = {
    "QStyleOptionFrame"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionFrame_function_signatures[] = {
    "\nQStyleOptionFrame other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionFrame_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionFrame_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionFrame::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionFrame)
Q_DECLARE_METATYPE(QStyleOptionFrame*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionFrame)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionFrame*)
Q_DECLARE_METATYPE(QStyleOptionFrame::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionFrame::StyleOptionType)
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
// QStyleOptionFrame::StyleOptionVersion
//

static const QStyleOptionFrame::StyleOptionVersion qtscript_QStyleOptionFrame_StyleOptionVersion_values[] = {
    QStyleOptionFrame::Version
};

static const char * const qtscript_QStyleOptionFrame_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionFrame_StyleOptionVersion_toStringHelper(QStyleOptionFrame::StyleOptionVersion value)
{
    if ((value >= QStyleOptionFrame::Version) && (value <= QStyleOptionFrame::Version))
        return qtscript_QStyleOptionFrame_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionFrame::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionFrame_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionFrame::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionFrame"));
    return clazz.property(qtscript_QStyleOptionFrame_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionFrame_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionFrame::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionFrame::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionFrame_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionFrame::Version) && (arg <= QStyleOptionFrame::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionFrame::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionFrame_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrame::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionFrame::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFrame_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrame::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionFrame::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionFrame_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionFrame_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionFrame_StyleOptionVersion,
        qtscript_QStyleOptionFrame_StyleOptionVersion_valueOf, qtscript_QStyleOptionFrame_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionFrame::StyleOptionVersion>(engine, qtscript_QStyleOptionFrame_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionFrame_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionFrame_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionFrame_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionFrame::StyleOptionType
//

static const QStyleOptionFrame::StyleOptionType qtscript_QStyleOptionFrame_StyleOptionType_values[] = {
    QStyleOptionFrame::Type
};

static const char * const qtscript_QStyleOptionFrame_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionFrame_StyleOptionType_toStringHelper(QStyleOptionFrame::StyleOptionType value)
{
    if ((value >= QStyleOptionFrame::Type) && (value <= QStyleOptionFrame::Type))
        return qtscript_QStyleOptionFrame_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionFrame::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionFrame_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionFrame::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionFrame"));
    return clazz.property(qtscript_QStyleOptionFrame_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionFrame_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionFrame::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionFrame::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionFrame_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionFrame::Type) && (arg <= QStyleOptionFrame::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionFrame::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionFrame_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrame::StyleOptionType value = qscriptvalue_cast<QStyleOptionFrame::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFrame_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrame::StyleOptionType value = qscriptvalue_cast<QStyleOptionFrame::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionFrame_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionFrame_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionFrame_StyleOptionType,
        qtscript_QStyleOptionFrame_StyleOptionType_valueOf, qtscript_QStyleOptionFrame_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionFrame::StyleOptionType>(engine, qtscript_QStyleOptionFrame_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionFrame_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionFrame_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionFrame_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionFrame
//

static QScriptValue qtscript_QStyleOptionFrame_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionFrame* _q_self = qscriptvalue_cast<QStyleOptionFrame*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionFrame.%0(): this object is not a QStyleOptionFrame")
            .arg(qtscript_QStyleOptionFrame_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionFrame");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionFrame_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionFrame_function_names[_id+1],
        qtscript_QStyleOptionFrame_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionFrame_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionFrame(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionFrame _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFrame)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionFrame _q_arg0 = qscriptvalue_cast<QStyleOptionFrame>(context->argument(0));
        QtScriptShell_QStyleOptionFrame _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFrame)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionFrame_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionFrame_function_names[_id],
        qtscript_QStyleOptionFrame_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionFrame_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFrame*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionFrame*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFrame>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFrame*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionFrame_static_call, proto, qtscript_QStyleOptionFrame_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionFrame_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionFrame_StyleOptionType_class(engine, ctor));
    return ctor;
}
