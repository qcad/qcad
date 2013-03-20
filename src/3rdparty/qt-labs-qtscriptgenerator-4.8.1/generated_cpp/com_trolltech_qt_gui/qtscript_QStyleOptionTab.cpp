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

#include "qtscriptshell_QStyleOptionTab.h"

static const char * const qtscript_QStyleOptionTab_function_names[] = {
    "QStyleOptionTab"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionTab_function_signatures[] = {
    "\nQStyleOptionTab other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionTab_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionTab_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionTab::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionTab)
Q_DECLARE_METATYPE(QStyleOptionTab*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTab)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTab*)
Q_DECLARE_METATYPE(QStyleOptionTab::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionTab::CornerWidget)
Q_DECLARE_METATYPE(QFlags<QStyleOptionTab::CornerWidget>)
Q_DECLARE_METATYPE(QStyleOptionTab::TabPosition)
Q_DECLARE_METATYPE(QStyleOptionTab::SelectedPosition)
Q_DECLARE_METATYPE(QStyleOptionTab::StyleOptionType)
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
// QStyleOptionTab::StyleOptionVersion
//

static const QStyleOptionTab::StyleOptionVersion qtscript_QStyleOptionTab_StyleOptionVersion_values[] = {
    QStyleOptionTab::Version
};

static const char * const qtscript_QStyleOptionTab_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionTab_StyleOptionVersion_toStringHelper(QStyleOptionTab::StyleOptionVersion value)
{
    if ((value >= QStyleOptionTab::Version) && (value <= QStyleOptionTab::Version))
        return qtscript_QStyleOptionTab_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTab::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTab_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionTab::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTab"));
    return clazz.property(qtscript_QStyleOptionTab_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionTab_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionTab::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionTab::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTab_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTab::Version) && (arg <= QStyleOptionTab::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTab::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTab_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTab::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTab_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTab::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTab_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTab_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTab_StyleOptionVersion,
        qtscript_QStyleOptionTab_StyleOptionVersion_valueOf, qtscript_QStyleOptionTab_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionTab::StyleOptionVersion>(engine, qtscript_QStyleOptionTab_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionTab_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTab_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTab_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTab::CornerWidget
//

static const QStyleOptionTab::CornerWidget qtscript_QStyleOptionTab_CornerWidget_values[] = {
    QStyleOptionTab::NoCornerWidgets
    , QStyleOptionTab::LeftCornerWidget
    , QStyleOptionTab::RightCornerWidget
};

static const char * const qtscript_QStyleOptionTab_CornerWidget_keys[] = {
    "NoCornerWidgets"
    , "LeftCornerWidget"
    , "RightCornerWidget"
};

static QString qtscript_QStyleOptionTab_CornerWidget_toStringHelper(QStyleOptionTab::CornerWidget value)
{
    if ((value >= QStyleOptionTab::NoCornerWidgets) && (value <= QStyleOptionTab::RightCornerWidget))
        return qtscript_QStyleOptionTab_CornerWidget_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTab::NoCornerWidgets)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTab_CornerWidget_toScriptValue(QScriptEngine *engine, const QStyleOptionTab::CornerWidget &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTab"));
    return clazz.property(qtscript_QStyleOptionTab_CornerWidget_toStringHelper(value));
}

static void qtscript_QStyleOptionTab_CornerWidget_fromScriptValue(const QScriptValue &value, QStyleOptionTab::CornerWidget &out)
{
    out = qvariant_cast<QStyleOptionTab::CornerWidget>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTab_CornerWidget(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTab::NoCornerWidgets) && (arg <= QStyleOptionTab::RightCornerWidget))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTab::CornerWidget>(arg));
    return context->throwError(QString::fromLatin1("CornerWidget(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTab_CornerWidget_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::CornerWidget value = qscriptvalue_cast<QStyleOptionTab::CornerWidget>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTab_CornerWidget_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::CornerWidget value = qscriptvalue_cast<QStyleOptionTab::CornerWidget>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTab_CornerWidget_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTab_CornerWidget_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTab_CornerWidget,
        qtscript_QStyleOptionTab_CornerWidget_valueOf, qtscript_QStyleOptionTab_CornerWidget_toString);
    qScriptRegisterMetaType<QStyleOptionTab::CornerWidget>(engine, qtscript_QStyleOptionTab_CornerWidget_toScriptValue,
        qtscript_QStyleOptionTab_CornerWidget_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTab_CornerWidget_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTab_CornerWidget_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTab::CornerWidgets
//

static QScriptValue qtscript_QStyleOptionTab_CornerWidgets_toScriptValue(QScriptEngine *engine, const QStyleOptionTab::CornerWidgets &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyleOptionTab_CornerWidgets_fromScriptValue(const QScriptValue &value, QStyleOptionTab::CornerWidgets &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyleOptionTab::CornerWidgets>())
        out = qvariant_cast<QStyleOptionTab::CornerWidgets>(var);
    else if (var.userType() == qMetaTypeId<QStyleOptionTab::CornerWidget>())
        out = qvariant_cast<QStyleOptionTab::CornerWidget>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyleOptionTab_CornerWidgets(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::CornerWidgets result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyleOptionTab::CornerWidgets>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyleOptionTab::CornerWidget>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("CornerWidgets(): argument %0 is not of type CornerWidget").arg(i));
            }
            result |= qvariant_cast<QStyleOptionTab::CornerWidget>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyleOptionTab_CornerWidgets_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::CornerWidgets value = qscriptvalue_cast<QStyleOptionTab::CornerWidgets>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTab_CornerWidgets_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::CornerWidgets value = qscriptvalue_cast<QStyleOptionTab::CornerWidgets>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QStyleOptionTab_CornerWidget_values[i]) == qtscript_QStyleOptionTab_CornerWidget_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyleOptionTab_CornerWidget_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyleOptionTab_CornerWidgets_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyleOptionTab::CornerWidgets>() == otherObj.value<QStyleOptionTab::CornerWidgets>())));
}

static QScriptValue qtscript_create_QStyleOptionTab_CornerWidgets_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyleOptionTab_CornerWidgets, qtscript_QStyleOptionTab_CornerWidgets_valueOf,
        qtscript_QStyleOptionTab_CornerWidgets_toString, qtscript_QStyleOptionTab_CornerWidgets_equals);
    qScriptRegisterMetaType<QStyleOptionTab::CornerWidgets>(engine, qtscript_QStyleOptionTab_CornerWidgets_toScriptValue,
        qtscript_QStyleOptionTab_CornerWidgets_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyleOptionTab::TabPosition
//

static const QStyleOptionTab::TabPosition qtscript_QStyleOptionTab_TabPosition_values[] = {
    QStyleOptionTab::Beginning
    , QStyleOptionTab::Middle
    , QStyleOptionTab::End
    , QStyleOptionTab::OnlyOneTab
};

static const char * const qtscript_QStyleOptionTab_TabPosition_keys[] = {
    "Beginning"
    , "Middle"
    , "End"
    , "OnlyOneTab"
};

static QString qtscript_QStyleOptionTab_TabPosition_toStringHelper(QStyleOptionTab::TabPosition value)
{
    if ((value >= QStyleOptionTab::Beginning) && (value <= QStyleOptionTab::OnlyOneTab))
        return qtscript_QStyleOptionTab_TabPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTab::Beginning)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTab_TabPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionTab::TabPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTab"));
    return clazz.property(qtscript_QStyleOptionTab_TabPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionTab_TabPosition_fromScriptValue(const QScriptValue &value, QStyleOptionTab::TabPosition &out)
{
    out = qvariant_cast<QStyleOptionTab::TabPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTab_TabPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTab::Beginning) && (arg <= QStyleOptionTab::OnlyOneTab))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTab::TabPosition>(arg));
    return context->throwError(QString::fromLatin1("TabPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTab_TabPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::TabPosition value = qscriptvalue_cast<QStyleOptionTab::TabPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTab_TabPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::TabPosition value = qscriptvalue_cast<QStyleOptionTab::TabPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTab_TabPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTab_TabPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTab_TabPosition,
        qtscript_QStyleOptionTab_TabPosition_valueOf, qtscript_QStyleOptionTab_TabPosition_toString);
    qScriptRegisterMetaType<QStyleOptionTab::TabPosition>(engine, qtscript_QStyleOptionTab_TabPosition_toScriptValue,
        qtscript_QStyleOptionTab_TabPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTab_TabPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTab_TabPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTab::SelectedPosition
//

static const QStyleOptionTab::SelectedPosition qtscript_QStyleOptionTab_SelectedPosition_values[] = {
    QStyleOptionTab::NotAdjacent
    , QStyleOptionTab::NextIsSelected
    , QStyleOptionTab::PreviousIsSelected
};

static const char * const qtscript_QStyleOptionTab_SelectedPosition_keys[] = {
    "NotAdjacent"
    , "NextIsSelected"
    , "PreviousIsSelected"
};

static QString qtscript_QStyleOptionTab_SelectedPosition_toStringHelper(QStyleOptionTab::SelectedPosition value)
{
    if ((value >= QStyleOptionTab::NotAdjacent) && (value <= QStyleOptionTab::PreviousIsSelected))
        return qtscript_QStyleOptionTab_SelectedPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTab::NotAdjacent)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTab_SelectedPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionTab::SelectedPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTab"));
    return clazz.property(qtscript_QStyleOptionTab_SelectedPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionTab_SelectedPosition_fromScriptValue(const QScriptValue &value, QStyleOptionTab::SelectedPosition &out)
{
    out = qvariant_cast<QStyleOptionTab::SelectedPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTab_SelectedPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTab::NotAdjacent) && (arg <= QStyleOptionTab::PreviousIsSelected))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTab::SelectedPosition>(arg));
    return context->throwError(QString::fromLatin1("SelectedPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTab_SelectedPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::SelectedPosition value = qscriptvalue_cast<QStyleOptionTab::SelectedPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTab_SelectedPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::SelectedPosition value = qscriptvalue_cast<QStyleOptionTab::SelectedPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTab_SelectedPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTab_SelectedPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTab_SelectedPosition,
        qtscript_QStyleOptionTab_SelectedPosition_valueOf, qtscript_QStyleOptionTab_SelectedPosition_toString);
    qScriptRegisterMetaType<QStyleOptionTab::SelectedPosition>(engine, qtscript_QStyleOptionTab_SelectedPosition_toScriptValue,
        qtscript_QStyleOptionTab_SelectedPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTab_SelectedPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTab_SelectedPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTab::StyleOptionType
//

static const QStyleOptionTab::StyleOptionType qtscript_QStyleOptionTab_StyleOptionType_values[] = {
    QStyleOptionTab::Type
};

static const char * const qtscript_QStyleOptionTab_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionTab_StyleOptionType_toStringHelper(QStyleOptionTab::StyleOptionType value)
{
    if ((value >= QStyleOptionTab::Type) && (value <= QStyleOptionTab::Type))
        return qtscript_QStyleOptionTab_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTab::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTab_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionTab::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTab"));
    return clazz.property(qtscript_QStyleOptionTab_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionTab_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionTab::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionTab::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTab_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTab::Type) && (arg <= QStyleOptionTab::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTab::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTab_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::StyleOptionType value = qscriptvalue_cast<QStyleOptionTab::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTab_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTab::StyleOptionType value = qscriptvalue_cast<QStyleOptionTab::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTab_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTab_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTab_StyleOptionType,
        qtscript_QStyleOptionTab_StyleOptionType_valueOf, qtscript_QStyleOptionTab_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionTab::StyleOptionType>(engine, qtscript_QStyleOptionTab_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionTab_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTab_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTab_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTab
//

static QScriptValue qtscript_QStyleOptionTab_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionTab* _q_self = qscriptvalue_cast<QStyleOptionTab*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionTab.%0(): this object is not a QStyleOptionTab")
            .arg(qtscript_QStyleOptionTab_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionTab");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTab_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTab_function_names[_id+1],
        qtscript_QStyleOptionTab_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionTab_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionTab(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionTab _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTab)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionTab _q_arg0 = qscriptvalue_cast<QStyleOptionTab>(context->argument(0));
        QtScriptShell_QStyleOptionTab _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTab)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTab_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTab_function_names[_id],
        qtscript_QStyleOptionTab_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionTab_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTab*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionTab*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTab>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTab*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionTab_static_call, proto, qtscript_QStyleOptionTab_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionTab_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CornerWidget"),
        qtscript_create_QStyleOptionTab_CornerWidget_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CornerWidgets"),
        qtscript_create_QStyleOptionTab_CornerWidgets_class(engine));
    ctor.setProperty(QString::fromLatin1("TabPosition"),
        qtscript_create_QStyleOptionTab_TabPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectedPosition"),
        qtscript_create_QStyleOptionTab_SelectedPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionTab_StyleOptionType_class(engine, ctor));
    return ctor;
}
