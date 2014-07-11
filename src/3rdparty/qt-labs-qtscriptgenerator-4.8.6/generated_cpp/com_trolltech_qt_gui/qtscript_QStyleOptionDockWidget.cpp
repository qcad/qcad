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

#include "qtscriptshell_QStyleOptionDockWidget.h"

static const char * const qtscript_QStyleOptionDockWidget_function_names[] = {
    "QStyleOptionDockWidget"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionDockWidget_function_signatures[] = {
    "\nQStyleOptionDockWidget other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionDockWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionDockWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionDockWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionDockWidget)
Q_DECLARE_METATYPE(QStyleOptionDockWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionDockWidget)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionDockWidget*)
Q_DECLARE_METATYPE(QStyleOptionDockWidget::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionDockWidget::StyleOptionType)
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
// QStyleOptionDockWidget::StyleOptionVersion
//

static const QStyleOptionDockWidget::StyleOptionVersion qtscript_QStyleOptionDockWidget_StyleOptionVersion_values[] = {
    QStyleOptionDockWidget::Version
};

static const char * const qtscript_QStyleOptionDockWidget_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionDockWidget_StyleOptionVersion_toStringHelper(QStyleOptionDockWidget::StyleOptionVersion value)
{
    if ((value >= QStyleOptionDockWidget::Version) && (value <= QStyleOptionDockWidget::Version))
        return qtscript_QStyleOptionDockWidget_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionDockWidget::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionDockWidget_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionDockWidget::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionDockWidget"));
    return clazz.property(qtscript_QStyleOptionDockWidget_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionDockWidget_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionDockWidget::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionDockWidget::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionDockWidget_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionDockWidget::Version) && (arg <= QStyleOptionDockWidget::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionDockWidget::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionDockWidget_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionDockWidget::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionDockWidget::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionDockWidget_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionDockWidget::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionDockWidget::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionDockWidget_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionDockWidget_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionDockWidget_StyleOptionVersion,
        qtscript_QStyleOptionDockWidget_StyleOptionVersion_valueOf, qtscript_QStyleOptionDockWidget_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionDockWidget::StyleOptionVersion>(engine, qtscript_QStyleOptionDockWidget_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionDockWidget_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionDockWidget_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionDockWidget_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionDockWidget::StyleOptionType
//

static const QStyleOptionDockWidget::StyleOptionType qtscript_QStyleOptionDockWidget_StyleOptionType_values[] = {
    QStyleOptionDockWidget::Type
};

static const char * const qtscript_QStyleOptionDockWidget_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionDockWidget_StyleOptionType_toStringHelper(QStyleOptionDockWidget::StyleOptionType value)
{
    if ((value >= QStyleOptionDockWidget::Type) && (value <= QStyleOptionDockWidget::Type))
        return qtscript_QStyleOptionDockWidget_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionDockWidget::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionDockWidget_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionDockWidget::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionDockWidget"));
    return clazz.property(qtscript_QStyleOptionDockWidget_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionDockWidget_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionDockWidget::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionDockWidget::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionDockWidget_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionDockWidget::Type) && (arg <= QStyleOptionDockWidget::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionDockWidget::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionDockWidget_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionDockWidget::StyleOptionType value = qscriptvalue_cast<QStyleOptionDockWidget::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionDockWidget_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionDockWidget::StyleOptionType value = qscriptvalue_cast<QStyleOptionDockWidget::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionDockWidget_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionDockWidget_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionDockWidget_StyleOptionType,
        qtscript_QStyleOptionDockWidget_StyleOptionType_valueOf, qtscript_QStyleOptionDockWidget_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionDockWidget::StyleOptionType>(engine, qtscript_QStyleOptionDockWidget_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionDockWidget_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionDockWidget_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionDockWidget_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionDockWidget
//

static QScriptValue qtscript_QStyleOptionDockWidget_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionDockWidget* _q_self = qscriptvalue_cast<QStyleOptionDockWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionDockWidget.%0(): this object is not a QStyleOptionDockWidget")
            .arg(qtscript_QStyleOptionDockWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionDockWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionDockWidget_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionDockWidget_function_names[_id+1],
        qtscript_QStyleOptionDockWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionDockWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionDockWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionDockWidget _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionDockWidget)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionDockWidget _q_arg0 = qscriptvalue_cast<QStyleOptionDockWidget>(context->argument(0));
        QtScriptShell_QStyleOptionDockWidget _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionDockWidget)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionDockWidget_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionDockWidget_function_names[_id],
        qtscript_QStyleOptionDockWidget_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionDockWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionDockWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionDockWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionDockWidget>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionDockWidget*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionDockWidget_static_call, proto, qtscript_QStyleOptionDockWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionDockWidget_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionDockWidget_StyleOptionType_class(engine, ctor));
    return ctor;
}
