#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsignaltransition.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qabstractstate.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsignaltransition.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QSignalTransition.h"

static const char * const qtscript_QSignalTransition_function_names[] = {
    "QSignalTransition"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QSignalTransition_function_signatures[] = {
    "QObject sender, char signal, QState sourceState\nQState sourceState"
    // static
    // prototype
""
};

static const int qtscript_QSignalTransition_function_lengths[] = {
    3
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QSignalTransition_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSignalTransition::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSignalTransition*)
Q_DECLARE_METATYPE(QtScriptShell_QSignalTransition*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QState*)
Q_DECLARE_METATYPE(QAbstractTransition*)

//
// QSignalTransition
//

static QScriptValue qtscript_QSignalTransition_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSignalTransition* _q_self = qscriptvalue_cast<QSignalTransition*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSignalTransition.%0(): this object is not a QSignalTransition")
            .arg(qtscript_QSignalTransition_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QSignalTransition");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSignalTransition_throw_ambiguity_error_helper(context,
        qtscript_QSignalTransition_function_names[_id+1],
        qtscript_QSignalTransition_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSignalTransition_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSignalTransition(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSignalTransition* _q_cpp_result = new QtScriptShell_QSignalTransition();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSignalTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QState* _q_arg0 = qscriptvalue_cast<QState*>(context->argument(0));
        QtScriptShell_QSignalTransition* _q_cpp_result = new QtScriptShell_QSignalTransition(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSignalTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        QtScriptShell_QSignalTransition* _q_cpp_result = new QtScriptShell_QSignalTransition(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSignalTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        QState* _q_arg2 = qscriptvalue_cast<QState*>(context->argument(2));
        QtScriptShell_QSignalTransition* _q_cpp_result = new QtScriptShell_QSignalTransition(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSignalTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSignalTransition_throw_ambiguity_error_helper(context,
        qtscript_QSignalTransition_function_names[_id],
        qtscript_QSignalTransition_function_signatures[_id]);
}

static QScriptValue qtscript_QSignalTransition_toScriptValue(QScriptEngine *engine, QSignalTransition* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSignalTransition_fromScriptValue(const QScriptValue &value, QSignalTransition* &out)
{
    out = qobject_cast<QSignalTransition*>(value.toQObject());
}

QScriptValue qtscript_create_QSignalTransition_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSignalTransition*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSignalTransition*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractTransition*>()));

    qScriptRegisterMetaType<QSignalTransition*>(engine, qtscript_QSignalTransition_toScriptValue, 
        qtscript_QSignalTransition_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSignalTransition_static_call, proto, qtscript_QSignalTransition_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
