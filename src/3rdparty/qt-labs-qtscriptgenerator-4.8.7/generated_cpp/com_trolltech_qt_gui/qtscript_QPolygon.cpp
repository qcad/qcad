#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpolygon.h>
#include <QVariant>
#include <qdatastream.h>
#include <qlist.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qvector.h>

static const char * const qtscript_QPolygon_function_names[] = {
    "QPolygon"
    // static
    , "fromList"
    // prototype
    , "append"
    , "at"
    , "boundingRect"
    , "capacity"
    , "clear"
    , "contains"
    , "containsPoint"
    , "count"
    , "empty"
    , "endsWith"
    , "fill"
    , "first"
    , "indexOf"
    , "intersected"
    , "isEmpty"
    , "isSharedWith"
    , "last"
    , "lastIndexOf"
    , "mid"
    , "equals"
    , "pop_back"
    , "pop_front"
    , "prepend"
    , "push_back"
    , "push_front"
    , "readFrom"
    , "remove"
    , "replace"
    , "reserve"
    , "resize"
    , "setSharable"
    , "size"
    , "squeeze"
    , "startsWith"
    , "subtracted"
    , "swap"
    , "toList"
    , "translate"
    , "translated"
    , "united"
    , "value"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QPolygon_function_signatures[] = {
    "\nQPolygon a\nQRect r, bool closed\nList v\nint size"
    // static
    , "List list"
    // prototype
    , "QPoint t"
    , "int i"
    , ""
    , ""
    , ""
    , "QPoint t"
    , "QPoint pt, FillRule fillRule"
    , "\nQPoint t"
    , ""
    , "QPoint t"
    , "QPoint t, int size"
    , ""
    , "QPoint t, int from"
    , "QPolygon r"
    , ""
    , "List other"
    , ""
    , "QPoint t, int from"
    , "int pos, int length"
    , "List v"
    , ""
    , ""
    , "QPoint t"
    , "QPoint t"
    , "QPoint t"
    , "QDataStream stream"
    , "int i\nint i, int n"
    , "int i, QPoint t"
    , "int size"
    , "int size"
    , "bool sharable"
    , ""
    , ""
    , "QPoint t"
    , "QPolygon r"
    , "QPolygon other"
    , ""
    , "QPoint offset\nint dx, int dy"
    , "QPoint offset\nint dx, int dy"
    , "QPolygon r"
    , "int i\nint i, QPoint defaultValue"
    , "QDataStream stream"
""
};

static const int qtscript_QPolygon_function_lengths[] = {
    2
    // static
    , 1
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 0
    , 1
    , 2
    , 0
    , 2
    , 1
    , 0
    , 1
    , 0
    , 2
    , 2
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 2
    , 2
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QPolygon_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPolygon::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPolygon*)
Q_DECLARE_METATYPE(Qt::FillRule)
Q_DECLARE_METATYPE(QVector<QPoint>)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QList<QPoint>)

//
// QPolygon
//

static QScriptValue qtscript_QPolygon_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 42;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPolygon* _q_self = qscriptvalue_cast<QPolygon*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPolygon.%0(): this object is not a QPolygon")
            .arg(qtscript_QPolygon_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->append(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPoint _q_result = _q_self->at(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->capacity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        Qt::FillRule _q_arg1 = qscriptvalue_cast<Qt::FillRule>(context->argument(1));
        bool _q_result = _q_self->containsPoint(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_result = _q_self->count(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->empty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        bool _q_result = _q_self->endsWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QVector<QPoint> _q_result = _q_self->fill(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVector<QPoint> _q_result = _q_self->fill(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->first();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->indexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
        QPolygon _q_result = _q_self->intersected(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QVector<QPoint> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        bool _q_result = _q_self->isSharedWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->last();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_result = _q_self->lastIndexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->lastIndexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector<QPoint> _q_result = _q_self->mid(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QVector<QPoint> _q_result = _q_self->mid(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QVector<QPoint> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->pop_back();
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        _q_self->pop_front();
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->prepend(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->push_back(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->push_front(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->remove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->remove(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        _q_self->replace(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->reserve(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->resize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSharable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        _q_self->squeeze();
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        bool _q_result = _q_self->startsWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
        QPolygon _q_result = _q_self->subtracted(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QList<QPoint> _q_result = _q_self->toList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPolygon _q_result = _q_self->translated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPolygon _q_result = _q_self->translated(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
        QPolygon _q_result = _q_self->united(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPoint _q_result = _q_self->value(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QPoint _q_result = _q_self->value(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 42: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPolygon_throw_ambiguity_error_helper(context,
        qtscript_QPolygon_function_names[_id+2],
        qtscript_QPolygon_function_signatures[_id+2]);
}

static QScriptValue qtscript_QPolygon_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPolygon(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPolygon _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            QPolygon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QPolygon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isArray()) {
            QVector<QPoint> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QPolygon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QPolygon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        QPolygon _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QList<QPoint> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QVector<QPoint> _q_result = QPolygon::fromList(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPolygon_throw_ambiguity_error_helper(context,
        qtscript_QPolygon_function_names[_id],
        qtscript_QPolygon_function_signatures[_id]);
}

QScriptValue qtscript_create_QPolygon_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPolygon*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPolygon*)0));
    for (int i = 0; i < 43; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPolygon_prototype_call, qtscript_QPolygon_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPolygon_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPolygon>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPolygon*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPolygon_static_call, proto, qtscript_QPolygon_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPolygon_static_call,
            qtscript_QPolygon_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QPolygon_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
