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

#include "qtscriptshell_QStyleOptionToolBar.h"

static const char * const qtscript_QStyleOptionToolBar_function_names[] = {
    "QStyleOptionToolBar"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionToolBar_function_signatures[] = {
    "\nQStyleOptionToolBar other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionToolBar_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionToolBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionToolBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionToolBar)
Q_DECLARE_METATYPE(QStyleOptionToolBar*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolBar)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolBar*)
Q_DECLARE_METATYPE(QStyleOptionToolBar::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionToolBar::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionToolBar::ToolBarPosition)
Q_DECLARE_METATYPE(QStyleOptionToolBar::ToolBarFeature)
Q_DECLARE_METATYPE(QFlags<QStyleOptionToolBar::ToolBarFeature>)
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
// QStyleOptionToolBar::StyleOptionVersion
//

static const QStyleOptionToolBar::StyleOptionVersion qtscript_QStyleOptionToolBar_StyleOptionVersion_values[] = {
    QStyleOptionToolBar::Version
};

static const char * const qtscript_QStyleOptionToolBar_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionToolBar_StyleOptionVersion_toStringHelper(QStyleOptionToolBar::StyleOptionVersion value)
{
    if ((value >= QStyleOptionToolBar::Version) && (value <= QStyleOptionToolBar::Version))
        return qtscript_QStyleOptionToolBar_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBar::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBar_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBar::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBar"));
    return clazz.property(qtscript_QStyleOptionToolBar_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBar_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionToolBar::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionToolBar::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBar_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBar::Version) && (arg <= QStyleOptionToolBar::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBar::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBar_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolBar::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBar_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolBar::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBar_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBar_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBar_StyleOptionVersion,
        qtscript_QStyleOptionToolBar_StyleOptionVersion_valueOf, qtscript_QStyleOptionToolBar_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionToolBar::StyleOptionVersion>(engine, qtscript_QStyleOptionToolBar_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionToolBar_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBar_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBar_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBar::StyleOptionType
//

static const QStyleOptionToolBar::StyleOptionType qtscript_QStyleOptionToolBar_StyleOptionType_values[] = {
    QStyleOptionToolBar::Type
};

static const char * const qtscript_QStyleOptionToolBar_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionToolBar_StyleOptionType_toStringHelper(QStyleOptionToolBar::StyleOptionType value)
{
    if ((value >= QStyleOptionToolBar::Type) && (value <= QStyleOptionToolBar::Type))
        return qtscript_QStyleOptionToolBar_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBar::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBar_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBar::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBar"));
    return clazz.property(qtscript_QStyleOptionToolBar_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBar_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionToolBar::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionToolBar::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBar_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBar::Type) && (arg <= QStyleOptionToolBar::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBar::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBar_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::StyleOptionType value = qscriptvalue_cast<QStyleOptionToolBar::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBar_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::StyleOptionType value = qscriptvalue_cast<QStyleOptionToolBar::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBar_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBar_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBar_StyleOptionType,
        qtscript_QStyleOptionToolBar_StyleOptionType_valueOf, qtscript_QStyleOptionToolBar_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionToolBar::StyleOptionType>(engine, qtscript_QStyleOptionToolBar_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionToolBar_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBar_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBar_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBar::ToolBarPosition
//

static const QStyleOptionToolBar::ToolBarPosition qtscript_QStyleOptionToolBar_ToolBarPosition_values[] = {
    QStyleOptionToolBar::Beginning
    , QStyleOptionToolBar::Middle
    , QStyleOptionToolBar::End
    , QStyleOptionToolBar::OnlyOne
};

static const char * const qtscript_QStyleOptionToolBar_ToolBarPosition_keys[] = {
    "Beginning"
    , "Middle"
    , "End"
    , "OnlyOne"
};

static QString qtscript_QStyleOptionToolBar_ToolBarPosition_toStringHelper(QStyleOptionToolBar::ToolBarPosition value)
{
    if ((value >= QStyleOptionToolBar::Beginning) && (value <= QStyleOptionToolBar::OnlyOne))
        return qtscript_QStyleOptionToolBar_ToolBarPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBar::Beginning)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBar::ToolBarPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBar"));
    return clazz.property(qtscript_QStyleOptionToolBar_ToolBarPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBar_ToolBarPosition_fromScriptValue(const QScriptValue &value, QStyleOptionToolBar::ToolBarPosition &out)
{
    out = qvariant_cast<QStyleOptionToolBar::ToolBarPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBar_ToolBarPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBar::Beginning) && (arg <= QStyleOptionToolBar::OnlyOne))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBar::ToolBarPosition>(arg));
    return context->throwError(QString::fromLatin1("ToolBarPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarPosition value = qscriptvalue_cast<QStyleOptionToolBar::ToolBarPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarPosition value = qscriptvalue_cast<QStyleOptionToolBar::ToolBarPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBar_ToolBarPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBar_ToolBarPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBar_ToolBarPosition,
        qtscript_QStyleOptionToolBar_ToolBarPosition_valueOf, qtscript_QStyleOptionToolBar_ToolBarPosition_toString);
    qScriptRegisterMetaType<QStyleOptionToolBar::ToolBarPosition>(engine, qtscript_QStyleOptionToolBar_ToolBarPosition_toScriptValue,
        qtscript_QStyleOptionToolBar_ToolBarPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBar_ToolBarPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBar_ToolBarPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBar::ToolBarFeature
//

static const QStyleOptionToolBar::ToolBarFeature qtscript_QStyleOptionToolBar_ToolBarFeature_values[] = {
    QStyleOptionToolBar::None
    , QStyleOptionToolBar::Movable
};

static const char * const qtscript_QStyleOptionToolBar_ToolBarFeature_keys[] = {
    "None"
    , "Movable"
};

static QString qtscript_QStyleOptionToolBar_ToolBarFeature_toStringHelper(QStyleOptionToolBar::ToolBarFeature value)
{
    if ((value >= QStyleOptionToolBar::None) && (value <= QStyleOptionToolBar::Movable))
        return qtscript_QStyleOptionToolBar_ToolBarFeature_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBar::None)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeature_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBar::ToolBarFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBar"));
    return clazz.property(qtscript_QStyleOptionToolBar_ToolBarFeature_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBar_ToolBarFeature_fromScriptValue(const QScriptValue &value, QStyleOptionToolBar::ToolBarFeature &out)
{
    out = qvariant_cast<QStyleOptionToolBar::ToolBarFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBar_ToolBarFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBar::None) && (arg <= QStyleOptionToolBar::Movable))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBar::ToolBarFeature>(arg));
    return context->throwError(QString::fromLatin1("ToolBarFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarFeature value = qscriptvalue_cast<QStyleOptionToolBar::ToolBarFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarFeature value = qscriptvalue_cast<QStyleOptionToolBar::ToolBarFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBar_ToolBarFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBar_ToolBarFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBar_ToolBarFeature,
        qtscript_QStyleOptionToolBar_ToolBarFeature_valueOf, qtscript_QStyleOptionToolBar_ToolBarFeature_toString);
    qScriptRegisterMetaType<QStyleOptionToolBar::ToolBarFeature>(engine, qtscript_QStyleOptionToolBar_ToolBarFeature_toScriptValue,
        qtscript_QStyleOptionToolBar_ToolBarFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBar_ToolBarFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBar_ToolBarFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBar::ToolBarFeatures
//

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeatures_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBar::ToolBarFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyleOptionToolBar_ToolBarFeatures_fromScriptValue(const QScriptValue &value, QStyleOptionToolBar::ToolBarFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyleOptionToolBar::ToolBarFeatures>())
        out = qvariant_cast<QStyleOptionToolBar::ToolBarFeatures>(var);
    else if (var.userType() == qMetaTypeId<QStyleOptionToolBar::ToolBarFeature>())
        out = qvariant_cast<QStyleOptionToolBar::ToolBarFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyleOptionToolBar_ToolBarFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyleOptionToolBar::ToolBarFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyleOptionToolBar::ToolBarFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ToolBarFeatures(): argument %0 is not of type ToolBarFeature").arg(i));
            }
            result |= qvariant_cast<QStyleOptionToolBar::ToolBarFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarFeatures value = qscriptvalue_cast<QStyleOptionToolBar::ToolBarFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBar::ToolBarFeatures value = qscriptvalue_cast<QStyleOptionToolBar::ToolBarFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QStyleOptionToolBar_ToolBarFeature_values[i]) == qtscript_QStyleOptionToolBar_ToolBarFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyleOptionToolBar_ToolBarFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyleOptionToolBar_ToolBarFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyleOptionToolBar::ToolBarFeatures>() == otherObj.value<QStyleOptionToolBar::ToolBarFeatures>())));
}

static QScriptValue qtscript_create_QStyleOptionToolBar_ToolBarFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyleOptionToolBar_ToolBarFeatures, qtscript_QStyleOptionToolBar_ToolBarFeatures_valueOf,
        qtscript_QStyleOptionToolBar_ToolBarFeatures_toString, qtscript_QStyleOptionToolBar_ToolBarFeatures_equals);
    qScriptRegisterMetaType<QStyleOptionToolBar::ToolBarFeatures>(engine, qtscript_QStyleOptionToolBar_ToolBarFeatures_toScriptValue,
        qtscript_QStyleOptionToolBar_ToolBarFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyleOptionToolBar
//

static QScriptValue qtscript_QStyleOptionToolBar_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionToolBar* _q_self = qscriptvalue_cast<QStyleOptionToolBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionToolBar.%0(): this object is not a QStyleOptionToolBar")
            .arg(qtscript_QStyleOptionToolBar_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionToolBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolBar_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolBar_function_names[_id+1],
        qtscript_QStyleOptionToolBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionToolBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionToolBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionToolBar _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBar)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionToolBar _q_arg0 = qscriptvalue_cast<QStyleOptionToolBar>(context->argument(0));
        QtScriptShell_QStyleOptionToolBar _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBar)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolBar_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolBar_function_names[_id],
        qtscript_QStyleOptionToolBar_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionToolBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionToolBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBar>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBar*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionToolBar_static_call, proto, qtscript_QStyleOptionToolBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionToolBar_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionToolBar_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolBarPosition"),
        qtscript_create_QStyleOptionToolBar_ToolBarPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolBarFeature"),
        qtscript_create_QStyleOptionToolBar_ToolBarFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolBarFeatures"),
        qtscript_create_QStyleOptionToolBar_ToolBarFeatures_class(engine));
    return ctor;
}
