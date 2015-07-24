#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qeventloop.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QEventLoop.h"

static const char * const qtscript_QEventLoop_function_names[] = {
    "QEventLoop"
    // static
    // prototype
    , "exec"
    , "exit"
    , "isRunning"
    , "processEvents"
    , "wakeUp"
    , "toString"
};

static const char * const qtscript_QEventLoop_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "ProcessEventsFlags flags"
    , "int returnCode"
    , ""
    , "ProcessEventsFlags flags\nProcessEventsFlags flags, int maximumTime"
    , ""
""
};

static const int qtscript_QEventLoop_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 0
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QEventLoop_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QEventLoop::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QEventLoop*)
Q_DECLARE_METATYPE(QtScriptShell_QEventLoop*)
Q_DECLARE_METATYPE(QEventLoop::ProcessEventsFlag)
Q_DECLARE_METATYPE(QFlags<QEventLoop::ProcessEventsFlag>)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QEventLoop::ProcessEventsFlag
//

static const QEventLoop::ProcessEventsFlag qtscript_QEventLoop_ProcessEventsFlag_values[] = {
    QEventLoop::AllEvents
    , QEventLoop::ExcludeUserInputEvents
    , QEventLoop::ExcludeSocketNotifiers
    , QEventLoop::WaitForMoreEvents
    , QEventLoop::X11ExcludeTimers
    , QEventLoop::DeferredDeletion
    , QEventLoop::EventLoopExec
    , QEventLoop::DialogExec
};

static const char * const qtscript_QEventLoop_ProcessEventsFlag_keys[] = {
    "AllEvents"
    , "ExcludeUserInputEvents"
    , "ExcludeSocketNotifiers"
    , "WaitForMoreEvents"
    , "X11ExcludeTimers"
    , "DeferredDeletion"
    , "EventLoopExec"
    , "DialogExec"
};

static QString qtscript_QEventLoop_ProcessEventsFlag_toStringHelper(QEventLoop::ProcessEventsFlag value)
{
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QEventLoop_ProcessEventsFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QEventLoop_ProcessEventsFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QEventLoop_ProcessEventsFlag_toScriptValue(QScriptEngine *engine, const QEventLoop::ProcessEventsFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QEventLoop"));
    return clazz.property(qtscript_QEventLoop_ProcessEventsFlag_toStringHelper(value));
}

static void qtscript_QEventLoop_ProcessEventsFlag_fromScriptValue(const QScriptValue &value, QEventLoop::ProcessEventsFlag &out)
{
    out = qvariant_cast<QEventLoop::ProcessEventsFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QEventLoop_ProcessEventsFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QEventLoop_ProcessEventsFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QEventLoop::ProcessEventsFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("ProcessEventsFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QEventLoop_ProcessEventsFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QEventLoop::ProcessEventsFlag value = qscriptvalue_cast<QEventLoop::ProcessEventsFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QEventLoop_ProcessEventsFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QEventLoop::ProcessEventsFlag value = qscriptvalue_cast<QEventLoop::ProcessEventsFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QEventLoop_ProcessEventsFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QEventLoop_ProcessEventsFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QEventLoop_ProcessEventsFlag,
        qtscript_QEventLoop_ProcessEventsFlag_valueOf, qtscript_QEventLoop_ProcessEventsFlag_toString);
    qScriptRegisterMetaType<QEventLoop::ProcessEventsFlag>(engine, qtscript_QEventLoop_ProcessEventsFlag_toScriptValue,
        qtscript_QEventLoop_ProcessEventsFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QEventLoop_ProcessEventsFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QEventLoop_ProcessEventsFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QEventLoop::ProcessEventsFlags
//

static QScriptValue qtscript_QEventLoop_ProcessEventsFlags_toScriptValue(QScriptEngine *engine, const QEventLoop::ProcessEventsFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QEventLoop_ProcessEventsFlags_fromScriptValue(const QScriptValue &value, QEventLoop::ProcessEventsFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QEventLoop::ProcessEventsFlags>())
        out = qvariant_cast<QEventLoop::ProcessEventsFlags>(var);
    else if (var.userType() == qMetaTypeId<QEventLoop::ProcessEventsFlag>())
        out = qvariant_cast<QEventLoop::ProcessEventsFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QEventLoop_ProcessEventsFlags(QScriptContext *context, QScriptEngine *engine)
{
    QEventLoop::ProcessEventsFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QEventLoop::ProcessEventsFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QEventLoop::ProcessEventsFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ProcessEventsFlags(): argument %0 is not of type ProcessEventsFlag").arg(i));
            }
            result |= qvariant_cast<QEventLoop::ProcessEventsFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QEventLoop_ProcessEventsFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QEventLoop::ProcessEventsFlags value = qscriptvalue_cast<QEventLoop::ProcessEventsFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QEventLoop_ProcessEventsFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QEventLoop::ProcessEventsFlags value = qscriptvalue_cast<QEventLoop::ProcessEventsFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_QEventLoop_ProcessEventsFlag_values[i]) == qtscript_QEventLoop_ProcessEventsFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QEventLoop_ProcessEventsFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QEventLoop_ProcessEventsFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QEventLoop::ProcessEventsFlags>() == otherObj.value<QEventLoop::ProcessEventsFlags>())));
}

static QScriptValue qtscript_create_QEventLoop_ProcessEventsFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QEventLoop_ProcessEventsFlags, qtscript_QEventLoop_ProcessEventsFlags_valueOf,
        qtscript_QEventLoop_ProcessEventsFlags_toString, qtscript_QEventLoop_ProcessEventsFlags_equals);
    qScriptRegisterMetaType<QEventLoop::ProcessEventsFlags>(engine, qtscript_QEventLoop_ProcessEventsFlags_toScriptValue,
        qtscript_QEventLoop_ProcessEventsFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QEventLoop
//

static QScriptValue qtscript_QEventLoop_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QEventLoop* _q_self = qscriptvalue_cast<QEventLoop*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QEventLoop.%0(): this object is not a QEventLoop")
            .arg(qtscript_QEventLoop_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->exec();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<QEventLoop::ProcessEventsFlag> _q_arg0 = qscriptvalue_cast<QFlags<QEventLoop::ProcessEventsFlag> >(context->argument(0));
        int _q_result = _q_self->exec(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->exit();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->exit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRunning();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->processEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<QEventLoop::ProcessEventsFlag> _q_arg0 = qscriptvalue_cast<QFlags<QEventLoop::ProcessEventsFlag> >(context->argument(0));
        bool _q_result = _q_self->processEvents(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QFlags<QEventLoop::ProcessEventsFlag> _q_arg0 = qscriptvalue_cast<QFlags<QEventLoop::ProcessEventsFlag> >(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->processEvents(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->wakeUp();
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QEventLoop");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QEventLoop_throw_ambiguity_error_helper(context,
        qtscript_QEventLoop_function_names[_id+1],
        qtscript_QEventLoop_function_signatures[_id+1]);
}

static QScriptValue qtscript_QEventLoop_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QEventLoop(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QEventLoop* _q_cpp_result = new QtScriptShell_QEventLoop();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QEventLoop*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QEventLoop* _q_cpp_result = new QtScriptShell_QEventLoop(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QEventLoop*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QEventLoop_throw_ambiguity_error_helper(context,
        qtscript_QEventLoop_function_names[_id],
        qtscript_QEventLoop_function_signatures[_id]);
}

static QScriptValue qtscript_QEventLoop_toScriptValue(QScriptEngine *engine, QEventLoop* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QEventLoop_fromScriptValue(const QScriptValue &value, QEventLoop* &out)
{
    out = qobject_cast<QEventLoop*>(value.toQObject());
}

QScriptValue qtscript_create_QEventLoop_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QEventLoop*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QEventLoop*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QEventLoop_prototype_call, qtscript_QEventLoop_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QEventLoop_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QEventLoop*>(engine, qtscript_QEventLoop_toScriptValue, 
        qtscript_QEventLoop_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QEventLoop_static_call, proto, qtscript_QEventLoop_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ProcessEventsFlag"),
        qtscript_create_QEventLoop_ProcessEventsFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ProcessEventsFlags"),
        qtscript_create_QEventLoop_ProcessEventsFlags_class(engine));
    return ctor;
}
