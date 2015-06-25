#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qpauseanimation.h>
#include <QVariant>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpauseanimation.h>

#include "qtscriptshell_QPauseAnimation.h"

static const char * const qtscript_QPauseAnimation_function_names[] = {
    "QPauseAnimation"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QPauseAnimation_function_signatures[] = {
    "QObject parent\nint msecs, QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QPauseAnimation_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QPauseAnimation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPauseAnimation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPauseAnimation*)
Q_DECLARE_METATYPE(QtScriptShell_QPauseAnimation*)
Q_DECLARE_METATYPE(QAbstractAnimation*)

//
// QPauseAnimation
//

static QScriptValue qtscript_QPauseAnimation_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPauseAnimation* _q_self = qscriptvalue_cast<QPauseAnimation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPauseAnimation.%0(): this object is not a QPauseAnimation")
            .arg(qtscript_QPauseAnimation_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QPauseAnimation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPauseAnimation_throw_ambiguity_error_helper(context,
        qtscript_QPauseAnimation_function_names[_id+1],
        qtscript_QPauseAnimation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPauseAnimation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPauseAnimation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPauseAnimation* _q_cpp_result = new QtScriptShell_QPauseAnimation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPauseAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QPauseAnimation* _q_cpp_result = new QtScriptShell_QPauseAnimation(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPauseAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QtScriptShell_QPauseAnimation* _q_cpp_result = new QtScriptShell_QPauseAnimation(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPauseAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QPauseAnimation* _q_cpp_result = new QtScriptShell_QPauseAnimation(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPauseAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPauseAnimation_throw_ambiguity_error_helper(context,
        qtscript_QPauseAnimation_function_names[_id],
        qtscript_QPauseAnimation_function_signatures[_id]);
}

static QScriptValue qtscript_QPauseAnimation_toScriptValue(QScriptEngine *engine, QPauseAnimation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPauseAnimation_fromScriptValue(const QScriptValue &value, QPauseAnimation* &out)
{
    out = qobject_cast<QPauseAnimation*>(value.toQObject());
}

QScriptValue qtscript_create_QPauseAnimation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPauseAnimation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPauseAnimation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractAnimation*>()));

    qScriptRegisterMetaType<QPauseAnimation*>(engine, qtscript_QPauseAnimation_toScriptValue, 
        qtscript_QPauseAnimation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPauseAnimation_static_call, proto, qtscript_QPauseAnimation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
