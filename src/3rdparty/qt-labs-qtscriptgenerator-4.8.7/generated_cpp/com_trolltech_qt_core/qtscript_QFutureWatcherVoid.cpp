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

static const char * const qtscript_QFutureWatcherVoid_function_names[] = {
    "QFutureWatcherVoid"
    // static
    // prototype
    , "setFuture"
    , "toString"
};

static const char * const qtscript_QFutureWatcherVoid_function_signatures[] = {
    "QObject _parent"
    // static
    // prototype
    , "QFuture future"
""
};

static const int qtscript_QFutureWatcherVoid_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QFutureWatcherVoid_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFutureWatcherVoid::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptVoidFutureWatcher*)
Q_DECLARE_METATYPE(QtScriptVoidFuture)

//
// QFutureWatcherVoid
//

static QScriptValue qtscript_QFutureWatcherVoid_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QtScriptVoidFutureWatcher* _q_self = qscriptvalue_cast<QtScriptVoidFutureWatcher*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFutureWatcherVoid.%0(): this object is not a QFutureWatcherVoid")
            .arg(qtscript_QFutureWatcherVoid_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QtScriptVoidFuture _q_arg0 = qscriptvalue_cast<QtScriptVoidFuture>(context->argument(0));
        _q_self->setFuture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QFutureWatcherVoid");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureWatcherVoid_throw_ambiguity_error_helper(context,
        qtscript_QFutureWatcherVoid_function_names[_id+1],
        qtscript_QFutureWatcherVoid_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFutureWatcherVoid_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFutureWatcherVoid(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptVoidFutureWatcher* _q_cpp_result = new QtScriptVoidFutureWatcher();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptVoidFutureWatcher* _q_cpp_result = new QtScriptVoidFutureWatcher(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureWatcherVoid_throw_ambiguity_error_helper(context,
        qtscript_QFutureWatcherVoid_function_names[_id],
        qtscript_QFutureWatcherVoid_function_signatures[_id]);
}

QScriptValue qtscript_create_QFutureWatcherVoid_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QtScriptVoidFutureWatcher*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QtScriptVoidFutureWatcher*)0));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFutureWatcherVoid_prototype_call, qtscript_QFutureWatcherVoid_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFutureWatcherVoid_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QtScriptVoidFutureWatcher*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFutureWatcherVoid_static_call, proto, qtscript_QFutureWatcherVoid_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
