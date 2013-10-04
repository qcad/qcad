#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsemaphore.h>
#include <QVariant>
#include <qsemaphore.h>

static const char * const qtscript_QSemaphore_function_names[] = {
    "QSemaphore"
    // static
    // prototype
    , "acquire"
    , "available"
    , "release"
    , "tryAcquire"
    , "toString"
};

static const char * const qtscript_QSemaphore_function_signatures[] = {
    "int n"
    // static
    // prototype
    , "int n"
    , ""
    , "int n"
    , "int n\nint n, int timeout"
""
};

static const int qtscript_QSemaphore_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QSemaphore_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSemaphore::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSemaphore*)

//
// QSemaphore
//

static QScriptValue qtscript_QSemaphore_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSemaphore* _q_self = qscriptvalue_cast<QSemaphore*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSemaphore.%0(): this object is not a QSemaphore")
            .arg(qtscript_QSemaphore_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->acquire();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->acquire(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->available();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->release();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->release(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->tryAcquire();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->tryAcquire(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->tryAcquire(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QSemaphore");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSemaphore_throw_ambiguity_error_helper(context,
        qtscript_QSemaphore_function_names[_id+1],
        qtscript_QSemaphore_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSemaphore_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSemaphore(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSemaphore* _q_cpp_result = new QSemaphore();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QSemaphore* _q_cpp_result = new QSemaphore(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSemaphore_throw_ambiguity_error_helper(context,
        qtscript_QSemaphore_function_names[_id],
        qtscript_QSemaphore_function_signatures[_id]);
}

QScriptValue qtscript_create_QSemaphore_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSemaphore*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSemaphore*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSemaphore_prototype_call, qtscript_QSemaphore_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSemaphore_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSemaphore*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSemaphore_static_call, proto, qtscript_QSemaphore_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
