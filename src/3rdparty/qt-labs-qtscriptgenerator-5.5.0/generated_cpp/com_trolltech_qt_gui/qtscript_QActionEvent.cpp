#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qevent.h>
#include <QVariant>
#include <qaction.h>
#include <qcoreevent.h>

static const char * const qtscript_QActionEvent_function_names[] = {
    "QActionEvent"
    // static
    // prototype
    , "action"
    , "before"
    , "toString"
};

static const char * const qtscript_QActionEvent_function_signatures[] = {
    "int type, QAction action, QAction before"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QActionEvent_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QActionEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QActionEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QActionEvent*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QEvent*)

//
// QActionEvent
//

static QScriptValue qtscript_QActionEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QActionEvent* _q_self = qscriptvalue_cast<QActionEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QActionEvent.%0(): this object is not a QActionEvent")
            .arg(qtscript_QActionEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->action();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->before();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QActionEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QActionEvent_throw_ambiguity_error_helper(context,
        qtscript_QActionEvent_function_names[_id+1],
        qtscript_QActionEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QActionEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QActionEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QAction* _q_arg1 = qscriptvalue_cast<QAction*>(context->argument(1));
        QActionEvent* _q_cpp_result = new QActionEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QAction* _q_arg1 = qscriptvalue_cast<QAction*>(context->argument(1));
        QAction* _q_arg2 = qscriptvalue_cast<QAction*>(context->argument(2));
        QActionEvent* _q_cpp_result = new QActionEvent(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QActionEvent_throw_ambiguity_error_helper(context,
        qtscript_QActionEvent_function_names[_id],
        qtscript_QActionEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QActionEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QActionEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QActionEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QActionEvent_prototype_call, qtscript_QActionEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QActionEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QActionEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QActionEvent_static_call, proto, qtscript_QActionEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
