#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqlrelationaltablemodel.h>
#include <QVariant>

static const char * const qtscript_QSqlRelation_function_names[] = {
    "QSqlRelation"
    // static
    // prototype
    , "displayColumn"
    , "indexColumn"
    , "isValid"
    , "tableName"
    , "toString"
};

static const char * const qtscript_QSqlRelation_function_signatures[] = {
    "\nString aTableName, String indexCol, String displayCol"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSqlRelation_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSqlRelation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlRelation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlRelation)
Q_DECLARE_METATYPE(QSqlRelation*)

//
// QSqlRelation
//

static QScriptValue qtscript_QSqlRelation_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlRelation* _q_self = qscriptvalue_cast<QSqlRelation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlRelation.%0(): this object is not a QSqlRelation")
            .arg(qtscript_QSqlRelation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->displayColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->indexColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->tableName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QSqlRelation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlRelation_throw_ambiguity_error_helper(context,
        qtscript_QSqlRelation_function_names[_id+1],
        qtscript_QSqlRelation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlRelation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlRelation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSqlRelation _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QSqlRelation _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlRelation_throw_ambiguity_error_helper(context,
        qtscript_QSqlRelation_function_names[_id],
        qtscript_QSqlRelation_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlRelation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlRelation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlRelation*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlRelation_prototype_call, qtscript_QSqlRelation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlRelation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlRelation>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlRelation*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlRelation_static_call, proto, qtscript_QSqlRelation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
