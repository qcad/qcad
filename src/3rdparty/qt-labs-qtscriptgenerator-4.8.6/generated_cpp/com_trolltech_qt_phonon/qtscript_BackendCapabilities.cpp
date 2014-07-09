#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <backendcapabilities.h>
#include <QVariant>
#include <objectdescription.h>
#include <qlist.h>
#include <qstringlist.h>


static const char * const qtscript_BackendCapabilities_function_names[] = {
    "BackendCapabilities"
    // static
    , "availableAudioCaptureDevices"
    , "availableAudioEffects"
    , "availableAudioOutputDevices"
    , "availableMimeTypes"
    , "isMimeTypeAvailable"
    // prototype
    , "toString"
};

static const char * const qtscript_BackendCapabilities_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , ""
    , ""
    , "String mimeType"
    // prototype
""
};

static const int qtscript_BackendCapabilities_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 0
    , 0
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_BackendCapabilities_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("BackendCapabilities::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}


//
// BackendCapabilities
//

static QScriptValue qtscript_BackendCapabilities_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("BackendCapabilities cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<Phonon::AudioCaptureDevice> _q_result = Phonon::BackendCapabilities::availableAudioCaptureDevices();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<Phonon::EffectDescription> _q_result = Phonon::BackendCapabilities::availableAudioEffects();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<Phonon::AudioOutputDevice> _q_result = Phonon::BackendCapabilities::availableAudioOutputDevices();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QStringList _q_result = Phonon::BackendCapabilities::availableMimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = Phonon::BackendCapabilities::isMimeTypeAvailable(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_BackendCapabilities_throw_ambiguity_error_helper(context,
        qtscript_BackendCapabilities_function_names[_id],
        qtscript_BackendCapabilities_function_signatures[_id]);
}

QScriptValue qtscript_create_BackendCapabilities_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_BackendCapabilities_static_call, proto, qtscript_BackendCapabilities_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_BackendCapabilities_static_call,
            qtscript_BackendCapabilities_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_BackendCapabilities_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
