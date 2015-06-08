#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstatemachine.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qobject.h>

static const char * const qtscript_QStateMachine_WrappedEvent_function_names[] = {
    "QStateMachine_WrappedEvent"
    // static
    // prototype
    , "event"
    , "object"
    , "toString"
};

static const char * const qtscript_QStateMachine_WrappedEvent_function_signatures[] = {
    "QObject object, QEvent event"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QStateMachine_WrappedEvent_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QStateMachine_WrappedEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStateMachine_WrappedEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStateMachine::WrappedEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QStateMachine_WrappedEvent
//

static QScriptValue qtscript_QStateMachine_WrappedEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStateMachine::WrappedEvent* _q_self = qscriptvalue_cast<QStateMachine::WrappedEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStateMachine_WrappedEvent.%0(): this object is not a QStateMachine_WrappedEvent")
            .arg(qtscript_QStateMachine_WrappedEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QEvent* _q_result = _q_self->event();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->object();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QStateMachine_WrappedEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStateMachine_WrappedEvent_throw_ambiguity_error_helper(context,
        qtscript_QStateMachine_WrappedEvent_function_names[_id+1],
        qtscript_QStateMachine_WrappedEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStateMachine_WrappedEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStateMachine_WrappedEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        QStateMachine::WrappedEvent* _q_cpp_result = new QStateMachine::WrappedEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStateMachine_WrappedEvent_throw_ambiguity_error_helper(context,
        qtscript_QStateMachine_WrappedEvent_function_names[_id],
        qtscript_QStateMachine_WrappedEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QStateMachine_WrappedEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStateMachine::WrappedEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStateMachine::WrappedEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStateMachine_WrappedEvent_prototype_call, qtscript_QStateMachine_WrappedEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStateMachine_WrappedEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QStateMachine::WrappedEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStateMachine_WrappedEvent_static_call, proto, qtscript_QStateMachine_WrappedEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
