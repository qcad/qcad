#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qitemselectionmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qitemselectionmodel.h>
#include <qlist.h>

static const char * const qtscript_QItemSelectionRange_function_names[] = {
    "QItemSelectionRange"
    // static
    // prototype
    , "bottom"
    , "bottomRight"
    , "contains"
    , "height"
    , "indexes"
    , "intersected"
    , "intersects"
    , "isEmpty"
    , "isValid"
    , "left"
    , "model"
    , "equals"
    , "operator_less"
    , "parent"
    , "right"
    , "top"
    , "topLeft"
    , "width"
    , "toString"
};

static const char * const qtscript_QItemSelectionRange_function_signatures[] = {
    "\nQItemSelectionRange other\nQModelIndex index\nQModelIndex topLeft, QModelIndex bottomRight"
    // static
    // prototype
    , ""
    , ""
    , "QModelIndex index\nint row, int column, QModelIndex parentIndex"
    , ""
    , ""
    , "QItemSelectionRange other"
    , "QItemSelectionRange other"
    , ""
    , ""
    , ""
    , ""
    , "QItemSelectionRange other"
    , "QItemSelectionRange other"
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QItemSelectionRange_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 3
    , 0
    , 0
    , 1
    , 1
    , 0
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
    , 0
};

static QScriptValue qtscript_QItemSelectionRange_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QItemSelectionRange::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QItemSelectionRange)
Q_DECLARE_METATYPE(QItemSelectionRange*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QAbstractItemModel*)

//
// QItemSelectionRange
//

static QScriptValue qtscript_QItemSelectionRange_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 18;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QItemSelectionRange* _q_self = qscriptvalue_cast<QItemSelectionRange*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QItemSelectionRange.%0(): this object is not a QItemSelectionRange")
            .arg(qtscript_QItemSelectionRange_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->bottom();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->bottomRight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->contains(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->height();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QList<QModelIndex> _q_result = _q_self->indexes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        QItemSelectionRange _q_result = _q_self->intersected(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        bool _q_result = _q_self->intersects(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->left();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = const_cast<QAbstractItemModel*>(_q_self->model());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->parent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->right();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->top();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->topLeft();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->width();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemSelectionRange_throw_ambiguity_error_helper(context,
        qtscript_QItemSelectionRange_function_names[_id+1],
        qtscript_QItemSelectionRange_function_signatures[_id+1]);
}

static QScriptValue qtscript_QItemSelectionRange_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QItemSelectionRange(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QItemSelectionRange>() == context->argument(0).toVariant().userType())) {
            QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
            QItemSelectionRange _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QModelIndex>() == context->argument(0).toVariant().userType())) {
            QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
            QItemSelectionRange _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        QItemSelectionRange _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemSelectionRange_throw_ambiguity_error_helper(context,
        qtscript_QItemSelectionRange_function_names[_id],
        qtscript_QItemSelectionRange_function_signatures[_id]);
}

QScriptValue qtscript_create_QItemSelectionRange_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QItemSelectionRange*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QItemSelectionRange*)0));
    for (int i = 0; i < 19; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemSelectionRange_prototype_call, qtscript_QItemSelectionRange_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QItemSelectionRange_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QItemSelectionRange>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QItemSelectionRange*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QItemSelectionRange_static_call, proto, qtscript_QItemSelectionRange_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
