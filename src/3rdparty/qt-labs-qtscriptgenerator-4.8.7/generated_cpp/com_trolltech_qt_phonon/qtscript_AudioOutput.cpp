#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <audiooutput.h>
#include <QVariant>
#include <objectdescription.h>
#include <path.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_AudioOutput.h"

static const char * const qtscript_AudioOutput_function_names[] = {
    "AudioOutput"
    // static
    // prototype
    , "category"
    , "toString"
};

static const char * const qtscript_AudioOutput_function_signatures[] = {
    "Category category, QObject parent\nQObject parent"
    // static
    // prototype
    , ""
""
};

static const int qtscript_AudioOutput_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_AudioOutput_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AudioOutput::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::AudioOutput*)
Q_DECLARE_METATYPE(QtScriptShell_AudioOutput*)
Q_DECLARE_METATYPE(Phonon::AbstractAudioOutput*)

//
// AudioOutput
//

static QScriptValue qtscript_AudioOutput_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::AudioOutput* _q_self = qscriptvalue_cast<Phonon::AudioOutput*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AudioOutput.%0(): this object is not a AudioOutput")
            .arg(qtscript_AudioOutput_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Phonon::Category _q_result = _q_self->category();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("AudioOutput");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AudioOutput_throw_ambiguity_error_helper(context,
        qtscript_AudioOutput_function_names[_id+1],
        qtscript_AudioOutput_function_signatures[_id+1]);
}

static QScriptValue qtscript_AudioOutput_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AudioOutput(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AudioOutput* _q_cpp_result = new QtScriptShell_AudioOutput();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::AudioOutput*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Phonon::Category>() == context->argument(0).toVariant().userType())) {
            Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
            QtScriptShell_AudioOutput* _q_cpp_result = new QtScriptShell_AudioOutput(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::AudioOutput*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_AudioOutput* _q_cpp_result = new QtScriptShell_AudioOutput(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::AudioOutput*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_AudioOutput* _q_cpp_result = new QtScriptShell_AudioOutput(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::AudioOutput*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AudioOutput_throw_ambiguity_error_helper(context,
        qtscript_AudioOutput_function_names[_id],
        qtscript_AudioOutput_function_signatures[_id]);
}

static QScriptValue qtscript_AudioOutput_toScriptValue(QScriptEngine *engine, Phonon::AudioOutput* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_AudioOutput_fromScriptValue(const QScriptValue &value, Phonon::AudioOutput* &out)
{
    out = qobject_cast<Phonon::AudioOutput*>(value.toQObject());
}

QScriptValue qtscript_create_AudioOutput_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::AudioOutput*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::AudioOutput*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<Phonon::AbstractAudioOutput*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AudioOutput_prototype_call, qtscript_AudioOutput_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AudioOutput_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<Phonon::AudioOutput*>(engine, qtscript_AudioOutput_toScriptValue, 
        qtscript_AudioOutput_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_AudioOutput_static_call, proto, qtscript_AudioOutput_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
