#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsqlquery.h>
#include <QSize>
#include <QSqlError>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qsqldatabase.h>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qsqlresult.h>

static const char * const qtscript_QSqlQuery_function_names[] = {
    "QSqlQuery"
    // static
    // prototype
    , "addBindValue"
    , "at"
    , "bindValue"
    , "boundValue"
    , "boundValues"
    , "clear"
    , "driver"
    , "exec"
    , "execBatch"
    , "executedQuery"
    , "finish"
    , "first"
    , "isActive"
    , "isForwardOnly"
    , "isNull"
    , "isSelect"
    , "isValid"
    , "last"
    , "lastError"
    , "lastInsertId"
    , "lastQuery"
    , "next"
    , "nextResult"
    , "numRowsAffected"
    , "numericalPrecisionPolicy"
    , "prepare"
    , "previous"
    , "record"
    , "result"
    , "seek"
    , "setForwardOnly"
    , "setNumericalPrecisionPolicy"
    , "size"
    , "value"
    , "toString"
};

static const char * const qtscript_QSqlQuery_function_signatures[] = {
    "QSqlDatabase db\nQSqlResult r\nQSqlQuery other\nString query, QSqlDatabase db"
    // static
    // prototype
    , "Object val, ParamType type"
    , ""
    , "String placeholder, Object val, ParamType type\nint pos, Object val, ParamType type"
    , "String placeholder\nint pos"
    , ""
    , ""
    , ""
    , "\nString query"
    , "BatchExecutionMode mode"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String name\nint field"
    , ""
    , ""
    , ""
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
    , "int i, bool relative"
    , "bool forward"
    , "NumericalPrecisionPolicy precisionPolicy"
    , ""
    , "String name\nint i"
""
};

static const int qtscript_QSqlQuery_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 0
    , 3
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
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
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QSqlQuery_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlQuery::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlQuery)
Q_DECLARE_METATYPE(QSqlQuery*)
Q_DECLARE_METATYPE(QSqlQuery::BatchExecutionMode)
Q_DECLARE_METATYPE(QFlags<QSql::ParamTypeFlag>)
Q_DECLARE_METATYPE(const QSqlDriver*)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSql::NumericalPrecisionPolicy)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(const QSqlResult*)
Q_DECLARE_METATYPE(QSqlDatabase)
Q_DECLARE_METATYPE(QSqlResult*)

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
// QSqlQuery::BatchExecutionMode
//

static const QSqlQuery::BatchExecutionMode qtscript_QSqlQuery_BatchExecutionMode_values[] = {
    QSqlQuery::ValuesAsRows
    , QSqlQuery::ValuesAsColumns
};

static const char * const qtscript_QSqlQuery_BatchExecutionMode_keys[] = {
    "ValuesAsRows"
    , "ValuesAsColumns"
};

static QString qtscript_QSqlQuery_BatchExecutionMode_toStringHelper(QSqlQuery::BatchExecutionMode value)
{
    if ((value >= QSqlQuery::ValuesAsRows) && (value <= QSqlQuery::ValuesAsColumns))
        return qtscript_QSqlQuery_BatchExecutionMode_keys[static_cast<int>(value)-static_cast<int>(QSqlQuery::ValuesAsRows)];
    return QString();
}

static QScriptValue qtscript_QSqlQuery_BatchExecutionMode_toScriptValue(QScriptEngine *engine, const QSqlQuery::BatchExecutionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlQuery"));
    return clazz.property(qtscript_QSqlQuery_BatchExecutionMode_toStringHelper(value));
}

static void qtscript_QSqlQuery_BatchExecutionMode_fromScriptValue(const QScriptValue &value, QSqlQuery::BatchExecutionMode &out)
{
    out = qvariant_cast<QSqlQuery::BatchExecutionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlQuery_BatchExecutionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlQuery::ValuesAsRows) && (arg <= QSqlQuery::ValuesAsColumns))
        return qScriptValueFromValue(engine,  static_cast<QSqlQuery::BatchExecutionMode>(arg));
    return context->throwError(QString::fromLatin1("BatchExecutionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlQuery_BatchExecutionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlQuery::BatchExecutionMode value = qscriptvalue_cast<QSqlQuery::BatchExecutionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlQuery_BatchExecutionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlQuery::BatchExecutionMode value = qscriptvalue_cast<QSqlQuery::BatchExecutionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlQuery_BatchExecutionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlQuery_BatchExecutionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlQuery_BatchExecutionMode,
        qtscript_QSqlQuery_BatchExecutionMode_valueOf, qtscript_QSqlQuery_BatchExecutionMode_toString);
    qScriptRegisterMetaType<QSqlQuery::BatchExecutionMode>(engine, qtscript_QSqlQuery_BatchExecutionMode_toScriptValue,
        qtscript_QSqlQuery_BatchExecutionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlQuery_BatchExecutionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlQuery_BatchExecutionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlQuery
//

static QScriptValue qtscript_QSqlQuery_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 34;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlQuery* _q_self = qscriptvalue_cast<QSqlQuery*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlQuery.%0(): this object is not a QSqlQuery")
            .arg(qtscript_QSqlQuery_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->addBindValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        QFlags<QSql::ParamTypeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QSql::ParamTypeFlag> >(context->argument(1));
        _q_self->addBindValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->at();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && true) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_arg1 = context->argument(1).toVariant();
            _q_self->bindValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && true) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_arg1 = context->argument(1).toVariant();
            _q_self->bindValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && true
            && (qMetaTypeId<QFlags<QSql::ParamTypeFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_arg1 = context->argument(1).toVariant();
            QFlags<QSql::ParamTypeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QSql::ParamTypeFlag> >(context->argument(2));
            _q_self->bindValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && true
            && (qMetaTypeId<QFlags<QSql::ParamTypeFlag> >() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_arg1 = context->argument(1).toVariant();
            QFlags<QSql::ParamTypeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QSql::ParamTypeFlag> >(context->argument(2));
            _q_self->bindValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_result = _q_self->boundValue(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_result = _q_self->boundValue(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QMap<QString,QVariant > _q_result = _q_self->boundValues();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        const QSqlDriver* _q_result = const_cast<const QSqlDriver*>(_q_self->driver());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exec();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->exec(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->execBatch();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QSqlQuery::BatchExecutionMode _q_arg0 = qscriptvalue_cast<QSqlQuery::BatchExecutionMode>(context->argument(0));
        bool _q_result = _q_self->execBatch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->executedQuery();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        _q_self->finish();
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->first();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isForwardOnly();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->isNull(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            bool _q_result = _q_self->isNull(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSelect();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->last();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QSqlError _q_result = _q_self->lastError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->lastInsertId();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->lastQuery();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->next();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->nextResult();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->numRowsAffected();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QSql::NumericalPrecisionPolicy _q_result = _q_self->numericalPrecisionPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->prepare(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->previous();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QSqlRecord _q_result = _q_self->record();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        const QSqlResult* _q_result = const_cast<const QSqlResult*>(_q_self->result());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->seek(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        bool _q_result = _q_self->seek(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setForwardOnly(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QSql::NumericalPrecisionPolicy _q_arg0 = qscriptvalue_cast<QSql::NumericalPrecisionPolicy>(context->argument(0));
        _q_self->setNumericalPrecisionPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_result = _q_self->value(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_result = _q_self->value(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 34: {
    QString result = QString::fromLatin1("QSqlQuery");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlQuery_throw_ambiguity_error_helper(context,
        qtscript_QSqlQuery_function_names[_id+1],
        qtscript_QSqlQuery_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlQuery_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlQuery(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSqlQuery _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSqlDatabase>() == context->argument(0).toVariant().userType())) {
            QSqlDatabase _q_arg0 = qscriptvalue_cast<QSqlDatabase>(context->argument(0));
            QSqlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QSqlResult*>(context->argument(0))) {
            QSqlResult* _q_arg0 = qscriptvalue_cast<QSqlResult*>(context->argument(0));
            QSqlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QSqlQuery>() == context->argument(0).toVariant().userType())) {
            QSqlQuery _q_arg0 = qscriptvalue_cast<QSqlQuery>(context->argument(0));
            QSqlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QSqlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDatabase _q_arg1 = qscriptvalue_cast<QSqlDatabase>(context->argument(1));
        QSqlQuery _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlQuery_throw_ambiguity_error_helper(context,
        qtscript_QSqlQuery_function_names[_id],
        qtscript_QSqlQuery_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlQuery_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlQuery*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlQuery*)0));
    for (int i = 0; i < 35; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlQuery_prototype_call, qtscript_QSqlQuery_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlQuery_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlQuery>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlQuery*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlQuery_static_call, proto, qtscript_QSqlQuery_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("BatchExecutionMode"),
        qtscript_create_QSqlQuery_BatchExecutionMode_class(engine, ctor));
    return ctor;
}
