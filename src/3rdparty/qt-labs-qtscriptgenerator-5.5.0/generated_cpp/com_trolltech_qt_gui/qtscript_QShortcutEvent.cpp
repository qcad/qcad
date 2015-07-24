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
#include <qkeysequence.h>

#include "qtscriptshell_QShortcutEvent.h"

static const char * const qtscript_QShortcutEvent_function_names[] = {
    "QShortcutEvent"
    // static
    // prototype
    , "isAmbiguous"
    , "key"
    , "shortcutId"
    , "toString"
};

static const char * const qtscript_QShortcutEvent_function_signatures[] = {
    "QKeySequence key, int id, bool ambiguous"
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QShortcutEvent_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QShortcutEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QShortcutEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QShortcutEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QShortcutEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QShortcutEvent
//

static QScriptValue qtscript_QShortcutEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QShortcutEvent* _q_self = qscriptvalue_cast<QShortcutEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QShortcutEvent.%0(): this object is not a QShortcutEvent")
            .arg(qtscript_QShortcutEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAmbiguous();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        const QKeySequence& _q_result = _q_self->key();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->shortcutId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QShortcutEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QShortcutEvent_throw_ambiguity_error_helper(context,
        qtscript_QShortcutEvent_function_names[_id+1],
        qtscript_QShortcutEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QShortcutEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QShortcutEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QShortcutEvent* _q_cpp_result = new QtScriptShell_QShortcutEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QShortcutEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_arg2 = context->argument(2).toBoolean();
        QtScriptShell_QShortcutEvent* _q_cpp_result = new QtScriptShell_QShortcutEvent(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QShortcutEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QShortcutEvent_throw_ambiguity_error_helper(context,
        qtscript_QShortcutEvent_function_names[_id],
        qtscript_QShortcutEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QShortcutEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QShortcutEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QShortcutEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QShortcutEvent_prototype_call, qtscript_QShortcutEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QShortcutEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QShortcutEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QShortcutEvent_static_call, proto, qtscript_QShortcutEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
