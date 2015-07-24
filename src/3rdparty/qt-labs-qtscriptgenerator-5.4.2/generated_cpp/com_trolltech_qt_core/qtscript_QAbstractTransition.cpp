#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstracttransition.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qabstractstate.h>
#include <qabstracttransition.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QAbstractTransition.h"

static const char * const qtscript_QAbstractTransition_function_names[] = {
    "QAbstractTransition"
    // static
    // prototype
    , "addAnimation"
    , "animations"
    , "machine"
    , "removeAnimation"
    , "toString"
};

static const char * const qtscript_QAbstractTransition_function_signatures[] = {
    "QState sourceState"
    // static
    // prototype
    , "QAbstractAnimation animation"
    , ""
    , ""
    , "QAbstractAnimation animation"
""
};

static const int qtscript_QAbstractTransition_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractTransition_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractTransition::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractTransition*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractTransition*)
Q_DECLARE_METATYPE(QAbstractAnimation*)
Q_DECLARE_METATYPE(QList<QAbstractAnimation* >)
Q_DECLARE_METATYPE(QStateMachine*)
Q_DECLARE_METATYPE(QState*)

//
// QAbstractTransition
//

static QScriptValue qtscript_QAbstractTransition_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAbstractTransition* _q_self = qscriptvalue_cast<QAbstractTransition*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractTransition.%0(): this object is not a QAbstractTransition")
            .arg(qtscript_QAbstractTransition_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        _q_self->addAnimation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QAbstractAnimation* > _q_result = _q_self->animations();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStateMachine* _q_result = _q_self->machine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        _q_self->removeAnimation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QAbstractTransition");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractTransition_throw_ambiguity_error_helper(context,
        qtscript_QAbstractTransition_function_names[_id+1],
        qtscript_QAbstractTransition_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractTransition_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractTransition(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractTransition* _q_cpp_result = new QtScriptShell_QAbstractTransition();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QState* _q_arg0 = qscriptvalue_cast<QState*>(context->argument(0));
        QtScriptShell_QAbstractTransition* _q_cpp_result = new QtScriptShell_QAbstractTransition(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractTransition_throw_ambiguity_error_helper(context,
        qtscript_QAbstractTransition_function_names[_id],
        qtscript_QAbstractTransition_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractTransition_toScriptValue(QScriptEngine *engine, QAbstractTransition* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractTransition_fromScriptValue(const QScriptValue &value, QAbstractTransition* &out)
{
    out = qobject_cast<QAbstractTransition*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractTransition_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractTransition*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractTransition*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractTransition_prototype_call, qtscript_QAbstractTransition_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractTransition_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractTransition*>(engine, qtscript_QAbstractTransition_toScriptValue, 
        qtscript_QAbstractTransition_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractTransition_static_call, proto, qtscript_QAbstractTransition_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
