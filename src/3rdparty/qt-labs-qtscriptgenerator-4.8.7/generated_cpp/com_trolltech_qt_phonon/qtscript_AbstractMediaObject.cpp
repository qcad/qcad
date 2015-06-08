#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <mediaobjectinterface.h>
#include <QVariant>
#include <mediasource.h>

#include "qtscriptshell_AbstractMediaObject.h"

static const char * const qtscript_AbstractMediaObject_function_names[] = {
    "AbstractMediaObject"
    // static
    // prototype
    , "currentTime"
    , "errorString"
    , "errorType"
    , "hasVideo"
    , "isSeekable"
    , "pause"
    , "play"
    , "prefinishMark"
    , "remainingTime"
    , "seek"
    , "setNextSource"
    , "setPrefinishMark"
    , "setSource"
    , "setTickInterval"
    , "setTransitionTime"
    , "source"
    , "state"
    , "stop"
    , "tickInterval"
    , "totalTime"
    , "transitionTime"
    , "toString"
};

static const char * const qtscript_AbstractMediaObject_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qint64 milliseconds"
    , "MediaSource source"
    , "int arg__1"
    , "MediaSource arg__1"
    , "int interval"
    , "int arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_AbstractMediaObject_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_AbstractMediaObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractMediaObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::MediaObjectInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractMediaObject*)
Q_DECLARE_METATYPE(Phonon::MediaSource)

//
// AbstractMediaObject
//

static QScriptValue qtscript_AbstractMediaObject_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::MediaObjectInterface* _q_self = qscriptvalue_cast<Phonon::MediaObjectInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractMediaObject.%0(): this object is not a AbstractMediaObject")
            .arg(qtscript_AbstractMediaObject_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->currentTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Phonon::ErrorType _q_result = _q_self->errorType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasVideo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSeekable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->pause();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->play();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->prefinishMark();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->remainingTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->seek(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
        _q_self->setNextSource(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPrefinishMark(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
        _q_self->setSource(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTickInterval(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTransitionTime(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        Phonon::MediaSource _q_result = _q_self->source();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        Phonon::State _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        _q_self->stop();
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->tickInterval();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->totalTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->transitionTime();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("AbstractMediaObject");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractMediaObject_throw_ambiguity_error_helper(context,
        qtscript_AbstractMediaObject_function_names[_id+1],
        qtscript_AbstractMediaObject_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractMediaObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AbstractMediaObject(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AbstractMediaObject* _q_cpp_result = new QtScriptShell_AbstractMediaObject();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::MediaObjectInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractMediaObject_throw_ambiguity_error_helper(context,
        qtscript_AbstractMediaObject_function_names[_id],
        qtscript_AbstractMediaObject_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractMediaObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaObjectInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::MediaObjectInterface*)0));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractMediaObject_prototype_call, qtscript_AbstractMediaObject_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractMediaObject_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaObjectInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractMediaObject_static_call, proto, qtscript_AbstractMediaObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
