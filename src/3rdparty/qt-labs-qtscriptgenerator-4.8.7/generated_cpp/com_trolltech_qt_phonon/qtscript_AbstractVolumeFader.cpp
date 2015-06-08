#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <volumefaderinterface.h>
#include <QVariant>

#include "qtscriptshell_AbstractVolumeFader.h"

static const char * const qtscript_AbstractVolumeFader_function_names[] = {
    "AbstractVolumeFader"
    // static
    // prototype
    , "fadeCurve"
    , "fadeTo"
    , "setFadeCurve"
    , "setVolume"
    , "volume"
    , "toString"
};

static const char * const qtscript_AbstractVolumeFader_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "float arg__1, int arg__2"
    , "FadeCurve arg__1"
    , "float arg__1"
    , ""
""
};

static const int qtscript_AbstractVolumeFader_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 2
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_AbstractVolumeFader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractVolumeFader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::VolumeFaderInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractVolumeFader*)
Q_DECLARE_METATYPE(Phonon::VolumeFaderEffect::FadeCurve)

//
// AbstractVolumeFader
//

static QScriptValue qtscript_AbstractVolumeFader_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::VolumeFaderInterface* _q_self = qscriptvalue_cast<Phonon::VolumeFaderInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractVolumeFader.%0(): this object is not a AbstractVolumeFader")
            .arg(qtscript_AbstractVolumeFader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Phonon::VolumeFaderEffect::FadeCurve _q_result = _q_self->fadeCurve();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->fadeTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        Phonon::VolumeFaderEffect::FadeCurve _q_arg0 = qscriptvalue_cast<Phonon::VolumeFaderEffect::FadeCurve>(context->argument(0));
        _q_self->setFadeCurve(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setVolume(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->volume();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("AbstractVolumeFader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractVolumeFader_throw_ambiguity_error_helper(context,
        qtscript_AbstractVolumeFader_function_names[_id+1],
        qtscript_AbstractVolumeFader_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractVolumeFader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AbstractVolumeFader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AbstractVolumeFader* _q_cpp_result = new QtScriptShell_AbstractVolumeFader();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::VolumeFaderInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractVolumeFader_throw_ambiguity_error_helper(context,
        qtscript_AbstractVolumeFader_function_names[_id],
        qtscript_AbstractVolumeFader_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractVolumeFader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::VolumeFaderInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::VolumeFaderInterface*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractVolumeFader_prototype_call, qtscript_AbstractVolumeFader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractVolumeFader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::VolumeFaderInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractVolumeFader_static_call, proto, qtscript_AbstractVolumeFader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
