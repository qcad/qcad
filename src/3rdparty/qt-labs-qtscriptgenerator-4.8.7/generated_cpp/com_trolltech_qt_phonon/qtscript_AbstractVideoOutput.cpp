#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <abstractvideooutput.h>
#include <QVariant>
#include <path.h>
#include <qlist.h>

static const char * const qtscript_AbstractVideoOutput_function_names[] = {
    "AbstractVideoOutput"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_AbstractVideoOutput_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_AbstractVideoOutput_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_AbstractVideoOutput_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractVideoOutput::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::AbstractVideoOutput*)
Q_DECLARE_METATYPE(Phonon::MediaNode*)

//
// AbstractVideoOutput
//

static QScriptValue qtscript_AbstractVideoOutput_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::AbstractVideoOutput* _q_self = qscriptvalue_cast<Phonon::AbstractVideoOutput*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractVideoOutput.%0(): this object is not a AbstractVideoOutput")
            .arg(qtscript_AbstractVideoOutput_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("AbstractVideoOutput");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractVideoOutput_throw_ambiguity_error_helper(context,
        qtscript_AbstractVideoOutput_function_names[_id+1],
        qtscript_AbstractVideoOutput_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractVideoOutput_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("AbstractVideoOutput cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractVideoOutput_throw_ambiguity_error_helper(context,
        qtscript_AbstractVideoOutput_function_names[_id],
        qtscript_AbstractVideoOutput_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractVideoOutput_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::AbstractVideoOutput*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::AbstractVideoOutput*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<Phonon::MediaNode*>()));

    engine->setDefaultPrototype(qMetaTypeId<Phonon::AbstractVideoOutput*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractVideoOutput_static_call, proto, qtscript_AbstractVideoOutput_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
