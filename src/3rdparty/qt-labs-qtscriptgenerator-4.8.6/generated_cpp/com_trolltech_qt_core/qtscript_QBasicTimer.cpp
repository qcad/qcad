#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbasictimer.h>
#include <QVariant>
#include <qobject.h>

static const char * const qtscript_QBasicTimer_function_names[] = {
    "QBasicTimer"
    // static
    // prototype
    , "isActive"
    , "start"
    , "stop"
    , "timerId"
    , "toString"
};

static const char * const qtscript_QBasicTimer_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "int msec, QObject obj"
    , ""
    , ""
""
};

static const int qtscript_QBasicTimer_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 2
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QBasicTimer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QBasicTimer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QBasicTimer)
Q_DECLARE_METATYPE(QBasicTimer*)

//
// QBasicTimer
//

static QScriptValue qtscript_QBasicTimer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QBasicTimer* _q_self = qscriptvalue_cast<QBasicTimer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QBasicTimer.%0(): this object is not a QBasicTimer")
            .arg(qtscript_QBasicTimer_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QObject* _q_arg1 = context->argument(1).toQObject();
        _q_self->start(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->stop();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->timerId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QBasicTimer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBasicTimer_throw_ambiguity_error_helper(context,
        qtscript_QBasicTimer_function_names[_id+1],
        qtscript_QBasicTimer_function_signatures[_id+1]);
}

static QScriptValue qtscript_QBasicTimer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QBasicTimer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QBasicTimer _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBasicTimer_throw_ambiguity_error_helper(context,
        qtscript_QBasicTimer_function_names[_id],
        qtscript_QBasicTimer_function_signatures[_id]);
}

QScriptValue qtscript_create_QBasicTimer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QBasicTimer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QBasicTimer*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QBasicTimer_prototype_call, qtscript_QBasicTimer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QBasicTimer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QBasicTimer>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QBasicTimer*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QBasicTimer_static_call, proto, qtscript_QBasicTimer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
