#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsql.h>
#include <QVariant>

#include <qsql.h>

static const char * const qtscript_QSql_function_names[] = {
    "QSql"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QSql_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QSql_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QSql_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSql::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSql::NumericalPrecisionPolicy)
Q_DECLARE_METATYPE(QSql::Location)
Q_DECLARE_METATYPE(QSql::ParamTypeFlag)
Q_DECLARE_METATYPE(QFlags<QSql::ParamTypeFlag>)
Q_DECLARE_METATYPE(QSql::TableType)

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
// QSql::NumericalPrecisionPolicy
//

static const QSql::NumericalPrecisionPolicy qtscript_QSql_NumericalPrecisionPolicy_values[] = {
    QSql::HighPrecision
    , QSql::LowPrecisionInt32
    , QSql::LowPrecisionInt64
    , QSql::LowPrecisionDouble
};

static const char * const qtscript_QSql_NumericalPrecisionPolicy_keys[] = {
    "HighPrecision"
    , "LowPrecisionInt32"
    , "LowPrecisionInt64"
    , "LowPrecisionDouble"
};

static QString qtscript_QSql_NumericalPrecisionPolicy_toStringHelper(QSql::NumericalPrecisionPolicy value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QSql_NumericalPrecisionPolicy_values[i] == value)
            return QString::fromLatin1(qtscript_QSql_NumericalPrecisionPolicy_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QSql_NumericalPrecisionPolicy_toScriptValue(QScriptEngine *engine, const QSql::NumericalPrecisionPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSql"));
    return clazz.property(qtscript_QSql_NumericalPrecisionPolicy_toStringHelper(value));
}

static void qtscript_QSql_NumericalPrecisionPolicy_fromScriptValue(const QScriptValue &value, QSql::NumericalPrecisionPolicy &out)
{
    out = qvariant_cast<QSql::NumericalPrecisionPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QSql_NumericalPrecisionPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QSql_NumericalPrecisionPolicy_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QSql::NumericalPrecisionPolicy>(arg));
    }
    return context->throwError(QString::fromLatin1("NumericalPrecisionPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSql_NumericalPrecisionPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSql::NumericalPrecisionPolicy value = qscriptvalue_cast<QSql::NumericalPrecisionPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSql_NumericalPrecisionPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSql::NumericalPrecisionPolicy value = qscriptvalue_cast<QSql::NumericalPrecisionPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QSql_NumericalPrecisionPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QSql_NumericalPrecisionPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSql_NumericalPrecisionPolicy,
        qtscript_QSql_NumericalPrecisionPolicy_valueOf, qtscript_QSql_NumericalPrecisionPolicy_toString);
    qScriptRegisterMetaType<QSql::NumericalPrecisionPolicy>(engine, qtscript_QSql_NumericalPrecisionPolicy_toScriptValue,
        qtscript_QSql_NumericalPrecisionPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSql_NumericalPrecisionPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSql_NumericalPrecisionPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSql::Location
//

static const QSql::Location qtscript_QSql_Location_values[] = {
    QSql::AfterLastRow
    , QSql::BeforeFirstRow
};

static const char * const qtscript_QSql_Location_keys[] = {
    "AfterLastRow"
    , "BeforeFirstRow"
};

static QString qtscript_QSql_Location_toStringHelper(QSql::Location value)
{
    if ((value >= QSql::AfterLastRow) && (value <= QSql::BeforeFirstRow))
        return qtscript_QSql_Location_keys[static_cast<int>(value)-static_cast<int>(QSql::AfterLastRow)];
    return QString();
}

static QScriptValue qtscript_QSql_Location_toScriptValue(QScriptEngine *engine, const QSql::Location &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSql"));
    return clazz.property(qtscript_QSql_Location_toStringHelper(value));
}

static void qtscript_QSql_Location_fromScriptValue(const QScriptValue &value, QSql::Location &out)
{
    out = qvariant_cast<QSql::Location>(value.toVariant());
}

static QScriptValue qtscript_construct_QSql_Location(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSql::AfterLastRow) && (arg <= QSql::BeforeFirstRow))
        return qScriptValueFromValue(engine,  static_cast<QSql::Location>(arg));
    return context->throwError(QString::fromLatin1("Location(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSql_Location_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSql::Location value = qscriptvalue_cast<QSql::Location>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSql_Location_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSql::Location value = qscriptvalue_cast<QSql::Location>(context->thisObject());
    return QScriptValue(engine, qtscript_QSql_Location_toStringHelper(value));
}

static QScriptValue qtscript_create_QSql_Location_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSql_Location,
        qtscript_QSql_Location_valueOf, qtscript_QSql_Location_toString);
    qScriptRegisterMetaType<QSql::Location>(engine, qtscript_QSql_Location_toScriptValue,
        qtscript_QSql_Location_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSql_Location_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSql_Location_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSql::ParamTypeFlag
//

static const QSql::ParamTypeFlag qtscript_QSql_ParamTypeFlag_values[] = {
    QSql::In
    , QSql::Out
    , QSql::InOut
    , QSql::Binary
};

static const char * const qtscript_QSql_ParamTypeFlag_keys[] = {
    "In"
    , "Out"
    , "InOut"
    , "Binary"
};

static QString qtscript_QSql_ParamTypeFlag_toStringHelper(QSql::ParamTypeFlag value)
{
    if ((value >= QSql::In) && (value <= QSql::Binary))
        return qtscript_QSql_ParamTypeFlag_keys[static_cast<int>(value)-static_cast<int>(QSql::In)];
    return QString();
}

static QScriptValue qtscript_QSql_ParamTypeFlag_toScriptValue(QScriptEngine *engine, const QSql::ParamTypeFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSql"));
    return clazz.property(qtscript_QSql_ParamTypeFlag_toStringHelper(value));
}

static void qtscript_QSql_ParamTypeFlag_fromScriptValue(const QScriptValue &value, QSql::ParamTypeFlag &out)
{
    out = qvariant_cast<QSql::ParamTypeFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QSql_ParamTypeFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSql::In) && (arg <= QSql::Binary))
        return qScriptValueFromValue(engine,  static_cast<QSql::ParamTypeFlag>(arg));
    return context->throwError(QString::fromLatin1("ParamTypeFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSql_ParamTypeFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSql::ParamTypeFlag value = qscriptvalue_cast<QSql::ParamTypeFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSql_ParamTypeFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSql::ParamTypeFlag value = qscriptvalue_cast<QSql::ParamTypeFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QSql_ParamTypeFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QSql_ParamTypeFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSql_ParamTypeFlag,
        qtscript_QSql_ParamTypeFlag_valueOf, qtscript_QSql_ParamTypeFlag_toString);
    qScriptRegisterMetaType<QSql::ParamTypeFlag>(engine, qtscript_QSql_ParamTypeFlag_toScriptValue,
        qtscript_QSql_ParamTypeFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSql_ParamTypeFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSql_ParamTypeFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSql::ParamType
//

static QScriptValue qtscript_QSql_ParamType_toScriptValue(QScriptEngine *engine, const QSql::ParamType &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QSql_ParamType_fromScriptValue(const QScriptValue &value, QSql::ParamType &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QSql::ParamType>())
        out = qvariant_cast<QSql::ParamType>(var);
    else if (var.userType() == qMetaTypeId<QSql::ParamTypeFlag>())
        out = qvariant_cast<QSql::ParamTypeFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QSql_ParamType(QScriptContext *context, QScriptEngine *engine)
{
    QSql::ParamType result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QSql::ParamType>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QSql::ParamTypeFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ParamType(): argument %0 is not of type ParamTypeFlag").arg(i));
            }
            result |= qvariant_cast<QSql::ParamTypeFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QSql_ParamType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSql::ParamType value = qscriptvalue_cast<QSql::ParamType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSql_ParamType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSql::ParamType value = qscriptvalue_cast<QSql::ParamType>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QSql_ParamTypeFlag_values[i]) == qtscript_QSql_ParamTypeFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QSql_ParamTypeFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QSql_ParamType_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QSql::ParamType>() == otherObj.value<QSql::ParamType>())));
}

static QScriptValue qtscript_create_QSql_ParamType_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QSql_ParamType, qtscript_QSql_ParamType_valueOf,
        qtscript_QSql_ParamType_toString, qtscript_QSql_ParamType_equals);
    qScriptRegisterMetaType<QSql::ParamType>(engine, qtscript_QSql_ParamType_toScriptValue,
        qtscript_QSql_ParamType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QSql::TableType
//

static const QSql::TableType qtscript_QSql_TableType_values[] = {
    QSql::Tables
    , QSql::SystemTables
    , QSql::Views
    , QSql::AllTables
};

static const char * const qtscript_QSql_TableType_keys[] = {
    "Tables"
    , "SystemTables"
    , "Views"
    , "AllTables"
};

static QString qtscript_QSql_TableType_toStringHelper(QSql::TableType value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QSql_TableType_values[i] == value)
            return QString::fromLatin1(qtscript_QSql_TableType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QSql_TableType_toScriptValue(QScriptEngine *engine, const QSql::TableType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSql"));
    return clazz.property(qtscript_QSql_TableType_toStringHelper(value));
}

static void qtscript_QSql_TableType_fromScriptValue(const QScriptValue &value, QSql::TableType &out)
{
    out = qvariant_cast<QSql::TableType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSql_TableType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QSql_TableType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QSql::TableType>(arg));
    }
    return context->throwError(QString::fromLatin1("TableType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSql_TableType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSql::TableType value = qscriptvalue_cast<QSql::TableType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSql_TableType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSql::TableType value = qscriptvalue_cast<QSql::TableType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSql_TableType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSql_TableType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSql_TableType,
        qtscript_QSql_TableType_valueOf, qtscript_QSql_TableType_toString);
    qScriptRegisterMetaType<QSql::TableType>(engine, qtscript_QSql_TableType_toScriptValue,
        qtscript_QSql_TableType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSql_TableType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSql_TableType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSql
//

static QScriptValue qtscript_QSql_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QSql cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSql_throw_ambiguity_error_helper(context,
        qtscript_QSql_function_names[_id],
        qtscript_QSql_function_signatures[_id]);
}

QScriptValue qtscript_create_QSql_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_QSql_static_call, proto, qtscript_QSql_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("NumericalPrecisionPolicy"),
        qtscript_create_QSql_NumericalPrecisionPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Location"),
        qtscript_create_QSql_Location_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ParamTypeFlag"),
        qtscript_create_QSql_ParamTypeFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ParamType"),
        qtscript_create_QSql_ParamType_class(engine));
    ctor.setProperty(QString::fromLatin1("TableType"),
        qtscript_create_QSql_TableType_class(engine, ctor));
    return ctor;
}
