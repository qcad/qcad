#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qline.h>
#include <QVariant>
#include <qdatastream.h>
#include <qline.h>
#include <qpoint.h>

static const char * const qtscript_QLineF_function_names[] = {
    "QLineF"
    // static
    , "fromPolar"
    // prototype
    , "angle"
    , "angleTo"
    , "dx"
    , "dy"
    , "intersect"
    , "isNull"
    , "length"
    , "normalVector"
    , "equals"
    , "p1"
    , "p2"
    , "pointAt"
    , "readFrom"
    , "setAngle"
    , "setLength"
    , "setLine"
    , "setP1"
    , "setP2"
    , "setPoints"
    , "toLine"
    , "translate"
    , "translated"
    , "unitVector"
    , "writeTo"
    , "x1"
    , "x2"
    , "y1"
    , "y2"
    , "toString"
};

static const char * const qtscript_QLineF_function_signatures[] = {
    "\nQLine line\nQPointF pt1, QPointF pt2\nqreal x1, qreal y1, qreal x2, qreal y2"
    // static
    , "qreal length, qreal angle"
    // prototype
    , "\nQLineF l"
    , "QLineF l"
    , ""
    , ""
    , "QLineF l, QPointF intersectionPoint"
    , ""
    , ""
    , ""
    , "QLineF d"
    , ""
    , ""
    , "qreal t"
    , "QDataStream arg__1"
    , "qreal angle"
    , "qreal len"
    , "qreal x1, qreal y1, qreal x2, qreal y2"
    , "QPointF p1"
    , "QPointF p2"
    , "QPointF p1, QPointF p2"
    , ""
    , "QPointF p\nqreal dx, qreal dy"
    , "QPointF p\nqreal dx, qreal dy"
    , ""
    , "QDataStream arg__1"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QLineF_function_lengths[] = {
    4
    // static
    , 2
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 4
    , 1
    , 1
    , 2
    , 0
    , 2
    , 2
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QLineF_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLineF::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLineF*)
Q_DECLARE_METATYPE(QLineF::IntersectType)
Q_DECLARE_METATYPE(QPointF*)
Q_DECLARE_METATYPE(QDataStream*)

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
// QLineF::IntersectType
//

static const QLineF::IntersectType qtscript_QLineF_IntersectType_values[] = {
    QLineF::NoIntersection
    , QLineF::BoundedIntersection
    , QLineF::UnboundedIntersection
};

static const char * const qtscript_QLineF_IntersectType_keys[] = {
    "NoIntersection"
    , "BoundedIntersection"
    , "UnboundedIntersection"
};

static QString qtscript_QLineF_IntersectType_toStringHelper(QLineF::IntersectType value)
{
    if ((value >= QLineF::NoIntersection) && (value <= QLineF::UnboundedIntersection))
        return qtscript_QLineF_IntersectType_keys[static_cast<int>(value)-static_cast<int>(QLineF::NoIntersection)];
    return QString();
}

static QScriptValue qtscript_QLineF_IntersectType_toScriptValue(QScriptEngine *engine, const QLineF::IntersectType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLineF"));
    return clazz.property(qtscript_QLineF_IntersectType_toStringHelper(value));
}

static void qtscript_QLineF_IntersectType_fromScriptValue(const QScriptValue &value, QLineF::IntersectType &out)
{
    out = qvariant_cast<QLineF::IntersectType>(value.toVariant());
}

static QScriptValue qtscript_construct_QLineF_IntersectType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QLineF::NoIntersection) && (arg <= QLineF::UnboundedIntersection))
        return qScriptValueFromValue(engine,  static_cast<QLineF::IntersectType>(arg));
    return context->throwError(QString::fromLatin1("IntersectType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLineF_IntersectType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLineF::IntersectType value = qscriptvalue_cast<QLineF::IntersectType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLineF_IntersectType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLineF::IntersectType value = qscriptvalue_cast<QLineF::IntersectType>(context->thisObject());
    return QScriptValue(engine, qtscript_QLineF_IntersectType_toStringHelper(value));
}

static QScriptValue qtscript_create_QLineF_IntersectType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLineF_IntersectType,
        qtscript_QLineF_IntersectType_valueOf, qtscript_QLineF_IntersectType_toString);
    qScriptRegisterMetaType<QLineF::IntersectType>(engine, qtscript_QLineF_IntersectType_toScriptValue,
        qtscript_QLineF_IntersectType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLineF_IntersectType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLineF_IntersectType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLineF
//

static QScriptValue qtscript_QLineF_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 28;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QLineF* _q_self = qscriptvalue_cast<QLineF*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLineF.%0(): this object is not a QLineF")
            .arg(qtscript_QLineF_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->angle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        qreal _q_result = _q_self->angle(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        qreal _q_result = _q_self->angleTo(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dx();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        QPointF* _q_arg1 = qscriptvalue_cast<QPointF*>(context->argument(1));
        QLineF::IntersectType _q_result = _q_self->intersect(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->length();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QLineF _q_result = _q_self->normalVector();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->p1();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->p2();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPointF _q_result = _q_self->pointAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setAngle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setLength(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setLine(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setP1(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setP2(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        _q_self->setPoints(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QLine _q_result = _q_self->toLine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QLineF _q_result = _q_self->translated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QLineF _q_result = _q_self->translated(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QLineF _q_result = _q_self->unitVector();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->x1();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->x2();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->y1();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->y2();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLineF_throw_ambiguity_error_helper(context,
        qtscript_QLineF_function_names[_id+2],
        qtscript_QLineF_function_signatures[_id+2]);
}

static QScriptValue qtscript_QLineF_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLineF(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QLineF _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QLine _q_arg0 = qscriptvalue_cast<QLine>(context->argument(0));
        QLineF _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QLineF _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QLineF _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QLineF _q_result = QLineF::fromPolar(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLineF_throw_ambiguity_error_helper(context,
        qtscript_QLineF_function_names[_id],
        qtscript_QLineF_function_signatures[_id]);
}

QScriptValue qtscript_create_QLineF_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLineF*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLineF*)0));
    for (int i = 0; i < 29; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLineF_prototype_call, qtscript_QLineF_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLineF_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QLineF>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QLineF*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLineF_static_call, proto, qtscript_QLineF_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLineF_static_call,
            qtscript_QLineF_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLineF_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("IntersectType"),
        qtscript_create_QLineF_IntersectType_class(engine, ctor));
    return ctor;
}
