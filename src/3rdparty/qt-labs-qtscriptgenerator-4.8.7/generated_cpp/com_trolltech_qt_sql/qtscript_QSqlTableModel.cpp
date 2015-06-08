#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqltablemodel.h>
#include <QSize>
#include <QSqlIndex>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qstringlist.h>

#include "qtscriptshell_QSqlTableModel.h"

static const char * const qtscript_QSqlTableModel_function_names[] = {
    "QSqlTableModel"
    // static
    // prototype
    , "database"
    , "editStrategy"
    , "fieldIndex"
    , "filter"
    , "insertRecord"
    , "isDirty"
    , "primaryKey"
    , "revertRow"
    , "select"
    , "setEditStrategy"
    , "setFilter"
    , "setRecord"
    , "setSort"
    , "setTable"
    , "tableName"
    , "toString"
};

static const char * const qtscript_QSqlTableModel_function_signatures[] = {
    "QObject parent, QSqlDatabase db"
    // static
    // prototype
    , ""
    , ""
    , "String fieldName"
    , ""
    , "int row, QSqlRecord record"
    , "QModelIndex index"
    , ""
    , "int row"
    , ""
    , "EditStrategy strategy"
    , "String filter"
    , "int row, QSqlRecord record"
    , "int column, SortOrder order"
    , "String tableName"
    , ""
""
};

static const int qtscript_QSqlTableModel_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 2
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 2
    , 2
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QSqlTableModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlTableModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlTableModel*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlTableModel*)
Q_DECLARE_METATYPE(QSqlTableModel::EditStrategy)
Q_DECLARE_METATYPE(QSqlDatabase)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QSqlIndex)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QSqlQueryModel*)

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
// QSqlTableModel::EditStrategy
//

static const QSqlTableModel::EditStrategy qtscript_QSqlTableModel_EditStrategy_values[] = {
    QSqlTableModel::OnFieldChange
    , QSqlTableModel::OnRowChange
    , QSqlTableModel::OnManualSubmit
};

static const char * const qtscript_QSqlTableModel_EditStrategy_keys[] = {
    "OnFieldChange"
    , "OnRowChange"
    , "OnManualSubmit"
};

static QString qtscript_QSqlTableModel_EditStrategy_toStringHelper(QSqlTableModel::EditStrategy value)
{
    if ((value >= QSqlTableModel::OnFieldChange) && (value <= QSqlTableModel::OnManualSubmit))
        return qtscript_QSqlTableModel_EditStrategy_keys[static_cast<int>(value)-static_cast<int>(QSqlTableModel::OnFieldChange)];
    return QString();
}

static QScriptValue qtscript_QSqlTableModel_EditStrategy_toScriptValue(QScriptEngine *engine, const QSqlTableModel::EditStrategy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlTableModel"));
    return clazz.property(qtscript_QSqlTableModel_EditStrategy_toStringHelper(value));
}

static void qtscript_QSqlTableModel_EditStrategy_fromScriptValue(const QScriptValue &value, QSqlTableModel::EditStrategy &out)
{
    out = qvariant_cast<QSqlTableModel::EditStrategy>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlTableModel_EditStrategy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlTableModel::OnFieldChange) && (arg <= QSqlTableModel::OnManualSubmit))
        return qScriptValueFromValue(engine,  static_cast<QSqlTableModel::EditStrategy>(arg));
    return context->throwError(QString::fromLatin1("EditStrategy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlTableModel_EditStrategy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlTableModel::EditStrategy value = qscriptvalue_cast<QSqlTableModel::EditStrategy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlTableModel_EditStrategy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlTableModel::EditStrategy value = qscriptvalue_cast<QSqlTableModel::EditStrategy>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlTableModel_EditStrategy_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlTableModel_EditStrategy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlTableModel_EditStrategy,
        qtscript_QSqlTableModel_EditStrategy_valueOf, qtscript_QSqlTableModel_EditStrategy_toString);
    qScriptRegisterMetaType<QSqlTableModel::EditStrategy>(engine, qtscript_QSqlTableModel_EditStrategy_toScriptValue,
        qtscript_QSqlTableModel_EditStrategy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlTableModel_EditStrategy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlTableModel_EditStrategy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlTableModel
//

static QScriptValue qtscript_QSqlTableModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 15;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlTableModel* _q_self = qscriptvalue_cast<QSqlTableModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlTableModel.%0(): this object is not a QSqlTableModel")
            .arg(qtscript_QSqlTableModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSqlDatabase _q_result = _q_self->database();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSqlTableModel::EditStrategy _q_result = _q_self->editStrategy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->fieldIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->filter();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlRecord _q_arg1 = qscriptvalue_cast<QSqlRecord>(context->argument(1));
        bool _q_result = _q_self->insertRecord(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->isDirty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QSqlIndex _q_result = _q_self->primaryKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->revertRow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->select();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QSqlTableModel::EditStrategy _q_arg0 = qscriptvalue_cast<QSqlTableModel::EditStrategy>(context->argument(0));
        _q_self->setEditStrategy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlRecord _q_arg1 = qscriptvalue_cast<QSqlRecord>(context->argument(1));
        bool _q_result = _q_self->setRecord(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->setSort(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setTable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->tableName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15: {
    QString result = QString::fromLatin1("QSqlTableModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlTableModel_throw_ambiguity_error_helper(context,
        qtscript_QSqlTableModel_function_names[_id+1],
        qtscript_QSqlTableModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlTableModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlTableModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSqlTableModel* _q_cpp_result = new QtScriptShell_QSqlTableModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSqlTableModel* _q_cpp_result = new QtScriptShell_QSqlTableModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QSqlDatabase _q_arg1 = qscriptvalue_cast<QSqlDatabase>(context->argument(1));
        QtScriptShell_QSqlTableModel* _q_cpp_result = new QtScriptShell_QSqlTableModel(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlTableModel_throw_ambiguity_error_helper(context,
        qtscript_QSqlTableModel_function_names[_id],
        qtscript_QSqlTableModel_function_signatures[_id]);
}

static QScriptValue qtscript_QSqlTableModel_toScriptValue(QScriptEngine *engine, QSqlTableModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSqlTableModel_fromScriptValue(const QScriptValue &value, QSqlTableModel* &out)
{
    out = qobject_cast<QSqlTableModel*>(value.toQObject());
}

QScriptValue qtscript_create_QSqlTableModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlTableModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlTableModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QSqlQueryModel*>()));
    for (int i = 0; i < 16; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlTableModel_prototype_call, qtscript_QSqlTableModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlTableModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSqlTableModel*>(engine, qtscript_QSqlTableModel_toScriptValue, 
        qtscript_QSqlTableModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlTableModel_static_call, proto, qtscript_QSqlTableModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("EditStrategy"),
        qtscript_create_QSqlTableModel_EditStrategy_class(engine, ctor));
    return ctor;
}
