#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtimer.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qtimer.h>

#include "qtscriptshell_QTimer.h"

static const char * const qtscript_QTimer_function_names[] = {
    "QTimer"
    // static
    // prototype
    , "timerId"
    , "toString"
};

static const char * const qtscript_QTimer_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
""
};

static const int qtscript_QTimer_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QTimer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTimer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTimer*)
Q_DECLARE_METATYPE(QtScriptShell_QTimer*)

//
// QTimer
//

static QScriptValue qtscript_QTimer_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTimer* _q_self = qscriptvalue_cast<QTimer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTimer.%0(): this object is not a QTimer")
            .arg(qtscript_QTimer_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->timerId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QTimer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTimer_throw_ambiguity_error_helper(context,
        qtscript_QTimer_function_names[_id+1],
        qtscript_QTimer_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTimer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTimer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTimer* _q_cpp_result = new QtScriptShell_QTimer();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QTimer* _q_cpp_result = new QtScriptShell_QTimer(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTimer_throw_ambiguity_error_helper(context,
        qtscript_QTimer_function_names[_id],
        qtscript_QTimer_function_signatures[_id]);
}

static QScriptValue qtscript_QTimer_toScriptValue(QScriptEngine *engine, QTimer* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTimer_fromScriptValue(const QScriptValue &value, QTimer* &out)
{
    out = qobject_cast<QTimer*>(value.toQObject());
}

QScriptValue qtscript_create_QTimer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTimer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTimer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTimer_prototype_call, qtscript_QTimer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTimer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTimer*>(engine, qtscript_QTimer_toScriptValue, 
        qtscript_QTimer_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTimer_static_call, proto, qtscript_QTimer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
