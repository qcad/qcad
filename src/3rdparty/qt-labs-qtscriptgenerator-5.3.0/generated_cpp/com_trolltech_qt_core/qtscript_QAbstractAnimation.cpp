#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractanimation.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QAbstractAnimation.h"

static const char * const qtscript_QAbstractAnimation_function_names[] = {
    "QAbstractAnimation"
    // static
    // prototype
    , "currentLoopTime"
    , "group"
    , "totalDuration"
    , "toString"
};

static const char * const qtscript_QAbstractAnimation_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QAbstractAnimation_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractAnimation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractAnimation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QAbstractAnimation_metaObject()
{
    return &QAbstractAnimation::staticMetaObject;
}

Q_DECLARE_METATYPE(QAbstractAnimation*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractAnimation*)
Q_DECLARE_METATYPE(QAbstractAnimation::State)
Q_DECLARE_METATYPE(QAbstractAnimation::Direction)
Q_DECLARE_METATYPE(QAbstractAnimation::DeletionPolicy)
Q_DECLARE_METATYPE(QAnimationGroup*)

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
// QAbstractAnimation::State
//

static const QAbstractAnimation::State qtscript_QAbstractAnimation_State_values[] = {
    QAbstractAnimation::Stopped
    , QAbstractAnimation::Paused
    , QAbstractAnimation::Running
};

static const char * const qtscript_QAbstractAnimation_State_keys[] = {
    "Stopped"
    , "Paused"
    , "Running"
};

static QString qtscript_QAbstractAnimation_State_toStringHelper(QAbstractAnimation::State value)
{
    const QMetaObject *meta = qtscript_QAbstractAnimation_metaObject();
    int idx = meta->indexOfEnumerator("State");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractAnimation_State_toScriptValue(QScriptEngine *engine, const QAbstractAnimation::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractAnimation"));
    return clazz.property(qtscript_QAbstractAnimation_State_toStringHelper(value));
}

static void qtscript_QAbstractAnimation_State_fromScriptValue(const QScriptValue &value, QAbstractAnimation::State &out)
{
    out = qvariant_cast<QAbstractAnimation::State>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractAnimation_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractAnimation_metaObject();
    int idx = meta->indexOfEnumerator("State");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractAnimation::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractAnimation_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::State value = qscriptvalue_cast<QAbstractAnimation::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractAnimation_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::State value = qscriptvalue_cast<QAbstractAnimation::State>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractAnimation_State_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractAnimation_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractAnimation_State,
        qtscript_QAbstractAnimation_State_valueOf, qtscript_QAbstractAnimation_State_toString);
    qScriptRegisterMetaType<QAbstractAnimation::State>(engine, qtscript_QAbstractAnimation_State_toScriptValue,
        qtscript_QAbstractAnimation_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractAnimation_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractAnimation_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractAnimation::Direction
//

static const QAbstractAnimation::Direction qtscript_QAbstractAnimation_Direction_values[] = {
    QAbstractAnimation::Forward
    , QAbstractAnimation::Backward
};

static const char * const qtscript_QAbstractAnimation_Direction_keys[] = {
    "Forward"
    , "Backward"
};

static QString qtscript_QAbstractAnimation_Direction_toStringHelper(QAbstractAnimation::Direction value)
{
    const QMetaObject *meta = qtscript_QAbstractAnimation_metaObject();
    int idx = meta->indexOfEnumerator("Direction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractAnimation_Direction_toScriptValue(QScriptEngine *engine, const QAbstractAnimation::Direction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractAnimation"));
    return clazz.property(qtscript_QAbstractAnimation_Direction_toStringHelper(value));
}

static void qtscript_QAbstractAnimation_Direction_fromScriptValue(const QScriptValue &value, QAbstractAnimation::Direction &out)
{
    out = qvariant_cast<QAbstractAnimation::Direction>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractAnimation_Direction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractAnimation_metaObject();
    int idx = meta->indexOfEnumerator("Direction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractAnimation::Direction>(arg));
    return context->throwError(QString::fromLatin1("Direction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractAnimation_Direction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::Direction value = qscriptvalue_cast<QAbstractAnimation::Direction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractAnimation_Direction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::Direction value = qscriptvalue_cast<QAbstractAnimation::Direction>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractAnimation_Direction_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractAnimation_Direction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractAnimation_Direction,
        qtscript_QAbstractAnimation_Direction_valueOf, qtscript_QAbstractAnimation_Direction_toString);
    qScriptRegisterMetaType<QAbstractAnimation::Direction>(engine, qtscript_QAbstractAnimation_Direction_toScriptValue,
        qtscript_QAbstractAnimation_Direction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractAnimation_Direction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractAnimation_Direction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractAnimation::DeletionPolicy
//

static const QAbstractAnimation::DeletionPolicy qtscript_QAbstractAnimation_DeletionPolicy_values[] = {
    QAbstractAnimation::KeepWhenStopped
    , QAbstractAnimation::DeleteWhenStopped
};

static const char * const qtscript_QAbstractAnimation_DeletionPolicy_keys[] = {
    "KeepWhenStopped"
    , "DeleteWhenStopped"
};

static QString qtscript_QAbstractAnimation_DeletionPolicy_toStringHelper(QAbstractAnimation::DeletionPolicy value)
{
    if ((value >= QAbstractAnimation::KeepWhenStopped) && (value <= QAbstractAnimation::DeleteWhenStopped))
        return qtscript_QAbstractAnimation_DeletionPolicy_keys[static_cast<int>(value)-static_cast<int>(QAbstractAnimation::KeepWhenStopped)];
    return QString();
}

static QScriptValue qtscript_QAbstractAnimation_DeletionPolicy_toScriptValue(QScriptEngine *engine, const QAbstractAnimation::DeletionPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractAnimation"));
    return clazz.property(qtscript_QAbstractAnimation_DeletionPolicy_toStringHelper(value));
}

static void qtscript_QAbstractAnimation_DeletionPolicy_fromScriptValue(const QScriptValue &value, QAbstractAnimation::DeletionPolicy &out)
{
    out = qvariant_cast<QAbstractAnimation::DeletionPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractAnimation_DeletionPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractAnimation::KeepWhenStopped) && (arg <= QAbstractAnimation::DeleteWhenStopped))
        return qScriptValueFromValue(engine,  static_cast<QAbstractAnimation::DeletionPolicy>(arg));
    return context->throwError(QString::fromLatin1("DeletionPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractAnimation_DeletionPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::DeletionPolicy value = qscriptvalue_cast<QAbstractAnimation::DeletionPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractAnimation_DeletionPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::DeletionPolicy value = qscriptvalue_cast<QAbstractAnimation::DeletionPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractAnimation_DeletionPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractAnimation_DeletionPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractAnimation_DeletionPolicy,
        qtscript_QAbstractAnimation_DeletionPolicy_valueOf, qtscript_QAbstractAnimation_DeletionPolicy_toString);
    qScriptRegisterMetaType<QAbstractAnimation::DeletionPolicy>(engine, qtscript_QAbstractAnimation_DeletionPolicy_toScriptValue,
        qtscript_QAbstractAnimation_DeletionPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractAnimation_DeletionPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractAnimation_DeletionPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractAnimation
//

static QScriptValue qtscript_QAbstractAnimation_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAbstractAnimation* _q_self = qscriptvalue_cast<QAbstractAnimation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractAnimation.%0(): this object is not a QAbstractAnimation")
            .arg(qtscript_QAbstractAnimation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentLoopTime();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QAnimationGroup* _q_result = _q_self->group();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->totalDuration();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QAbstractAnimation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractAnimation_throw_ambiguity_error_helper(context,
        qtscript_QAbstractAnimation_function_names[_id+1],
        qtscript_QAbstractAnimation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractAnimation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractAnimation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractAnimation* _q_cpp_result = new QtScriptShell_QAbstractAnimation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractAnimation* _q_cpp_result = new QtScriptShell_QAbstractAnimation(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractAnimation_throw_ambiguity_error_helper(context,
        qtscript_QAbstractAnimation_function_names[_id],
        qtscript_QAbstractAnimation_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractAnimation_toScriptValue(QScriptEngine *engine, QAbstractAnimation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractAnimation_fromScriptValue(const QScriptValue &value, QAbstractAnimation* &out)
{
    out = qobject_cast<QAbstractAnimation*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractAnimation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractAnimation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractAnimation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractAnimation_prototype_call, qtscript_QAbstractAnimation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractAnimation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractAnimation*>(engine, qtscript_QAbstractAnimation_toScriptValue, 
        qtscript_QAbstractAnimation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractAnimation_static_call, proto, qtscript_QAbstractAnimation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QAbstractAnimation_State_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Direction"),
        qtscript_create_QAbstractAnimation_Direction_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DeletionPolicy"),
        qtscript_create_QAbstractAnimation_DeletionPolicy_class(engine, ctor));
    return ctor;
}
