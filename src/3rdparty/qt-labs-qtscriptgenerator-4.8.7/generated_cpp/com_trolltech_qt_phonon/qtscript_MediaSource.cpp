#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <mediasource.h>
#include <QVariant>
#include <abstractmediastream.h>
#include <mediasource.h>
#include <qiodevice.h>
#include <qurl.h>

static const char * const qtscript_MediaSource_function_names[] = {
    "MediaSource"
    // static
    // prototype
    , "autoDelete"
    , "deviceName"
    , "discType"
    , "fileName"
    , "equals"
    , "setAutoDelete"
    , "stream"
    , "type"
    , "url"
    , "toString"
};

static const char * const qtscript_MediaSource_function_signatures[] = {
    "\nAbstractMediaStream stream\nDiscType discType, String deviceName\nQIODevice ioDevice\nMediaSource rhs\nString fileName\nQUrl url"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "MediaSource rhs"
    , "bool enable"
    , ""
    , ""
    , ""
""
};

static const int qtscript_MediaSource_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_MediaSource_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("MediaSource::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::MediaSource)
Q_DECLARE_METATYPE(Phonon::MediaSource*)
Q_DECLARE_METATYPE(Phonon::MediaSource::Type)
Q_DECLARE_METATYPE(Phonon::DiscType)
Q_DECLARE_METATYPE(Phonon::AbstractMediaStream*)
Q_DECLARE_METATYPE(QIODevice*)

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
// Phonon::MediaSource::Type
//

static const Phonon::MediaSource::Type qtscript_MediaSource_Type_values[] = {
    Phonon::MediaSource::Invalid
    , Phonon::MediaSource::LocalFile
    , Phonon::MediaSource::Url
    , Phonon::MediaSource::Disc
    , Phonon::MediaSource::Stream
    , Phonon::MediaSource::Empty
};

static const char * const qtscript_MediaSource_Type_keys[] = {
    "Invalid"
    , "LocalFile"
    , "Url"
    , "Disc"
    , "Stream"
    , "Empty"
};

static QString qtscript_MediaSource_Type_toStringHelper(Phonon::MediaSource::Type value)
{
    if ((value >= Phonon::MediaSource::Invalid) && (value <= Phonon::MediaSource::Empty))
        return qtscript_MediaSource_Type_keys[static_cast<int>(value)-static_cast<int>(Phonon::MediaSource::Invalid)];
    return QString();
}

static QScriptValue qtscript_MediaSource_Type_toScriptValue(QScriptEngine *engine, const Phonon::MediaSource::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("MediaSource"));
    return clazz.property(qtscript_MediaSource_Type_toStringHelper(value));
}

static void qtscript_MediaSource_Type_fromScriptValue(const QScriptValue &value, Phonon::MediaSource::Type &out)
{
    out = qvariant_cast<Phonon::MediaSource::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_MediaSource_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::MediaSource::Invalid) && (arg <= Phonon::MediaSource::Empty))
        return qScriptValueFromValue(engine,  static_cast<Phonon::MediaSource::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_MediaSource_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaSource::Type value = qscriptvalue_cast<Phonon::MediaSource::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_MediaSource_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaSource::Type value = qscriptvalue_cast<Phonon::MediaSource::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_MediaSource_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_MediaSource_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_MediaSource_Type,
        qtscript_MediaSource_Type_valueOf, qtscript_MediaSource_Type_toString);
    qScriptRegisterMetaType<Phonon::MediaSource::Type>(engine, qtscript_MediaSource_Type_toScriptValue,
        qtscript_MediaSource_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_MediaSource_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_MediaSource_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// MediaSource
//

static QScriptValue qtscript_MediaSource_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::MediaSource* _q_self = qscriptvalue_cast<Phonon::MediaSource*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("MediaSource.%0(): this object is not a MediaSource")
            .arg(qtscript_MediaSource_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoDelete();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->deviceName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Phonon::DiscType _q_result = _q_self->discType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoDelete(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        Phonon::AbstractMediaStream* _q_result = _q_self->stream();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Phonon::MediaSource::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->url();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("MediaSource");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaSource_throw_ambiguity_error_helper(context,
        qtscript_MediaSource_function_names[_id+1],
        qtscript_MediaSource_function_signatures[_id+1]);
}

static QScriptValue qtscript_MediaSource_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("MediaSource(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        Phonon::MediaSource _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<Phonon::AbstractMediaStream*>(context->argument(0))) {
            Phonon::AbstractMediaStream* _q_arg0 = qscriptvalue_cast<Phonon::AbstractMediaStream*>(context->argument(0));
            Phonon::MediaSource _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<Phonon::DiscType>() == context->argument(0).toVariant().userType())) {
            Phonon::DiscType _q_arg0 = qscriptvalue_cast<Phonon::DiscType>(context->argument(0));
            Phonon::MediaSource _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            Phonon::MediaSource _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<Phonon::MediaSource>() == context->argument(0).toVariant().userType())) {
            Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
            Phonon::MediaSource _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            Phonon::MediaSource _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            Phonon::MediaSource _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        Phonon::DiscType _q_arg0 = qscriptvalue_cast<Phonon::DiscType>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        Phonon::MediaSource _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaSource_throw_ambiguity_error_helper(context,
        qtscript_MediaSource_function_names[_id],
        qtscript_MediaSource_function_signatures[_id]);
}

QScriptValue qtscript_create_MediaSource_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaSource*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::MediaSource*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_MediaSource_prototype_call, qtscript_MediaSource_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_MediaSource_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaSource>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaSource*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_MediaSource_static_call, proto, qtscript_MediaSource_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_MediaSource_Type_class(engine, ctor));
    return ctor;
}
