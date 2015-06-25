#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmatrix.h>
#include <QPainterPath>
#include <QVariant>
#include <qline.h>
#include <qmatrix.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>

static const char * const qtscript_QMatrix_function_names[] = {
    "QMatrix"
    // static
    // prototype
    , "determinant"
    , "dx"
    , "dy"
    , "inverted"
    , "isIdentity"
    , "isInvertible"
    , "m11"
    , "m12"
    , "m21"
    , "m22"
    , "map"
    , "mapRect"
    , "mapToPolygon"
    , "equals"
    , "operator_multiply"
    , "operator_multiply_assign"
    , "reset"
    , "rotate_private"
    , "scale_private"
    , "setMatrix"
    , "shear_private"
    , "translate_private"
    , "toString"
};

static const char * const qtscript_QMatrix_function_signatures[] = {
    "\nQMatrix matrix\nqreal m11, qreal m12, qreal m21, qreal m22, qreal dx, qreal dy"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QLine l\nQLineF l\nQPainterPath p\nQPoint p\nQPointF p\nQPolygon a\nQPolygonF a\nQRegion r"
    , "QRect arg__1\nQRectF arg__1"
    , "QRect r"
    , "QMatrix arg__1"
    , "QMatrix o"
    , "QMatrix arg__1"
    , ""
    , "qreal a"
    , "qreal sx, qreal sy"
    , "qreal m11, qreal m12, qreal m21, qreal m22, qreal dx, qreal dy"
    , "qreal sh, qreal sv"
    , "qreal dx, qreal dy"
""
};

static const int qtscript_QMatrix_function_lengths[] = {
    6
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 0
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
    , 0
    , 1
    , 2
    , 6
    , 2
    , 2
    , 0
};

static QScriptValue qtscript_QMatrix_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMatrix::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMatrix*)
Q_DECLARE_METATYPE(QPainterPath)

//
// QMatrix
//

static QScriptValue qtscript_QMatrix_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 22;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMatrix* _q_self = qscriptvalue_cast<QMatrix*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMatrix.%0(): this object is not a QMatrix")
            .arg(qtscript_QMatrix_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->determinant();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dx();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QMatrix _q_result = _q_self->inverted();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isIdentity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isInvertible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m11();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m12();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m21();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m22();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QLine>() == context->argument(0).toVariant().userType())) {
            QLine _q_arg0 = qscriptvalue_cast<QLine>(context->argument(0));
            QLine _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QLineF>() == context->argument(0).toVariant().userType())) {
            QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
            QLineF _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPoint _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            QPolygon _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QPolygonF _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            QRegion _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QRect _q_result = _q_self->mapRect(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QRectF _q_result = _q_self->mapRect(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QPolygon _q_result = _q_self->mapToPolygon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        QMatrix _q_result = _q_self->operator*(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        QMatrix& _q_result = _q_self->operator*=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QMatrix& _q_result = _q_self->rotate(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QMatrix& _q_result = _q_self->scale(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->setMatrix(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QMatrix& _q_result = _q_self->shear(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QMatrix& _q_result = _q_self->translate(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMatrix_throw_ambiguity_error_helper(context,
        qtscript_QMatrix_function_names[_id+1],
        qtscript_QMatrix_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMatrix_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMatrix(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QMatrix _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        QMatrix _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        QMatrix _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMatrix_throw_ambiguity_error_helper(context,
        qtscript_QMatrix_function_names[_id],
        qtscript_QMatrix_function_signatures[_id]);
}

QScriptValue qtscript_create_QMatrix_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMatrix*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMatrix*)0));
    for (int i = 0; i < 23; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMatrix_prototype_call, qtscript_QMatrix_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMatrix_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMatrix>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QMatrix*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMatrix_static_call, proto, qtscript_QMatrix_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
