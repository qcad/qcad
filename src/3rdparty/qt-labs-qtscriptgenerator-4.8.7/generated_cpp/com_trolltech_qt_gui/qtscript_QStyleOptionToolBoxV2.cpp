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

#include "qtscriptshell_QStyleOptionToolBoxV2.h"

static const char * const qtscript_QStyleOptionToolBoxV2_function_names[] = {
    "QStyleOptionToolBoxV2"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionToolBoxV2_function_signatures[] = {
    "\nQStyleOptionToolBox other\nQStyleOptionToolBoxV2 other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionToolBoxV2_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionToolBoxV2_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionToolBoxV2::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionToolBoxV2)
Q_DECLARE_METATYPE(QStyleOptionToolBoxV2*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolBoxV2)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionToolBoxV2*)
Q_DECLARE_METATYPE(QStyleOptionToolBoxV2::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionToolBoxV2::TabPosition)
Q_DECLARE_METATYPE(QStyleOptionToolBoxV2::SelectedPosition)
Q_DECLARE_METATYPE(QStyleOptionToolBox)
Q_DECLARE_METATYPE(QStyleOptionToolBox*)

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
// QStyleOptionToolBoxV2::StyleOptionVersion
//

static const QStyleOptionToolBoxV2::StyleOptionVersion qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_values[] = {
    QStyleOptionToolBoxV2::Version
};

static const char * const qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toStringHelper(QStyleOptionToolBoxV2::StyleOptionVersion value)
{
    if ((value >= QStyleOptionToolBoxV2::Version) && (value <= QStyleOptionToolBoxV2::Version))
        return qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBoxV2::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBoxV2::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBoxV2"));
    return clazz.property(qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionToolBoxV2::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionToolBoxV2::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBoxV2_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBoxV2::Version) && (arg <= QStyleOptionToolBoxV2::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBoxV2::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBoxV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolBoxV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBoxV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionToolBoxV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBoxV2_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBoxV2_StyleOptionVersion,
        qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_valueOf, qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionToolBoxV2::StyleOptionVersion>(engine, qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBoxV2_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBoxV2::TabPosition
//

static const QStyleOptionToolBoxV2::TabPosition qtscript_QStyleOptionToolBoxV2_TabPosition_values[] = {
    QStyleOptionToolBoxV2::Beginning
    , QStyleOptionToolBoxV2::Middle
    , QStyleOptionToolBoxV2::End
    , QStyleOptionToolBoxV2::OnlyOneTab
};

static const char * const qtscript_QStyleOptionToolBoxV2_TabPosition_keys[] = {
    "Beginning"
    , "Middle"
    , "End"
    , "OnlyOneTab"
};

static QString qtscript_QStyleOptionToolBoxV2_TabPosition_toStringHelper(QStyleOptionToolBoxV2::TabPosition value)
{
    if ((value >= QStyleOptionToolBoxV2::Beginning) && (value <= QStyleOptionToolBoxV2::OnlyOneTab))
        return qtscript_QStyleOptionToolBoxV2_TabPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBoxV2::Beginning)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_TabPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBoxV2::TabPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBoxV2"));
    return clazz.property(qtscript_QStyleOptionToolBoxV2_TabPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBoxV2_TabPosition_fromScriptValue(const QScriptValue &value, QStyleOptionToolBoxV2::TabPosition &out)
{
    out = qvariant_cast<QStyleOptionToolBoxV2::TabPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBoxV2_TabPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBoxV2::Beginning) && (arg <= QStyleOptionToolBoxV2::OnlyOneTab))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBoxV2::TabPosition>(arg));
    return context->throwError(QString::fromLatin1("TabPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_TabPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBoxV2::TabPosition value = qscriptvalue_cast<QStyleOptionToolBoxV2::TabPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_TabPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBoxV2::TabPosition value = qscriptvalue_cast<QStyleOptionToolBoxV2::TabPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBoxV2_TabPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBoxV2_TabPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBoxV2_TabPosition,
        qtscript_QStyleOptionToolBoxV2_TabPosition_valueOf, qtscript_QStyleOptionToolBoxV2_TabPosition_toString);
    qScriptRegisterMetaType<QStyleOptionToolBoxV2::TabPosition>(engine, qtscript_QStyleOptionToolBoxV2_TabPosition_toScriptValue,
        qtscript_QStyleOptionToolBoxV2_TabPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBoxV2_TabPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBoxV2_TabPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBoxV2::SelectedPosition
//

static const QStyleOptionToolBoxV2::SelectedPosition qtscript_QStyleOptionToolBoxV2_SelectedPosition_values[] = {
    QStyleOptionToolBoxV2::NotAdjacent
    , QStyleOptionToolBoxV2::NextIsSelected
    , QStyleOptionToolBoxV2::PreviousIsSelected
};

static const char * const qtscript_QStyleOptionToolBoxV2_SelectedPosition_keys[] = {
    "NotAdjacent"
    , "NextIsSelected"
    , "PreviousIsSelected"
};

static QString qtscript_QStyleOptionToolBoxV2_SelectedPosition_toStringHelper(QStyleOptionToolBoxV2::SelectedPosition value)
{
    if ((value >= QStyleOptionToolBoxV2::NotAdjacent) && (value <= QStyleOptionToolBoxV2::PreviousIsSelected))
        return qtscript_QStyleOptionToolBoxV2_SelectedPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionToolBoxV2::NotAdjacent)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_SelectedPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionToolBoxV2::SelectedPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionToolBoxV2"));
    return clazz.property(qtscript_QStyleOptionToolBoxV2_SelectedPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionToolBoxV2_SelectedPosition_fromScriptValue(const QScriptValue &value, QStyleOptionToolBoxV2::SelectedPosition &out)
{
    out = qvariant_cast<QStyleOptionToolBoxV2::SelectedPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionToolBoxV2_SelectedPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionToolBoxV2::NotAdjacent) && (arg <= QStyleOptionToolBoxV2::PreviousIsSelected))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionToolBoxV2::SelectedPosition>(arg));
    return context->throwError(QString::fromLatin1("SelectedPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_SelectedPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBoxV2::SelectedPosition value = qscriptvalue_cast<QStyleOptionToolBoxV2::SelectedPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_SelectedPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionToolBoxV2::SelectedPosition value = qscriptvalue_cast<QStyleOptionToolBoxV2::SelectedPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionToolBoxV2_SelectedPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionToolBoxV2_SelectedPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionToolBoxV2_SelectedPosition,
        qtscript_QStyleOptionToolBoxV2_SelectedPosition_valueOf, qtscript_QStyleOptionToolBoxV2_SelectedPosition_toString);
    qScriptRegisterMetaType<QStyleOptionToolBoxV2::SelectedPosition>(engine, qtscript_QStyleOptionToolBoxV2_SelectedPosition_toScriptValue,
        qtscript_QStyleOptionToolBoxV2_SelectedPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionToolBoxV2_SelectedPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionToolBoxV2_SelectedPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionToolBoxV2
//

static QScriptValue qtscript_QStyleOptionToolBoxV2_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionToolBoxV2* _q_self = qscriptvalue_cast<QStyleOptionToolBoxV2*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionToolBoxV2.%0(): this object is not a QStyleOptionToolBoxV2")
            .arg(qtscript_QStyleOptionToolBoxV2_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionToolBoxV2");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolBoxV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolBoxV2_function_names[_id+1],
        qtscript_QStyleOptionToolBoxV2_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionToolBoxV2_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionToolBoxV2(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionToolBoxV2 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBoxV2)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOptionToolBox>() == context->argument(0).toVariant().userType())) {
            QStyleOptionToolBox _q_arg0 = qscriptvalue_cast<QStyleOptionToolBox>(context->argument(0));
            QtScriptShell_QStyleOptionToolBoxV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBoxV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QStyleOptionToolBoxV2>() == context->argument(0).toVariant().userType())) {
            QStyleOptionToolBoxV2 _q_arg0 = qscriptvalue_cast<QStyleOptionToolBoxV2>(context->argument(0));
            QtScriptShell_QStyleOptionToolBoxV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionToolBoxV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionToolBoxV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionToolBoxV2_function_names[_id],
        qtscript_QStyleOptionToolBoxV2_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionToolBoxV2_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBoxV2*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionToolBoxV2*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionToolBox*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBoxV2>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionToolBoxV2*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionToolBoxV2_static_call, proto, qtscript_QStyleOptionToolBoxV2_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionToolBoxV2_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TabPosition"),
        qtscript_create_QStyleOptionToolBoxV2_TabPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectedPosition"),
        qtscript_create_QStyleOptionToolBoxV2_SelectedPosition_class(engine, ctor));
    return ctor;
}
