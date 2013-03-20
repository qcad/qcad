#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>

static const char * const qtscript_QFocusEvent_function_names[] = {
    "QFocusEvent"
    // static
    // prototype
    , "gotFocus"
    , "lostFocus"
    , "reason"
    , "toString"
};

static const char * const qtscript_QFocusEvent_function_signatures[] = {
    "Type type, FocusReason reason"
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QFocusEvent_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QFocusEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFocusEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(Qt::FocusReason)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QEvent*)

//
// QFocusEvent
//

static QScriptValue qtscript_QFocusEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFocusEvent* _q_self = qscriptvalue_cast<QFocusEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFocusEvent.%0(): this object is not a QFocusEvent")
            .arg(qtscript_QFocusEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->gotFocus();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->lostFocus();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Qt::FocusReason _q_result = _q_self->reason();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QFocusEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFocusEvent_throw_ambiguity_error_helper(context,
        qtscript_QFocusEvent_function_names[_id+1],
        qtscript_QFocusEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFocusEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFocusEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QFocusEvent* _q_cpp_result = new QFocusEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        Qt::FocusReason _q_arg1 = qscriptvalue_cast<Qt::FocusReason>(context->argument(1));
        QFocusEvent* _q_cpp_result = new QFocusEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFocusEvent_throw_ambiguity_error_helper(context,
        qtscript_QFocusEvent_function_names[_id],
        qtscript_QFocusEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QFocusEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFocusEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFocusEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFocusEvent_prototype_call, qtscript_QFocusEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFocusEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QFocusEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFocusEvent_static_call, proto, qtscript_QFocusEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
