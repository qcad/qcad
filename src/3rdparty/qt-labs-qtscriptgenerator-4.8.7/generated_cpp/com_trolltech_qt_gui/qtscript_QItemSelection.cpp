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
#include <qvector.h>

static const char * const qtscript_QItemSelection_function_names[] = {
    "QItemSelection"
    // static
    , "fromVector"
    , "split"
    // prototype
    , "append"
    , "at"
    , "back"
    , "clear"
    , "contains"
    , "count"
    , "detachShared"
    , "empty"
    , "endsWith"
    , "first"
    , "front"
    , "indexOf"
    , "indexes"
    , "isEmpty"
    , "isSharedWith"
    , "last"
    , "lastIndexOf"
    , "length"
    , "merge"
    , "mid"
    , "move"
    , "equals"
    , "pop_back"
    , "pop_front"
    , "prepend"
    , "push_back"
    , "push_front"
    , "removeAll"
    , "removeAt"
    , "removeFirst"
    , "removeLast"
    , "removeOne"
    , "replace"
    , "reserve"
    , "select"
    , "setSharable"
    , "size"
    , "startsWith"
    , "swap"
    , "takeAt"
    , "takeFirst"
    , "takeLast"
    , "toVector"
    , "value"
    , "toString"
};

static const char * const qtscript_QItemSelection_function_signatures[] = {
    "\nQModelIndex topLeft, QModelIndex bottomRight"
    // static
    , "List vector"
    , "QItemSelectionRange range, QItemSelectionRange other, QItemSelection result"
    // prototype
    , "QItemSelectionRange t\nList t"
    , "int i"
    , ""
    , ""
    , "QModelIndex index"
    , "\nQItemSelectionRange t"
    , ""
    , ""
    , "QItemSelectionRange t"
    , ""
    , ""
    , "QItemSelectionRange t, int from"
    , ""
    , ""
    , "List other"
    , ""
    , "QItemSelectionRange t, int from"
    , ""
    , "QItemSelection other, SelectionFlags command"
    , "int pos, int length"
    , "int from, int to"
    , "List l"
    , ""
    , ""
    , "QItemSelectionRange t"
    , "QItemSelectionRange t"
    , "QItemSelectionRange t"
    , "QItemSelectionRange t"
    , "int i"
    , ""
    , ""
    , "QItemSelectionRange t"
    , "int i, QItemSelectionRange t"
    , "int size"
    , "QModelIndex topLeft, QModelIndex bottomRight"
    , "bool sharable"
    , ""
    , "QItemSelectionRange t"
    , "List other\nint i, int j"
    , "int i"
    , ""
    , ""
    , ""
    , "int i\nint i, QItemSelectionRange defaultValue"
""
};

static const int qtscript_QItemSelection_function_lengths[] = {
    2
    // static
    , 1
    , 3
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 1
    , 0
    , 2
    , 0
    , 2
    , 2
    , 2
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 2
    , 1
    , 2
    , 1
    , 0
    , 1
    , 2
    , 1
    , 0
    , 0
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QItemSelection_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QItemSelection::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QItemSelection)
Q_DECLARE_METATYPE(QItemSelection*)
Q_DECLARE_METATYPE(QItemSelectionRange)
Q_DECLARE_METATYPE(QList<QItemSelectionRange>)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(QVector<QItemSelectionRange>)

//
// QItemSelection
//

static QScriptValue qtscript_QItemSelection_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 44;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QItemSelection* _q_self = qscriptvalue_cast<QItemSelection*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QItemSelection.%0(): this object is not a QItemSelection")
            .arg(qtscript_QItemSelection_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QItemSelectionRange>() == context->argument(0).toVariant().userType())) {
            QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
            _q_self->append(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isArray()) {
            QList<QItemSelectionRange> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->append(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QItemSelectionRange _q_result = _q_self->at(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_result = _q_self->back();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        int _q_result = _q_self->count(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->detachShared();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->empty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        bool _q_result = _q_self->endsWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_result = _q_self->first();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_result = _q_self->front();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->indexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QList<QModelIndex> _q_result = _q_self->indexes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QList<QItemSelectionRange> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        bool _q_result = _q_self->isSharedWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_result = _q_self->last();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        int _q_result = _q_self->lastIndexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->lastIndexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        QItemSelection _q_arg0 = qscriptvalue_cast<QItemSelection>(context->argument(0));
        QFlags<QItemSelectionModel::SelectionFlag> _q_arg1 = qscriptvalue_cast<QFlags<QItemSelectionModel::SelectionFlag> >(context->argument(1));
        _q_self->merge(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QItemSelectionRange> _q_result = _q_self->mid(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QList<QItemSelectionRange> _q_result = _q_self->mid(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->move(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QList<QItemSelectionRange> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        _q_self->pop_back();
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->pop_front();
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        _q_self->prepend(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        _q_self->push_back(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        _q_self->push_front(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        int _q_result = _q_self->removeAll(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeAt(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        _q_self->removeFirst();
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        _q_self->removeLast();
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        bool _q_result = _q_self->removeOne(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QItemSelectionRange _q_arg1 = qscriptvalue_cast<QItemSelectionRange>(context->argument(1));
        _q_self->replace(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->reserve(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        _q_self->select(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSharable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        bool _q_result = _q_self->startsWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QList<QItemSelectionRange> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->swap(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QItemSelectionRange _q_result = _q_self->takeAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_result = _q_self->takeFirst();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QItemSelectionRange _q_result = _q_self->takeLast();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        QVector<QItemSelectionRange> _q_result = _q_self->toVector();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QItemSelectionRange _q_result = _q_self->value(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QItemSelectionRange _q_arg1 = qscriptvalue_cast<QItemSelectionRange>(context->argument(1));
        QItemSelectionRange _q_result = _q_self->value(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44: {
    QString result = QString::fromLatin1("QItemSelection");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemSelection_throw_ambiguity_error_helper(context,
        qtscript_QItemSelection_function_names[_id+3],
        qtscript_QItemSelection_function_signatures[_id+3]);
}

static QScriptValue qtscript_QItemSelection_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QItemSelection(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QItemSelection _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        QItemSelection _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QVector<QItemSelectionRange> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QList<QItemSelectionRange> _q_result = QItemSelection::fromVector(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QItemSelectionRange _q_arg0 = qscriptvalue_cast<QItemSelectionRange>(context->argument(0));
        QItemSelectionRange _q_arg1 = qscriptvalue_cast<QItemSelectionRange>(context->argument(1));
        QItemSelection* _q_arg2 = qscriptvalue_cast<QItemSelection*>(context->argument(2));
        QItemSelection::split(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemSelection_throw_ambiguity_error_helper(context,
        qtscript_QItemSelection_function_names[_id],
        qtscript_QItemSelection_function_signatures[_id]);
}

QScriptValue qtscript_create_QItemSelection_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QItemSelection*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QItemSelection*)0));
    for (int i = 0; i < 45; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemSelection_prototype_call, qtscript_QItemSelection_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QItemSelection_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QItemSelection>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QItemSelection*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QItemSelection_static_call, proto, qtscript_QItemSelection_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemSelection_static_call,
            qtscript_QItemSelection_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QItemSelection_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
