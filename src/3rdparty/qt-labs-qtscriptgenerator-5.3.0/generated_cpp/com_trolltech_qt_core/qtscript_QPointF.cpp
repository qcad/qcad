#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qpoint.h>
#include <QVariant>
#include <qpoint.h>

static const char * const qtscript_QPointF_function_names[] = {
    "QPointF"
    // static
    , "dotProduct"
    // prototype
    , "isNull"
    , "manhattanLength"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "setX"
    , "setY"
    , "toPoint"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QPointF_function_signatures[] = {
    "\nQPoint p\nqreal xpos, qreal ypos"
    // static
    , "QPointF p1, QPointF p2"
    // prototype
    , ""
    , ""
    , "QPointF p"
    , "qreal c"
    , "QPointF p2"
    , "qreal c"
    , "QPointF p"
    , "qreal x"
    , "qreal y"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QPointF_function_lengths[] = {
    2
    // static
    , 2
    // prototype
    , 0
    , 0
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
    , 0
};

static QScriptValue qtscript_QPointF_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPointF::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPointF*)

//
// QPointF
//

static QScriptValue qtscript_QPointF_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPointF* _q_self = qscriptvalue_cast<QPointF*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPointF.%0(): this object is not a QPointF")
            .arg(qtscript_QPointF_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->manhattanLength();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF& _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPointF& _q_result = _q_self->operator/=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPointF& _q_result = _q_self->operator*=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF& _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->toPoint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->x();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->y();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPointF_throw_ambiguity_error_helper(context,
        qtscript_QPointF_function_names[_id+2],
        qtscript_QPointF_function_signatures[_id+2]);
}

static QScriptValue qtscript_QPointF_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPointF(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPointF _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPointF _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPointF _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        qreal _q_result = QPointF::dotProduct(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPointF_throw_ambiguity_error_helper(context,
        qtscript_QPointF_function_names[_id],
        qtscript_QPointF_function_signatures[_id]);
}

QScriptValue qtscript_create_QPointF_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPointF*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPointF*)0));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPointF_prototype_call, qtscript_QPointF_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPointF_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPointF>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPointF*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPointF_static_call, proto, qtscript_QPointF_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPointF_static_call,
            qtscript_QPointF_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QPointF_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
