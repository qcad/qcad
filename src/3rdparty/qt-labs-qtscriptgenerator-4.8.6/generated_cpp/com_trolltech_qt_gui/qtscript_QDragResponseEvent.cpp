#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>

#include "qtscriptshell_QDragResponseEvent.h"

static const char * const qtscript_QDragResponseEvent_function_names[] = {
    "QDragResponseEvent"
    // static
    // prototype
    , "dragAccepted"
    , "toString"
};

static const char * const qtscript_QDragResponseEvent_function_signatures[] = {
    "bool accepted"
    // static
    // prototype
    , ""
""
};

static const int qtscript_QDragResponseEvent_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QDragResponseEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDragResponseEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDragResponseEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QDragResponseEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QDragResponseEvent
//

static QScriptValue qtscript_QDragResponseEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDragResponseEvent* _q_self = qscriptvalue_cast<QDragResponseEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDragResponseEvent.%0(): this object is not a QDragResponseEvent")
            .arg(qtscript_QDragResponseEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->dragAccepted();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QDragResponseEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragResponseEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragResponseEvent_function_names[_id+1],
        qtscript_QDragResponseEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDragResponseEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDragResponseEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QtScriptShell_QDragResponseEvent* _q_cpp_result = new QtScriptShell_QDragResponseEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDragResponseEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragResponseEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragResponseEvent_function_names[_id],
        qtscript_QDragResponseEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QDragResponseEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDragResponseEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDragResponseEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDragResponseEvent_prototype_call, qtscript_QDragResponseEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDragResponseEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDragResponseEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDragResponseEvent_static_call, proto, qtscript_QDragResponseEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
