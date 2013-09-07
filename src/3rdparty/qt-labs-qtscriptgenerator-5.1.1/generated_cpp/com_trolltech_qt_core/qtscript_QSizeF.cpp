#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsize.h>
#include <QVariant>
#include <qsize.h>

static const char * const qtscript_QSizeF_function_names[] = {
    "QSizeF"
    // static
    // prototype
    , "boundedTo"
    , "expandedTo"
    , "height"
    , "isEmpty"
    , "isNull"
    , "isValid"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "scale"
    , "scaled"
    , "setHeight"
    , "setWidth"
    , "toSize"
    , "transpose"
    , "transposed"
    , "width"
    , "toString"
};

static const char * const qtscript_QSizeF_function_signatures[] = {
    "\nQSize sz\nqreal w, qreal h"
    // static
    // prototype
    , "QSizeF arg__1"
    , "QSizeF arg__1"
    , ""
    , ""
    , ""
    , ""
    , "QSizeF arg__1"
    , "qreal c"
    , "QSizeF s2"
    , "qreal c"
    , "QSizeF arg__1"
    , "QSizeF s, AspectRatioMode mode\nqreal w, qreal h, AspectRatioMode mode"
    , "QSizeF s, AspectRatioMode mode\nqreal w, qreal h, AspectRatioMode mode"
    , "qreal h"
    , "qreal w"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSizeF_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 3
    , 3
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSizeF_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSizeF::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSizeF*)
Q_DECLARE_METATYPE(Qt::AspectRatioMode)

//
// QSizeF
//

static QScriptValue qtscript_QSizeF_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSizeF* _q_self = qscriptvalue_cast<QSizeF*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSizeF.%0(): this object is not a QSizeF")
            .arg(qtscript_QSizeF_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        QSizeF _q_result = _q_self->boundedTo(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        QSizeF _q_result = _q_self->expandedTo(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        QSizeF& _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QSizeF& _q_result = _q_self->operator/=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QSizeF& _q_result = _q_self->operator*=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        QSizeF& _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
        _q_self->scale(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        Qt::AspectRatioMode _q_arg2 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(2));
        _q_self->scale(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
        QSizeF _q_result = _q_self->scaled(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        Qt::AspectRatioMode _q_arg2 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(2));
        QSizeF _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->toSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        _q_self->transpose();
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->transposed();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSizeF_throw_ambiguity_error_helper(context,
        qtscript_QSizeF_function_names[_id+1],
        qtscript_QSizeF_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSizeF_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSizeF(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSizeF _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QSizeF _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QSizeF _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSizeF_throw_ambiguity_error_helper(context,
        qtscript_QSizeF_function_names[_id],
        qtscript_QSizeF_function_signatures[_id]);
}

QScriptValue qtscript_create_QSizeF_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSizeF*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSizeF*)0));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSizeF_prototype_call, qtscript_QSizeF_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSizeF_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSizeF>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSizeF*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSizeF_static_call, proto, qtscript_QSizeF_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
