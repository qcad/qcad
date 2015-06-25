#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsqlquerymodel.h>
#include <QSize>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qstringlist.h>
#include <qvector.h>

#include "qtscriptshell_QSqlQueryModel.h"

static const char * const qtscript_QSqlQueryModel_function_names[] = {
    "QSqlQueryModel"
    // static
    // prototype
    , "clear"
    , "lastError"
    , "query"
    , "record"
    , "setQuery"
    , "toString"
};

static const char * const qtscript_QSqlQueryModel_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "\nint row"
    , "QSqlQuery query\nString query, QSqlDatabase db"
""
};

static const int qtscript_QSqlQueryModel_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QSqlQueryModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlQueryModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlQueryModel*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlQueryModel*)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSqlQuery)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlDatabase)
Q_DECLARE_METATYPE(QAbstractTableModel*)

//
// QSqlQueryModel
//

static QScriptValue qtscript_QSqlQueryModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlQueryModel* _q_self = qscriptvalue_cast<QSqlQueryModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlQueryModel.%0(): this object is not a QSqlQueryModel")
            .arg(qtscript_QSqlQueryModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSqlError _q_result = _q_self->lastError();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QSqlQuery _q_result = _q_self->query();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSqlRecord _q_result = _q_self->record();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlRecord _q_result = _q_self->record(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSqlQuery>() == context->argument(0).toVariant().userType())) {
            QSqlQuery _q_arg0 = qscriptvalue_cast<QSqlQuery>(context->argument(0));
            _q_self->setQuery(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setQuery(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSqlDatabase _q_arg1 = qscriptvalue_cast<QSqlDatabase>(context->argument(1));
        _q_self->setQuery(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QSqlQueryModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlQueryModel_throw_ambiguity_error_helper(context,
        qtscript_QSqlQueryModel_function_names[_id+1],
        qtscript_QSqlQueryModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlQueryModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlQueryModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSqlQueryModel* _q_cpp_result = new QtScriptShell_QSqlQueryModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlQueryModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSqlQueryModel* _q_cpp_result = new QtScriptShell_QSqlQueryModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSqlQueryModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlQueryModel_throw_ambiguity_error_helper(context,
        qtscript_QSqlQueryModel_function_names[_id],
        qtscript_QSqlQueryModel_function_signatures[_id]);
}

static QScriptValue qtscript_QSqlQueryModel_toScriptValue(QScriptEngine *engine, QSqlQueryModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSqlQueryModel_fromScriptValue(const QScriptValue &value, QSqlQueryModel* &out)
{
    out = qobject_cast<QSqlQueryModel*>(value.toQObject());
}

QScriptValue qtscript_create_QSqlQueryModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlQueryModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlQueryModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractTableModel*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlQueryModel_prototype_call, qtscript_QSqlQueryModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlQueryModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSqlQueryModel*>(engine, qtscript_QSqlQueryModel_toScriptValue, 
        qtscript_QSqlQueryModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlQueryModel_static_call, proto, qtscript_QSqlQueryModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
