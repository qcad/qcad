#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmatrix4x4.h>
#include <QVariant>
#include <qdatastream.h>
#include <qgenericmatrix.h>
#include <qmatrix.h>
#include <qmatrix4x4.h>
#include <qpoint.h>
#include <qquaternion.h>
#include <qrect.h>
#include <qtransform.h>
#include <qvector3d.h>
#include <qvector4d.h>

static const char * const qtscript_QMatrix4x4_function_names[] = {
    "QMatrix4x4"
    // static
    // prototype
    , "column"
    , "constData"
    , "copyDataTo"
    , "data"
    , "determinant"
    , "fill"
    , "flipCoordinates"
    , "frustum"
    , "inverted"
    , "isIdentity"
    , "lookAt"
    , "map"
    , "mapRect"
    , "mapVector"
    , "normalMatrix"
    , "operator_add_assign"
    , "operator_cast_"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "optimize"
    , "ortho"
    , "perspective"
    , "readFrom"
    , "rotate"
    , "row"
    , "scale"
    , "setColumn"
    , "setRow"
    , "setToIdentity"
    , "toAffine"
    , "toTransform"
    , "translate"
    , "transposed"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QMatrix4x4_function_signatures[] = {
    "\nQMatrix matrix\nQTransform transform\nqreal values\nqreal values, int cols, int rows\nqreal m11, qreal m12, qreal m13, qreal m14, qreal m21, qreal m22, qreal m23, qreal m24, qreal m31, qreal m32, qreal m33, qreal m34, qreal m41, qreal m42, qreal m43, qreal m44"
    // static
    // prototype
    , "int index"
    , ""
    , "qreal values"
    , ""
    , ""
    , "qreal value"
    , ""
    , "qreal left, qreal right, qreal bottom, qreal top, qreal nearPlane, qreal farPlane"
    , "bool invertible"
    , ""
    , "QVector3D eye, QVector3D center, QVector3D up"
    , "QPoint point\nQPointF point\nQVector3D point\nQVector4D point"
    , "QRect rect\nQRectF rect"
    , "QVector3D vector"
    , ""
    , "QMatrix4x4 other"
    , "int row, int column"
    , "qreal divisor"
    , "QMatrix4x4 other"
    , "QMatrix4x4 other\nqreal factor"
    , "QMatrix4x4 other"
    , ""
    , "QRect rect\nQRectF rect\nqreal left, qreal right, qreal bottom, qreal top, qreal nearPlane, qreal farPlane"
    , "qreal angle, qreal aspect, qreal nearPlane, qreal farPlane"
    , "QDataStream arg__1"
    , "QQuaternion quaternion\nqreal angle, QVector3D vector\nqreal angle, qreal x, qreal y, qreal z"
    , "int index"
    , "QVector3D vector\nqreal factor\nqreal x, qreal y\nqreal x, qreal y, qreal z"
    , "int index, QVector4D value"
    , "int index, QVector4D value"
    , ""
    , ""
    , "\nqreal distanceToPlane"
    , "QVector3D vector\nqreal x, qreal y\nqreal x, qreal y, qreal z"
    , ""
    , "QDataStream arg__1"
""
};

static const int qtscript_QMatrix4x4_function_lengths[] = {
    16
    // static
    // prototype
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 6
    , 1
    , 0
    , 3
    , 1
    , 1
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 6
    , 4
    , 1
    , 4
    , 1
    , 3
    , 2
    , 2
    , 0
    , 0
    , 1
    , 3
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QMatrix4x4_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMatrix4x4::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMatrix4x4*)
Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QDataStream*)

//
// QMatrix4x4
//

static QScriptValue qtscript_QMatrix4x4_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 36;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMatrix4x4* _q_self = qscriptvalue_cast<QMatrix4x4*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMatrix4x4.%0(): this object is not a QMatrix4x4")
            .arg(qtscript_QMatrix4x4_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector4D _q_result = _q_self->column(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal* _q_result = const_cast<qreal*>(_q_self->constData());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
        _q_self->copyDataTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal* _q_result = _q_self->data();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->determinant();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->fill(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->flipCoordinates();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->frustum(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QMatrix4x4 _q_result = _q_self->inverted();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool* _q_arg0 = qscriptvalue_cast<bool*>(context->argument(0));
        QMatrix4x4 _q_result = _q_self->inverted(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isIdentity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 3) {
        QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
        QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
        QVector3D _q_arg2 = qscriptvalue_cast<QVector3D>(context->argument(2));
        _q_self->lookAt(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPoint _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QVector3D>() == context->argument(0).toVariant().userType())) {
            QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
            QVector3D _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QVector4D>() == context->argument(0).toVariant().userType())) {
            QVector4D _q_arg0 = qscriptvalue_cast<QVector4D>(context->argument(0));
            QVector4D _q_result = _q_self->map(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 12:
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

    case 13:
    if (context->argumentCount() == 1) {
        QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
        QVector3D _q_result = _q_self->mapVector(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QMatrix3x3 _q_result = _q_self->normalMatrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QMatrix4x4 _q_arg0 = qscriptvalue_cast<QMatrix4x4>(context->argument(0));
        QMatrix4x4 _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        qreal _q_result = _q_self->operator()(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QMatrix4x4 _q_result = _q_self->operator/=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QMatrix4x4 _q_arg0 = qscriptvalue_cast<QMatrix4x4>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix4x4>() == context->argument(0).toVariant().userType())) {
            QMatrix4x4 _q_arg0 = qscriptvalue_cast<QMatrix4x4>(context->argument(0));
            QMatrix4x4 _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qreal>() == context->argument(0).toVariant().userType())) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            QMatrix4x4 _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QMatrix4x4 _q_arg0 = qscriptvalue_cast<QMatrix4x4>(context->argument(0));
        QMatrix4x4 _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        _q_self->optimize();
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->ortho(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->ortho(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->ortho(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->perspective(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
        _q_self->rotate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
        _q_self->rotate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->rotate(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->rotate(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector4D _q_result = _q_self->row(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QVector3D>() == context->argument(0).toVariant().userType())) {
            QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
            _q_self->scale(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<qreal>() == context->argument(0).toVariant().userType())) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            _q_self->scale(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->scale(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->scale(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector4D _q_arg1 = qscriptvalue_cast<QVector4D>(context->argument(1));
        _q_self->setColumn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector4D _q_arg1 = qscriptvalue_cast<QVector4D>(context->argument(1));
        _q_self->setRow(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        _q_self->setToIdentity();
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QMatrix _q_result = _q_self->toAffine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->toTransform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTransform _q_result = _q_self->toTransform(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->translate(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        QMatrix4x4 _q_result = _q_self->transposed();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 36: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMatrix4x4_throw_ambiguity_error_helper(context,
        qtscript_QMatrix4x4_function_names[_id+1],
        qtscript_QMatrix4x4_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMatrix4x4_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMatrix4x4(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QMatrix4x4 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            QMatrix4x4 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QMatrix4x4 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<qreal*>(context->argument(0))) {
            qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
            QMatrix4x4 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QMatrix4x4 _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 16) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        qreal _q_arg6 = qscriptvalue_cast<qreal>(context->argument(6));
        qreal _q_arg7 = qscriptvalue_cast<qreal>(context->argument(7));
        qreal _q_arg8 = qscriptvalue_cast<qreal>(context->argument(8));
        qreal _q_arg9 = qscriptvalue_cast<qreal>(context->argument(9));
        qreal _q_arg10 = qscriptvalue_cast<qreal>(context->argument(10));
        qreal _q_arg11 = qscriptvalue_cast<qreal>(context->argument(11));
        qreal _q_arg12 = qscriptvalue_cast<qreal>(context->argument(12));
        qreal _q_arg13 = qscriptvalue_cast<qreal>(context->argument(13));
        qreal _q_arg14 = qscriptvalue_cast<qreal>(context->argument(14));
        qreal _q_arg15 = qscriptvalue_cast<qreal>(context->argument(15));
        QMatrix4x4 _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8, _q_arg9, _q_arg10, _q_arg11, _q_arg12, _q_arg13, _q_arg14, _q_arg15);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMatrix4x4_throw_ambiguity_error_helper(context,
        qtscript_QMatrix4x4_function_names[_id],
        qtscript_QMatrix4x4_function_signatures[_id]);
}

QScriptValue qtscript_create_QMatrix4x4_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMatrix4x4*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMatrix4x4*)0));
    for (int i = 0; i < 37; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMatrix4x4_prototype_call, qtscript_QMatrix4x4_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMatrix4x4_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMatrix4x4>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QMatrix4x4*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMatrix4x4_static_call, proto, qtscript_QMatrix4x4_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
