#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtscriptconcurrent.h>
#include <QVariant>
#include <qfuture.h>
#include <qobject.h>

static const char * const qtscript_QFutureWatcher_function_names[] = {
    "QFutureWatcher"
    // static
    // prototype
    , "setFuture"
    , "toString"
};

static const char * const qtscript_QFutureWatcher_function_signatures[] = {
    "QObject _parent"
    // static
    // prototype
    , "QFuture future"
""
};

static const int qtscript_QFutureWatcher_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QFutureWatcher_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFutureWatcher::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptFutureWatcher*)
Q_DECLARE_METATYPE(QtScriptFuture)

//
// QFutureWatcher
//

static QScriptValue qtscript_QFutureWatcher_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QtScriptFutureWatcher* _q_self = qscriptvalue_cast<QtScriptFutureWatcher*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFutureWatcher.%0(): this object is not a QFutureWatcher")
            .arg(qtscript_QFutureWatcher_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QtScriptFuture _q_arg0 = qscriptvalue_cast<QtScriptFuture>(context->argument(0));
        _q_self->setFuture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QFutureWatcher");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureWatcher_throw_ambiguity_error_helper(context,
        qtscript_QFutureWatcher_function_names[_id+1],
        qtscript_QFutureWatcher_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFutureWatcher_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFutureWatcher(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptFutureWatcher* _q_cpp_result = new QtScriptFutureWatcher();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptFutureWatcher* _q_cpp_result = new QtScriptFutureWatcher(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureWatcher_throw_ambiguity_error_helper(context,
        qtscript_QFutureWatcher_function_names[_id],
        qtscript_QFutureWatcher_function_signatures[_id]);
}

QScriptValue qtscript_create_QFutureWatcher_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QtScriptFutureWatcher*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QtScriptFutureWatcher*)0));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFutureWatcher_prototype_call, qtscript_QFutureWatcher_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFutureWatcher_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QtScriptFutureWatcher*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFutureWatcher_static_call, proto, qtscript_QFutureWatcher_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
