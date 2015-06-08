#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessible.h>
#include <QVariant>

static const char * const qtscript_QAccessibleEvent_function_names[] = {
    "QAccessibleEvent"
    // static
    // prototype
    , "child"
    , "setValue"
    , "value"
    , "toString"
};

static const char * const qtscript_QAccessibleEvent_function_signatures[] = {
    "Type type, int child"
    // static
    // prototype
    , ""
    , "String aText"
    , ""
""
};

static const int qtscript_QAccessibleEvent_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QAccessibleEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleEvent*)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QEvent*)

//
// QAccessibleEvent
//

static QScriptValue qtscript_QAccessibleEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAccessibleEvent* _q_self = qscriptvalue_cast<QAccessibleEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleEvent.%0(): this object is not a QAccessibleEvent")
            .arg(qtscript_QAccessibleEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->child();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->value();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QAccessibleEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleEvent_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleEvent_function_names[_id+1],
        qtscript_QAccessibleEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QAccessibleEvent* _q_cpp_result = new QAccessibleEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleEvent_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleEvent_function_names[_id],
        qtscript_QAccessibleEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessibleEvent_prototype_call, qtscript_QAccessibleEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAccessibleEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleEvent_static_call, proto, qtscript_QAccessibleEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
