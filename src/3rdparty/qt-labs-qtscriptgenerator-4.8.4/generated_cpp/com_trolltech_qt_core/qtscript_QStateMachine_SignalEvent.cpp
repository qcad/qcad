#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstatemachine.h>
#include <QVariant>
#include <qlist.h>
#include <qobject.h>

static const char * const qtscript_QStateMachine_SignalEvent_function_names[] = {
    "QStateMachine_SignalEvent"
    // static
    // prototype
    , "arguments"
    , "sender"
    , "signalIndex"
    , "toString"
};

static const char * const qtscript_QStateMachine_SignalEvent_function_signatures[] = {
    "QObject sender, int signalIndex, List arguments"
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QStateMachine_SignalEvent_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QStateMachine_SignalEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStateMachine_SignalEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStateMachine::SignalEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QStateMachine_SignalEvent
//

static QScriptValue qtscript_QStateMachine_SignalEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStateMachine::SignalEvent* _q_self = qscriptvalue_cast<QStateMachine::SignalEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStateMachine_SignalEvent.%0(): this object is not a QStateMachine_SignalEvent")
            .arg(qtscript_QStateMachine_SignalEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QVariant> _q_result = _q_self->arguments();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->sender();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->signalIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QStateMachine_SignalEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStateMachine_SignalEvent_throw_ambiguity_error_helper(context,
        qtscript_QStateMachine_SignalEvent_function_names[_id+1],
        qtscript_QStateMachine_SignalEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStateMachine_SignalEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStateMachine_SignalEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        int _q_arg1 = context->argument(1).toInt32();
        QList<QVariant> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QStateMachine::SignalEvent* _q_cpp_result = new QStateMachine::SignalEvent(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStateMachine_SignalEvent_throw_ambiguity_error_helper(context,
        qtscript_QStateMachine_SignalEvent_function_names[_id],
        qtscript_QStateMachine_SignalEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QStateMachine_SignalEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStateMachine::SignalEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStateMachine::SignalEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStateMachine_SignalEvent_prototype_call, qtscript_QStateMachine_SignalEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStateMachine_SignalEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QStateMachine::SignalEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStateMachine_SignalEvent_static_call, proto, qtscript_QStateMachine_SignalEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
