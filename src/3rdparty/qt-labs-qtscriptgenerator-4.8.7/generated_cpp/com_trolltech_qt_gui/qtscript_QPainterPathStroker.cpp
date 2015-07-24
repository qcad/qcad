#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpainterpath.h>
#include <QVariant>
#include <qpainterpath.h>
#include <qvector.h>

static const char * const qtscript_QPainterPathStroker_function_names[] = {
    "QPainterPathStroker"
    // static
    // prototype
    , "capStyle"
    , "createStroke"
    , "curveThreshold"
    , "dashOffset"
    , "dashPattern"
    , "joinStyle"
    , "miterLimit"
    , "setCapStyle"
    , "setCurveThreshold"
    , "setDashOffset"
    , "setDashPattern"
    , "setJoinStyle"
    , "setMiterLimit"
    , "setWidth"
    , "width"
    , "toString"
};

static const char * const qtscript_QPainterPathStroker_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "QPainterPath path"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "PenCapStyle style"
    , "qreal threshold"
    , "qreal offset"
    , "PenStyle arg__1\nList dashPattern"
    , "PenJoinStyle style"
    , "qreal length"
    , "qreal width"
    , ""
""
};

static const int qtscript_QPainterPathStroker_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 0
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
};

static QScriptValue qtscript_QPainterPathStroker_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPainterPathStroker::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPainterPathStroker*)
Q_DECLARE_METATYPE(Qt::PenCapStyle)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QVector<qreal>)
Q_DECLARE_METATYPE(Qt::PenJoinStyle)
Q_DECLARE_METATYPE(Qt::PenStyle)

//
// QPainterPathStroker
//

static QScriptValue qtscript_QPainterPathStroker_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPainterPathStroker* _q_self = qscriptvalue_cast<QPainterPathStroker*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPainterPathStroker.%0(): this object is not a QPainterPathStroker")
            .arg(qtscript_QPainterPathStroker_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Qt::PenCapStyle _q_result = _q_self->capStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->createStroke(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->curveThreshold();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dashOffset();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QVector<qreal> _q_result = _q_self->dashPattern();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        Qt::PenJoinStyle _q_result = _q_self->joinStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->miterLimit();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        Qt::PenCapStyle _q_arg0 = qscriptvalue_cast<Qt::PenCapStyle>(context->argument(0));
        _q_self->setCapStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setCurveThreshold(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setDashOffset(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::PenStyle>() == context->argument(0).toVariant().userType())) {
            Qt::PenStyle _q_arg0 = qscriptvalue_cast<Qt::PenStyle>(context->argument(0));
            _q_self->setDashPattern(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isArray()) {
            QVector<qreal> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->setDashPattern(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        Qt::PenJoinStyle _q_arg0 = qscriptvalue_cast<Qt::PenJoinStyle>(context->argument(0));
        _q_self->setJoinStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMiterLimit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15: {
    QString result = QString::fromLatin1("QPainterPathStroker");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPainterPathStroker_throw_ambiguity_error_helper(context,
        qtscript_QPainterPathStroker_function_names[_id+1],
        qtscript_QPainterPathStroker_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPainterPathStroker_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPainterPathStroker(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPainterPathStroker* _q_cpp_result = new QPainterPathStroker();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPainterPathStroker_throw_ambiguity_error_helper(context,
        qtscript_QPainterPathStroker_function_names[_id],
        qtscript_QPainterPathStroker_function_signatures[_id]);
}

QScriptValue qtscript_create_QPainterPathStroker_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPainterPathStroker*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPainterPathStroker*)0));
    for (int i = 0; i < 16; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPainterPathStroker_prototype_call, qtscript_QPainterPathStroker_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPainterPathStroker_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPainterPathStroker*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPainterPathStroker_static_call, proto, qtscript_QPainterPathStroker_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
