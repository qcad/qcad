#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <addoninterface.h>
#include <QVariant>
#include <qlist.h>

#include "qtscriptshell_AbstractAddon.h"

static const char * const qtscript_AbstractAddon_function_names[] = {
    "AbstractAddon"
    // static
    // prototype
    , "hasInterface"
    , "interfaceCall"
    , "toString"
};

static const char * const qtscript_AbstractAddon_function_signatures[] = {
    ""
    // static
    // prototype
    , "Interface iface"
    , "Interface iface, int command, List arguments"
""
};

static const int qtscript_AbstractAddon_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 3
    , 0
};

static QScriptValue qtscript_AbstractAddon_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractAddon::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::AddonInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractAddon*)
Q_DECLARE_METATYPE(Phonon::AddonInterface::SubtitleCommand)
Q_DECLARE_METATYPE(Phonon::AddonInterface::TitleCommand)
Q_DECLARE_METATYPE(Phonon::AddonInterface::Interface)
Q_DECLARE_METATYPE(Phonon::AddonInterface::AudioChannelCommand)
Q_DECLARE_METATYPE(Phonon::AddonInterface::ChapterCommand)
Q_DECLARE_METATYPE(Phonon::AddonInterface::NavigationCommand)
Q_DECLARE_METATYPE(Phonon::AddonInterface::AngleCommand)

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
// Phonon::AddonInterface::SubtitleCommand
//

static const Phonon::AddonInterface::SubtitleCommand qtscript_AbstractAddon_SubtitleCommand_values[] = {
    Phonon::AddonInterface::availableSubtitles
    , Phonon::AddonInterface::currentSubtitle
    , Phonon::AddonInterface::setCurrentSubtitle
};

static const char * const qtscript_AbstractAddon_SubtitleCommand_keys[] = {
    "availableSubtitles"
    , "currentSubtitle"
    , "setCurrentSubtitle"
};

static QString qtscript_AbstractAddon_SubtitleCommand_toStringHelper(Phonon::AddonInterface::SubtitleCommand value)
{
    if ((value >= Phonon::AddonInterface::availableSubtitles) && (value <= Phonon::AddonInterface::setCurrentSubtitle))
        return qtscript_AbstractAddon_SubtitleCommand_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::availableSubtitles)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_SubtitleCommand_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::SubtitleCommand &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_SubtitleCommand_toStringHelper(value));
}

static void qtscript_AbstractAddon_SubtitleCommand_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::SubtitleCommand &out)
{
    out = qvariant_cast<Phonon::AddonInterface::SubtitleCommand>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_SubtitleCommand(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::availableSubtitles) && (arg <= Phonon::AddonInterface::setCurrentSubtitle))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::SubtitleCommand>(arg));
    return context->throwError(QString::fromLatin1("SubtitleCommand(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_SubtitleCommand_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::SubtitleCommand value = qscriptvalue_cast<Phonon::AddonInterface::SubtitleCommand>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_SubtitleCommand_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::SubtitleCommand value = qscriptvalue_cast<Phonon::AddonInterface::SubtitleCommand>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_SubtitleCommand_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_SubtitleCommand_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_SubtitleCommand,
        qtscript_AbstractAddon_SubtitleCommand_valueOf, qtscript_AbstractAddon_SubtitleCommand_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::SubtitleCommand>(engine, qtscript_AbstractAddon_SubtitleCommand_toScriptValue,
        qtscript_AbstractAddon_SubtitleCommand_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_SubtitleCommand_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_SubtitleCommand_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::AddonInterface::TitleCommand
//

static const Phonon::AddonInterface::TitleCommand qtscript_AbstractAddon_TitleCommand_values[] = {
    Phonon::AddonInterface::availableTitles
    , Phonon::AddonInterface::title
    , Phonon::AddonInterface::setTitle
    , Phonon::AddonInterface::autoplayTitles
    , Phonon::AddonInterface::setAutoplayTitles
};

static const char * const qtscript_AbstractAddon_TitleCommand_keys[] = {
    "availableTitles"
    , "title"
    , "setTitle"
    , "autoplayTitles"
    , "setAutoplayTitles"
};

static QString qtscript_AbstractAddon_TitleCommand_toStringHelper(Phonon::AddonInterface::TitleCommand value)
{
    if ((value >= Phonon::AddonInterface::availableTitles) && (value <= Phonon::AddonInterface::setAutoplayTitles))
        return qtscript_AbstractAddon_TitleCommand_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::availableTitles)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_TitleCommand_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::TitleCommand &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_TitleCommand_toStringHelper(value));
}

static void qtscript_AbstractAddon_TitleCommand_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::TitleCommand &out)
{
    out = qvariant_cast<Phonon::AddonInterface::TitleCommand>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_TitleCommand(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::availableTitles) && (arg <= Phonon::AddonInterface::setAutoplayTitles))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::TitleCommand>(arg));
    return context->throwError(QString::fromLatin1("TitleCommand(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_TitleCommand_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::TitleCommand value = qscriptvalue_cast<Phonon::AddonInterface::TitleCommand>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_TitleCommand_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::TitleCommand value = qscriptvalue_cast<Phonon::AddonInterface::TitleCommand>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_TitleCommand_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_TitleCommand_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_TitleCommand,
        qtscript_AbstractAddon_TitleCommand_valueOf, qtscript_AbstractAddon_TitleCommand_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::TitleCommand>(engine, qtscript_AbstractAddon_TitleCommand_toScriptValue,
        qtscript_AbstractAddon_TitleCommand_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_TitleCommand_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_TitleCommand_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::AddonInterface::Interface
//

static const Phonon::AddonInterface::Interface qtscript_AbstractAddon_Interface_values[] = {
    Phonon::AddonInterface::NavigationInterface
    , Phonon::AddonInterface::ChapterInterface
    , Phonon::AddonInterface::AngleInterface
    , Phonon::AddonInterface::TitleInterface
    , Phonon::AddonInterface::SubtitleInterface
    , Phonon::AddonInterface::AudioChannelInterface
};

static const char * const qtscript_AbstractAddon_Interface_keys[] = {
    "NavigationInterface"
    , "ChapterInterface"
    , "AngleInterface"
    , "TitleInterface"
    , "SubtitleInterface"
    , "AudioChannelInterface"
};

static QString qtscript_AbstractAddon_Interface_toStringHelper(Phonon::AddonInterface::Interface value)
{
    if ((value >= Phonon::AddonInterface::NavigationInterface) && (value <= Phonon::AddonInterface::AudioChannelInterface))
        return qtscript_AbstractAddon_Interface_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::NavigationInterface)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_Interface_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::Interface &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_Interface_toStringHelper(value));
}

static void qtscript_AbstractAddon_Interface_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::Interface &out)
{
    out = qvariant_cast<Phonon::AddonInterface::Interface>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_Interface(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::NavigationInterface) && (arg <= Phonon::AddonInterface::AudioChannelInterface))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::Interface>(arg));
    return context->throwError(QString::fromLatin1("Interface(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_Interface_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::Interface value = qscriptvalue_cast<Phonon::AddonInterface::Interface>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_Interface_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::Interface value = qscriptvalue_cast<Phonon::AddonInterface::Interface>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_Interface_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_Interface_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_Interface,
        qtscript_AbstractAddon_Interface_valueOf, qtscript_AbstractAddon_Interface_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::Interface>(engine, qtscript_AbstractAddon_Interface_toScriptValue,
        qtscript_AbstractAddon_Interface_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_Interface_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_Interface_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::AddonInterface::AudioChannelCommand
//

static const Phonon::AddonInterface::AudioChannelCommand qtscript_AbstractAddon_AudioChannelCommand_values[] = {
    Phonon::AddonInterface::availableAudioChannels
    , Phonon::AddonInterface::currentAudioChannel
    , Phonon::AddonInterface::setCurrentAudioChannel
};

static const char * const qtscript_AbstractAddon_AudioChannelCommand_keys[] = {
    "availableAudioChannels"
    , "currentAudioChannel"
    , "setCurrentAudioChannel"
};

static QString qtscript_AbstractAddon_AudioChannelCommand_toStringHelper(Phonon::AddonInterface::AudioChannelCommand value)
{
    if ((value >= Phonon::AddonInterface::availableAudioChannels) && (value <= Phonon::AddonInterface::setCurrentAudioChannel))
        return qtscript_AbstractAddon_AudioChannelCommand_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::availableAudioChannels)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_AudioChannelCommand_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::AudioChannelCommand &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_AudioChannelCommand_toStringHelper(value));
}

static void qtscript_AbstractAddon_AudioChannelCommand_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::AudioChannelCommand &out)
{
    out = qvariant_cast<Phonon::AddonInterface::AudioChannelCommand>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_AudioChannelCommand(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::availableAudioChannels) && (arg <= Phonon::AddonInterface::setCurrentAudioChannel))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::AudioChannelCommand>(arg));
    return context->throwError(QString::fromLatin1("AudioChannelCommand(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_AudioChannelCommand_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::AudioChannelCommand value = qscriptvalue_cast<Phonon::AddonInterface::AudioChannelCommand>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_AudioChannelCommand_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::AudioChannelCommand value = qscriptvalue_cast<Phonon::AddonInterface::AudioChannelCommand>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_AudioChannelCommand_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_AudioChannelCommand_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_AudioChannelCommand,
        qtscript_AbstractAddon_AudioChannelCommand_valueOf, qtscript_AbstractAddon_AudioChannelCommand_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::AudioChannelCommand>(engine, qtscript_AbstractAddon_AudioChannelCommand_toScriptValue,
        qtscript_AbstractAddon_AudioChannelCommand_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_AudioChannelCommand_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_AudioChannelCommand_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::AddonInterface::ChapterCommand
//

static const Phonon::AddonInterface::ChapterCommand qtscript_AbstractAddon_ChapterCommand_values[] = {
    Phonon::AddonInterface::availableChapters
    , Phonon::AddonInterface::chapter
    , Phonon::AddonInterface::setChapter
};

static const char * const qtscript_AbstractAddon_ChapterCommand_keys[] = {
    "availableChapters"
    , "chapter"
    , "setChapter"
};

static QString qtscript_AbstractAddon_ChapterCommand_toStringHelper(Phonon::AddonInterface::ChapterCommand value)
{
    if ((value >= Phonon::AddonInterface::availableChapters) && (value <= Phonon::AddonInterface::setChapter))
        return qtscript_AbstractAddon_ChapterCommand_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::availableChapters)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_ChapterCommand_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::ChapterCommand &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_ChapterCommand_toStringHelper(value));
}

static void qtscript_AbstractAddon_ChapterCommand_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::ChapterCommand &out)
{
    out = qvariant_cast<Phonon::AddonInterface::ChapterCommand>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_ChapterCommand(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::availableChapters) && (arg <= Phonon::AddonInterface::setChapter))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::ChapterCommand>(arg));
    return context->throwError(QString::fromLatin1("ChapterCommand(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_ChapterCommand_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::ChapterCommand value = qscriptvalue_cast<Phonon::AddonInterface::ChapterCommand>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_ChapterCommand_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::ChapterCommand value = qscriptvalue_cast<Phonon::AddonInterface::ChapterCommand>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_ChapterCommand_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_ChapterCommand_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_ChapterCommand,
        qtscript_AbstractAddon_ChapterCommand_valueOf, qtscript_AbstractAddon_ChapterCommand_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::ChapterCommand>(engine, qtscript_AbstractAddon_ChapterCommand_toScriptValue,
        qtscript_AbstractAddon_ChapterCommand_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_ChapterCommand_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_ChapterCommand_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::AddonInterface::NavigationCommand
//

static const Phonon::AddonInterface::NavigationCommand qtscript_AbstractAddon_NavigationCommand_values[] = {
    Phonon::AddonInterface::Menu1Button
};

static const char * const qtscript_AbstractAddon_NavigationCommand_keys[] = {
    "Menu1Button"
};

static QString qtscript_AbstractAddon_NavigationCommand_toStringHelper(Phonon::AddonInterface::NavigationCommand value)
{
    if ((value >= Phonon::AddonInterface::Menu1Button) && (value <= Phonon::AddonInterface::Menu1Button))
        return qtscript_AbstractAddon_NavigationCommand_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::Menu1Button)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_NavigationCommand_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::NavigationCommand &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_NavigationCommand_toStringHelper(value));
}

static void qtscript_AbstractAddon_NavigationCommand_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::NavigationCommand &out)
{
    out = qvariant_cast<Phonon::AddonInterface::NavigationCommand>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_NavigationCommand(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::Menu1Button) && (arg <= Phonon::AddonInterface::Menu1Button))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::NavigationCommand>(arg));
    return context->throwError(QString::fromLatin1("NavigationCommand(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_NavigationCommand_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::NavigationCommand value = qscriptvalue_cast<Phonon::AddonInterface::NavigationCommand>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_NavigationCommand_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::NavigationCommand value = qscriptvalue_cast<Phonon::AddonInterface::NavigationCommand>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_NavigationCommand_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_NavigationCommand_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_NavigationCommand,
        qtscript_AbstractAddon_NavigationCommand_valueOf, qtscript_AbstractAddon_NavigationCommand_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::NavigationCommand>(engine, qtscript_AbstractAddon_NavigationCommand_toScriptValue,
        qtscript_AbstractAddon_NavigationCommand_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_NavigationCommand_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_NavigationCommand_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::AddonInterface::AngleCommand
//

static const Phonon::AddonInterface::AngleCommand qtscript_AbstractAddon_AngleCommand_values[] = {
    Phonon::AddonInterface::availableAngles
    , Phonon::AddonInterface::angle
    , Phonon::AddonInterface::setAngle
};

static const char * const qtscript_AbstractAddon_AngleCommand_keys[] = {
    "availableAngles"
    , "angle"
    , "setAngle"
};

static QString qtscript_AbstractAddon_AngleCommand_toStringHelper(Phonon::AddonInterface::AngleCommand value)
{
    if ((value >= Phonon::AddonInterface::availableAngles) && (value <= Phonon::AddonInterface::setAngle))
        return qtscript_AbstractAddon_AngleCommand_keys[static_cast<int>(value)-static_cast<int>(Phonon::AddonInterface::availableAngles)];
    return QString();
}

static QScriptValue qtscript_AbstractAddon_AngleCommand_toScriptValue(QScriptEngine *engine, const Phonon::AddonInterface::AngleCommand &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractAddon"));
    return clazz.property(qtscript_AbstractAddon_AngleCommand_toStringHelper(value));
}

static void qtscript_AbstractAddon_AngleCommand_fromScriptValue(const QScriptValue &value, Phonon::AddonInterface::AngleCommand &out)
{
    out = qvariant_cast<Phonon::AddonInterface::AngleCommand>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractAddon_AngleCommand(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::AddonInterface::availableAngles) && (arg <= Phonon::AddonInterface::setAngle))
        return qScriptValueFromValue(engine,  static_cast<Phonon::AddonInterface::AngleCommand>(arg));
    return context->throwError(QString::fromLatin1("AngleCommand(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractAddon_AngleCommand_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::AngleCommand value = qscriptvalue_cast<Phonon::AddonInterface::AngleCommand>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractAddon_AngleCommand_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::AddonInterface::AngleCommand value = qscriptvalue_cast<Phonon::AddonInterface::AngleCommand>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractAddon_AngleCommand_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractAddon_AngleCommand_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractAddon_AngleCommand,
        qtscript_AbstractAddon_AngleCommand_valueOf, qtscript_AbstractAddon_AngleCommand_toString);
    qScriptRegisterMetaType<Phonon::AddonInterface::AngleCommand>(engine, qtscript_AbstractAddon_AngleCommand_toScriptValue,
        qtscript_AbstractAddon_AngleCommand_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractAddon_AngleCommand_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractAddon_AngleCommand_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// AbstractAddon
//

static QScriptValue qtscript_AbstractAddon_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::AddonInterface* _q_self = qscriptvalue_cast<Phonon::AddonInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractAddon.%0(): this object is not a AbstractAddon")
            .arg(qtscript_AbstractAddon_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        Phonon::AddonInterface::Interface _q_arg0 = qscriptvalue_cast<Phonon::AddonInterface::Interface>(context->argument(0));
        bool _q_result = _q_self->hasInterface(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        Phonon::AddonInterface::Interface _q_arg0 = qscriptvalue_cast<Phonon::AddonInterface::Interface>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QList<QVariant> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QVariant _q_result = _q_self->interfaceCall(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("AbstractAddon");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractAddon_throw_ambiguity_error_helper(context,
        qtscript_AbstractAddon_function_names[_id+1],
        qtscript_AbstractAddon_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractAddon_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AbstractAddon(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AbstractAddon* _q_cpp_result = new QtScriptShell_AbstractAddon();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::AddonInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractAddon_throw_ambiguity_error_helper(context,
        qtscript_AbstractAddon_function_names[_id],
        qtscript_AbstractAddon_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractAddon_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::AddonInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::AddonInterface*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractAddon_prototype_call, qtscript_AbstractAddon_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractAddon_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::AddonInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractAddon_static_call, proto, qtscript_AbstractAddon_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SubtitleCommand"),
        qtscript_create_AbstractAddon_SubtitleCommand_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TitleCommand"),
        qtscript_create_AbstractAddon_TitleCommand_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Interface"),
        qtscript_create_AbstractAddon_Interface_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AudioChannelCommand"),
        qtscript_create_AbstractAddon_AudioChannelCommand_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ChapterCommand"),
        qtscript_create_AbstractAddon_ChapterCommand_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NavigationCommand"),
        qtscript_create_AbstractAddon_NavigationCommand_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AngleCommand"),
        qtscript_create_AbstractAddon_AngleCommand_class(engine, ctor));
    return ctor;
}
