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

#include "qtscriptshell_QStyleOptionHeader.h"

static const char * const qtscript_QStyleOptionHeader_function_names[] = {
    "QStyleOptionHeader"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionHeader_function_signatures[] = {
    "\nQStyleOptionHeader other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionHeader_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionHeader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionHeader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionHeader)
Q_DECLARE_METATYPE(QStyleOptionHeader*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionHeader)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionHeader*)
Q_DECLARE_METATYPE(QStyleOptionHeader::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionHeader::SectionPosition)
Q_DECLARE_METATYPE(QStyleOptionHeader::SelectedPosition)
Q_DECLARE_METATYPE(QStyleOptionHeader::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionHeader::SortIndicator)
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
// QStyleOptionHeader::StyleOptionVersion
//

static const QStyleOptionHeader::StyleOptionVersion qtscript_QStyleOptionHeader_StyleOptionVersion_values[] = {
    QStyleOptionHeader::Version
};

static const char * const qtscript_QStyleOptionHeader_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionHeader_StyleOptionVersion_toStringHelper(QStyleOptionHeader::StyleOptionVersion value)
{
    if ((value >= QStyleOptionHeader::Version) && (value <= QStyleOptionHeader::Version))
        return qtscript_QStyleOptionHeader_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionHeader::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionHeader_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionHeader::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionHeader"));
    return clazz.property(qtscript_QStyleOptionHeader_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionHeader_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionHeader::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionHeader::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionHeader_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionHeader::Version) && (arg <= QStyleOptionHeader::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionHeader::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionHeader_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionHeader::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionHeader_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionHeader::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionHeader_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionHeader_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionHeader_StyleOptionVersion,
        qtscript_QStyleOptionHeader_StyleOptionVersion_valueOf, qtscript_QStyleOptionHeader_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionHeader::StyleOptionVersion>(engine, qtscript_QStyleOptionHeader_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionHeader_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionHeader_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionHeader_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionHeader::SectionPosition
//

static const QStyleOptionHeader::SectionPosition qtscript_QStyleOptionHeader_SectionPosition_values[] = {
    QStyleOptionHeader::Beginning
    , QStyleOptionHeader::Middle
    , QStyleOptionHeader::End
    , QStyleOptionHeader::OnlyOneSection
};

static const char * const qtscript_QStyleOptionHeader_SectionPosition_keys[] = {
    "Beginning"
    , "Middle"
    , "End"
    , "OnlyOneSection"
};

static QString qtscript_QStyleOptionHeader_SectionPosition_toStringHelper(QStyleOptionHeader::SectionPosition value)
{
    if ((value >= QStyleOptionHeader::Beginning) && (value <= QStyleOptionHeader::OnlyOneSection))
        return qtscript_QStyleOptionHeader_SectionPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionHeader::Beginning)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionHeader_SectionPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionHeader::SectionPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionHeader"));
    return clazz.property(qtscript_QStyleOptionHeader_SectionPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionHeader_SectionPosition_fromScriptValue(const QScriptValue &value, QStyleOptionHeader::SectionPosition &out)
{
    out = qvariant_cast<QStyleOptionHeader::SectionPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionHeader_SectionPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionHeader::Beginning) && (arg <= QStyleOptionHeader::OnlyOneSection))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionHeader::SectionPosition>(arg));
    return context->throwError(QString::fromLatin1("SectionPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionHeader_SectionPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::SectionPosition value = qscriptvalue_cast<QStyleOptionHeader::SectionPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionHeader_SectionPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::SectionPosition value = qscriptvalue_cast<QStyleOptionHeader::SectionPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionHeader_SectionPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionHeader_SectionPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionHeader_SectionPosition,
        qtscript_QStyleOptionHeader_SectionPosition_valueOf, qtscript_QStyleOptionHeader_SectionPosition_toString);
    qScriptRegisterMetaType<QStyleOptionHeader::SectionPosition>(engine, qtscript_QStyleOptionHeader_SectionPosition_toScriptValue,
        qtscript_QStyleOptionHeader_SectionPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionHeader_SectionPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionHeader_SectionPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionHeader::SelectedPosition
//

static const QStyleOptionHeader::SelectedPosition qtscript_QStyleOptionHeader_SelectedPosition_values[] = {
    QStyleOptionHeader::NotAdjacent
    , QStyleOptionHeader::NextIsSelected
    , QStyleOptionHeader::PreviousIsSelected
    , QStyleOptionHeader::NextAndPreviousAreSelected
};

static const char * const qtscript_QStyleOptionHeader_SelectedPosition_keys[] = {
    "NotAdjacent"
    , "NextIsSelected"
    , "PreviousIsSelected"
    , "NextAndPreviousAreSelected"
};

static QString qtscript_QStyleOptionHeader_SelectedPosition_toStringHelper(QStyleOptionHeader::SelectedPosition value)
{
    if ((value >= QStyleOptionHeader::NotAdjacent) && (value <= QStyleOptionHeader::NextAndPreviousAreSelected))
        return qtscript_QStyleOptionHeader_SelectedPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionHeader::NotAdjacent)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionHeader_SelectedPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionHeader::SelectedPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionHeader"));
    return clazz.property(qtscript_QStyleOptionHeader_SelectedPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionHeader_SelectedPosition_fromScriptValue(const QScriptValue &value, QStyleOptionHeader::SelectedPosition &out)
{
    out = qvariant_cast<QStyleOptionHeader::SelectedPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionHeader_SelectedPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionHeader::NotAdjacent) && (arg <= QStyleOptionHeader::NextAndPreviousAreSelected))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionHeader::SelectedPosition>(arg));
    return context->throwError(QString::fromLatin1("SelectedPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionHeader_SelectedPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::SelectedPosition value = qscriptvalue_cast<QStyleOptionHeader::SelectedPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionHeader_SelectedPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::SelectedPosition value = qscriptvalue_cast<QStyleOptionHeader::SelectedPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionHeader_SelectedPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionHeader_SelectedPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionHeader_SelectedPosition,
        qtscript_QStyleOptionHeader_SelectedPosition_valueOf, qtscript_QStyleOptionHeader_SelectedPosition_toString);
    qScriptRegisterMetaType<QStyleOptionHeader::SelectedPosition>(engine, qtscript_QStyleOptionHeader_SelectedPosition_toScriptValue,
        qtscript_QStyleOptionHeader_SelectedPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionHeader_SelectedPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionHeader_SelectedPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionHeader::StyleOptionType
//

static const QStyleOptionHeader::StyleOptionType qtscript_QStyleOptionHeader_StyleOptionType_values[] = {
    QStyleOptionHeader::Type
};

static const char * const qtscript_QStyleOptionHeader_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionHeader_StyleOptionType_toStringHelper(QStyleOptionHeader::StyleOptionType value)
{
    if ((value >= QStyleOptionHeader::Type) && (value <= QStyleOptionHeader::Type))
        return qtscript_QStyleOptionHeader_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionHeader::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionHeader_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionHeader::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionHeader"));
    return clazz.property(qtscript_QStyleOptionHeader_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionHeader_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionHeader::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionHeader::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionHeader_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionHeader::Type) && (arg <= QStyleOptionHeader::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionHeader::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionHeader_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::StyleOptionType value = qscriptvalue_cast<QStyleOptionHeader::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionHeader_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::StyleOptionType value = qscriptvalue_cast<QStyleOptionHeader::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionHeader_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionHeader_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionHeader_StyleOptionType,
        qtscript_QStyleOptionHeader_StyleOptionType_valueOf, qtscript_QStyleOptionHeader_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionHeader::StyleOptionType>(engine, qtscript_QStyleOptionHeader_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionHeader_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionHeader_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionHeader_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionHeader::SortIndicator
//

static const QStyleOptionHeader::SortIndicator qtscript_QStyleOptionHeader_SortIndicator_values[] = {
    QStyleOptionHeader::None
    , QStyleOptionHeader::SortUp
    , QStyleOptionHeader::SortDown
};

static const char * const qtscript_QStyleOptionHeader_SortIndicator_keys[] = {
    "None"
    , "SortUp"
    , "SortDown"
};

static QString qtscript_QStyleOptionHeader_SortIndicator_toStringHelper(QStyleOptionHeader::SortIndicator value)
{
    if ((value >= QStyleOptionHeader::None) && (value <= QStyleOptionHeader::SortDown))
        return qtscript_QStyleOptionHeader_SortIndicator_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionHeader::None)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionHeader_SortIndicator_toScriptValue(QScriptEngine *engine, const QStyleOptionHeader::SortIndicator &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionHeader"));
    return clazz.property(qtscript_QStyleOptionHeader_SortIndicator_toStringHelper(value));
}

static void qtscript_QStyleOptionHeader_SortIndicator_fromScriptValue(const QScriptValue &value, QStyleOptionHeader::SortIndicator &out)
{
    out = qvariant_cast<QStyleOptionHeader::SortIndicator>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionHeader_SortIndicator(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionHeader::None) && (arg <= QStyleOptionHeader::SortDown))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionHeader::SortIndicator>(arg));
    return context->throwError(QString::fromLatin1("SortIndicator(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionHeader_SortIndicator_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::SortIndicator value = qscriptvalue_cast<QStyleOptionHeader::SortIndicator>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionHeader_SortIndicator_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionHeader::SortIndicator value = qscriptvalue_cast<QStyleOptionHeader::SortIndicator>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionHeader_SortIndicator_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionHeader_SortIndicator_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionHeader_SortIndicator,
        qtscript_QStyleOptionHeader_SortIndicator_valueOf, qtscript_QStyleOptionHeader_SortIndicator_toString);
    qScriptRegisterMetaType<QStyleOptionHeader::SortIndicator>(engine, qtscript_QStyleOptionHeader_SortIndicator_toScriptValue,
        qtscript_QStyleOptionHeader_SortIndicator_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionHeader_SortIndicator_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionHeader_SortIndicator_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionHeader
//

static QScriptValue qtscript_QStyleOptionHeader_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionHeader* _q_self = qscriptvalue_cast<QStyleOptionHeader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionHeader.%0(): this object is not a QStyleOptionHeader")
            .arg(qtscript_QStyleOptionHeader_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionHeader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionHeader_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionHeader_function_names[_id+1],
        qtscript_QStyleOptionHeader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionHeader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionHeader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionHeader _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionHeader)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionHeader _q_arg0 = qscriptvalue_cast<QStyleOptionHeader>(context->argument(0));
        QtScriptShell_QStyleOptionHeader _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionHeader)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionHeader_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionHeader_function_names[_id],
        qtscript_QStyleOptionHeader_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionHeader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionHeader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionHeader*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionHeader>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionHeader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionHeader_static_call, proto, qtscript_QStyleOptionHeader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionHeader_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SectionPosition"),
        qtscript_create_QStyleOptionHeader_SectionPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectedPosition"),
        qtscript_create_QStyleOptionHeader_SelectedPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionHeader_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SortIndicator"),
        qtscript_create_QStyleOptionHeader_SortIndicator_class(engine, ctor));
    return ctor;
}
