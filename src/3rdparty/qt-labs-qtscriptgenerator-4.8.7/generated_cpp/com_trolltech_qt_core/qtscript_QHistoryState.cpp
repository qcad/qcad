#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qhistorystate.h>
#include <QVariant>
#include <qabstractstate.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhistorystate.h>
#include <qlist.h>
#include <qobject.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QHistoryState.h"

static const char * const qtscript_QHistoryState_function_names[] = {
    "QHistoryState"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QHistoryState_function_signatures[] = {
    "HistoryType type, QState parent\nQState parent"
    // static
    // prototype
""
};

static const int qtscript_QHistoryState_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QHistoryState_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHistoryState::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QHistoryState_metaObject()
{
    return &QHistoryState::staticMetaObject;
}

Q_DECLARE_METATYPE(QHistoryState*)
Q_DECLARE_METATYPE(QtScriptShell_QHistoryState*)
Q_DECLARE_METATYPE(QHistoryState::HistoryType)
Q_DECLARE_METATYPE(QState*)
Q_DECLARE_METATYPE(QAbstractState*)

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
// QHistoryState::HistoryType
//

static const QHistoryState::HistoryType qtscript_QHistoryState_HistoryType_values[] = {
    QHistoryState::ShallowHistory
    , QHistoryState::DeepHistory
};

static const char * const qtscript_QHistoryState_HistoryType_keys[] = {
    "ShallowHistory"
    , "DeepHistory"
};

static QString qtscript_QHistoryState_HistoryType_toStringHelper(QHistoryState::HistoryType value)
{
    const QMetaObject *meta = qtscript_QHistoryState_metaObject();
    int idx = meta->indexOfEnumerator("HistoryType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QHistoryState_HistoryType_toScriptValue(QScriptEngine *engine, const QHistoryState::HistoryType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QHistoryState"));
    return clazz.property(qtscript_QHistoryState_HistoryType_toStringHelper(value));
}

static void qtscript_QHistoryState_HistoryType_fromScriptValue(const QScriptValue &value, QHistoryState::HistoryType &out)
{
    out = qvariant_cast<QHistoryState::HistoryType>(value.toVariant());
}

static QScriptValue qtscript_construct_QHistoryState_HistoryType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QHistoryState_metaObject();
    int idx = meta->indexOfEnumerator("HistoryType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QHistoryState::HistoryType>(arg));
    return context->throwError(QString::fromLatin1("HistoryType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QHistoryState_HistoryType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QHistoryState::HistoryType value = qscriptvalue_cast<QHistoryState::HistoryType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QHistoryState_HistoryType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QHistoryState::HistoryType value = qscriptvalue_cast<QHistoryState::HistoryType>(context->thisObject());
    return QScriptValue(engine, qtscript_QHistoryState_HistoryType_toStringHelper(value));
}

static QScriptValue qtscript_create_QHistoryState_HistoryType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QHistoryState_HistoryType,
        qtscript_QHistoryState_HistoryType_valueOf, qtscript_QHistoryState_HistoryType_toString);
    qScriptRegisterMetaType<QHistoryState::HistoryType>(engine, qtscript_QHistoryState_HistoryType_toScriptValue,
        qtscript_QHistoryState_HistoryType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QHistoryState_HistoryType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QHistoryState_HistoryType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QHistoryState
//

static QScriptValue qtscript_QHistoryState_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QHistoryState* _q_self = qscriptvalue_cast<QHistoryState*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHistoryState.%0(): this object is not a QHistoryState")
            .arg(qtscript_QHistoryState_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QHistoryState");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHistoryState_throw_ambiguity_error_helper(context,
        qtscript_QHistoryState_function_names[_id+1],
        qtscript_QHistoryState_function_signatures[_id+1]);
}

static QScriptValue qtscript_QHistoryState_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHistoryState(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QHistoryState* _q_cpp_result = new QtScriptShell_QHistoryState();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHistoryState*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QHistoryState::HistoryType>() == context->argument(0).toVariant().userType())) {
            QHistoryState::HistoryType _q_arg0 = qscriptvalue_cast<QHistoryState::HistoryType>(context->argument(0));
            QtScriptShell_QHistoryState* _q_cpp_result = new QtScriptShell_QHistoryState(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHistoryState*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QState*>(context->argument(0))) {
            QState* _q_arg0 = qscriptvalue_cast<QState*>(context->argument(0));
            QtScriptShell_QHistoryState* _q_cpp_result = new QtScriptShell_QHistoryState(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHistoryState*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QHistoryState::HistoryType _q_arg0 = qscriptvalue_cast<QHistoryState::HistoryType>(context->argument(0));
        QState* _q_arg1 = qscriptvalue_cast<QState*>(context->argument(1));
        QtScriptShell_QHistoryState* _q_cpp_result = new QtScriptShell_QHistoryState(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHistoryState*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHistoryState_throw_ambiguity_error_helper(context,
        qtscript_QHistoryState_function_names[_id],
        qtscript_QHistoryState_function_signatures[_id]);
}

static QScriptValue qtscript_QHistoryState_toScriptValue(QScriptEngine *engine, QHistoryState* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QHistoryState_fromScriptValue(const QScriptValue &value, QHistoryState* &out)
{
    out = qobject_cast<QHistoryState*>(value.toQObject());
}

QScriptValue qtscript_create_QHistoryState_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHistoryState*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHistoryState*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractState*>()));

    qScriptRegisterMetaType<QHistoryState*>(engine, qtscript_QHistoryState_toScriptValue, 
        qtscript_QHistoryState_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHistoryState_static_call, proto, qtscript_QHistoryState_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("HistoryType"),
        qtscript_create_QHistoryState_HistoryType_class(engine, ctor));
    return ctor;
}
