#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsqldriver.h>
#include <QSize>
#include <QSqlError>
#include <QSqlIndex>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlfield.h>
#include <qsqlindex.h>
#include <qsqlrecord.h>
#include <qsqlresult.h>
#include <qstringlist.h>

#include "qtscriptshell_QSqlDriver.h"

static const char * const qtscript_QSqlDriver_function_names[] = {
    "QSqlDriver"
    // static
    // prototype
    , "beginTransaction"
    , "close"
    , "commitTransaction"
    , "createResult"
    , "escapeIdentifier"
    , "formatValue"
    , "handle"
    , "hasFeature"
    , "isIdentifierEscaped"
    , "isOpen"
    , "isOpenError"
    , "lastError"
    , "numericalPrecisionPolicy"
    , "open"
    , "primaryIndex"
    , "record"
    , "rollbackTransaction"
    , "setNumericalPrecisionPolicy"
    , "sqlStatement"
    , "stripDelimiters"
    , "subscribeToNotification"
    , "subscribedToNotifications"
    , "tables"
    , "unsubscribeFromNotification"
    , "toString"
};

static const char * const qtscript_QSqlDriver_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "String identifier, IdentifierType type"
    , "QSqlField field, bool trimStrings"
    , ""
    , "DriverFeature f"
    , "String identifier, IdentifierType type"
    , ""
    , ""
    , ""
    , ""
    , "String db, String user, String password, String host, int port, String connOpts"
    , "String tableName"
    , "String tableName"
    , ""
    , "NumericalPrecisionPolicy precisionPolicy"
    , "StatementType type, String tableName, QSqlRecord rec, bool preparedStatement"
    , "String identifier, IdentifierType type"
    , "String name"
    , ""
    , "TableType tableType"
    , "String name"
""
};

static const int qtscript_QSqlDriver_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 2
    , 2
    , 0
    , 1
    , 2
    , 0
    , 0
    , 0
    , 0
    , 6
    , 1
    , 1
    , 0
    , 1
    , 4
    , 2
    , 1
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QSqlDriver_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlDriver::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlDriver*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlDriver*)
Q_DECLARE_METATYPE(QSqlDriver::DriverFeature)
Q_DECLARE_METATYPE(QSqlDriver::StatementType)
Q_DECLARE_METATYPE(QSqlDriver::IdentifierType)
Q_DECLARE_METATYPE(QSqlResult*)
Q_DECLARE_METATYPE(QSqlField)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSql::NumericalPrecisionPolicy)
Q_DECLARE_METATYPE(QSqlIndex)
Q_DECLARE_METATYPE(QSqlRecord)
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

//
// QSqlDriver::DriverFeature
//

static const QSqlDriver::DriverFeature qtscript_QSqlDriver_DriverFeature_values[] = {
    QSqlDriver::Transactions
    , QSqlDriver::QuerySize
    , QSqlDriver::BLOB
    , QSqlDriver::Unicode
    , QSqlDriver::PreparedQueries
    , QSqlDriver::NamedPlaceholders
    , QSqlDriver::PositionalPlaceholders
    , QSqlDriver::LastInsertId
    , QSqlDriver::BatchOperations
    , QSqlDriver::SimpleLocking
    , QSqlDriver::LowPrecisionNumbers
    , QSqlDriver::EventNotifications
    , QSqlDriver::FinishQuery
    , QSqlDriver::MultipleResultSets
    , QSqlDriver::CancelQuery
};

static const char * const qtscript_QSqlDriver_DriverFeature_keys[] = {
    "Transactions"
    , "QuerySize"
    , "BLOB"
    , "Unicode"
    , "PreparedQueries"
    , "NamedPlaceholders"
    , "PositionalPlaceholders"
    , "LastInsertId"
    , "BatchOperations"
    , "SimpleLocking"
    , "LowPrecisionNumbers"
    , "EventNotifications"
    , "FinishQuery"
    , "MultipleResultSets"
    , "CancelQuery"
};

static QString qtscript_QSqlDriver_DriverFeature_toStringHelper(QSqlDriver::DriverFeature value)
{
    if ((value >= QSqlDriver::Transactions) && (value <= QSqlDriver::CancelQuery))
        return qtscript_QSqlDriver_DriverFeature_keys[static_cast<int>(value)-static_cast<int>(QSqlDriver::Transactions)];
    return QString();
}

static QScriptValue qtscript_QSqlDriver_DriverFeature_toScriptValue(QScriptEngine *engine, const QSqlDriver::DriverFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlDriver"));
    return clazz.property(qtscript_QSqlDriver_DriverFeature_toStringHelper(value));
}

static void qtscript_QSqlDriver_DriverFeature_fromScriptValue(const QScriptValue &value, QSqlDriver::DriverFeature &out)
{
    out = qvariant_cast<QSqlDriver::DriverFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlDriver_DriverFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlDriver::Transactions) && (arg <= QSqlDriver::CancelQuery))
        return qScriptValueFromValue(engine,  static_cast<QSqlDriver::DriverFeature>(arg));
    return context->throwError(QString::fromLatin1("DriverFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlDriver_DriverFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlDriver::DriverFeature value = qscriptvalue_cast<QSqlDriver::DriverFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlDriver_DriverFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlDriver::DriverFeature value = qscriptvalue_cast<QSqlDriver::DriverFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlDriver_DriverFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlDriver_DriverFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlDriver_DriverFeature,
        qtscript_QSqlDriver_DriverFeature_valueOf, qtscript_QSqlDriver_DriverFeature_toString);
    qScriptRegisterMetaType<QSqlDriver::DriverFeature>(engine, qtscript_QSqlDriver_DriverFeature_toScriptValue,
        qtscript_QSqlDriver_DriverFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlDriver_DriverFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlDriver_DriverFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlDriver::StatementType
//

static const QSqlDriver::StatementType qtscript_QSqlDriver_StatementType_values[] = {
    QSqlDriver::WhereStatement
    , QSqlDriver::SelectStatement
    , QSqlDriver::UpdateStatement
    , QSqlDriver::InsertStatement
    , QSqlDriver::DeleteStatement
};

static const char * const qtscript_QSqlDriver_StatementType_keys[] = {
    "WhereStatement"
    , "SelectStatement"
    , "UpdateStatement"
    , "InsertStatement"
    , "DeleteStatement"
};

static QString qtscript_QSqlDriver_StatementType_toStringHelper(QSqlDriver::StatementType value)
{
    if ((value >= QSqlDriver::WhereStatement) && (value <= QSqlDriver::DeleteStatement))
        return qtscript_QSqlDriver_StatementType_keys[static_cast<int>(value)-static_cast<int>(QSqlDriver::WhereStatement)];
    return QString();
}

static QScriptValue qtscript_QSqlDriver_StatementType_toScriptValue(QScriptEngine *engine, const QSqlDriver::StatementType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlDriver"));
    return clazz.property(qtscript_QSqlDriver_StatementType_toStringHelper(value));
}

static void qtscript_QSqlDriver_StatementType_fromScriptValue(const QScriptValue &value, QSqlDriver::StatementType &out)
{
    out = qvariant_cast<QSqlDriver::StatementType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlDriver_StatementType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlDriver::WhereStatement) && (arg <= QSqlDriver::DeleteStatement))
        return qScriptValueFromValue(engine,  static_cast<QSqlDriver::StatementType>(arg));
    return context->throwError(QString::fromLatin1("StatementType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlDriver_StatementType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlDriver::StatementType value = qscriptvalue_cast<QSqlDriver::StatementType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlDriver_StatementType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlDriver::StatementType value = qscriptvalue_cast<QSqlDriver::StatementType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlDriver_StatementType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlDriver_StatementType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlDriver_StatementType,
        qtscript_QSqlDriver_StatementType_valueOf, qtscript_QSqlDriver_StatementType_toString);
    qScriptRegisterMetaType<QSqlDriver::StatementType>(engine, qtscript_QSqlDriver_StatementType_toScriptValue,
        qtscript_QSqlDriver_StatementType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlDriver_StatementType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlDriver_StatementType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlDriver::IdentifierType
//

static const QSqlDriver::IdentifierType qtscript_QSqlDriver_IdentifierType_values[] = {
    QSqlDriver::FieldName
    , QSqlDriver::TableName
};

static const char * const qtscript_QSqlDriver_IdentifierType_keys[] = {
    "FieldName"
    , "TableName"
};

static QString qtscript_QSqlDriver_IdentifierType_toStringHelper(QSqlDriver::IdentifierType value)
{
    if ((value >= QSqlDriver::FieldName) && (value <= QSqlDriver::TableName))
        return qtscript_QSqlDriver_IdentifierType_keys[static_cast<int>(value)-static_cast<int>(QSqlDriver::FieldName)];
    return QString();
}

static QScriptValue qtscript_QSqlDriver_IdentifierType_toScriptValue(QScriptEngine *engine, const QSqlDriver::IdentifierType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlDriver"));
    return clazz.property(qtscript_QSqlDriver_IdentifierType_toStringHelper(value));
}

static void qtscript_QSqlDriver_IdentifierType_fromScriptValue(const QScriptValue &value, QSqlDriver::IdentifierType &out)
{
    out = qvariant_cast<QSqlDriver::IdentifierType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlDriver_IdentifierType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlDriver::FieldName) && (arg <= QSqlDriver::TableName))
        return qScriptValueFromValue(engine,  static_cast<QSqlDriver::IdentifierType>(arg));
    return context->throwError(QString::fromLatin1("IdentifierType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlDriver_IdentifierType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlDriver::IdentifierType value = qscriptvalue_cast<QSqlDriver::IdentifierType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlDriver_IdentifierType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlDriver::IdentifierType value = qscriptvalue_cast<QSqlDriver::IdentifierType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlDriver_IdentifierType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlDriver_IdentifierType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlDriver_IdentifierType,
        qtscript_QSqlDriver_IdentifierType_valueOf, qtscript_QSqlDriver_IdentifierType_toString);
    qScriptRegisterMetaType<QSqlDriver::IdentifierType>(engine, qtscript_QSqlDriver_IdentifierType_toScriptValue,
        qtscript_QSqlDriver_IdentifierType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlDriver_IdentifierType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlDriver_IdentifierType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlDriver
//

static QScriptValue qtscript_QSqlDriver_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlDriver* _q_self = qscriptvalue_cast<QSqlDriver*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlDriver.%0(): this object is not a QSqlDriver")
            .arg(qtscript_QSqlDriver_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->beginTransaction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->close();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->commitTransaction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSqlResult* _q_result = _q_self->createResult();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDriver::IdentifierType _q_arg1 = qscriptvalue_cast<QSqlDriver::IdentifierType>(context->argument(1));
        QString _q_result = _q_self->escapeIdentifier(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QSqlField _q_arg0 = qscriptvalue_cast<QSqlField>(context->argument(0));
        QString _q_result = _q_self->formatValue(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QSqlField _q_arg0 = qscriptvalue_cast<QSqlField>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        QString _q_result = _q_self->formatValue(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QSqlDriver::DriverFeature _q_arg0 = qscriptvalue_cast<QSqlDriver::DriverFeature>(context->argument(0));
        bool _q_result = _q_self->hasFeature(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDriver::IdentifierType _q_arg1 = qscriptvalue_cast<QSqlDriver::IdentifierType>(context->argument(1));
        bool _q_result = _q_self->isIdentifierEscaped(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isOpen();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isOpenError();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QSqlError _q_result = _q_self->lastError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QSql::NumericalPrecisionPolicy _q_result = _q_self->numericalPrecisionPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->open(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->open(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        bool _q_result = _q_self->open(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        bool _q_result = _q_self->open(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->open(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 6) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        int _q_arg4 = context->argument(4).toInt32();
        QString _q_arg5 = context->argument(5).toString();
        bool _q_result = _q_self->open(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlIndex _q_result = _q_self->primaryIndex(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlRecord _q_result = _q_self->record(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->rollbackTransaction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QSql::NumericalPrecisionPolicy _q_arg0 = qscriptvalue_cast<QSql::NumericalPrecisionPolicy>(context->argument(0));
        _q_self->setNumericalPrecisionPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 4) {
        QSqlDriver::StatementType _q_arg0 = qscriptvalue_cast<QSqlDriver::StatementType>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QSqlRecord _q_arg2 = qscriptvalue_cast<QSqlRecord>(context->argument(2));
        bool _q_arg3 = context->argument(3).toBoolean();
        QString _q_result = _q_self->sqlStatement(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDriver::IdentifierType _q_arg1 = qscriptvalue_cast<QSqlDriver::IdentifierType>(context->argument(1));
        QString _q_result = _q_self->stripDelimiters(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->subscribeToNotification(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->subscribedToNotifications();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QSql::TableType _q_arg0 = qscriptvalue_cast<QSql::TableType>(context->argument(0));
        QStringList _q_result = _q_self->tables(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->unsubscribeFromNotification(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24: {
    QString result = QString::fromLatin1("QSqlDriver");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlDriver_throw_ambiguity_error_helper(context,
        qtscript_QSqlDriver_function_names[_id+1],
        qtscript_QSqlDriver_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlDriver_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlDriver(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSqlDriver* _q_cpp_result = new QtScriptShell_QSqlDriver();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlDriver*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSqlDriver* _q_cpp_result = new QtScriptShell_QSqlDriver(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlDriver*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlDriver_throw_ambiguity_error_helper(context,
        qtscript_QSqlDriver_function_names[_id],
        qtscript_QSqlDriver_function_signatures[_id]);
}

static QScriptValue qtscript_QSqlDriver_toScriptValue(QScriptEngine *engine, QSqlDriver* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSqlDriver_fromScriptValue(const QScriptValue &value, QSqlDriver* &out)
{
    out = qobject_cast<QSqlDriver*>(value.toQObject());
}

QScriptValue qtscript_create_QSqlDriver_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlDriver*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlDriver*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlDriver_prototype_call, qtscript_QSqlDriver_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlDriver_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSqlDriver*>(engine, qtscript_QSqlDriver_toScriptValue, 
        qtscript_QSqlDriver_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlDriver_static_call, proto, qtscript_QSqlDriver_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("DriverFeature"),
        qtscript_create_QSqlDriver_DriverFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StatementType"),
        qtscript_create_QSqlDriver_StatementType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("IdentifierType"),
        qtscript_create_QSqlDriver_IdentifierType_class(engine, ctor));
    return ctor;
}
