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

#include "qtscriptshell_QStyleOptionButton.h"

static const char * const qtscript_QStyleOptionButton_function_names[] = {
    "QStyleOptionButton"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionButton_function_signatures[] = {
    "\nQStyleOptionButton other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionButton_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionButton)
Q_DECLARE_METATYPE(QStyleOptionButton*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionButton)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionButton*)
Q_DECLARE_METATYPE(QStyleOptionButton::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionButton::ButtonFeature)
Q_DECLARE_METATYPE(QFlags<QStyleOptionButton::ButtonFeature>)
Q_DECLARE_METATYPE(QStyleOptionButton::StyleOptionVersion)
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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QStyleOptionButton::StyleOptionType
//

static const QStyleOptionButton::StyleOptionType qtscript_QStyleOptionButton_StyleOptionType_values[] = {
    QStyleOptionButton::Type
};

static const char * const qtscript_QStyleOptionButton_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionButton_StyleOptionType_toStringHelper(QStyleOptionButton::StyleOptionType value)
{
    if ((value >= QStyleOptionButton::Type) && (value <= QStyleOptionButton::Type))
        return qtscript_QStyleOptionButton_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionButton::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionButton_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionButton::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionButton"));
    return clazz.property(qtscript_QStyleOptionButton_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionButton_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionButton::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionButton::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionButton_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionButton::Type) && (arg <= QStyleOptionButton::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionButton::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionButton_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::StyleOptionType value = qscriptvalue_cast<QStyleOptionButton::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionButton_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::StyleOptionType value = qscriptvalue_cast<QStyleOptionButton::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionButton_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionButton_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionButton_StyleOptionType,
        qtscript_QStyleOptionButton_StyleOptionType_valueOf, qtscript_QStyleOptionButton_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionButton::StyleOptionType>(engine, qtscript_QStyleOptionButton_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionButton_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionButton_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionButton_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionButton::ButtonFeature
//

static const QStyleOptionButton::ButtonFeature qtscript_QStyleOptionButton_ButtonFeature_values[] = {
    QStyleOptionButton::None
    , QStyleOptionButton::Flat
    , QStyleOptionButton::HasMenu
    , QStyleOptionButton::DefaultButton
    , QStyleOptionButton::AutoDefaultButton
    , QStyleOptionButton::CommandLinkButton
};

static const char * const qtscript_QStyleOptionButton_ButtonFeature_keys[] = {
    "None"
    , "Flat"
    , "HasMenu"
    , "DefaultButton"
    , "AutoDefaultButton"
    , "CommandLinkButton"
};

static QString qtscript_QStyleOptionButton_ButtonFeature_toStringHelper(QStyleOptionButton::ButtonFeature value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QStyleOptionButton_ButtonFeature_values[i] == value)
            return QString::fromLatin1(qtscript_QStyleOptionButton_ButtonFeature_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyleOptionButton_ButtonFeature_toScriptValue(QScriptEngine *engine, const QStyleOptionButton::ButtonFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionButton"));
    return clazz.property(qtscript_QStyleOptionButton_ButtonFeature_toStringHelper(value));
}

static void qtscript_QStyleOptionButton_ButtonFeature_fromScriptValue(const QScriptValue &value, QStyleOptionButton::ButtonFeature &out)
{
    out = qvariant_cast<QStyleOptionButton::ButtonFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionButton_ButtonFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QStyleOptionButton_ButtonFeature_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyleOptionButton::ButtonFeature>(arg));
    }
    return context->throwError(QString::fromLatin1("ButtonFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionButton_ButtonFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::ButtonFeature value = qscriptvalue_cast<QStyleOptionButton::ButtonFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionButton_ButtonFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::ButtonFeature value = qscriptvalue_cast<QStyleOptionButton::ButtonFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionButton_ButtonFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionButton_ButtonFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionButton_ButtonFeature,
        qtscript_QStyleOptionButton_ButtonFeature_valueOf, qtscript_QStyleOptionButton_ButtonFeature_toString);
    qScriptRegisterMetaType<QStyleOptionButton::ButtonFeature>(engine, qtscript_QStyleOptionButton_ButtonFeature_toScriptValue,
        qtscript_QStyleOptionButton_ButtonFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionButton_ButtonFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionButton_ButtonFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionButton::ButtonFeatures
//

static QScriptValue qtscript_QStyleOptionButton_ButtonFeatures_toScriptValue(QScriptEngine *engine, const QStyleOptionButton::ButtonFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyleOptionButton_ButtonFeatures_fromScriptValue(const QScriptValue &value, QStyleOptionButton::ButtonFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyleOptionButton::ButtonFeatures>())
        out = qvariant_cast<QStyleOptionButton::ButtonFeatures>(var);
    else if (var.userType() == qMetaTypeId<QStyleOptionButton::ButtonFeature>())
        out = qvariant_cast<QStyleOptionButton::ButtonFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyleOptionButton_ButtonFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::ButtonFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyleOptionButton::ButtonFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyleOptionButton::ButtonFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ButtonFeatures(): argument %0 is not of type ButtonFeature").arg(i));
            }
            result |= qvariant_cast<QStyleOptionButton::ButtonFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyleOptionButton_ButtonFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::ButtonFeatures value = qscriptvalue_cast<QStyleOptionButton::ButtonFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionButton_ButtonFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::ButtonFeatures value = qscriptvalue_cast<QStyleOptionButton::ButtonFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_QStyleOptionButton_ButtonFeature_values[i]) == qtscript_QStyleOptionButton_ButtonFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyleOptionButton_ButtonFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyleOptionButton_ButtonFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyleOptionButton::ButtonFeatures>() == otherObj.value<QStyleOptionButton::ButtonFeatures>())));
}

static QScriptValue qtscript_create_QStyleOptionButton_ButtonFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyleOptionButton_ButtonFeatures, qtscript_QStyleOptionButton_ButtonFeatures_valueOf,
        qtscript_QStyleOptionButton_ButtonFeatures_toString, qtscript_QStyleOptionButton_ButtonFeatures_equals);
    qScriptRegisterMetaType<QStyleOptionButton::ButtonFeatures>(engine, qtscript_QStyleOptionButton_ButtonFeatures_toScriptValue,
        qtscript_QStyleOptionButton_ButtonFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyleOptionButton::StyleOptionVersion
//

static const QStyleOptionButton::StyleOptionVersion qtscript_QStyleOptionButton_StyleOptionVersion_values[] = {
    QStyleOptionButton::Version
};

static const char * const qtscript_QStyleOptionButton_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionButton_StyleOptionVersion_toStringHelper(QStyleOptionButton::StyleOptionVersion value)
{
    if ((value >= QStyleOptionButton::Version) && (value <= QStyleOptionButton::Version))
        return qtscript_QStyleOptionButton_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionButton::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionButton_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionButton::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionButton"));
    return clazz.property(qtscript_QStyleOptionButton_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionButton_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionButton::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionButton::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionButton_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionButton::Version) && (arg <= QStyleOptionButton::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionButton::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionButton_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionButton::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionButton_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionButton::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionButton::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionButton_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionButton_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionButton_StyleOptionVersion,
        qtscript_QStyleOptionButton_StyleOptionVersion_valueOf, qtscript_QStyleOptionButton_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionButton::StyleOptionVersion>(engine, qtscript_QStyleOptionButton_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionButton_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionButton_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionButton_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionButton
//

static QScriptValue qtscript_QStyleOptionButton_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionButton* _q_self = qscriptvalue_cast<QStyleOptionButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionButton.%0(): this object is not a QStyleOptionButton")
            .arg(qtscript_QStyleOptionButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionButton_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionButton_function_names[_id+1],
        qtscript_QStyleOptionButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionButton _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionButton)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionButton _q_arg0 = qscriptvalue_cast<QStyleOptionButton>(context->argument(0));
        QtScriptShell_QStyleOptionButton _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionButton)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionButton_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionButton_function_names[_id],
        qtscript_QStyleOptionButton_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionButton>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionButton*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionButton_static_call, proto, qtscript_QStyleOptionButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionButton_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ButtonFeature"),
        qtscript_create_QStyleOptionButton_ButtonFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ButtonFeatures"),
        qtscript_create_QStyleOptionButton_ButtonFeatures_class(engine));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionButton_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
