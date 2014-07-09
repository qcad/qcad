#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qrunnable.h>
#include <QVariant>

#include "qtscriptshell_QRunnable.h"

static const char * const qtscript_QRunnable_function_names[] = {
    "QRunnable"
    // static
    // prototype
    , "autoDelete"
    , "run"
    , "setAutoDelete"
    , "toString"
};

static const char * const qtscript_QRunnable_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , "bool _autoDelete"
""
};

static const int qtscript_QRunnable_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QRunnable_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRunnable::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRunnable*)
Q_DECLARE_METATYPE(QtScriptShell_QRunnable*)

//
// QRunnable
//

static QScriptValue qtscript_QRunnable_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QRunnable* _q_self = qscriptvalue_cast<QRunnable*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRunnable.%0(): this object is not a QRunnable")
            .arg(qtscript_QRunnable_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoDelete();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->run();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoDelete(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QRunnable");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRunnable_throw_ambiguity_error_helper(context,
        qtscript_QRunnable_function_names[_id+1],
        qtscript_QRunnable_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRunnable_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRunnable(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QRunnable* _q_cpp_result = new QtScriptShell_QRunnable();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QRunnable*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRunnable_throw_ambiguity_error_helper(context,
        qtscript_QRunnable_function_names[_id],
        qtscript_QRunnable_function_signatures[_id]);
}

QScriptValue qtscript_create_QRunnable_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRunnable*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRunnable*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRunnable_prototype_call, qtscript_QRunnable_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRunnable_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QRunnable*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRunnable_static_call, proto, qtscript_QRunnable_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
