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

#include "qtscriptshell_QInputEvent.h"

static const char * const qtscript_QInputEvent_function_names[] = {
    "QInputEvent"
    // static
    // prototype
    , "modifiers"
    , "setModifiers"
    , "setTimestamp"
    , "timestamp"
    , "toString"
};

static const char * const qtscript_QInputEvent_function_signatures[] = {
    "Type type, KeyboardModifiers modifiers"
    // static
    // prototype
    , ""
    , "KeyboardModifiers amodifiers"
    , "ulong atimestamp"
    , ""
""
};

static const int qtscript_QInputEvent_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QInputEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QInputEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QInputEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QInputEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QEvent*)

//
// QInputEvent
//

static QScriptValue qtscript_QInputEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QInputEvent* _q_self = qscriptvalue_cast<QInputEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QInputEvent.%0(): this object is not a QInputEvent")
            .arg(qtscript_QInputEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = _q_self->modifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QFlags<Qt::KeyboardModifier> _q_arg0 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(0));
        _q_self->setModifiers(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        ulong _q_arg0 = qscriptvalue_cast<ulong>(context->argument(0));
        _q_self->setTimestamp(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        ulong _q_result = _q_self->timestamp();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QInputEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputEvent_throw_ambiguity_error_helper(context,
        qtscript_QInputEvent_function_names[_id+1],
        qtscript_QInputEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QInputEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QInputEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QtScriptShell_QInputEvent* _q_cpp_result = new QtScriptShell_QInputEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QInputEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QFlags<Qt::KeyboardModifier> _q_arg1 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(1));
        QtScriptShell_QInputEvent* _q_cpp_result = new QtScriptShell_QInputEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QInputEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputEvent_throw_ambiguity_error_helper(context,
        qtscript_QInputEvent_function_names[_id],
        qtscript_QInputEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QInputEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QInputEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QInputEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QInputEvent_prototype_call, qtscript_QInputEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QInputEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QInputEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QInputEvent_static_call, proto, qtscript_QInputEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
