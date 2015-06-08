#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <objectdescription.h>
#include <QVariant>
#include <effectparameter.h>
#include <medianode.h>
#include <mediaobject.h>
#include <mediasource.h>
#include <path.h>

#include <objectdescription.h>
#include <phononnamespace.h>

static const char * const qtscript_Phonon_function_names[] = {
    "Phonon"
    // static
    , "categoryToString"
    , "createPath"
    , "createPlayer"
    , "phononVersion"
    , "qHash"
    // prototype
    , "toString"
};

static const char * const qtscript_Phonon_function_signatures[] = {
    ""
    // static
    , "Category c"
    , "MediaNode source, MediaNode sink"
    , "Category category, MediaSource source"
    , ""
    , "EffectParameter param"
    // prototype
""
};

static const int qtscript_Phonon_function_lengths[] = {
    0
    // static
    , 1
    , 2
    , 2
    , 0
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_Phonon_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("Phonon::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::DiscType)
Q_DECLARE_METATYPE(Phonon::MetaData)
Q_DECLARE_METATYPE(Phonon::ObjectDescriptionType)
Q_DECLARE_METATYPE(Phonon::MediaNode*)
Q_DECLARE_METATYPE(Phonon::Path)
Q_DECLARE_METATYPE(Phonon::MediaSource)
Q_DECLARE_METATYPE(Phonon::MediaObject*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(Phonon::EffectParameter)

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
// Phonon::DiscType
//

static const Phonon::DiscType qtscript_Phonon_DiscType_values[] = {
    Phonon::NoDisc
    , Phonon::Cd
    , Phonon::Dvd
    , Phonon::Vcd
};

static const char * const qtscript_Phonon_DiscType_keys[] = {
    "NoDisc"
    , "Cd"
    , "Dvd"
    , "Vcd"
};

static QString qtscript_Phonon_DiscType_toStringHelper(Phonon::DiscType value)
{
    if ((value >= Phonon::NoDisc) && (value <= Phonon::Vcd))
        return qtscript_Phonon_DiscType_keys[static_cast<int>(value)-static_cast<int>(Phonon::NoDisc)];
    return QString();
}

static QScriptValue qtscript_Phonon_DiscType_toScriptValue(QScriptEngine *engine, const Phonon::DiscType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Phonon"));
    return clazz.property(qtscript_Phonon_DiscType_toStringHelper(value));
}

static void qtscript_Phonon_DiscType_fromScriptValue(const QScriptValue &value, Phonon::DiscType &out)
{
    out = qvariant_cast<Phonon::DiscType>(value.toVariant());
}

static QScriptValue qtscript_construct_Phonon_DiscType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::NoDisc) && (arg <= Phonon::Vcd))
        return qScriptValueFromValue(engine,  static_cast<Phonon::DiscType>(arg));
    return context->throwError(QString::fromLatin1("DiscType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Phonon_DiscType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::DiscType value = qscriptvalue_cast<Phonon::DiscType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Phonon_DiscType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::DiscType value = qscriptvalue_cast<Phonon::DiscType>(context->thisObject());
    return QScriptValue(engine, qtscript_Phonon_DiscType_toStringHelper(value));
}

static QScriptValue qtscript_create_Phonon_DiscType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Phonon_DiscType,
        qtscript_Phonon_DiscType_valueOf, qtscript_Phonon_DiscType_toString);
    qScriptRegisterMetaType<Phonon::DiscType>(engine, qtscript_Phonon_DiscType_toScriptValue,
        qtscript_Phonon_DiscType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Phonon_DiscType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Phonon_DiscType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::MetaData
//

static const Phonon::MetaData qtscript_Phonon_MetaData_values[] = {
    Phonon::ArtistMetaData
    , Phonon::AlbumMetaData
    , Phonon::TitleMetaData
    , Phonon::DateMetaData
    , Phonon::GenreMetaData
    , Phonon::TracknumberMetaData
    , Phonon::DescriptionMetaData
    , Phonon::MusicBrainzDiscIdMetaData
};

static const char * const qtscript_Phonon_MetaData_keys[] = {
    "ArtistMetaData"
    , "AlbumMetaData"
    , "TitleMetaData"
    , "DateMetaData"
    , "GenreMetaData"
    , "TracknumberMetaData"
    , "DescriptionMetaData"
    , "MusicBrainzDiscIdMetaData"
};

static QString qtscript_Phonon_MetaData_toStringHelper(Phonon::MetaData value)
{
    if ((value >= Phonon::ArtistMetaData) && (value <= Phonon::MusicBrainzDiscIdMetaData))
        return qtscript_Phonon_MetaData_keys[static_cast<int>(value)-static_cast<int>(Phonon::ArtistMetaData)];
    return QString();
}

static QScriptValue qtscript_Phonon_MetaData_toScriptValue(QScriptEngine *engine, const Phonon::MetaData &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Phonon"));
    return clazz.property(qtscript_Phonon_MetaData_toStringHelper(value));
}

static void qtscript_Phonon_MetaData_fromScriptValue(const QScriptValue &value, Phonon::MetaData &out)
{
    out = qvariant_cast<Phonon::MetaData>(value.toVariant());
}

static QScriptValue qtscript_construct_Phonon_MetaData(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::ArtistMetaData) && (arg <= Phonon::MusicBrainzDiscIdMetaData))
        return qScriptValueFromValue(engine,  static_cast<Phonon::MetaData>(arg));
    return context->throwError(QString::fromLatin1("MetaData(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Phonon_MetaData_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MetaData value = qscriptvalue_cast<Phonon::MetaData>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Phonon_MetaData_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::MetaData value = qscriptvalue_cast<Phonon::MetaData>(context->thisObject());
    return QScriptValue(engine, qtscript_Phonon_MetaData_toStringHelper(value));
}

static QScriptValue qtscript_create_Phonon_MetaData_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Phonon_MetaData,
        qtscript_Phonon_MetaData_valueOf, qtscript_Phonon_MetaData_toString);
    qScriptRegisterMetaType<Phonon::MetaData>(engine, qtscript_Phonon_MetaData_toScriptValue,
        qtscript_Phonon_MetaData_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Phonon_MetaData_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Phonon_MetaData_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::Category
//

static const Phonon::Category qtscript_Phonon_Category_values[] = {
    Phonon::NoCategory
    , Phonon::NotificationCategory
    , Phonon::MusicCategory
    , Phonon::VideoCategory
    , Phonon::CommunicationCategory
    , Phonon::GameCategory
    , Phonon::AccessibilityCategory
};

static const char * const qtscript_Phonon_Category_keys[] = {
    "NoCategory"
    , "NotificationCategory"
    , "MusicCategory"
    , "VideoCategory"
    , "CommunicationCategory"
    , "GameCategory"
    , "AccessibilityCategory"
};

static QString qtscript_Phonon_Category_toStringHelper(Phonon::Category value)
{
    if ((value >= Phonon::NoCategory) && (value <= Phonon::AccessibilityCategory))
        return qtscript_Phonon_Category_keys[static_cast<int>(value)-static_cast<int>(Phonon::NoCategory)];
    return QString();
}

static QScriptValue qtscript_Phonon_Category_toScriptValue(QScriptEngine *engine, const Phonon::Category &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Phonon"));
    return clazz.property(qtscript_Phonon_Category_toStringHelper(value));
}

static void qtscript_Phonon_Category_fromScriptValue(const QScriptValue &value, Phonon::Category &out)
{
    out = qvariant_cast<Phonon::Category>(value.toVariant());
}

static QScriptValue qtscript_construct_Phonon_Category(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::NoCategory) && (arg <= Phonon::AccessibilityCategory))
        return qScriptValueFromValue(engine,  static_cast<Phonon::Category>(arg));
    return context->throwError(QString::fromLatin1("Category(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Phonon_Category_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::Category value = qscriptvalue_cast<Phonon::Category>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Phonon_Category_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::Category value = qscriptvalue_cast<Phonon::Category>(context->thisObject());
    return QScriptValue(engine, qtscript_Phonon_Category_toStringHelper(value));
}

static QScriptValue qtscript_create_Phonon_Category_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Phonon_Category,
        qtscript_Phonon_Category_valueOf, qtscript_Phonon_Category_toString);
    qScriptRegisterMetaType<Phonon::Category>(engine, qtscript_Phonon_Category_toScriptValue,
        qtscript_Phonon_Category_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Phonon_Category_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Phonon_Category_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::ObjectDescriptionType
//

static const Phonon::ObjectDescriptionType qtscript_Phonon_ObjectDescriptionType_values[] = {
    Phonon::AudioOutputDeviceType
    , Phonon::EffectType
    , Phonon::AudioChannelType
    , Phonon::SubtitleType
    , Phonon::AudioCaptureDeviceType
};

static const char * const qtscript_Phonon_ObjectDescriptionType_keys[] = {
    "AudioOutputDeviceType"
    , "EffectType"
    , "AudioChannelType"
    , "SubtitleType"
    , "AudioCaptureDeviceType"
};

static QString qtscript_Phonon_ObjectDescriptionType_toStringHelper(Phonon::ObjectDescriptionType value)
{
    if ((value >= Phonon::AudioOutputDeviceType) && (value <= Phonon::AudioCaptureDeviceType))
        return qtscript_Phonon_ObjectDescriptionType_keys[static_cast<int>(value)-static_cast<int>(Phonon::AudioOutputDeviceType)];
    return QString();
}

static QScriptValue qtscript_Phonon_ObjectDescriptionType_toScriptValue(QScriptEngine *engine, const Phonon::ObjectDescriptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Phonon"));
    return clazz.property(qtscript_Phonon_ObjectDescriptionType_toStringHelper(value));
}

static void qtscript_Phonon_ObjectDescriptionType_fromScriptValue(const QScriptValue &value, Phonon::ObjectDescriptionType &out)
{
    out = qvariant_cast<Phonon::ObjectDescriptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_Phonon_ObjectDescriptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AudioOutputDeviceType) && (arg <= Phonon::AudioCaptureDeviceType))
        return qScriptValueFromValue(engine,  static_cast<Phonon::ObjectDescriptionType>(arg));
    return context->throwError(QString::fromLatin1("ObjectDescriptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Phonon_ObjectDescriptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::ObjectDescriptionType value = qscriptvalue_cast<Phonon::ObjectDescriptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Phonon_ObjectDescriptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::ObjectDescriptionType value = qscriptvalue_cast<Phonon::ObjectDescriptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_Phonon_ObjectDescriptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_Phonon_ObjectDescriptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Phonon_ObjectDescriptionType,
        qtscript_Phonon_ObjectDescriptionType_valueOf, qtscript_Phonon_ObjectDescriptionType_toString);
    qScriptRegisterMetaType<Phonon::ObjectDescriptionType>(engine, qtscript_Phonon_ObjectDescriptionType_toScriptValue,
        qtscript_Phonon_ObjectDescriptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Phonon_ObjectDescriptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Phonon_ObjectDescriptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::State
//

static const Phonon::State qtscript_Phonon_State_values[] = {
    Phonon::LoadingState
    , Phonon::StoppedState
    , Phonon::PlayingState
    , Phonon::BufferingState
    , Phonon::PausedState
    , Phonon::ErrorState
};

static const char * const qtscript_Phonon_State_keys[] = {
    "LoadingState"
    , "StoppedState"
    , "PlayingState"
    , "BufferingState"
    , "PausedState"
    , "ErrorState"
};

static QString qtscript_Phonon_State_toStringHelper(Phonon::State value)
{
    if ((value >= Phonon::LoadingState) && (value <= Phonon::ErrorState))
        return qtscript_Phonon_State_keys[static_cast<int>(value)-static_cast<int>(Phonon::LoadingState)];
    return QString();
}

static QScriptValue qtscript_Phonon_State_toScriptValue(QScriptEngine *engine, const Phonon::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Phonon"));
    return clazz.property(qtscript_Phonon_State_toStringHelper(value));
}

static void qtscript_Phonon_State_fromScriptValue(const QScriptValue &value, Phonon::State &out)
{
    out = qvariant_cast<Phonon::State>(value.toVariant());
}

static QScriptValue qtscript_construct_Phonon_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::LoadingState) && (arg <= Phonon::ErrorState))
        return qScriptValueFromValue(engine,  static_cast<Phonon::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Phonon_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::State value = qscriptvalue_cast<Phonon::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Phonon_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::State value = qscriptvalue_cast<Phonon::State>(context->thisObject());
    return QScriptValue(engine, qtscript_Phonon_State_toStringHelper(value));
}

static QScriptValue qtscript_create_Phonon_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Phonon_State,
        qtscript_Phonon_State_valueOf, qtscript_Phonon_State_toString);
    qScriptRegisterMetaType<Phonon::State>(engine, qtscript_Phonon_State_toScriptValue,
        qtscript_Phonon_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Phonon_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Phonon_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::ErrorType
//

static const Phonon::ErrorType qtscript_Phonon_ErrorType_values[] = {
    Phonon::NoError
    , Phonon::NormalError
    , Phonon::FatalError
};

static const char * const qtscript_Phonon_ErrorType_keys[] = {
    "NoError"
    , "NormalError"
    , "FatalError"
};

static QString qtscript_Phonon_ErrorType_toStringHelper(Phonon::ErrorType value)
{
    if ((value >= Phonon::NoError) && (value <= Phonon::FatalError))
        return qtscript_Phonon_ErrorType_keys[static_cast<int>(value)-static_cast<int>(Phonon::NoError)];
    return QString();
}

static QScriptValue qtscript_Phonon_ErrorType_toScriptValue(QScriptEngine *engine, const Phonon::ErrorType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Phonon"));
    return clazz.property(qtscript_Phonon_ErrorType_toStringHelper(value));
}

static void qtscript_Phonon_ErrorType_fromScriptValue(const QScriptValue &value, Phonon::ErrorType &out)
{
    out = qvariant_cast<Phonon::ErrorType>(value.toVariant());
}

static QScriptValue qtscript_construct_Phonon_ErrorType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::NoError) && (arg <= Phonon::FatalError))
        return qScriptValueFromValue(engine,  static_cast<Phonon::ErrorType>(arg));
    return context->throwError(QString::fromLatin1("ErrorType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Phonon_ErrorType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::ErrorType value = qscriptvalue_cast<Phonon::ErrorType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Phonon_ErrorType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::ErrorType value = qscriptvalue_cast<Phonon::ErrorType>(context->thisObject());
    return QScriptValue(engine, qtscript_Phonon_ErrorType_toStringHelper(value));
}

static QScriptValue qtscript_create_Phonon_ErrorType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Phonon_ErrorType,
        qtscript_Phonon_ErrorType_valueOf, qtscript_Phonon_ErrorType_toString);
    qScriptRegisterMetaType<Phonon::ErrorType>(engine, qtscript_Phonon_ErrorType_toScriptValue,
        qtscript_Phonon_ErrorType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Phonon_ErrorType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Phonon_ErrorType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon
//

static QScriptValue qtscript_Phonon_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("Phonon cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 1) {
        Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
        QString _q_result = Phonon::categoryToString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        Phonon::MediaNode* _q_arg0 = qscriptvalue_cast<Phonon::MediaNode*>(context->argument(0));
        Phonon::MediaNode* _q_arg1 = qscriptvalue_cast<Phonon::MediaNode*>(context->argument(1));
        Phonon::Path _q_result = Phonon::createPath(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
        Phonon::MediaObject* _q_result = Phonon::createPlayer(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
        Phonon::MediaSource _q_arg1 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(1));
        Phonon::MediaObject* _q_result = Phonon::createPlayer(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        char* _q_result = const_cast<char*>(Phonon::phononVersion());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        Phonon::EffectParameter _q_arg0 = qscriptvalue_cast<Phonon::EffectParameter>(context->argument(0));
        uint _q_result = Phonon::qHash(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_Phonon_throw_ambiguity_error_helper(context,
        qtscript_Phonon_function_names[_id],
        qtscript_Phonon_function_signatures[_id]);
}

QScriptValue qtscript_create_Phonon_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_Phonon_static_call, proto, qtscript_Phonon_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_Phonon_static_call,
            qtscript_Phonon_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_Phonon_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("DiscType"),
        qtscript_create_Phonon_DiscType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MetaData"),
        qtscript_create_Phonon_MetaData_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Category"),
        qtscript_create_Phonon_Category_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ObjectDescriptionType"),
        qtscript_create_Phonon_ObjectDescriptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_Phonon_State_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ErrorType"),
        qtscript_create_Phonon_ErrorType_class(engine, ctor));
    return ctor;
}
