#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qwaitcondition.h>
#include <QVariant>
#include <qmutex.h>
#include <qreadwritelock.h>
#include <qwaitcondition.h>

static const char * const qtscript_QWaitCondition_function_names[] = {
    "QWaitCondition"
    // static
    // prototype
    , "wait"
    , "wakeAll"
    , "wakeOne"
    , "toString"
};

static const char * const qtscript_QWaitCondition_function_signatures[] = {
    ""
    // static
    // prototype
    , "QMutex lockedMutex, unsigned long time\nQReadWriteLock lockedReadWriteLock, unsigned long time"
    , ""
    , ""
""
};

static const int qtscript_QWaitCondition_function_lengths[] = {
    0
    // static
    // prototype
    , 2
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QWaitCondition_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWaitCondition::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWaitCondition*)
Q_DECLARE_METATYPE(QMutex*)
Q_DECLARE_METATYPE(QReadWriteLock*)

//
// QWaitCondition
//

static QScriptValue qtscript_QWaitCondition_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWaitCondition* _q_self = qscriptvalue_cast<QWaitCondition*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWaitCondition.%0(): this object is not a QWaitCondition")
            .arg(qtscript_QWaitCondition_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QMutex*>(context->argument(0))) {
            QMutex* _q_arg0 = qscriptvalue_cast<QMutex*>(context->argument(0));
            bool _q_result = _q_self->wait(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QReadWriteLock*>(context->argument(0))) {
            QReadWriteLock* _q_arg0 = qscriptvalue_cast<QReadWriteLock*>(context->argument(0));
            bool _q_result = _q_self->wait(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QMutex*>(context->argument(0))
            && (qMetaTypeId<ulong>() == context->argument(1).toVariant().userType())) {
            QMutex* _q_arg0 = qscriptvalue_cast<QMutex*>(context->argument(0));
            ulong _q_arg1 = qscriptvalue_cast<ulong>(context->argument(1));
            bool _q_result = _q_self->wait(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QReadWriteLock*>(context->argument(0))
            && (qMetaTypeId<ulong>() == context->argument(1).toVariant().userType())) {
            QReadWriteLock* _q_arg0 = qscriptvalue_cast<QReadWriteLock*>(context->argument(0));
            ulong _q_arg1 = qscriptvalue_cast<ulong>(context->argument(1));
            bool _q_result = _q_self->wait(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->wakeAll();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->wakeOne();
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QWaitCondition");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWaitCondition_throw_ambiguity_error_helper(context,
        qtscript_QWaitCondition_function_names[_id+1],
        qtscript_QWaitCondition_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWaitCondition_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWaitCondition(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QWaitCondition* _q_cpp_result = new QWaitCondition();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWaitCondition_throw_ambiguity_error_helper(context,
        qtscript_QWaitCondition_function_names[_id],
        qtscript_QWaitCondition_function_signatures[_id]);
}

QScriptValue qtscript_create_QWaitCondition_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWaitCondition*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWaitCondition*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWaitCondition_prototype_call, qtscript_QWaitCondition_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWaitCondition_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWaitCondition*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWaitCondition_static_call, proto, qtscript_QWaitCondition_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
