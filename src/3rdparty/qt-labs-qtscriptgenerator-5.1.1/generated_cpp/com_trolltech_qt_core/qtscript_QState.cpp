#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstate.h>
#include <QVariant>
#include <qabstractstate.h>
#include <qabstracttransition.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsignaltransition.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QState.h"

static const char * const qtscript_QState_function_names[] = {
    "QState"
    // static
    // prototype
    , "addTransition"
    , "assignProperty"
    , "removeTransition"
    , "transitions"
    , "toString"
};

static const char * const qtscript_QState_function_signatures[] = {
    "QState parent\nChildMode childMode, QState parent"
    // static
    // prototype
    , "QAbstractState target\nQAbstractTransition transition\nQObject sender, char signal, QAbstractState target"
    , "QObject object, char name, Object value"
    , "QAbstractTransition transition"
    , ""
""
};

static const int qtscript_QState_function_lengths[] = {
    2
    // static
    // prototype
    , 3
    , 3
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QState_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QState::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QState_metaObject()
{
    return &QState::staticMetaObject;
}

Q_DECLARE_METATYPE(QState*)
Q_DECLARE_METATYPE(QtScriptShell_QState*)
Q_DECLARE_METATYPE(QState::ChildMode)
Q_DECLARE_METATYPE(QAbstractState*)
Q_DECLARE_METATYPE(QAbstractTransition*)
Q_DECLARE_METATYPE(const QObject*)
Q_DECLARE_METATYPE(const char*)
Q_DECLARE_METATYPE(QSignalTransition*)
Q_DECLARE_METATYPE(QList<QAbstractTransition* >)

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
// QState::ChildMode
//

static const QState::ChildMode qtscript_QState_ChildMode_values[] = {
    QState::ExclusiveStates
    , QState::ParallelStates
};

static const char * const qtscript_QState_ChildMode_keys[] = {
    "ExclusiveStates"
    , "ParallelStates"
};

static QString qtscript_QState_ChildMode_toStringHelper(QState::ChildMode value)
{
    const QMetaObject *meta = qtscript_QState_metaObject();
    int idx = meta->indexOfEnumerator("ChildMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QState_ChildMode_toScriptValue(QScriptEngine *engine, const QState::ChildMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QState"));
    return clazz.property(qtscript_QState_ChildMode_toStringHelper(value));
}

static void qtscript_QState_ChildMode_fromScriptValue(const QScriptValue &value, QState::ChildMode &out)
{
    out = qvariant_cast<QState::ChildMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QState_ChildMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QState_metaObject();
    int idx = meta->indexOfEnumerator("ChildMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QState::ChildMode>(arg));
    return context->throwError(QString::fromLatin1("ChildMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QState_ChildMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QState::ChildMode value = qscriptvalue_cast<QState::ChildMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QState_ChildMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QState::ChildMode value = qscriptvalue_cast<QState::ChildMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QState_ChildMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QState_ChildMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QState_ChildMode,
        qtscript_QState_ChildMode_valueOf, qtscript_QState_ChildMode_toString);
    qScriptRegisterMetaType<QState::ChildMode>(engine, qtscript_QState_ChildMode_toScriptValue,
        qtscript_QState_ChildMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QState_ChildMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QState_ChildMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QState
//

static QScriptValue qtscript_QState_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QState* _q_self = qscriptvalue_cast<QState*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QState.%0(): this object is not a QState")
            .arg(qtscript_QState_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QAbstractState*>(context->argument(0))) {
            QAbstractState* _q_arg0 = qscriptvalue_cast<QAbstractState*>(context->argument(0));
            QAbstractTransition* _q_result = _q_self->addTransition(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QAbstractTransition*>(context->argument(0))) {
            QAbstractTransition* _q_arg0 = qscriptvalue_cast<QAbstractTransition*>(context->argument(0));
            _q_self->addTransition(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        const QObject* _q_arg0 = qscriptvalue_cast<const QObject*>(context->argument(0));
        const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
        QAbstractState* _q_arg2 = qscriptvalue_cast<QAbstractState*>(context->argument(2));
        QSignalTransition* _q_result = _q_self->addTransition(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QVariant _q_arg2 = context->argument(2).toVariant();
        _q_self->assignProperty(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QAbstractTransition* _q_arg0 = qscriptvalue_cast<QAbstractTransition*>(context->argument(0));
        _q_self->removeTransition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QAbstractTransition* > _q_result = _q_self->transitions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QState");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QState_throw_ambiguity_error_helper(context,
        qtscript_QState_function_names[_id+1],
        qtscript_QState_function_signatures[_id+1]);
}

static QScriptValue qtscript_QState_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QState(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QState* _q_cpp_result = new QtScriptShell_QState();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QState*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QState*>(context->argument(0))) {
            QState* _q_arg0 = qscriptvalue_cast<QState*>(context->argument(0));
            QtScriptShell_QState* _q_cpp_result = new QtScriptShell_QState(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QState*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QState::ChildMode>() == context->argument(0).toVariant().userType())) {
            QState::ChildMode _q_arg0 = qscriptvalue_cast<QState::ChildMode>(context->argument(0));
            QtScriptShell_QState* _q_cpp_result = new QtScriptShell_QState(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QState*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QState::ChildMode _q_arg0 = qscriptvalue_cast<QState::ChildMode>(context->argument(0));
        QState* _q_arg1 = qscriptvalue_cast<QState*>(context->argument(1));
        QtScriptShell_QState* _q_cpp_result = new QtScriptShell_QState(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QState*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QState_throw_ambiguity_error_helper(context,
        qtscript_QState_function_names[_id],
        qtscript_QState_function_signatures[_id]);
}

static QScriptValue qtscript_QState_toScriptValue(QScriptEngine *engine, QState* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QState_fromScriptValue(const QScriptValue &value, QState* &out)
{
    out = qobject_cast<QState*>(value.toQObject());
}

QScriptValue qtscript_create_QState_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QState*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QState*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractState*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QState_prototype_call, qtscript_QState_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QState_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QState*>(engine, qtscript_QState_toScriptValue, 
        qtscript_QState_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QState_static_call, proto, qtscript_QState_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ChildMode"),
        qtscript_create_QState_ChildMode_class(engine, ctor));
    return ctor;
}
