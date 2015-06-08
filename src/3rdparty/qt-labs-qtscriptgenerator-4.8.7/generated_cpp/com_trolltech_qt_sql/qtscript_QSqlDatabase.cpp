#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqldatabase.h>
#include <QSize>
#include <QSqlError>
#include <QSqlIndex>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qsqldatabase.h>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qstringlist.h>

#include "qtscriptshell_QSqlDatabase.h"

static const char * const qtscript_QSqlDatabase_function_names[] = {
    "QSqlDatabase"
    // static
    , "addDatabase"
    , "cloneDatabase"
    , "connectionNames"
    , "contains"
    , "database"
    , "drivers"
    , "isDriverAvailable"
    , "registerSqlDriver"
    , "removeDatabase"
    // prototype
    , "close"
    , "commit"
    , "connectOptions"
    , "connectionName"
    , "databaseName"
    , "driver"
    , "driverName"
    , "exec"
    , "hostName"
    , "isOpen"
    , "isOpenError"
    , "isValid"
    , "lastError"
    , "numericalPrecisionPolicy"
    , "open"
    , "password"
    , "port"
    , "primaryIndex"
    , "record"
    , "rollback"
    , "setConnectOptions"
    , "setDatabaseName"
    , "setHostName"
    , "setNumericalPrecisionPolicy"
    , "setPassword"
    , "setPort"
    , "setUserName"
    , "tables"
    , "transaction"
    , "userName"
    , "toString"
};

static const char * const qtscript_QSqlDatabase_function_signatures[] = {
    "\nQSqlDatabase other"
    // static
    , "QSqlDriver driver, String connectionName\nString type, String connectionName"
    , "QSqlDatabase other, String connectionName"
    , ""
    , "String connectionName"
    , "String connectionName, bool open"
    , ""
    , "String name"
    , "String name, QSqlDriverCreatorBase creator"
    , "String connectionName"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String query"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "\nString user, String password"
    , ""
    , ""
    , "String tablename"
    , "String tablename"
    , ""
    , "String options"
    , "String name"
    , "String host"
    , "NumericalPrecisionPolicy precisionPolicy"
    , "String password"
    , "int p"
    , "String name"
    , "TableType type"
    , ""
    , ""
""
};

static const int qtscript_QSqlDatabase_function_lengths[] = {
    1
    // static
    , 2
    , 2
    , 0
    , 1
    , 2
    , 0
    , 1
    , 2
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSqlDatabase_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlDatabase::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlDatabase)
Q_DECLARE_METATYPE(QSqlDatabase*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlDatabase)
Q_DECLARE_METATYPE(QtScriptShell_QSqlDatabase*)
Q_DECLARE_METATYPE(QSqlDriver*)
Q_DECLARE_METATYPE(QSqlQuery)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSql::NumericalPrecisionPolicy)
Q_DECLARE_METATYPE(QSqlIndex)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSql::TableType)
Q_DECLARE_METATYPE(QSqlDriverCreatorBase*)

//
// QSqlDatabase
//

static QScriptValue qtscript_QSqlDatabase_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 30;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlDatabase* _q_self = qscriptvalue_cast<QSqlDatabase*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlDatabase.%0(): this object is not a QSqlDatabase")
            .arg(qtscript_QSqlDatabase_function_names[_id+10]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->close();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->commit();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->connectOptions();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->connectionName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->databaseName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QSqlDriver* _q_result = _q_self->driver();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->driverName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QSqlQuery _q_result = _q_self->exec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlQuery _q_result = _q_self->exec(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->hostName();
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
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QSqlError _q_result = _q_self->lastError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QSql::NumericalPrecisionPolicy _q_result = _q_self->numericalPrecisionPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->open();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->open(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->password();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->port();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlIndex _q_result = _q_self->primaryIndex(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlRecord _q_result = _q_self->record(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->rollback();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->setConnectOptions();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setConnectOptions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDatabaseName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHostName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QSql::NumericalPrecisionPolicy _q_arg0 = qscriptvalue_cast<QSql::NumericalPrecisionPolicy>(context->argument(0));
        _q_self->setNumericalPrecisionPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPassword(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUserName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->tables();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QSql::TableType _q_arg0 = qscriptvalue_cast<QSql::TableType>(context->argument(0));
        QStringList _q_result = _q_self->tables(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->transaction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->userName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlDatabase_throw_ambiguity_error_helper(context,
        qtscript_QSqlDatabase_function_names[_id+10],
        qtscript_QSqlDatabase_function_signatures[_id+10]);
}

static QScriptValue qtscript_QSqlDatabase_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlDatabase(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSqlDatabase _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSqlDatabase)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QSqlDatabase _q_arg0 = qscriptvalue_cast<QSqlDatabase>(context->argument(0));
        QtScriptShell_QSqlDatabase _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSqlDatabase)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QSqlDriver*>(context->argument(0))
            && context->argument(1).isString()) {
            QSqlDriver* _q_arg0 = qscriptvalue_cast<QSqlDriver*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QSqlDatabase _q_result = QSqlDatabase::addDatabase(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QSqlDatabase _q_result = QSqlDatabase::addDatabase(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QSqlDatabase _q_arg0 = qscriptvalue_cast<QSqlDatabase>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QSqlDatabase _q_result = QSqlDatabase::cloneDatabase(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QSqlDatabase::connectionNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QSqlDatabase::contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDatabase _q_result = QSqlDatabase::database(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_arg1 = context->argument(1).toBoolean();
        QSqlDatabase _q_result = QSqlDatabase::database(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QSqlDatabase::drivers();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QSqlDatabase::isDriverAvailable(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDriverCreatorBase* _q_arg1 = qscriptvalue_cast<QSqlDriverCreatorBase*>(context->argument(1));
        QSqlDatabase::registerSqlDriver(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDatabase::removeDatabase(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlDatabase_throw_ambiguity_error_helper(context,
        qtscript_QSqlDatabase_function_names[_id],
        qtscript_QSqlDatabase_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlDatabase_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlDatabase*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlDatabase*)0));
    for (int i = 0; i < 31; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlDatabase_prototype_call, qtscript_QSqlDatabase_function_lengths[i+10]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlDatabase_function_names[i+10]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlDatabase>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlDatabase*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlDatabase_static_call, proto, qtscript_QSqlDatabase_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlDatabase_static_call,
            qtscript_QSqlDatabase_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSqlDatabase_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
