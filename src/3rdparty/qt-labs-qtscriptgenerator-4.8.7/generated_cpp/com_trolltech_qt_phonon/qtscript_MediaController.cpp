#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <mediacontroller.h>
#include <QVariant>
#include <mediaobject.h>
#include <objectdescription.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_MediaController.h"

static const char * const qtscript_MediaController_function_names[] = {
    "MediaController"
    // static
    // prototype
    , "autoplayTitles"
    , "availableAngles"
    , "availableAudioChannels"
    , "availableChapters"
    , "availableSubtitles"
    , "availableTitles"
    , "currentAngle"
    , "currentAudioChannel"
    , "currentChapter"
    , "currentSubtitle"
    , "currentTitle"
    , "setCurrentAudioChannel"
    , "setCurrentSubtitle"
    , "supportedFeatures"
    , "toString"
};

static const char * const qtscript_MediaController_function_signatures[] = {
    "MediaObject parent"
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
    , ""
    , ""
    , "AudioChannelDescription stream"
    , "SubtitleDescription stream"
    , ""
""
};

static const int qtscript_MediaController_function_lengths[] = {
    1
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
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_MediaController_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("MediaController::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::MediaController*)
Q_DECLARE_METATYPE(QtScriptShell_MediaController*)
Q_DECLARE_METATYPE(Phonon::MediaController::Feature)
Q_DECLARE_METATYPE(QFlags<Phonon::MediaController::Feature>)
Q_DECLARE_METATYPE(Phonon::MediaObject*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// Phonon::MediaController::Feature
//

static const Phonon::MediaController::Feature qtscript_MediaController_Feature_values[] = {
    Phonon::MediaController::Angles
    , Phonon::MediaController::Chapters
    , Phonon::MediaController::Titles
};

static const char * const qtscript_MediaController_Feature_keys[] = {
    "Angles"
    , "Chapters"
    , "Titles"
};

static QString qtscript_MediaController_Feature_toStringHelper(Phonon::MediaController::Feature value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_MediaController_Feature_values[i] == value)
            return QString::fromLatin1(qtscript_MediaController_Feature_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_MediaController_Feature_toScriptValue(QScriptEngine *engine, const Phonon::MediaController::Feature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("MediaController"));
    return clazz.property(qtscript_MediaController_Feature_toStringHelper(value));
}

static void qtscript_MediaController_Feature_fromScriptValue(const QScriptValue &value, Phonon::MediaController::Feature &out)
{
    out = qvariant_cast<Phonon::MediaController::Feature>(value.toVariant());
}

static QScriptValue qtscript_construct_MediaController_Feature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_MediaController_Feature_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Phonon::MediaController::Feature>(arg));
    }
    return context->throwError(QString::fromLatin1("Feature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_MediaController_Feature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaController::Feature value = qscriptvalue_cast<Phonon::MediaController::Feature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_MediaController_Feature_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaController::Feature value = qscriptvalue_cast<Phonon::MediaController::Feature>(context->thisObject());
    return QScriptValue(engine, qtscript_MediaController_Feature_toStringHelper(value));
}

static QScriptValue qtscript_create_MediaController_Feature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_MediaController_Feature,
        qtscript_MediaController_Feature_valueOf, qtscript_MediaController_Feature_toString);
    qScriptRegisterMetaType<Phonon::MediaController::Feature>(engine, qtscript_MediaController_Feature_toScriptValue,
        qtscript_MediaController_Feature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_MediaController_Feature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_MediaController_Feature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::MediaController::Features
//

static QScriptValue qtscript_MediaController_Features_toScriptValue(QScriptEngine *engine, const Phonon::MediaController::Features &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_MediaController_Features_fromScriptValue(const QScriptValue &value, Phonon::MediaController::Features &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Phonon::MediaController::Features>())
        out = qvariant_cast<Phonon::MediaController::Features>(var);
    else if (var.userType() == qMetaTypeId<Phonon::MediaController::Feature>())
        out = qvariant_cast<Phonon::MediaController::Feature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_MediaController_Features(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaController::Features result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Phonon::MediaController::Features>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Phonon::MediaController::Feature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Features(): argument %0 is not of type Feature").arg(i));
            }
            result |= qvariant_cast<Phonon::MediaController::Feature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_MediaController_Features_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaController::Features value = qscriptvalue_cast<Phonon::MediaController::Features>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_MediaController_Features_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MediaController::Features value = qscriptvalue_cast<Phonon::MediaController::Features>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_MediaController_Feature_values[i]) == qtscript_MediaController_Feature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_MediaController_Feature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_MediaController_Features_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Phonon::MediaController::Features>() == otherObj.value<Phonon::MediaController::Features>())));
}

static QScriptValue qtscript_create_MediaController_Features_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_MediaController_Features, qtscript_MediaController_Features_valueOf,
        qtscript_MediaController_Features_toString, qtscript_MediaController_Features_equals);
    qScriptRegisterMetaType<Phonon::MediaController::Features>(engine, qtscript_MediaController_Features_toScriptValue,
        qtscript_MediaController_Features_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// MediaController
//

static QScriptValue qtscript_MediaController_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::MediaController* _q_self = qscriptvalue_cast<Phonon::MediaController*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("MediaController.%0(): this object is not a MediaController")
            .arg(qtscript_MediaController_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoplayTitles();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->availableAngles();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<Phonon::AudioChannelDescription> _q_result = _q_self->availableAudioChannels();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->availableChapters();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QList<Phonon::SubtitleDescription> _q_result = _q_self->availableSubtitles();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->availableTitles();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentAngle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Phonon::AudioChannelDescription _q_result = _q_self->currentAudioChannel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentChapter();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        Phonon::SubtitleDescription _q_result = _q_self->currentSubtitle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentTitle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        Phonon::AudioChannelDescription _q_arg0 = qscriptvalue_cast<Phonon::AudioChannelDescription>(context->argument(0));
        _q_self->setCurrentAudioChannel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        Phonon::SubtitleDescription _q_arg0 = qscriptvalue_cast<Phonon::SubtitleDescription>(context->argument(0));
        _q_self->setCurrentSubtitle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QFlags<Phonon::MediaController::Feature> _q_result = _q_self->supportedFeatures();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("MediaController");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaController_throw_ambiguity_error_helper(context,
        qtscript_MediaController_function_names[_id+1],
        qtscript_MediaController_function_signatures[_id+1]);
}

static QScriptValue qtscript_MediaController_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("MediaController(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        Phonon::MediaObject* _q_arg0 = qscriptvalue_cast<Phonon::MediaObject*>(context->argument(0));
        QtScriptShell_MediaController* _q_cpp_result = new QtScriptShell_MediaController(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::MediaController*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaController_throw_ambiguity_error_helper(context,
        qtscript_MediaController_function_names[_id],
        qtscript_MediaController_function_signatures[_id]);
}

static QScriptValue qtscript_MediaController_toScriptValue(QScriptEngine *engine, Phonon::MediaController* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_MediaController_fromScriptValue(const QScriptValue &value, Phonon::MediaController* &out)
{
    out = qobject_cast<Phonon::MediaController*>(value.toQObject());
}

QScriptValue qtscript_create_MediaController_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaController*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::MediaController*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_MediaController_prototype_call, qtscript_MediaController_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_MediaController_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<Phonon::MediaController*>(engine, qtscript_MediaController_toScriptValue, 
        qtscript_MediaController_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_MediaController_static_call, proto, qtscript_MediaController_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Feature"),
        qtscript_create_MediaController_Feature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Features"),
        qtscript_create_MediaController_Features_class(engine));
    return ctor;
}
