#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <abstractaudiooutput.h>
#include <QVariant>
#include <path.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_AbstractAudioOutput.h"

static const char * const qtscript_AbstractAudioOutput_function_names[] = {
    "AbstractAudioOutput"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_AbstractAudioOutput_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_AbstractAudioOutput_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_AbstractAudioOutput_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractAudioOutput::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::AbstractAudioOutput*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractAudioOutput*)
Q_DECLARE_METATYPE(Phonon::MediaNode*)

//
// AbstractAudioOutput
//

static QScriptValue qtscript_AbstractAudioOutput_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::AbstractAudioOutput* _q_self = qscriptvalue_cast<Phonon::AbstractAudioOutput*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractAudioOutput.%0(): this object is not a AbstractAudioOutput")
            .arg(qtscript_AbstractAudioOutput_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("AbstractAudioOutput");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractAudioOutput_throw_ambiguity_error_helper(context,
        qtscript_AbstractAudioOutput_function_names[_id+1],
        qtscript_AbstractAudioOutput_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractAudioOutput_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("AbstractAudioOutput cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractAudioOutput_throw_ambiguity_error_helper(context,
        qtscript_AbstractAudioOutput_function_names[_id],
        qtscript_AbstractAudioOutput_function_signatures[_id]);
}

static QScriptValue qtscript_AbstractAudioOutput_toScriptValue(QScriptEngine *engine, Phonon::AbstractAudioOutput* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_AbstractAudioOutput_fromScriptValue(const QScriptValue &value, Phonon::AbstractAudioOutput* &out)
{
    out = qobject_cast<Phonon::AbstractAudioOutput*>(value.toQObject());
}

QScriptValue qtscript_create_AbstractAudioOutput_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::AbstractAudioOutput*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::AbstractAudioOutput*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    proto.setProperty(QString::fromLatin1("__MediaNode__"),
        engine->defaultPrototype(qMetaTypeId<Phonon::MediaNode*>()),
        QScriptValue::SkipInEnumeration);

    qScriptRegisterMetaType<Phonon::AbstractAudioOutput*>(engine, qtscript_AbstractAudioOutput_toScriptValue, 
        qtscript_AbstractAudioOutput_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractAudioOutput_static_call, proto, qtscript_AbstractAudioOutput_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
