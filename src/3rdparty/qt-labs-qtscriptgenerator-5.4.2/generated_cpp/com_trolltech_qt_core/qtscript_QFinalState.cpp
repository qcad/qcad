#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qfinalstate.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfinalstate.h>
#include <qlist.h>
#include <qobject.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QFinalState.h"

static const char * const qtscript_QFinalState_function_names[] = {
    "QFinalState"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QFinalState_function_signatures[] = {
    "QState parent"
    // static
    // prototype
""
};

static const int qtscript_QFinalState_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QFinalState_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFinalState::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFinalState*)
Q_DECLARE_METATYPE(QtScriptShell_QFinalState*)
Q_DECLARE_METATYPE(QState*)
Q_DECLARE_METATYPE(QAbstractState*)

//
// QFinalState
//

static QScriptValue qtscript_QFinalState_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFinalState* _q_self = qscriptvalue_cast<QFinalState*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFinalState.%0(): this object is not a QFinalState")
            .arg(qtscript_QFinalState_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QFinalState");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFinalState_throw_ambiguity_error_helper(context,
        qtscript_QFinalState_function_names[_id+1],
        qtscript_QFinalState_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFinalState_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFinalState(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFinalState* _q_cpp_result = new QtScriptShell_QFinalState();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFinalState*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QState* _q_arg0 = qscriptvalue_cast<QState*>(context->argument(0));
        QtScriptShell_QFinalState* _q_cpp_result = new QtScriptShell_QFinalState(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFinalState*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFinalState_throw_ambiguity_error_helper(context,
        qtscript_QFinalState_function_names[_id],
        qtscript_QFinalState_function_signatures[_id]);
}

static QScriptValue qtscript_QFinalState_toScriptValue(QScriptEngine *engine, QFinalState* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFinalState_fromScriptValue(const QScriptValue &value, QFinalState* &out)
{
    out = qobject_cast<QFinalState*>(value.toQObject());
}

QScriptValue qtscript_create_QFinalState_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFinalState*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFinalState*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractState*>()));

    qScriptRegisterMetaType<QFinalState*>(engine, qtscript_QFinalState_toScriptValue, 
        qtscript_QFinalState_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFinalState_static_call, proto, qtscript_QFinalState_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
