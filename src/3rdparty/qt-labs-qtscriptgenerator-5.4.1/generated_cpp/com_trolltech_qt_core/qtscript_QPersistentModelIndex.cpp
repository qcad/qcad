#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractitemmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>

static const char * const qtscript_QPersistentModelIndex_function_names[] = {
    "QPersistentModelIndex"
    // static
    // prototype
    , "child"
    , "column"
    , "data"
    , "flags"
    , "internalId"
    , "isValid"
    , "model"
    , "operator_cast_QModelIndex"
    , "equals"
    , "operator_less"
    , "parent"
    , "row"
    , "sibling"
    , "swap"
    , "toString"
};

static const char * const qtscript_QPersistentModelIndex_function_signatures[] = {
    "\nQModelIndex index\nQPersistentModelIndex other"
    // static
    // prototype
    , "int row, int column"
    , ""
    , "int role"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QModelIndex other\nQPersistentModelIndex other"
    , "QPersistentModelIndex other"
    , ""
    , ""
    , "int row, int column"
    , "QPersistentModelIndex other"
""
};

static const int qtscript_QPersistentModelIndex_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QPersistentModelIndex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPersistentModelIndex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPersistentModelIndex)
Q_DECLARE_METATYPE(QPersistentModelIndex*)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(quintptr)
Q_DECLARE_METATYPE(const QAbstractItemModel*)

//
// QPersistentModelIndex
//

static QScriptValue qtscript_QPersistentModelIndex_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPersistentModelIndex* _q_self = qscriptvalue_cast<QPersistentModelIndex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPersistentModelIndex.%0(): this object is not a QPersistentModelIndex")
            .arg(qtscript_QPersistentModelIndex_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_result = _q_self->child(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->column();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->data();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFlags<Qt::ItemFlag> _q_result = _q_self->flags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        quintptr _q_result = _q_self->internalId();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        const QAbstractItemModel* _q_result = const_cast<const QAbstractItemModel*>(_q_self->model());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->operator const QModelIndex&();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QModelIndex>() == context->argument(0).toVariant().userType())) {
            QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
            bool _q_result = _q_self->operator==(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPersistentModelIndex>() == context->argument(0).toVariant().userType())) {
            QPersistentModelIndex _q_arg0 = qscriptvalue_cast<QPersistentModelIndex>(context->argument(0));
            bool _q_result = _q_self->operator==(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPersistentModelIndex _q_arg0 = qscriptvalue_cast<QPersistentModelIndex>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->parent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->row();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_result = _q_self->sibling(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QPersistentModelIndex _q_arg0 = qscriptvalue_cast<QPersistentModelIndex>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPersistentModelIndex_throw_ambiguity_error_helper(context,
        qtscript_QPersistentModelIndex_function_names[_id+1],
        qtscript_QPersistentModelIndex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPersistentModelIndex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPersistentModelIndex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPersistentModelIndex _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QModelIndex>() == context->argument(0).toVariant().userType())) {
            QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
            QPersistentModelIndex _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPersistentModelIndex>() == context->argument(0).toVariant().userType())) {
            QPersistentModelIndex _q_arg0 = qscriptvalue_cast<QPersistentModelIndex>(context->argument(0));
            QPersistentModelIndex _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPersistentModelIndex_throw_ambiguity_error_helper(context,
        qtscript_QPersistentModelIndex_function_names[_id],
        qtscript_QPersistentModelIndex_function_signatures[_id]);
}

QScriptValue qtscript_create_QPersistentModelIndex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPersistentModelIndex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPersistentModelIndex*)0));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPersistentModelIndex_prototype_call, qtscript_QPersistentModelIndex_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPersistentModelIndex_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPersistentModelIndex>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPersistentModelIndex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPersistentModelIndex_static_call, proto, qtscript_QPersistentModelIndex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
