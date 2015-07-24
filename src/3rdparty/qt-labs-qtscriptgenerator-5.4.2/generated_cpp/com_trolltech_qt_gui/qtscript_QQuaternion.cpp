#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qquaternion.h>
#include <QVariant>
#include <qquaternion.h>
#include <qvector3d.h>
#include <qvector4d.h>

static const char * const qtscript_QQuaternion_function_names[] = {
    "QQuaternion"
    // static
    , "fromAxisAndAngle"
    , "nlerp"
    , "slerp"
    // prototype
    , "conjugate"
    , "isIdentity"
    , "isNull"
    , "length"
    , "lengthSquared"
    , "normalize"
    , "normalized"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "rotatedVector"
    , "scalar"
    , "setScalar"
    , "setVector"
    , "setX"
    , "setY"
    , "setZ"
    , "toVector4D"
    , "vector"
    , "x"
    , "y"
    , "z"
    , "toString"
};

static const char * const qtscript_QQuaternion_function_signatures[] = {
    "\nQVector4D vector\nfloat scalar, QVector3D vector\nfloat scalar, float xpos, float ypos, float zpos"
    // static
    , "QVector3D axis, float angle\nfloat x, float y, float z, float angle"
    , "QQuaternion q1, QQuaternion q2, float t"
    , "QQuaternion q1, QQuaternion q2, float t"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QQuaternion quaternion"
    , "float divisor"
    , "QQuaternion q2"
    , "QQuaternion quaternion\nfloat factor"
    , "QQuaternion quaternion"
    , "QVector3D vector"
    , ""
    , "float scalar"
    , "QVector3D vector\nfloat x, float y, float z"
    , "float x"
    , "float y"
    , "float z"
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QQuaternion_function_lengths[] = {
    4
    // static
    , 4
    , 3
    , 3
    // prototype
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
    , 0
    , 1
    , 3
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QQuaternion_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QQuaternion::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QQuaternion*)

//
// QQuaternion
//

static QScriptValue qtscript_QQuaternion_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QQuaternion* _q_self = qscriptvalue_cast<QQuaternion*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QQuaternion.%0(): this object is not a QQuaternion")
            .arg(qtscript_QQuaternion_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QQuaternion _q_result = _q_self->conjugate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isIdentity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->length();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->lengthSquared();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->normalize();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QQuaternion _q_result = _q_self->normalized();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
        QQuaternion& _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        QQuaternion& _q_result = _q_self->operator/=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QQuaternion>() == context->argument(0).toVariant().userType())) {
            QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
            QQuaternion& _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            QQuaternion& _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
        QQuaternion& _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
        QVector3D _q_result = _q_self->rotatedVector(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->scalar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setScalar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
        _q_self->setVector(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
        float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
        _q_self->setVector(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setZ(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QVector4D _q_result = _q_self->toVector4D();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QVector3D _q_result = _q_self->vector();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->x();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->y();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->z();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QQuaternion_throw_ambiguity_error_helper(context,
        qtscript_QQuaternion_function_names[_id+4],
        qtscript_QQuaternion_function_signatures[_id+4]);
}

static QScriptValue qtscript_QQuaternion_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QQuaternion(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QQuaternion _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QVector4D _q_arg0 = qscriptvalue_cast<QVector4D>(context->argument(0));
        QQuaternion _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
        QQuaternion _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
        float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
        float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
        QQuaternion _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QVector3D _q_arg0 = qscriptvalue_cast<QVector3D>(context->argument(0));
        float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
        QQuaternion _q_result = QQuaternion::fromAxisAndAngle(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
        float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
        float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
        QQuaternion _q_result = QQuaternion::fromAxisAndAngle(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
        QQuaternion _q_arg1 = qscriptvalue_cast<QQuaternion>(context->argument(1));
        float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
        QQuaternion _q_result = QQuaternion::nlerp(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QQuaternion _q_arg0 = qscriptvalue_cast<QQuaternion>(context->argument(0));
        QQuaternion _q_arg1 = qscriptvalue_cast<QQuaternion>(context->argument(1));
        float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
        QQuaternion _q_result = QQuaternion::slerp(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QQuaternion_throw_ambiguity_error_helper(context,
        qtscript_QQuaternion_function_names[_id],
        qtscript_QQuaternion_function_signatures[_id]);
}

QScriptValue qtscript_create_QQuaternion_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QQuaternion*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QQuaternion*)0));
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QQuaternion_prototype_call, qtscript_QQuaternion_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QQuaternion_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QQuaternion>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QQuaternion*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QQuaternion_static_call, proto, qtscript_QQuaternion_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QQuaternion_static_call,
            qtscript_QQuaternion_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QQuaternion_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
