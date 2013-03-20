#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbrush.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qpair.h>
#include <qpoint.h>
#include <qvector.h>

static const char * const qtscript_QRadialGradient_function_names[] = {
    "QRadialGradient"
    // static
    // prototype
    , "center"
    , "focalPoint"
    , "radius"
    , "setCenter"
    , "setFocalPoint"
    , "setRadius"
    , "toString"
};

static const char * const qtscript_QRadialGradient_function_signatures[] = {
    "\nQPointF center, qreal radius\nQPointF center, qreal radius, QPointF focalPoint\nqreal cx, qreal cy, qreal radius\nqreal cx, qreal cy, qreal radius, qreal fx, qreal fy"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QPointF center\nqreal x, qreal y"
    , "QPointF focalPoint\nqreal x, qreal y"
    , "qreal radius"
""
};

static const int qtscript_QRadialGradient_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QRadialGradient_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRadialGradient::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRadialGradient)
Q_DECLARE_METATYPE(QRadialGradient*)
Q_DECLARE_METATYPE(QGradient*)
Q_DECLARE_METATYPE(QGradient)

//
// QRadialGradient
//

static QScriptValue qtscript_QRadialGradient_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QRadialGradient* _q_self = qscriptvalue_cast<QRadialGradient*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRadialGradient.%0(): this object is not a QRadialGradient")
            .arg(qtscript_QRadialGradient_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->center();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->focalPoint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->radius();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setCenter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setCenter(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setFocalPoint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setFocalPoint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRadius(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QRadialGradient");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRadialGradient_throw_ambiguity_error_helper(context,
        qtscript_QRadialGradient_function_names[_id+1],
        qtscript_QRadialGradient_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRadialGradient_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRadialGradient(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QRadialGradient _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QRadialGradient _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QPointF>() == context->argument(2).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            QPointF _q_arg2 = qscriptvalue_cast<QPointF>(context->argument(2));
            QRadialGradient _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<qreal>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(2).toVariant().userType())) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
            QRadialGradient _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        QRadialGradient _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRadialGradient_throw_ambiguity_error_helper(context,
        qtscript_QRadialGradient_function_names[_id],
        qtscript_QRadialGradient_function_signatures[_id]);
}

QScriptValue qtscript_create_QRadialGradient_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRadialGradient*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRadialGradient*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGradient*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRadialGradient_prototype_call, qtscript_QRadialGradient_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRadialGradient_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QRadialGradient>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QRadialGradient*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRadialGradient_static_call, proto, qtscript_QRadialGradient_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
