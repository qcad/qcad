#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <effectinterface.h>
#include <QVariant>
#include <effectparameter.h>
#include <qlist.h>

#include "qtscriptshell_AbstractEffect.h"

static const char * const qtscript_AbstractEffect_function_names[] = {
    "AbstractEffect"
    // static
    // prototype
    , "parameterValue"
    , "parameters"
    , "setParameterValue"
    , "toString"
};

static const char * const qtscript_AbstractEffect_function_signatures[] = {
    ""
    // static
    // prototype
    , "EffectParameter arg__1"
    , ""
    , "EffectParameter arg__1, Object newValue"
""
};

static const int qtscript_AbstractEffect_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_AbstractEffect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractEffect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::EffectInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractEffect*)
Q_DECLARE_METATYPE(Phonon::EffectParameter)
Q_DECLARE_METATYPE(QList<Phonon::EffectParameter>)

//
// AbstractEffect
//

static QScriptValue qtscript_AbstractEffect_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::EffectInterface* _q_self = qscriptvalue_cast<Phonon::EffectInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractEffect.%0(): this object is not a AbstractEffect")
            .arg(qtscript_AbstractEffect_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        Phonon::EffectParameter _q_arg0 = qscriptvalue_cast<Phonon::EffectParameter>(context->argument(0));
        QVariant _q_result = _q_self->parameterValue(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<Phonon::EffectParameter> _q_result = _q_self->parameters();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        Phonon::EffectParameter _q_arg0 = qscriptvalue_cast<Phonon::EffectParameter>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setParameterValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("AbstractEffect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractEffect_throw_ambiguity_error_helper(context,
        qtscript_AbstractEffect_function_names[_id+1],
        qtscript_AbstractEffect_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractEffect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AbstractEffect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AbstractEffect* _q_cpp_result = new QtScriptShell_AbstractEffect();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::EffectInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractEffect_throw_ambiguity_error_helper(context,
        qtscript_AbstractEffect_function_names[_id],
        qtscript_AbstractEffect_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractEffect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::EffectInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::EffectInterface*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractEffect_prototype_call, qtscript_AbstractEffect_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractEffect_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::EffectInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractEffect_static_call, proto, qtscript_AbstractEffect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
