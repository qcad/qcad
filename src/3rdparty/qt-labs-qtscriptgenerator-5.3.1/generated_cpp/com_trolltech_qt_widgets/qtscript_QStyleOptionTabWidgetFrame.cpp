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

#include "qtscriptshell_QStyleOptionTabWidgetFrame.h"

static const char * const qtscript_QStyleOptionTabWidgetFrame_function_names[] = {
    "QStyleOptionTabWidgetFrame"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionTabWidgetFrame_function_signatures[] = {
    "\nQStyleOptionTabWidgetFrame other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionTabWidgetFrame_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionTabWidgetFrame::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionTabWidgetFrame)
Q_DECLARE_METATYPE(QStyleOptionTabWidgetFrame*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTabWidgetFrame)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTabWidgetFrame*)
Q_DECLARE_METATYPE(QStyleOptionTabWidgetFrame::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionTabWidgetFrame::StyleOptionVersion)
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
// QStyleOptionTabWidgetFrame::StyleOptionType
//

static const QStyleOptionTabWidgetFrame::StyleOptionType qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_values[] = {
    QStyleOptionTabWidgetFrame::Type
};

static const char * const qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toStringHelper(QStyleOptionTabWidgetFrame::StyleOptionType value)
{
    if ((value >= QStyleOptionTabWidgetFrame::Type) && (value <= QStyleOptionTabWidgetFrame::Type))
        return qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTabWidgetFrame::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionTabWidgetFrame::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTabWidgetFrame"));
    return clazz.property(qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionTabWidgetFrame::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionTabWidgetFrame::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTabWidgetFrame_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTabWidgetFrame::Type) && (arg <= QStyleOptionTabWidgetFrame::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTabWidgetFrame::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabWidgetFrame::StyleOptionType value = qscriptvalue_cast<QStyleOptionTabWidgetFrame::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabWidgetFrame::StyleOptionType value = qscriptvalue_cast<QStyleOptionTabWidgetFrame::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTabWidgetFrame_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTabWidgetFrame_StyleOptionType,
        qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_valueOf, qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionTabWidgetFrame::StyleOptionType>(engine, qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTabWidgetFrame_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTabWidgetFrame::StyleOptionVersion
//

static const QStyleOptionTabWidgetFrame::StyleOptionVersion qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_values[] = {
    QStyleOptionTabWidgetFrame::Version
};

static const char * const qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toStringHelper(QStyleOptionTabWidgetFrame::StyleOptionVersion value)
{
    if ((value >= QStyleOptionTabWidgetFrame::Version) && (value <= QStyleOptionTabWidgetFrame::Version))
        return qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTabWidgetFrame::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionTabWidgetFrame::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTabWidgetFrame"));
    return clazz.property(qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionTabWidgetFrame::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionTabWidgetFrame::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTabWidgetFrame_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTabWidgetFrame::Version) && (arg <= QStyleOptionTabWidgetFrame::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTabWidgetFrame::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabWidgetFrame::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTabWidgetFrame::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabWidgetFrame::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTabWidgetFrame::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTabWidgetFrame_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTabWidgetFrame_StyleOptionVersion,
        qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_valueOf, qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionTabWidgetFrame::StyleOptionVersion>(engine, qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTabWidgetFrame_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTabWidgetFrame
//

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionTabWidgetFrame* _q_self = qscriptvalue_cast<QStyleOptionTabWidgetFrame*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionTabWidgetFrame.%0(): this object is not a QStyleOptionTabWidgetFrame")
            .arg(qtscript_QStyleOptionTabWidgetFrame_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionTabWidgetFrame");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTabWidgetFrame_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTabWidgetFrame_function_names[_id+1],
        qtscript_QStyleOptionTabWidgetFrame_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionTabWidgetFrame_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionTabWidgetFrame(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionTabWidgetFrame _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabWidgetFrame)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionTabWidgetFrame _q_arg0 = qscriptvalue_cast<QStyleOptionTabWidgetFrame>(context->argument(0));
        QtScriptShell_QStyleOptionTabWidgetFrame _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabWidgetFrame)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTabWidgetFrame_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTabWidgetFrame_function_names[_id],
        qtscript_QStyleOptionTabWidgetFrame_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionTabWidgetFrame_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabWidgetFrame*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionTabWidgetFrame*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabWidgetFrame>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabWidgetFrame*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionTabWidgetFrame_static_call, proto, qtscript_QStyleOptionTabWidgetFrame_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionTabWidgetFrame_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionTabWidgetFrame_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
