#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qeasingcurve.h>
#include <QVariant>
#include <qdatastream.h>

static const char * const qtscript_QEasingCurve_function_names[] = {
    "QEasingCurve"
    // static
    // prototype
    , "amplitude"
    , "overshoot"
    , "period"
    , "readFrom"
    , "setAmplitude"
    , "setOvershoot"
    , "setPeriod"
    , "setType"
    , "type"
    , "valueForProgress"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QEasingCurve_function_signatures[] = {
    "Type type"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
    , "qreal amplitude"
    , "qreal overshoot"
    , "qreal period"
    , "Type type"
    , ""
    , "qreal progress"
    , "QDataStream arg__1"
""
};

static const int qtscript_QEasingCurve_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QEasingCurve_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QEasingCurve::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QEasingCurve_metaObject()
{
    return &QEasingCurve::staticMetaObject;
}

Q_DECLARE_METATYPE(QEasingCurve*)
Q_DECLARE_METATYPE(QEasingCurve::Type)
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
// QEasingCurve::Type
//

static const QEasingCurve::Type qtscript_QEasingCurve_Type_values[] = {
    QEasingCurve::Linear
    , QEasingCurve::InQuad
    , QEasingCurve::OutQuad
    , QEasingCurve::InOutQuad
    , QEasingCurve::OutInQuad
    , QEasingCurve::InCubic
    , QEasingCurve::OutCubic
    , QEasingCurve::InOutCubic
    , QEasingCurve::OutInCubic
    , QEasingCurve::InQuart
    , QEasingCurve::OutQuart
    , QEasingCurve::InOutQuart
    , QEasingCurve::OutInQuart
    , QEasingCurve::InQuint
    , QEasingCurve::OutQuint
    , QEasingCurve::InOutQuint
    , QEasingCurve::OutInQuint
    , QEasingCurve::InSine
    , QEasingCurve::OutSine
    , QEasingCurve::InOutSine
    , QEasingCurve::OutInSine
    , QEasingCurve::InExpo
    , QEasingCurve::OutExpo
    , QEasingCurve::InOutExpo
    , QEasingCurve::OutInExpo
    , QEasingCurve::InCirc
    , QEasingCurve::OutCirc
    , QEasingCurve::InOutCirc
    , QEasingCurve::OutInCirc
    , QEasingCurve::InElastic
    , QEasingCurve::OutElastic
    , QEasingCurve::InOutElastic
    , QEasingCurve::OutInElastic
    , QEasingCurve::InBack
    , QEasingCurve::OutBack
    , QEasingCurve::InOutBack
    , QEasingCurve::OutInBack
    , QEasingCurve::InBounce
    , QEasingCurve::OutBounce
    , QEasingCurve::InOutBounce
    , QEasingCurve::OutInBounce
    , QEasingCurve::InCurve
    , QEasingCurve::OutCurve
    , QEasingCurve::SineCurve
    , QEasingCurve::CosineCurve
    , QEasingCurve::Custom
    , QEasingCurve::NCurveTypes
};

static const char * const qtscript_QEasingCurve_Type_keys[] = {
    "Linear"
    , "InQuad"
    , "OutQuad"
    , "InOutQuad"
    , "OutInQuad"
    , "InCubic"
    , "OutCubic"
    , "InOutCubic"
    , "OutInCubic"
    , "InQuart"
    , "OutQuart"
    , "InOutQuart"
    , "OutInQuart"
    , "InQuint"
    , "OutQuint"
    , "InOutQuint"
    , "OutInQuint"
    , "InSine"
    , "OutSine"
    , "InOutSine"
    , "OutInSine"
    , "InExpo"
    , "OutExpo"
    , "InOutExpo"
    , "OutInExpo"
    , "InCirc"
    , "OutCirc"
    , "InOutCirc"
    , "OutInCirc"
    , "InElastic"
    , "OutElastic"
    , "InOutElastic"
    , "OutInElastic"
    , "InBack"
    , "OutBack"
    , "InOutBack"
    , "OutInBack"
    , "InBounce"
    , "OutBounce"
    , "InOutBounce"
    , "OutInBounce"
    , "InCurve"
    , "OutCurve"
    , "SineCurve"
    , "CosineCurve"
    , "Custom"
    , "NCurveTypes"
};

static QString qtscript_QEasingCurve_Type_toStringHelper(QEasingCurve::Type value)
{
    const QMetaObject *meta = qtscript_QEasingCurve_metaObject();
    int idx = meta->indexOfEnumerator("Type");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QEasingCurve_Type_toScriptValue(QScriptEngine *engine, const QEasingCurve::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QEasingCurve"));
    return clazz.property(qtscript_QEasingCurve_Type_toStringHelper(value));
}

static void qtscript_QEasingCurve_Type_fromScriptValue(const QScriptValue &value, QEasingCurve::Type &out)
{
    out = qvariant_cast<QEasingCurve::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QEasingCurve_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QEasingCurve_metaObject();
    int idx = meta->indexOfEnumerator("Type");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QEasingCurve::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QEasingCurve_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QEasingCurve::Type value = qscriptvalue_cast<QEasingCurve::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QEasingCurve_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QEasingCurve::Type value = qscriptvalue_cast<QEasingCurve::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QEasingCurve_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QEasingCurve_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QEasingCurve_Type,
        qtscript_QEasingCurve_Type_valueOf, qtscript_QEasingCurve_Type_toString);
    qScriptRegisterMetaType<QEasingCurve::Type>(engine, qtscript_QEasingCurve_Type_toScriptValue,
        qtscript_QEasingCurve_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 47; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QEasingCurve_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QEasingCurve_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QEasingCurve
//

static QScriptValue qtscript_QEasingCurve_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QEasingCurve* _q_self = qscriptvalue_cast<QEasingCurve*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QEasingCurve.%0(): this object is not a QEasingCurve")
            .arg(qtscript_QEasingCurve_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->amplitude();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->overshoot();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->period();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setAmplitude(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setOvershoot(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPeriod(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QEasingCurve::Type _q_arg0 = qscriptvalue_cast<QEasingCurve::Type>(context->argument(0));
        _q_self->setType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QEasingCurve::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->valueForProgress(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 11: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QEasingCurve_throw_ambiguity_error_helper(context,
        qtscript_QEasingCurve_function_names[_id+1],
        qtscript_QEasingCurve_function_signatures[_id+1]);
}

static QScriptValue qtscript_QEasingCurve_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QEasingCurve(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QEasingCurve _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QEasingCurve::Type _q_arg0 = qscriptvalue_cast<QEasingCurve::Type>(context->argument(0));
        QEasingCurve _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QEasingCurve_throw_ambiguity_error_helper(context,
        qtscript_QEasingCurve_function_names[_id],
        qtscript_QEasingCurve_function_signatures[_id]);
}

QScriptValue qtscript_create_QEasingCurve_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QEasingCurve*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QEasingCurve*)0));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QEasingCurve_prototype_call, qtscript_QEasingCurve_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QEasingCurve_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QEasingCurve>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QEasingCurve*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QEasingCurve_static_call, proto, qtscript_QEasingCurve_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QEasingCurve_Type_class(engine, ctor));
    return ctor;
}
