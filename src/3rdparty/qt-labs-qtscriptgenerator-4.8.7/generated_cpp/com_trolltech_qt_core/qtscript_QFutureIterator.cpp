#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtscriptconcurrent.h>
#include <QVariant>
#include <qfuture.h>

static const char * const qtscript_QFutureIterator_function_names[] = {
    "QFutureIterator"
    // static
    // prototype
    , "hasNext"
    , "hasPrevious"
    , "toBack"
    , "toFront"
    , "toString"
};

static const char * const qtscript_QFutureIterator_function_signatures[] = {
    "QFuture container"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QFutureIterator_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QFutureIterator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFutureIterator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptFutureIterator*)
Q_DECLARE_METATYPE(QtScriptFuture)

//
// QFutureIterator
//

static QScriptValue qtscript_QFutureIterator_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QtScriptFutureIterator* _q_self = qscriptvalue_cast<QtScriptFutureIterator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFutureIterator.%0(): this object is not a QFutureIterator")
            .arg(qtscript_QFutureIterator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasNext();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasPrevious();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->toBack();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->toFront();
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QFutureIterator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureIterator_throw_ambiguity_error_helper(context,
        qtscript_QFutureIterator_function_names[_id+1],
        qtscript_QFutureIterator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFutureIterator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFutureIterator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QtScriptFuture _q_arg0 = qscriptvalue_cast<QtScriptFuture>(context->argument(0));
        QtScriptFutureIterator* _q_cpp_result = new QtScriptFutureIterator(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFutureIterator_throw_ambiguity_error_helper(context,
        qtscript_QFutureIterator_function_names[_id],
        qtscript_QFutureIterator_function_signatures[_id]);
}

QScriptValue qtscript_create_QFutureIterator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QtScriptFutureIterator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QtScriptFutureIterator*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFutureIterator_prototype_call, qtscript_QFutureIterator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFutureIterator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QtScriptFutureIterator*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFutureIterator_static_call, proto, qtscript_QFutureIterator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
