#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtscriptconcurrent.h>
#include <QVariant>
#include <qfuture.h>

static const char * const qtscript_QFutureVoid_function_names[] = {
    "QFutureVoid"
    // static
    // prototype
    , "cancel"
    , "isCanceled"
    , "isFinished"
    , "isPaused"
    , "isRunning"
    , "isStarted"
    , "equals"
    , "pause"
    , "progressMaximum"
    , "progressMinimum"
    , "progressText"
    , "progressValue"
    , "resume"
    , "setPaused"
    , "togglePaused"
    , "waitForFinished"
    , "toString"
};

static const char * const qtscript_QFutureVoid_function_signatures[] = {
    "\nQFuture other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QFuture other"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool paused"
    , ""
    , ""
""
};

static const int qtscript_QFutureVoid_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QFutureVoid_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFutureVoid::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptVoidFuture)
Q_DECLARE_METATYPE(QtScriptVoidFuture*)

//
// QFutureVoid
//

static QScriptValue qtscript_QFutureVoid_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 16;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QtScriptVoidFuture* _q_self = qscriptvalue_cast<QtScriptVoidFuture*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFutureVoid.%0(): this object is not a QFutureVoid")
            .arg(qtscript_QFutureVoid_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->cancel();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCanceled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFinished();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isPaused();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRunning();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isStarted();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QtScriptVoidFuture _q_arg0 = qscriptvalue_cast<QtScriptVoidFuture>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->pause();
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->progressMaximum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->progressMinimum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->progressText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->progressValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        _q_self->resume();
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setPaused(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        _q_self->togglePaused();
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        _q_self->waitForFinished();
        return context->engine()->undefinedValue();
    }
    break;

    case 16: {
    QString result = QString::fromLatin1("QFutureVoid");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureVoid_throw_ambiguity_error_helper(context,
        qtscript_QFutureVoid_function_names[_id+1],
        qtscript_QFutureVoid_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFutureVoid_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFutureVoid(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptVoidFuture _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QtScriptVoidFuture _q_arg0 = qscriptvalue_cast<QtScriptVoidFuture>(context->argument(0));
        QtScriptVoidFuture _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureVoid_throw_ambiguity_error_helper(context,
        qtscript_QFutureVoid_function_names[_id],
        qtscript_QFutureVoid_function_signatures[_id]);
}

QScriptValue qtscript_create_QFutureVoid_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QtScriptVoidFuture*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QtScriptVoidFuture*)0));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFutureVoid_prototype_call, qtscript_QFutureVoid_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFutureVoid_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QtScriptVoidFuture>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QtScriptVoidFuture*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFutureVoid_static_call, proto, qtscript_QFutureVoid_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
