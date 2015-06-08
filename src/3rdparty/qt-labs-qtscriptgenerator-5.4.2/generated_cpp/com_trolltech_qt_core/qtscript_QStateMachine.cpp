#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstatemachine.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qabstractstate.h>
#include <qabstracttransition.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsignaltransition.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QStateMachine.h"

static const char * const qtscript_QStateMachine_function_names[] = {
    "QStateMachine"
    // static
    // prototype
    , "addDefaultAnimation"
    , "addState"
    , "cancelDelayedEvent"
    , "clearError"
    , "configuration"
    , "defaultAnimations"
    , "error"
    , "isRunning"
    , "postDelayedEvent"
    , "postEvent"
    , "removeDefaultAnimation"
    , "removeState"
    , "toString"
};

static const char * const qtscript_QStateMachine_function_signatures[] = {
    "QObject parent\nChildMode childMode, QObject parent"
    // static
    // prototype
    , "QAbstractAnimation animation"
    , "QAbstractState state"
    , "int id"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QEvent event, int delay"
    , "QEvent event, EventPriority priority"
    , "QAbstractAnimation animation"
    , "QAbstractState state"
""
};

static const int qtscript_QStateMachine_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QStateMachine_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStateMachine::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStateMachine*)
Q_DECLARE_METATYPE(QtScriptShell_QStateMachine*)
Q_DECLARE_METATYPE(QStateMachine::EventPriority)
Q_DECLARE_METATYPE(QStateMachine::Error)
Q_DECLARE_METATYPE(QAbstractAnimation*)
Q_DECLARE_METATYPE(QAbstractState*)
Q_DECLARE_METATYPE(QSet<QAbstractState* >)
Q_DECLARE_METATYPE(QList<QAbstractAnimation* >)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QState::ChildMode)
Q_DECLARE_METATYPE(QState*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QStateMachine::EventPriority
//

static const QStateMachine::EventPriority qtscript_QStateMachine_EventPriority_values[] = {
    QStateMachine::NormalPriority
    , QStateMachine::HighPriority
};

static const char * const qtscript_QStateMachine_EventPriority_keys[] = {
    "NormalPriority"
    , "HighPriority"
};

static QString qtscript_QStateMachine_EventPriority_toStringHelper(QStateMachine::EventPriority value)
{
    if ((value >= QStateMachine::NormalPriority) && (value <= QStateMachine::HighPriority))
        return qtscript_QStateMachine_EventPriority_keys[static_cast<int>(value)-static_cast<int>(QStateMachine::NormalPriority)];
    return QString();
}

static QScriptValue qtscript_QStateMachine_EventPriority_toScriptValue(QScriptEngine *engine, const QStateMachine::EventPriority &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStateMachine"));
    return clazz.property(qtscript_QStateMachine_EventPriority_toStringHelper(value));
}

static void qtscript_QStateMachine_EventPriority_fromScriptValue(const QScriptValue &value, QStateMachine::EventPriority &out)
{
    out = qvariant_cast<QStateMachine::EventPriority>(value.toVariant());
}

static QScriptValue qtscript_construct_QStateMachine_EventPriority(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStateMachine::NormalPriority) && (arg <= QStateMachine::HighPriority))
        return qScriptValueFromValue(engine,  static_cast<QStateMachine::EventPriority>(arg));
    return context->throwError(QString::fromLatin1("EventPriority(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStateMachine_EventPriority_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStateMachine::EventPriority value = qscriptvalue_cast<QStateMachine::EventPriority>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStateMachine_EventPriority_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStateMachine::EventPriority value = qscriptvalue_cast<QStateMachine::EventPriority>(context->thisObject());
    return QScriptValue(engine, qtscript_QStateMachine_EventPriority_toStringHelper(value));
}

static QScriptValue qtscript_create_QStateMachine_EventPriority_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStateMachine_EventPriority,
        qtscript_QStateMachine_EventPriority_valueOf, qtscript_QStateMachine_EventPriority_toString);
    qScriptRegisterMetaType<QStateMachine::EventPriority>(engine, qtscript_QStateMachine_EventPriority_toScriptValue,
        qtscript_QStateMachine_EventPriority_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStateMachine_EventPriority_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStateMachine_EventPriority_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStateMachine::Error
//

static const QStateMachine::Error qtscript_QStateMachine_Error_values[] = {
    QStateMachine::NoError
    , QStateMachine::NoInitialStateError
    , QStateMachine::NoDefaultStateInHistoryStateError
    , QStateMachine::NoCommonAncestorForTransitionError
};

static const char * const qtscript_QStateMachine_Error_keys[] = {
    "NoError"
    , "NoInitialStateError"
    , "NoDefaultStateInHistoryStateError"
    , "NoCommonAncestorForTransitionError"
};

static QString qtscript_QStateMachine_Error_toStringHelper(QStateMachine::Error value)
{
    if ((value >= QStateMachine::NoError) && (value <= QStateMachine::NoCommonAncestorForTransitionError))
        return qtscript_QStateMachine_Error_keys[static_cast<int>(value)-static_cast<int>(QStateMachine::NoError)];
    return QString();
}

static QScriptValue qtscript_QStateMachine_Error_toScriptValue(QScriptEngine *engine, const QStateMachine::Error &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStateMachine"));
    return clazz.property(qtscript_QStateMachine_Error_toStringHelper(value));
}

static void qtscript_QStateMachine_Error_fromScriptValue(const QScriptValue &value, QStateMachine::Error &out)
{
    out = qvariant_cast<QStateMachine::Error>(value.toVariant());
}

static QScriptValue qtscript_construct_QStateMachine_Error(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStateMachine::NoError) && (arg <= QStateMachine::NoCommonAncestorForTransitionError))
        return qScriptValueFromValue(engine,  static_cast<QStateMachine::Error>(arg));
    return context->throwError(QString::fromLatin1("Error(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStateMachine_Error_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStateMachine::Error value = qscriptvalue_cast<QStateMachine::Error>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStateMachine_Error_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStateMachine::Error value = qscriptvalue_cast<QStateMachine::Error>(context->thisObject());
    return QScriptValue(engine, qtscript_QStateMachine_Error_toStringHelper(value));
}

static QScriptValue qtscript_create_QStateMachine_Error_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStateMachine_Error,
        qtscript_QStateMachine_Error_valueOf, qtscript_QStateMachine_Error_toString);
    qScriptRegisterMetaType<QStateMachine::Error>(engine, qtscript_QStateMachine_Error_toScriptValue,
        qtscript_QStateMachine_Error_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStateMachine_Error_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStateMachine_Error_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStateMachine
//

static QScriptValue qtscript_QStateMachine_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStateMachine* _q_self = qscriptvalue_cast<QStateMachine*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStateMachine.%0(): this object is not a QStateMachine")
            .arg(qtscript_QStateMachine_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        _q_self->addDefaultAnimation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QAbstractState* _q_arg0 = qscriptvalue_cast<QAbstractState*>(context->argument(0));
        _q_self->addState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->cancelDelayedEvent(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clearError();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSet<QAbstractState* > _q_result = _q_self->configuration();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QAbstractAnimation* > _q_result = _q_self->defaultAnimations();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStateMachine::Error _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRunning();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->postDelayedEvent(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        _q_self->postEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        QStateMachine::EventPriority _q_arg1 = qscriptvalue_cast<QStateMachine::EventPriority>(context->argument(1));
        _q_self->postEvent(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        _q_self->removeDefaultAnimation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QAbstractState* _q_arg0 = qscriptvalue_cast<QAbstractState*>(context->argument(0));
        _q_self->removeState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QStateMachine");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStateMachine_throw_ambiguity_error_helper(context,
        qtscript_QStateMachine_function_names[_id+1],
        qtscript_QStateMachine_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStateMachine_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStateMachine(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStateMachine* _q_cpp_result = new QtScriptShell_QStateMachine();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStateMachine*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QStateMachine* _q_cpp_result = new QtScriptShell_QStateMachine(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStateMachine*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QState::ChildMode>() == context->argument(0).toVariant().userType())) {
            QState::ChildMode _q_arg0 = qscriptvalue_cast<QState::ChildMode>(context->argument(0));
            QtScriptShell_QStateMachine* _q_cpp_result = new QtScriptShell_QStateMachine(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStateMachine*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QState::ChildMode _q_arg0 = qscriptvalue_cast<QState::ChildMode>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QStateMachine* _q_cpp_result = new QtScriptShell_QStateMachine(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStateMachine*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStateMachine_throw_ambiguity_error_helper(context,
        qtscript_QStateMachine_function_names[_id],
        qtscript_QStateMachine_function_signatures[_id]);
}

static QScriptValue qtscript_QStateMachine_toScriptValue(QScriptEngine *engine, QStateMachine* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStateMachine_fromScriptValue(const QScriptValue &value, QStateMachine* &out)
{
    out = qobject_cast<QStateMachine*>(value.toQObject());
}

QScriptValue qtscript_create_QStateMachine_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStateMachine*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStateMachine*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QState*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStateMachine_prototype_call, qtscript_QStateMachine_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStateMachine_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStateMachine*>(engine, qtscript_QStateMachine_toScriptValue, 
        qtscript_QStateMachine_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStateMachine_static_call, proto, qtscript_QStateMachine_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("EventPriority"),
        qtscript_create_QStateMachine_EventPriority_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Error"),
        qtscript_create_QStateMachine_Error_class(engine, ctor));
    return ctor;
}
