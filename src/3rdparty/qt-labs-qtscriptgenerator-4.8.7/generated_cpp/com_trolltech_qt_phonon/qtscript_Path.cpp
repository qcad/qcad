#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <path.h>
#include <QVariant>
#include <effect.h>
#include <medianode.h>
#include <objectdescription.h>
#include <path.h>
#include <qlist.h>

static const char * const qtscript_Path_function_names[] = {
    "Path"
    // static
    // prototype
    , "disconnectPath"
    , "effects"
    , "insertEffect"
    , "isValid"
    , "equals"
    , "reconnect"
    , "removeEffect"
    , "sink"
    , "source"
    , "toString"
};

static const char * const qtscript_Path_function_signatures[] = {
    "\nPath arg__1"
    // static
    // prototype
    , ""
    , ""
    , "Effect newEffect, Effect insertBefore\nEffectDescription desc, Effect insertBefore"
    , ""
    , "Path p"
    , "MediaNode source, MediaNode sink"
    , "Effect effect"
    , ""
    , ""
""
};

static const int qtscript_Path_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 2
    , 0
    , 1
    , 2
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_Path_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("Path::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::Path)
Q_DECLARE_METATYPE(Phonon::Path*)
Q_DECLARE_METATYPE(Phonon::Effect*)
Q_DECLARE_METATYPE(QList<Phonon::Effect*>)
Q_DECLARE_METATYPE(Phonon::MediaNode*)

//
// Path
//

static QScriptValue qtscript_Path_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::Path* _q_self = qscriptvalue_cast<Phonon::Path*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("Path.%0(): this object is not a Path")
            .arg(qtscript_Path_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->disconnect();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<Phonon::Effect*> _q_result = _q_self->effects();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<Phonon::Effect*>(context->argument(0))) {
            Phonon::Effect* _q_arg0 = qscriptvalue_cast<Phonon::Effect*>(context->argument(0));
            bool _q_result = _q_self->insertEffect(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<Phonon::EffectDescription>() == context->argument(0).toVariant().userType())) {
            Phonon::EffectDescription _q_arg0 = qscriptvalue_cast<Phonon::EffectDescription>(context->argument(0));
            Phonon::Effect* _q_result = _q_self->insertEffect(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<Phonon::Effect*>(context->argument(0))
            && qscriptvalue_cast<Phonon::Effect*>(context->argument(1))) {
            Phonon::Effect* _q_arg0 = qscriptvalue_cast<Phonon::Effect*>(context->argument(0));
            Phonon::Effect* _q_arg1 = qscriptvalue_cast<Phonon::Effect*>(context->argument(1));
            bool _q_result = _q_self->insertEffect(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<Phonon::EffectDescription>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<Phonon::Effect*>(context->argument(1))) {
            Phonon::EffectDescription _q_arg0 = qscriptvalue_cast<Phonon::EffectDescription>(context->argument(0));
            Phonon::Effect* _q_arg1 = qscriptvalue_cast<Phonon::Effect*>(context->argument(1));
            Phonon::Effect* _q_result = _q_self->insertEffect(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        Phonon::Path _q_arg0 = qscriptvalue_cast<Phonon::Path>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        Phonon::MediaNode* _q_arg0 = qscriptvalue_cast<Phonon::MediaNode*>(context->argument(0));
        Phonon::MediaNode* _q_arg1 = qscriptvalue_cast<Phonon::MediaNode*>(context->argument(1));
        bool _q_result = _q_self->reconnect(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        Phonon::Effect* _q_arg0 = qscriptvalue_cast<Phonon::Effect*>(context->argument(0));
        bool _q_result = _q_self->removeEffect(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Phonon::MediaNode* _q_result = _q_self->sink();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        Phonon::MediaNode* _q_result = _q_self->source();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("Path");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_Path_throw_ambiguity_error_helper(context,
        qtscript_Path_function_names[_id+1],
        qtscript_Path_function_signatures[_id+1]);
}

static QScriptValue qtscript_Path_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("Path(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        Phonon::Path _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        Phonon::Path _q_arg0 = qscriptvalue_cast<Phonon::Path>(context->argument(0));
        Phonon::Path _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_Path_throw_ambiguity_error_helper(context,
        qtscript_Path_function_names[_id],
        qtscript_Path_function_signatures[_id]);
}

QScriptValue qtscript_create_Path_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::Path*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::Path*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_Path_prototype_call, qtscript_Path_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_Path_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::Path>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<Phonon::Path*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_Path_static_call, proto, qtscript_Path_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
