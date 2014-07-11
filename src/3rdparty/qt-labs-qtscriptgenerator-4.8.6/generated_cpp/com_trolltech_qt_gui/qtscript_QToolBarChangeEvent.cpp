#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>

static const char * const qtscript_QToolBarChangeEvent_function_names[] = {
    "QToolBarChangeEvent"
    // static
    // prototype
    , "toggle"
    , "toString"
};

static const char * const qtscript_QToolBarChangeEvent_function_signatures[] = {
    "bool t"
    // static
    // prototype
    , ""
""
};

static const int qtscript_QToolBarChangeEvent_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QToolBarChangeEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QToolBarChangeEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QToolBarChangeEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QToolBarChangeEvent
//

static QScriptValue qtscript_QToolBarChangeEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QToolBarChangeEvent* _q_self = qscriptvalue_cast<QToolBarChangeEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QToolBarChangeEvent.%0(): this object is not a QToolBarChangeEvent")
            .arg(qtscript_QToolBarChangeEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->toggle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QToolBarChangeEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolBarChangeEvent_throw_ambiguity_error_helper(context,
        qtscript_QToolBarChangeEvent_function_names[_id+1],
        qtscript_QToolBarChangeEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QToolBarChangeEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QToolBarChangeEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QToolBarChangeEvent* _q_cpp_result = new QToolBarChangeEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolBarChangeEvent_throw_ambiguity_error_helper(context,
        qtscript_QToolBarChangeEvent_function_names[_id],
        qtscript_QToolBarChangeEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QToolBarChangeEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QToolBarChangeEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QToolBarChangeEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QToolBarChangeEvent_prototype_call, qtscript_QToolBarChangeEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QToolBarChangeEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QToolBarChangeEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QToolBarChangeEvent_static_call, proto, qtscript_QToolBarChangeEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
