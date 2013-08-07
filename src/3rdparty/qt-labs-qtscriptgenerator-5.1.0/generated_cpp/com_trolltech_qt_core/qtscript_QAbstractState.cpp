#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractstate.h>
#include <QVariant>
#include <qabstractstate.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QAbstractState.h"

static const char * const qtscript_QAbstractState_function_names[] = {
    "QAbstractState"
    // static
    // prototype
    , "machine"
    , "parentState"
    , "toString"
};

static const char * const qtscript_QAbstractState_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QAbstractState_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractState_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractState::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractState*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractState*)
Q_DECLARE_METATYPE(QStateMachine*)
Q_DECLARE_METATYPE(QState*)

//
// QAbstractState
//

static QScriptValue qtscript_QAbstractState_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractState* _q_self = qscriptvalue_cast<QAbstractState*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractState.%0(): this object is not a QAbstractState")
            .arg(qtscript_QAbstractState_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QStateMachine* _q_result = _q_self->machine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QState* _q_result = _q_self->parentState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QAbstractState");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractState_throw_ambiguity_error_helper(context,
        qtscript_QAbstractState_function_names[_id+1],
        qtscript_QAbstractState_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractState_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QAbstractState cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractState_throw_ambiguity_error_helper(context,
        qtscript_QAbstractState_function_names[_id],
        qtscript_QAbstractState_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractState_toScriptValue(QScriptEngine *engine, QAbstractState* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractState_fromScriptValue(const QScriptValue &value, QAbstractState* &out)
{
    out = qobject_cast<QAbstractState*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractState_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractState*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractState*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractState_prototype_call, qtscript_QAbstractState_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractState_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractState*>(engine, qtscript_QAbstractState_toScriptValue, 
        qtscript_QAbstractState_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractState_static_call, proto, qtscript_QAbstractState_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
