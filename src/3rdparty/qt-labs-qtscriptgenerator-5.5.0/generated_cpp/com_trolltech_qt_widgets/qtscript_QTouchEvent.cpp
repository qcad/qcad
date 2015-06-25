#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qevent.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qevent.h>
#include <qlist.h>
#include <qobject.h>

static const char * const qtscript_QTouchEvent_function_names[] = {
    "QTouchEvent"
    // static
    // prototype
    , "setTarget"
    , "setTouchPointStates"
    , "setTouchPoints"
    , "target"
    , "touchPointStates"
    , "touchPoints"
    , "toString"
};

static const char * const qtscript_QTouchEvent_function_signatures[] = {
    ""
    // static
    // prototype
    , "QObject atarget"
    , "TouchPointStates aTouchPointStates"
    , "List atouchPoints"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTouchEvent_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTouchEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTouchEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTouchEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::TouchPointState>)
Q_DECLARE_METATYPE(QTouchEvent::TouchPoint)
Q_DECLARE_METATYPE(QList<QTouchEvent::TouchPoint >)
Q_DECLARE_METATYPE(QInputEvent*)

//
// QTouchEvent
//

static QScriptValue qtscript_QTouchEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTouchEvent* _q_self = qscriptvalue_cast<QTouchEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTouchEvent.%0(): this object is not a QTouchEvent")
            .arg(qtscript_QTouchEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->setTarget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QFlags<Qt::TouchPointState> _q_arg0 = qscriptvalue_cast<QFlags<Qt::TouchPointState> >(context->argument(0));
        _q_self->setTouchPointStates(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QList<QTouchEvent::TouchPoint> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setTouchPoints(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->target();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QFlags<Qt::TouchPointState> _q_result = _q_self->touchPointStates();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        const QList<QTouchEvent::TouchPoint >& _q_result = _q_self->touchPoints();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QTouchEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTouchEvent_throw_ambiguity_error_helper(context,
        qtscript_QTouchEvent_function_names[_id+1],
        qtscript_QTouchEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTouchEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QTouchEvent cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTouchEvent_throw_ambiguity_error_helper(context,
        qtscript_QTouchEvent_function_names[_id],
        qtscript_QTouchEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QTouchEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTouchEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTouchEvent_prototype_call, qtscript_QTouchEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTouchEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTouchEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTouchEvent_static_call, proto, qtscript_QTouchEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
