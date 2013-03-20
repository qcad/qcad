#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <volumefadereffect.h>
#include <QVariant>
#include <effectparameter.h>
#include <objectdescription.h>
#include <path.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_VolumeFaderEffect.h"

static const char * const qtscript_VolumeFaderEffect_function_names[] = {
    "VolumeFaderEffect"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_VolumeFaderEffect_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_VolumeFaderEffect_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_VolumeFaderEffect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("VolumeFaderEffect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_VolumeFaderEffect_metaObject()
{
    return &Phonon::VolumeFaderEffect::staticMetaObject;
}

Q_DECLARE_METATYPE(Phonon::VolumeFaderEffect*)
Q_DECLARE_METATYPE(QtScriptShell_VolumeFaderEffect*)
Q_DECLARE_METATYPE(Phonon::VolumeFaderEffect::FadeCurve)
Q_DECLARE_METATYPE(Phonon::Effect*)

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
// Phonon::VolumeFaderEffect::FadeCurve
//

static const Phonon::VolumeFaderEffect::FadeCurve qtscript_VolumeFaderEffect_FadeCurve_values[] = {
    Phonon::VolumeFaderEffect::Fade3Decibel
    , Phonon::VolumeFaderEffect::Fade6Decibel
    , Phonon::VolumeFaderEffect::Fade9Decibel
    , Phonon::VolumeFaderEffect::Fade12Decibel
};

static const char * const qtscript_VolumeFaderEffect_FadeCurve_keys[] = {
    "Fade3Decibel"
    , "Fade6Decibel"
    , "Fade9Decibel"
    , "Fade12Decibel"
};

static QString qtscript_VolumeFaderEffect_FadeCurve_toStringHelper(Phonon::VolumeFaderEffect::FadeCurve value)
{
    const QMetaObject *meta = qtscript_VolumeFaderEffect_metaObject();
    int idx = meta->indexOfEnumerator("FadeCurve");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_VolumeFaderEffect_FadeCurve_toScriptValue(QScriptEngine *engine, const Phonon::VolumeFaderEffect::FadeCurve &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("VolumeFaderEffect"));
    return clazz.property(qtscript_VolumeFaderEffect_FadeCurve_toStringHelper(value));
}

static void qtscript_VolumeFaderEffect_FadeCurve_fromScriptValue(const QScriptValue &value, Phonon::VolumeFaderEffect::FadeCurve &out)
{
    out = qvariant_cast<Phonon::VolumeFaderEffect::FadeCurve>(value.toVariant());
}

static QScriptValue qtscript_construct_VolumeFaderEffect_FadeCurve(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_VolumeFaderEffect_metaObject();
    int idx = meta->indexOfEnumerator("FadeCurve");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Phonon::VolumeFaderEffect::FadeCurve>(arg));
    return context->throwError(QString::fromLatin1("FadeCurve(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_VolumeFaderEffect_FadeCurve_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::VolumeFaderEffect::FadeCurve value = qscriptvalue_cast<Phonon::VolumeFaderEffect::FadeCurve>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_VolumeFaderEffect_FadeCurve_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::VolumeFaderEffect::FadeCurve value = qscriptvalue_cast<Phonon::VolumeFaderEffect::FadeCurve>(context->thisObject());
    return QScriptValue(engine, qtscript_VolumeFaderEffect_FadeCurve_toStringHelper(value));
}

static QScriptValue qtscript_create_VolumeFaderEffect_FadeCurve_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_VolumeFaderEffect_FadeCurve,
        qtscript_VolumeFaderEffect_FadeCurve_valueOf, qtscript_VolumeFaderEffect_FadeCurve_toString);
    qScriptRegisterMetaType<Phonon::VolumeFaderEffect::FadeCurve>(engine, qtscript_VolumeFaderEffect_FadeCurve_toScriptValue,
        qtscript_VolumeFaderEffect_FadeCurve_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_VolumeFaderEffect_FadeCurve_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_VolumeFaderEffect_FadeCurve_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// VolumeFaderEffect
//

static QScriptValue qtscript_VolumeFaderEffect_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::VolumeFaderEffect* _q_self = qscriptvalue_cast<Phonon::VolumeFaderEffect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("VolumeFaderEffect.%0(): this object is not a VolumeFaderEffect")
            .arg(qtscript_VolumeFaderEffect_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("VolumeFaderEffect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_VolumeFaderEffect_throw_ambiguity_error_helper(context,
        qtscript_VolumeFaderEffect_function_names[_id+1],
        qtscript_VolumeFaderEffect_function_signatures[_id+1]);
}

static QScriptValue qtscript_VolumeFaderEffect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("VolumeFaderEffect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_VolumeFaderEffect* _q_cpp_result = new QtScriptShell_VolumeFaderEffect();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VolumeFaderEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_VolumeFaderEffect* _q_cpp_result = new QtScriptShell_VolumeFaderEffect(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VolumeFaderEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_VolumeFaderEffect_throw_ambiguity_error_helper(context,
        qtscript_VolumeFaderEffect_function_names[_id],
        qtscript_VolumeFaderEffect_function_signatures[_id]);
}

static QScriptValue qtscript_VolumeFaderEffect_toScriptValue(QScriptEngine *engine, Phonon::VolumeFaderEffect* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_VolumeFaderEffect_fromScriptValue(const QScriptValue &value, Phonon::VolumeFaderEffect* &out)
{
    out = qobject_cast<Phonon::VolumeFaderEffect*>(value.toQObject());
}

QScriptValue qtscript_create_VolumeFaderEffect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::VolumeFaderEffect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::VolumeFaderEffect*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<Phonon::Effect*>()));

    qScriptRegisterMetaType<Phonon::VolumeFaderEffect*>(engine, qtscript_VolumeFaderEffect_toScriptValue, 
        qtscript_VolumeFaderEffect_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_VolumeFaderEffect_static_call, proto, qtscript_VolumeFaderEffect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("FadeCurve"),
        qtscript_create_VolumeFaderEffect_FadeCurve_class(engine, ctor));
    return ctor;
}
