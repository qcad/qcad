#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmutex.h>
#include <QVariant>

#include "qtscriptshell_QBasicMutex.h"

static const char * const qtscript_QBasicMutex_function_names[] = {
    "QBasicMutex"
    // static
    // prototype
    , "isRecursive"
    , "lock"
    , "tryLock"
    , "unlock"
    , "toString"
};

static const char * const qtscript_QBasicMutex_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QBasicMutex_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QBasicMutex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QBasicMutex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QBasicMutex*)
Q_DECLARE_METATYPE(QtScriptShell_QBasicMutex*)

//
// QBasicMutex
//

static QScriptValue qtscript_QBasicMutex_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QBasicMutex* _q_self = qscriptvalue_cast<QBasicMutex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QBasicMutex.%0(): this object is not a QBasicMutex")
            .arg(qtscript_QBasicMutex_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRecursive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->lock();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->tryLock();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->unlock();
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QBasicMutex");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBasicMutex_throw_ambiguity_error_helper(context,
        qtscript_QBasicMutex_function_names[_id+1],
        qtscript_QBasicMutex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QBasicMutex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QBasicMutex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QBasicMutex* _q_cpp_result = new QtScriptShell_QBasicMutex();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QBasicMutex*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBasicMutex_throw_ambiguity_error_helper(context,
        qtscript_QBasicMutex_function_names[_id],
        qtscript_QBasicMutex_function_signatures[_id]);
}

QScriptValue qtscript_create_QBasicMutex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QBasicMutex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QBasicMutex*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QBasicMutex_prototype_call, qtscript_QBasicMutex_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QBasicMutex_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QBasicMutex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QBasicMutex_static_call, proto, qtscript_QBasicMutex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
