#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtimeline.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qeasingcurve.h>
#include <qlist.h>
#include <qobject.h>
#include <qtimeline.h>

#include "qtscriptshell_QTimeLine.h"

static const char * const qtscript_QTimeLine_function_names[] = {
    "QTimeLine"
    // static
    // prototype
    , "currentFrame"
    , "currentValue"
    , "endFrame"
    , "frameForTime"
    , "setEndFrame"
    , "setFrameRange"
    , "setStartFrame"
    , "startFrame"
    , "state"
    , "valueForTime"
    , "toString"
};

static const char * const qtscript_QTimeLine_function_signatures[] = {
    "int duration, QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "int msec"
    , "int frame"
    , "int startFrame, int endFrame"
    , "int frame"
    , ""
    , ""
    , "int msec"
""
};

static const int qtscript_QTimeLine_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTimeLine_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTimeLine::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTimeLine*)
Q_DECLARE_METATYPE(QtScriptShell_QTimeLine*)
Q_DECLARE_METATYPE(QTimeLine::Direction)
Q_DECLARE_METATYPE(QTimeLine::CurveShape)
Q_DECLARE_METATYPE(QTimeLine::State)

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
// QTimeLine::Direction
//

static const QTimeLine::Direction qtscript_QTimeLine_Direction_values[] = {
    QTimeLine::Forward
    , QTimeLine::Backward
};

static const char * const qtscript_QTimeLine_Direction_keys[] = {
    "Forward"
    , "Backward"
};

static QString qtscript_QTimeLine_Direction_toStringHelper(QTimeLine::Direction value)
{
    if ((value >= QTimeLine::Forward) && (value <= QTimeLine::Backward))
        return qtscript_QTimeLine_Direction_keys[static_cast<int>(value)-static_cast<int>(QTimeLine::Forward)];
    return QString();
}

static QScriptValue qtscript_QTimeLine_Direction_toScriptValue(QScriptEngine *engine, const QTimeLine::Direction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTimeLine"));
    return clazz.property(qtscript_QTimeLine_Direction_toStringHelper(value));
}

static void qtscript_QTimeLine_Direction_fromScriptValue(const QScriptValue &value, QTimeLine::Direction &out)
{
    out = qvariant_cast<QTimeLine::Direction>(value.toVariant());
}

static QScriptValue qtscript_construct_QTimeLine_Direction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTimeLine::Forward) && (arg <= QTimeLine::Backward))
        return qScriptValueFromValue(engine,  static_cast<QTimeLine::Direction>(arg));
    return context->throwError(QString::fromLatin1("Direction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTimeLine_Direction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTimeLine::Direction value = qscriptvalue_cast<QTimeLine::Direction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTimeLine_Direction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTimeLine::Direction value = qscriptvalue_cast<QTimeLine::Direction>(context->thisObject());
    return QScriptValue(engine, qtscript_QTimeLine_Direction_toStringHelper(value));
}

static QScriptValue qtscript_create_QTimeLine_Direction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTimeLine_Direction,
        qtscript_QTimeLine_Direction_valueOf, qtscript_QTimeLine_Direction_toString);
    qScriptRegisterMetaType<QTimeLine::Direction>(engine, qtscript_QTimeLine_Direction_toScriptValue,
        qtscript_QTimeLine_Direction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTimeLine_Direction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTimeLine_Direction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTimeLine::CurveShape
//

static const QTimeLine::CurveShape qtscript_QTimeLine_CurveShape_values[] = {
    QTimeLine::EaseInCurve
    , QTimeLine::EaseOutCurve
    , QTimeLine::EaseInOutCurve
    , QTimeLine::LinearCurve
    , QTimeLine::SineCurve
    , QTimeLine::CosineCurve
};

static const char * const qtscript_QTimeLine_CurveShape_keys[] = {
    "EaseInCurve"
    , "EaseOutCurve"
    , "EaseInOutCurve"
    , "LinearCurve"
    , "SineCurve"
    , "CosineCurve"
};

static QString qtscript_QTimeLine_CurveShape_toStringHelper(QTimeLine::CurveShape value)
{
    if ((value >= QTimeLine::EaseInCurve) && (value <= QTimeLine::CosineCurve))
        return qtscript_QTimeLine_CurveShape_keys[static_cast<int>(value)-static_cast<int>(QTimeLine::EaseInCurve)];
    return QString();
}

static QScriptValue qtscript_QTimeLine_CurveShape_toScriptValue(QScriptEngine *engine, const QTimeLine::CurveShape &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTimeLine"));
    return clazz.property(qtscript_QTimeLine_CurveShape_toStringHelper(value));
}

static void qtscript_QTimeLine_CurveShape_fromScriptValue(const QScriptValue &value, QTimeLine::CurveShape &out)
{
    out = qvariant_cast<QTimeLine::CurveShape>(value.toVariant());
}

static QScriptValue qtscript_construct_QTimeLine_CurveShape(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTimeLine::EaseInCurve) && (arg <= QTimeLine::CosineCurve))
        return qScriptValueFromValue(engine,  static_cast<QTimeLine::CurveShape>(arg));
    return context->throwError(QString::fromLatin1("CurveShape(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTimeLine_CurveShape_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTimeLine::CurveShape value = qscriptvalue_cast<QTimeLine::CurveShape>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTimeLine_CurveShape_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTimeLine::CurveShape value = qscriptvalue_cast<QTimeLine::CurveShape>(context->thisObject());
    return QScriptValue(engine, qtscript_QTimeLine_CurveShape_toStringHelper(value));
}

static QScriptValue qtscript_create_QTimeLine_CurveShape_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTimeLine_CurveShape,
        qtscript_QTimeLine_CurveShape_valueOf, qtscript_QTimeLine_CurveShape_toString);
    qScriptRegisterMetaType<QTimeLine::CurveShape>(engine, qtscript_QTimeLine_CurveShape_toScriptValue,
        qtscript_QTimeLine_CurveShape_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTimeLine_CurveShape_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTimeLine_CurveShape_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTimeLine::State
//

static const QTimeLine::State qtscript_QTimeLine_State_values[] = {
    QTimeLine::NotRunning
    , QTimeLine::Paused
    , QTimeLine::Running
};

static const char * const qtscript_QTimeLine_State_keys[] = {
    "NotRunning"
    , "Paused"
    , "Running"
};

static QString qtscript_QTimeLine_State_toStringHelper(QTimeLine::State value)
{
    if ((value >= QTimeLine::NotRunning) && (value <= QTimeLine::Running))
        return qtscript_QTimeLine_State_keys[static_cast<int>(value)-static_cast<int>(QTimeLine::NotRunning)];
    return QString();
}

static QScriptValue qtscript_QTimeLine_State_toScriptValue(QScriptEngine *engine, const QTimeLine::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTimeLine"));
    return clazz.property(qtscript_QTimeLine_State_toStringHelper(value));
}

static void qtscript_QTimeLine_State_fromScriptValue(const QScriptValue &value, QTimeLine::State &out)
{
    out = qvariant_cast<QTimeLine::State>(value.toVariant());
}

static QScriptValue qtscript_construct_QTimeLine_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTimeLine::NotRunning) && (arg <= QTimeLine::Running))
        return qScriptValueFromValue(engine,  static_cast<QTimeLine::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTimeLine_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTimeLine::State value = qscriptvalue_cast<QTimeLine::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTimeLine_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTimeLine::State value = qscriptvalue_cast<QTimeLine::State>(context->thisObject());
    return QScriptValue(engine, qtscript_QTimeLine_State_toStringHelper(value));
}

static QScriptValue qtscript_create_QTimeLine_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTimeLine_State,
        qtscript_QTimeLine_State_valueOf, qtscript_QTimeLine_State_toString);
    qScriptRegisterMetaType<QTimeLine::State>(engine, qtscript_QTimeLine_State_toScriptValue,
        qtscript_QTimeLine_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTimeLine_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTimeLine_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTimeLine
//

static QScriptValue qtscript_QTimeLine_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTimeLine* _q_self = qscriptvalue_cast<QTimeLine*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTimeLine.%0(): this object is not a QTimeLine")
            .arg(qtscript_QTimeLine_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentFrame();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->currentValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->endFrame();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->frameForTime(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setEndFrame(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setFrameRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setStartFrame(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->startFrame();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QTimeLine::State _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->valueForTime(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QTimeLine");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTimeLine_throw_ambiguity_error_helper(context,
        qtscript_QTimeLine_function_names[_id+1],
        qtscript_QTimeLine_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTimeLine_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTimeLine(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTimeLine* _q_cpp_result = new QtScriptShell_QTimeLine();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeLine*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QtScriptShell_QTimeLine* _q_cpp_result = new QtScriptShell_QTimeLine(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeLine*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QTimeLine* _q_cpp_result = new QtScriptShell_QTimeLine(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeLine*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTimeLine_throw_ambiguity_error_helper(context,
        qtscript_QTimeLine_function_names[_id],
        qtscript_QTimeLine_function_signatures[_id]);
}

static QScriptValue qtscript_QTimeLine_toScriptValue(QScriptEngine *engine, QTimeLine* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTimeLine_fromScriptValue(const QScriptValue &value, QTimeLine* &out)
{
    out = qobject_cast<QTimeLine*>(value.toQObject());
}

QScriptValue qtscript_create_QTimeLine_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTimeLine*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTimeLine*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTimeLine_prototype_call, qtscript_QTimeLine_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTimeLine_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTimeLine*>(engine, qtscript_QTimeLine_toScriptValue, 
        qtscript_QTimeLine_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTimeLine_static_call, proto, qtscript_QTimeLine_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Direction"),
        qtscript_create_QTimeLine_Direction_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CurveShape"),
        qtscript_create_QTimeLine_CurveShape_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QTimeLine_State_class(engine, ctor));
    return ctor;
}
