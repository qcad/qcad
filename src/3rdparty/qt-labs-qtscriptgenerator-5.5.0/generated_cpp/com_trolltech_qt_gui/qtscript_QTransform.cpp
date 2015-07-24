#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtransform.h>
#include <QVariant>
#include <qline.h>
#include <qmatrix.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qtransform.h>

static const char * const qtscript_QTransform_function_names[] = {
    "QTransform"
    // static
    , "fromScale"
    , "fromTranslate"
    , "quadToQuad"
    , "quadToSquare"
    , "squareToQuad"
    // prototype
    , "adjoint"
    , "det"
    , "determinant"
    , "dx"
    , "dy"
    , "inverted"
    , "isAffine"
    , "isIdentity"
    , "isInvertible"
    , "isRotating"
    , "isScaling"
    , "isTranslating"
    , "m11"
    , "m12"
    , "m13"
    , "m21"
    , "m22"
    , "m23"
    , "m31"
    , "m32"
    , "m33"
    , "map"
    , "mapRect"
    , "mapToPolygon"
    , "multiplied"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "reset"
    , "rotate"
    , "rotateRadians"
    , "scale"
    , "setMatrix"
    , "shear"
    , "toAffine"
    , "translate"
    , "transposed"
    , "type"
    , "toString"
};

static const char * const qtscript_QTransform_function_signatures[] = {
    "\nQMatrix mtx\nqreal h11, qreal h12, qreal h13, qreal h21, qreal h22, qreal h23, qreal h31, qreal h32, qreal h33\nqreal h11, qreal h12, qreal h21, qreal h22, qreal dx, qreal dy"
    // static
    , "qreal dx, qreal dy"
    , "qreal dx, qreal dy"
    , "QPolygonF one, QPolygonF two, QTransform result"
    , "QPolygonF quad, QTransform result"
    , "QPolygonF square, QTransform result"
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
    , ""
    , "QLine l\nQLineF l\nQPainterPath p\nQPoint p\nQPointF p\nQPolygon a\nQPolygonF a\nQRegion r"
    , "QRect arg__1\nQRectF arg__1"
    , "QRect r"
    , "QTransform o"
    , "qreal div"
    , "qreal div"
    , "QTransform arg__1"
    , "QTransform arg__1\nqreal div"
    , "qreal div"
    , ""
    , "qreal a, Axis axis"
    , "qreal a, Axis axis"
    , "qreal sx, qreal sy"
    , "qreal m11, qreal m12, qreal m13, qreal m21, qreal m22, qreal m23, qreal m31, qreal m32, qreal m33"
    , "qreal sh, qreal sv"
    , ""
    , "qreal dx, qreal dy"
    , ""
    , ""
""
};

static const int qtscript_QTransform_function_lengths[] = {
    9
    // static
    , 2
    , 2
    , 3
    , 2
    , 2
    // prototype
    , 0
    , 0
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
    , 0
    , 0
    , 0
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
    , 1
    , 1
    , 1
    , 0
    , 2
    , 2
    , 2
    , 9
    , 2
    , 0
    , 2
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTransform_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTransform::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTransform*)
Q_DECLARE_METATYPE(QTransform::TransformationType)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(Qt::Axis)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QTransform::TransformationType
//

static const QTransform::TransformationType qtscript_QTransform_TransformationType_values[] = {
    QTransform::TxNone
    , QTransform::TxTranslate
    , QTransform::TxScale
    , QTransform::TxRotate
    , QTransform::TxShear
    , QTransform::TxProject
};

static const char * const qtscript_QTransform_TransformationType_keys[] = {
    "TxNone"
    , "TxTranslate"
    , "TxScale"
    , "TxRotate"
    , "TxShear"
    , "TxProject"
};

static QString qtscript_QTransform_TransformationType_toStringHelper(QTransform::TransformationType value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QTransform_TransformationType_values[i] == value)
            return QString::fromLatin1(qtscript_QTransform_TransformationType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTransform_TransformationType_toScriptValue(QScriptEngine *engine, const QTransform::TransformationType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTransform"));
    return clazz.property(qtscript_QTransform_TransformationType_toStringHelper(value));
}

static void qtscript_QTransform_TransformationType_fromScriptValue(const QScriptValue &value, QTransform::TransformationType &out)
{
    out = qvariant_cast<QTransform::TransformationType>(value.toVariant());
}

static QScriptValue qtscript_construct_QTransform_TransformationType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QTransform_TransformationType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTransform::TransformationType>(arg));
    }
    return context->throwError(QString::fromLatin1("TransformationType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTransform_TransformationType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTransform::TransformationType value = qscriptvalue_cast<QTransform::TransformationType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTransform_TransformationType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTransform::TransformationType value = qscriptvalue_cast<QTransform::TransformationType>(context->thisObject());
    return QScriptValue(engine, qtscript_QTransform_TransformationType_toStringHelper(value));
}

static QScriptValue qtscript_create_QTransform_TransformationType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTransform_TransformationType,
        qtscript_QTransform_TransformationType_valueOf, qtscript_QTransform_TransformationType_toString);
    qScriptRegisterMetaType<QTransform::TransformationType>(engine, qtscript_QTransform_TransformationType_toScriptValue,
        qtscript_QTransform_TransformationType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTransform_TransformationType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTransform_TransformationType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTransform
//

static QScriptValue qtscript_QTransform_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 40;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTransform* _q_self = qscriptvalue_cast<QTransform*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTransform.%0(): this object is not a QTransform")
            .arg(qtscript_QTransform_function_names[_id+6]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->adjoint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->det();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->determinant();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dx();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->inverted();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAffine();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isIdentity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isInvertible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRotating();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isScaling();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTranslating();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m11();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m12();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m13();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m21();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m22();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m23();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m31();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m32();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->m33();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
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

    case 22:
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

    case 23:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QPolygon _q_result = _q_self->mapToPolygon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        QTransform _q_result = _q_self->operator*(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTransform& _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTransform& _q_result = _q_self->operator/=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QTransform& _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qreal>() == context->argument(0).toVariant().userType())) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            QTransform& _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTransform& _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTransform& _q_result = _q_self->rotate(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        Qt::Axis _q_arg1 = qscriptvalue_cast<Qt::Axis>(context->argument(1));
        QTransform& _q_result = _q_self->rotate(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTransform& _q_result = _q_self->rotateRadians(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        Qt::Axis _q_arg1 = qscriptvalue_cast<Qt::Axis>(context->argument(1));
        QTransform& _q_result = _q_self->rotateRadians(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTransform& _q_result = _q_self->scale(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 9) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        qreal _q_arg6 = qscriptvalue_cast<qreal>(context->argument(6));
        qreal _q_arg7 = qscriptvalue_cast<qreal>(context->argument(7));
        qreal _q_arg8 = qscriptvalue_cast<qreal>(context->argument(8));
        _q_self->setMatrix(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTransform& _q_result = _q_self->shear(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        const QMatrix& _q_result = _q_self->toAffine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTransform& _q_result = _q_self->translate(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->transposed();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 0) {
        QTransform::TransformationType _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTransform_throw_ambiguity_error_helper(context,
        qtscript_QTransform_function_names[_id+6],
        qtscript_QTransform_function_signatures[_id+6]);
}

static QScriptValue qtscript_QTransform_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTransform(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTransform _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        QTransform _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        QTransform _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 8) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        qreal _q_arg6 = qscriptvalue_cast<qreal>(context->argument(6));
        qreal _q_arg7 = qscriptvalue_cast<qreal>(context->argument(7));
        QTransform _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 9) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        qreal _q_arg6 = qscriptvalue_cast<qreal>(context->argument(6));
        qreal _q_arg7 = qscriptvalue_cast<qreal>(context->argument(7));
        qreal _q_arg8 = qscriptvalue_cast<qreal>(context->argument(8));
        QTransform _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTransform _q_result = QTransform::fromScale(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTransform _q_result = QTransform::fromTranslate(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QPolygonF _q_arg1 = qscriptvalue_cast<QPolygonF>(context->argument(1));
        QTransform _q_arg2 = qscriptvalue_cast<QTransform>(context->argument(2));
        bool _q_result = QTransform::quadToQuad(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QTransform _q_arg1 = qscriptvalue_cast<QTransform>(context->argument(1));
        bool _q_result = QTransform::quadToSquare(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QTransform _q_arg1 = qscriptvalue_cast<QTransform>(context->argument(1));
        bool _q_result = QTransform::squareToQuad(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTransform_throw_ambiguity_error_helper(context,
        qtscript_QTransform_function_names[_id],
        qtscript_QTransform_function_signatures[_id]);
}

QScriptValue qtscript_create_QTransform_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTransform*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTransform*)0));
    for (int i = 0; i < 41; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTransform_prototype_call, qtscript_QTransform_function_lengths[i+6]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTransform_function_names[i+6]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTransform>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTransform*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTransform_static_call, proto, qtscript_QTransform_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTransform_static_call,
            qtscript_QTransform_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QTransform_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("TransformationType"),
        qtscript_create_QTransform_TransformationType_class(engine, ctor));
    return ctor;
}
