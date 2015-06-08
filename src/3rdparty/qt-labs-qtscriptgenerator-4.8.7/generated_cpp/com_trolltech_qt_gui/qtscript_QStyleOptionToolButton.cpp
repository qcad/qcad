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

#include "qtscriptshell_QStyleOptionToolButton.h"

static const char * const qtscript_QStyleOptionToolButton_function_names[] = {
    "QStyleOptionToolButton"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionToolButton_function_signatures[] = {
    "\nQStyleOptionToolButton other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionToolButton_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionToolButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionToolButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionToolButton)
Q_DECLARE_METATYPE(QStyleOptionToolButton*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolButton)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolButton*)
Q_DECLARE_METATYPE(QStyleOptionToolButton::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionToolButton::ToolButtonFeature)
Q_DECLARE_METATYPE(QFlags<QStyleOptionToolButton::ToolButtonFeature>)
Q_DECLARE_METATYPE(QStyleOptionToolButton::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionComplex*)

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
// QStyleOptionToolButton::StyleOptionVersion
//

static const QStyleOptionToolButton::StyleOptionVersion qtscript_QStyleOptionToolButton_StyleOptionVersion_values[] = {
    QStyleOptionToolButton::Version
};

static const char * const qtscript_QStyleOptionToolButton_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionToolButton_StyleOptionVersion_toStringHelper(QStyleOptionToolButton::StyleOptionVersion value)
{
    if ((value >= QStyleOptionToolButton::Version) && (value <= QStyleOptionToolButton::Version))
        return qtscript_QStyleOptionToolButton_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolButton::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolButton_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionToolButton::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolButton"));
    return clazz.property(qtscript_QStyleOptionToolButton_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionToolButton_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionToolButton::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionToolButton::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolButton_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolButton::Version) && (arg <= QStyleOptionToolButton::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolButton::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolButton_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolButton::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolButton_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolButton::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolButton_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolButton_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolButton_StyleOptionVersion,
        qtscript_QStyleOptionToolButton_StyleOptionVersion_valueOf, qtscript_QStyleOptionToolButton_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionToolButton::StyleOptionVersion>(engine, qtscript_QStyleOptionToolButton_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionToolButton_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolButton_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolButton_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolButton::ToolButtonFeature
//

static const QStyleOptionToolButton::ToolButtonFeature qtscript_QStyleOptionToolButton_ToolButtonFeature_values[] = {
    QStyleOptionToolButton::None
    , QStyleOptionToolButton::Arrow
    , QStyleOptionToolButton::Menu
    , QStyleOptionToolButton::PopupDelay
    , QStyleOptionToolButton::HasMenu
};

static const char * const qtscript_QStyleOptionToolButton_ToolButtonFeature_keys[] = {
    "None"
    , "Arrow"
    , "Menu"
    , "PopupDelay"
    , "HasMenu"
};

static QString qtscript_QStyleOptionToolButton_ToolButtonFeature_toStringHelper(QStyleOptionToolButton::ToolButtonFeature value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QStyleOptionToolButton_ToolButtonFeature_values[i] == value)
            return QString::fromLatin1(qtscript_QStyleOptionToolButton_ToolButtonFeature_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeature_toScriptValue(QScriptEngine *engine, const QStyleOptionToolButton::ToolButtonFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolButton"));
    return clazz.property(qtscript_QStyleOptionToolButton_ToolButtonFeature_toStringHelper(value));
}

static void qtscript_QStyleOptionToolButton_ToolButtonFeature_fromScriptValue(const QScriptValue &value, QStyleOptionToolButton::ToolButtonFeature &out)
{
    out = qvariant_cast<QStyleOptionToolButton::ToolButtonFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolButton_ToolButtonFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QStyleOptionToolButton_ToolButtonFeature_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolButton::ToolButtonFeature>(arg));
    }
    return context->throwError(QString::fromLatin1("ToolButtonFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::ToolButtonFeature value = qscriptvalue_cast<QStyleOptionToolButton::ToolButtonFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::ToolButtonFeature value = qscriptvalue_cast<QStyleOptionToolButton::ToolButtonFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolButton_ToolButtonFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolButton_ToolButtonFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolButton_ToolButtonFeature,
        qtscript_QStyleOptionToolButton_ToolButtonFeature_valueOf, qtscript_QStyleOptionToolButton_ToolButtonFeature_toString);
    qScriptRegisterMetaType<QStyleOptionToolButton::ToolButtonFeature>(engine, qtscript_QStyleOptionToolButton_ToolButtonFeature_toScriptValue,
        qtscript_QStyleOptionToolButton_ToolButtonFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolButton_ToolButtonFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolButton_ToolButtonFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolButton::ToolButtonFeatures
//

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeatures_toScriptValue(QScriptEngine *engine, const QStyleOptionToolButton::ToolButtonFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyleOptionToolButton_ToolButtonFeatures_fromScriptValue(const QScriptValue &value, QStyleOptionToolButton::ToolButtonFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyleOptionToolButton::ToolButtonFeatures>())
        out = qvariant_cast<QStyleOptionToolButton::ToolButtonFeatures>(var);
    else if (var.userType() == qMetaTypeId<QStyleOptionToolButton::ToolButtonFeature>())
        out = qvariant_cast<QStyleOptionToolButton::ToolButtonFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyleOptionToolButton_ToolButtonFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::ToolButtonFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyleOptionToolButton::ToolButtonFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyleOptionToolButton::ToolButtonFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ToolButtonFeatures(): argument %0 is not of type ToolButtonFeature").arg(i));
            }
            result |= qvariant_cast<QStyleOptionToolButton::ToolButtonFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::ToolButtonFeatures value = qscriptvalue_cast<QStyleOptionToolButton::ToolButtonFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::ToolButtonFeatures value = qscriptvalue_cast<QStyleOptionToolButton::ToolButtonFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QStyleOptionToolButton_ToolButtonFeature_values[i]) == qtscript_QStyleOptionToolButton_ToolButtonFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyleOptionToolButton_ToolButtonFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyleOptionToolButton_ToolButtonFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyleOptionToolButton::ToolButtonFeatures>() == otherObj.value<QStyleOptionToolButton::ToolButtonFeatures>())));
}

static QScriptValue qtscript_create_QStyleOptionToolButton_ToolButtonFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyleOptionToolButton_ToolButtonFeatures, qtscript_QStyleOptionToolButton_ToolButtonFeatures_valueOf,
        qtscript_QStyleOptionToolButton_ToolButtonFeatures_toString, qtscript_QStyleOptionToolButton_ToolButtonFeatures_equals);
    qScriptRegisterMetaType<QStyleOptionToolButton::ToolButtonFeatures>(engine, qtscript_QStyleOptionToolButton_ToolButtonFeatures_toScriptValue,
        qtscript_QStyleOptionToolButton_ToolButtonFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyleOptionToolButton::StyleOptionType
//

static const QStyleOptionToolButton::StyleOptionType qtscript_QStyleOptionToolButton_StyleOptionType_values[] = {
    QStyleOptionToolButton::Type
};

static const char * const qtscript_QStyleOptionToolButton_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionToolButton_StyleOptionType_toStringHelper(QStyleOptionToolButton::StyleOptionType value)
{
    if ((value >= QStyleOptionToolButton::Type) && (value <= QStyleOptionToolButton::Type))
        return qtscript_QStyleOptionToolButton_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolButton::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolButton_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionToolButton::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolButton"));
    return clazz.property(qtscript_QStyleOptionToolButton_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionToolButton_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionToolButton::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionToolButton::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolButton_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolButton::Type) && (arg <= QStyleOptionToolButton::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolButton::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolButton_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::StyleOptionType value = qscriptvalue_cast<QStyleOptionToolButton::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolButton_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolButton::StyleOptionType value = qscriptvalue_cast<QStyleOptionToolButton::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolButton_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolButton_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolButton_StyleOptionType,
        qtscript_QStyleOptionToolButton_StyleOptionType_valueOf, qtscript_QStyleOptionToolButton_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionToolButton::StyleOptionType>(engine, qtscript_QStyleOptionToolButton_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionToolButton_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolButton_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolButton_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolButton
//

static QScriptValue qtscript_QStyleOptionToolButton_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionToolButton* _q_self = qscriptvalue_cast<QStyleOptionToolButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionToolButton.%0(): this object is not a QStyleOptionToolButton")
            .arg(qtscript_QStyleOptionToolButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionToolButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolButton_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolButton_function_names[_id+1],
        qtscript_QStyleOptionToolButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionToolButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionToolButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionToolButton _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolButton)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionToolButton _q_arg0 = qscriptvalue_cast<QStyleOptionToolButton>(context->argument(0));
        QtScriptShell_QStyleOptionToolButton _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolButton)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolButton_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolButton_function_names[_id],
        qtscript_QStyleOptionToolButton_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionToolButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionToolButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionComplex*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolButton>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolButton*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionToolButton_static_call, proto, qtscript_QStyleOptionToolButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionToolButton_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolButtonFeature"),
        qtscript_create_QStyleOptionToolButton_ToolButtonFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolButtonFeatures"),
        qtscript_create_QStyleOptionToolButton_ToolButtonFeatures_class(engine));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionToolButton_StyleOptionType_class(engine, ctor));
    return ctor;
}
