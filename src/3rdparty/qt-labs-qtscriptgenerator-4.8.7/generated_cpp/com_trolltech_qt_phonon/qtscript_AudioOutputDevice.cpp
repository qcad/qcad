#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <objectdescription.h>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>

static const char * const qtscript_AudioOutputDevice_function_names[] = {
    "AudioOutputDevice"
    // static
    // prototype
    , "description"
    , "index"
    , "isValid"
    , "name"
    , "property"
    , "propertyNames"
    , "toString"
};

static const char * const qtscript_AudioOutputDevice_function_signatures[] = {
    "\nint index, HashMap properties"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "char name"
    , ""
""
};

static const int qtscript_AudioOutputDevice_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_AudioOutputDevice_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AudioOutputDevice::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::AudioOutputDevice*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QList<QByteArray>)
template <> \
struct QMetaTypeId< QHash<QByteArray,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QHash<QByteArray,QVariant> >("QHash<QByteArray,QVariant>"); \
        return metatype_id; \
    } \
};

//
// AudioOutputDevice
//

static QScriptValue qtscript_AudioOutputDevice_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::AudioOutputDevice* _q_self = qscriptvalue_cast<Phonon::AudioOutputDevice*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AudioOutputDevice.%0(): this object is not a AudioOutputDevice")
            .arg(qtscript_AudioOutputDevice_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->description();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->index();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        QVariant _q_result = _q_self->property(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QByteArray> _q_result = _q_self->propertyNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("AudioOutputDevice");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AudioOutputDevice_throw_ambiguity_error_helper(context,
        qtscript_AudioOutputDevice_function_names[_id+1],
        qtscript_AudioOutputDevice_function_signatures[_id+1]);
}

static QScriptValue qtscript_AudioOutputDevice_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AudioOutputDevice(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        Phonon::AudioOutputDevice _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QHash<QByteArray,QVariant> _q_arg1 = qscriptvalue_cast<QHash<QByteArray,QVariant> >(context->argument(1));
        Phonon::AudioOutputDevice _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AudioOutputDevice_throw_ambiguity_error_helper(context,
        qtscript_AudioOutputDevice_function_names[_id],
        qtscript_AudioOutputDevice_function_signatures[_id]);
}

QScriptValue qtscript_create_AudioOutputDevice_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::AudioOutputDevice*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::AudioOutputDevice*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AudioOutputDevice_prototype_call, qtscript_AudioOutputDevice_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AudioOutputDevice_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::AudioOutputDevice>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<Phonon::AudioOutputDevice*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AudioOutputDevice_static_call, proto, qtscript_AudioOutputDevice_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
