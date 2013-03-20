#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfont.h>
#include <QStringList>
#include <QVariant>
#include <qdatastream.h>
#include <qfont.h>
#include <qpaintdevice.h>
#include <qstringlist.h>

static const char * const qtscript_QFont_function_names[] = {
    "QFont"
    // static
    , "cacheStatistics"
    , "cleanup"
    , "initialize"
    , "insertSubstitution"
    , "insertSubstitutions"
    , "removeSubstitution"
    , "substitute"
    , "substitutes"
    , "substitutions"
    // prototype
    , "bold"
    , "capitalization"
    , "defaultFamily"
    , "exactMatch"
    , "family"
    , "fixedPitch"
    , "fromString"
    , "handle"
    , "isCopyOf"
    , "italic"
    , "kerning"
    , "key"
    , "lastResortFamily"
    , "lastResortFont"
    , "letterSpacing"
    , "letterSpacingType"
    , "equals"
    , "operator_less"
    , "overline"
    , "pixelSize"
    , "pointSize"
    , "pointSizeF"
    , "rawMode"
    , "rawName"
    , "readFrom"
    , "resolve"
    , "setBold"
    , "setCapitalization"
    , "setFamily"
    , "setFixedPitch"
    , "setItalic"
    , "setKerning"
    , "setLetterSpacing"
    , "setOverline"
    , "setPixelSize"
    , "setPointSize"
    , "setPointSizeF"
    , "setRawMode"
    , "setRawName"
    , "setStretch"
    , "setStrikeOut"
    , "setStyle"
    , "setStyleHint"
    , "setStyleName"
    , "setStyleStrategy"
    , "setUnderline"
    , "setWeight"
    , "setWordSpacing"
    , "stretch"
    , "strikeOut"
    , "style"
    , "styleHint"
    , "styleName"
    , "styleStrategy"
    , "toString"
    , "underline"
    , "weight"
    , "wordSpacing"
    , "writeTo"
};

static const char * const qtscript_QFont_function_signatures[] = {
    "\nQFont arg__1\nQFont arg__1, QPaintDevice pd\nString family, int pointSize, int weight, bool italic"
    // static
    , ""
    , ""
    , ""
    , "String arg__1, String arg__2"
    , "String arg__1, List arg__2"
    , "String arg__1"
    , "String arg__1"
    , "String arg__1"
    , ""
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String arg__1"
    , ""
    , "QFont arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QFont arg__1"
    , "QFont arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
    , "\nQFont arg__1\nuint mask"
    , "bool arg__1"
    , "Capitalization arg__1"
    , "String arg__1"
    , "bool arg__1"
    , "bool b"
    , "bool arg__1"
    , "SpacingType type, qreal spacing"
    , "bool arg__1"
    , "int arg__1"
    , "int arg__1"
    , "qreal arg__1"
    , "bool arg__1"
    , "String arg__1"
    , "int arg__1"
    , "bool arg__1"
    , "Style style"
    , "StyleHint arg__1, StyleStrategy arg__2"
    , "String arg__1"
    , "StyleStrategy s"
    , "bool arg__1"
    , "int arg__1"
    , "qreal spacing"
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
    , "QDataStream arg__1"
};

static const int qtscript_QFont_function_lengths[] = {
    4
    // static
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
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
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
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
    , 0
    , 0
    , 0
    , 1
};

static QScriptValue qtscript_QFont_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFont::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QFont_metaObject()
{
    return &QFont::staticMetaObject;
}

Q_DECLARE_METATYPE(QFont*)
Q_DECLARE_METATYPE(QFont::StyleStrategy)
Q_DECLARE_METATYPE(QFont::SpacingType)
Q_DECLARE_METATYPE(QFont::StyleHint)
Q_DECLARE_METATYPE(QFont::Weight)
Q_DECLARE_METATYPE(QFont::Capitalization)
Q_DECLARE_METATYPE(QFont::Stretch)
Q_DECLARE_METATYPE(QFont::Style)
Q_DECLARE_METATYPE(Qt::HANDLE)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QPaintDevice*)

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
// QFont::StyleStrategy
//

static const QFont::StyleStrategy qtscript_QFont_StyleStrategy_values[] = {
    QFont::PreferDefault
    , QFont::PreferBitmap
    , QFont::PreferDevice
    , QFont::PreferOutline
    , QFont::ForceOutline
    , QFont::PreferMatch
    , QFont::PreferQuality
    , QFont::PreferAntialias
    , QFont::NoAntialias
    , QFont::OpenGLCompatible
    , QFont::ForceIntegerMetrics
    , QFont::NoFontMerging
};

static const char * const qtscript_QFont_StyleStrategy_keys[] = {
    "PreferDefault"
    , "PreferBitmap"
    , "PreferDevice"
    , "PreferOutline"
    , "ForceOutline"
    , "PreferMatch"
    , "PreferQuality"
    , "PreferAntialias"
    , "NoAntialias"
    , "OpenGLCompatible"
    , "ForceIntegerMetrics"
    , "NoFontMerging"
};

static QString qtscript_QFont_StyleStrategy_toStringHelper(QFont::StyleStrategy value)
{
    const QMetaObject *meta = qtscript_QFont_metaObject();
    int idx = meta->indexOfEnumerator("StyleStrategy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFont_StyleStrategy_toScriptValue(QScriptEngine *engine, const QFont::StyleStrategy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_StyleStrategy_toStringHelper(value));
}

static void qtscript_QFont_StyleStrategy_fromScriptValue(const QScriptValue &value, QFont::StyleStrategy &out)
{
    out = qvariant_cast<QFont::StyleStrategy>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_StyleStrategy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFont_metaObject();
    int idx = meta->indexOfEnumerator("StyleStrategy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFont::StyleStrategy>(arg));
    return context->throwError(QString::fromLatin1("StyleStrategy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_StyleStrategy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::StyleStrategy value = qscriptvalue_cast<QFont::StyleStrategy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_StyleStrategy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::StyleStrategy value = qscriptvalue_cast<QFont::StyleStrategy>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_StyleStrategy_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_StyleStrategy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_StyleStrategy,
        qtscript_QFont_StyleStrategy_valueOf, qtscript_QFont_StyleStrategy_toString);
    qScriptRegisterMetaType<QFont::StyleStrategy>(engine, qtscript_QFont_StyleStrategy_toScriptValue,
        qtscript_QFont_StyleStrategy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 12; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_StyleStrategy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_StyleStrategy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont::SpacingType
//

static const QFont::SpacingType qtscript_QFont_SpacingType_values[] = {
    QFont::PercentageSpacing
    , QFont::AbsoluteSpacing
};

static const char * const qtscript_QFont_SpacingType_keys[] = {
    "PercentageSpacing"
    , "AbsoluteSpacing"
};

static QString qtscript_QFont_SpacingType_toStringHelper(QFont::SpacingType value)
{
    if ((value >= QFont::PercentageSpacing) && (value <= QFont::AbsoluteSpacing))
        return qtscript_QFont_SpacingType_keys[static_cast<int>(value)-static_cast<int>(QFont::PercentageSpacing)];
    return QString();
}

static QScriptValue qtscript_QFont_SpacingType_toScriptValue(QScriptEngine *engine, const QFont::SpacingType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_SpacingType_toStringHelper(value));
}

static void qtscript_QFont_SpacingType_fromScriptValue(const QScriptValue &value, QFont::SpacingType &out)
{
    out = qvariant_cast<QFont::SpacingType>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_SpacingType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFont::PercentageSpacing) && (arg <= QFont::AbsoluteSpacing))
        return qScriptValueFromValue(engine,  static_cast<QFont::SpacingType>(arg));
    return context->throwError(QString::fromLatin1("SpacingType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_SpacingType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::SpacingType value = qscriptvalue_cast<QFont::SpacingType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_SpacingType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::SpacingType value = qscriptvalue_cast<QFont::SpacingType>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_SpacingType_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_SpacingType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_SpacingType,
        qtscript_QFont_SpacingType_valueOf, qtscript_QFont_SpacingType_toString);
    qScriptRegisterMetaType<QFont::SpacingType>(engine, qtscript_QFont_SpacingType_toScriptValue,
        qtscript_QFont_SpacingType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_SpacingType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_SpacingType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont::StyleHint
//

static const QFont::StyleHint qtscript_QFont_StyleHint_values[] = {
    QFont::Helvetica
    , QFont::Times
    , QFont::Courier
    , QFont::OldEnglish
    , QFont::System
    , QFont::AnyStyle
    , QFont::Cursive
    , QFont::Monospace
    , QFont::Fantasy
};

static const char * const qtscript_QFont_StyleHint_keys[] = {
    "Helvetica"
    , "Times"
    , "Courier"
    , "OldEnglish"
    , "System"
    , "AnyStyle"
    , "Cursive"
    , "Monospace"
    , "Fantasy"
};

static QString qtscript_QFont_StyleHint_toStringHelper(QFont::StyleHint value)
{
    if ((value >= QFont::Helvetica) && (value <= QFont::Fantasy))
        return qtscript_QFont_StyleHint_keys[static_cast<int>(value)-static_cast<int>(QFont::Helvetica)];
    return QString();
}

static QScriptValue qtscript_QFont_StyleHint_toScriptValue(QScriptEngine *engine, const QFont::StyleHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_StyleHint_toStringHelper(value));
}

static void qtscript_QFont_StyleHint_fromScriptValue(const QScriptValue &value, QFont::StyleHint &out)
{
    out = qvariant_cast<QFont::StyleHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_StyleHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFont::Helvetica) && (arg <= QFont::Fantasy))
        return qScriptValueFromValue(engine,  static_cast<QFont::StyleHint>(arg));
    return context->throwError(QString::fromLatin1("StyleHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_StyleHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::StyleHint value = qscriptvalue_cast<QFont::StyleHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_StyleHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::StyleHint value = qscriptvalue_cast<QFont::StyleHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_StyleHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_StyleHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_StyleHint,
        qtscript_QFont_StyleHint_valueOf, qtscript_QFont_StyleHint_toString);
    qScriptRegisterMetaType<QFont::StyleHint>(engine, qtscript_QFont_StyleHint_toScriptValue,
        qtscript_QFont_StyleHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 9; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_StyleHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_StyleHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont::Weight
//

static const QFont::Weight qtscript_QFont_Weight_values[] = {
    QFont::Light
    , QFont::Normal
    , QFont::DemiBold
    , QFont::Bold
    , QFont::Black
};

static const char * const qtscript_QFont_Weight_keys[] = {
    "Light"
    , "Normal"
    , "DemiBold"
    , "Bold"
    , "Black"
};

static QString qtscript_QFont_Weight_toStringHelper(QFont::Weight value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QFont_Weight_values[i] == value)
            return QString::fromLatin1(qtscript_QFont_Weight_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QFont_Weight_toScriptValue(QScriptEngine *engine, const QFont::Weight &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_Weight_toStringHelper(value));
}

static void qtscript_QFont_Weight_fromScriptValue(const QScriptValue &value, QFont::Weight &out)
{
    out = qvariant_cast<QFont::Weight>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_Weight(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QFont_Weight_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QFont::Weight>(arg));
    }
    return context->throwError(QString::fromLatin1("Weight(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_Weight_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Weight value = qscriptvalue_cast<QFont::Weight>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_Weight_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Weight value = qscriptvalue_cast<QFont::Weight>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_Weight_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_Weight_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_Weight,
        qtscript_QFont_Weight_valueOf, qtscript_QFont_Weight_toString);
    qScriptRegisterMetaType<QFont::Weight>(engine, qtscript_QFont_Weight_toScriptValue,
        qtscript_QFont_Weight_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_Weight_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_Weight_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont::Capitalization
//

static const QFont::Capitalization qtscript_QFont_Capitalization_values[] = {
    QFont::MixedCase
    , QFont::AllUppercase
    , QFont::AllLowercase
    , QFont::SmallCaps
    , QFont::Capitalize
};

static const char * const qtscript_QFont_Capitalization_keys[] = {
    "MixedCase"
    , "AllUppercase"
    , "AllLowercase"
    , "SmallCaps"
    , "Capitalize"
};

static QString qtscript_QFont_Capitalization_toStringHelper(QFont::Capitalization value)
{
    if ((value >= QFont::MixedCase) && (value <= QFont::Capitalize))
        return qtscript_QFont_Capitalization_keys[static_cast<int>(value)-static_cast<int>(QFont::MixedCase)];
    return QString();
}

static QScriptValue qtscript_QFont_Capitalization_toScriptValue(QScriptEngine *engine, const QFont::Capitalization &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_Capitalization_toStringHelper(value));
}

static void qtscript_QFont_Capitalization_fromScriptValue(const QScriptValue &value, QFont::Capitalization &out)
{
    out = qvariant_cast<QFont::Capitalization>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_Capitalization(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFont::MixedCase) && (arg <= QFont::Capitalize))
        return qScriptValueFromValue(engine,  static_cast<QFont::Capitalization>(arg));
    return context->throwError(QString::fromLatin1("Capitalization(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_Capitalization_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Capitalization value = qscriptvalue_cast<QFont::Capitalization>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_Capitalization_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Capitalization value = qscriptvalue_cast<QFont::Capitalization>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_Capitalization_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_Capitalization_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_Capitalization,
        qtscript_QFont_Capitalization_valueOf, qtscript_QFont_Capitalization_toString);
    qScriptRegisterMetaType<QFont::Capitalization>(engine, qtscript_QFont_Capitalization_toScriptValue,
        qtscript_QFont_Capitalization_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_Capitalization_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_Capitalization_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont::Stretch
//

static const QFont::Stretch qtscript_QFont_Stretch_values[] = {
    QFont::UltraCondensed
    , QFont::ExtraCondensed
    , QFont::Condensed
    , QFont::SemiCondensed
    , QFont::Unstretched
    , QFont::SemiExpanded
    , QFont::Expanded
    , QFont::ExtraExpanded
    , QFont::UltraExpanded
};

static const char * const qtscript_QFont_Stretch_keys[] = {
    "UltraCondensed"
    , "ExtraCondensed"
    , "Condensed"
    , "SemiCondensed"
    , "Unstretched"
    , "SemiExpanded"
    , "Expanded"
    , "ExtraExpanded"
    , "UltraExpanded"
};

static QString qtscript_QFont_Stretch_toStringHelper(QFont::Stretch value)
{
    for (int i = 0; i < 9; ++i) {
        if (qtscript_QFont_Stretch_values[i] == value)
            return QString::fromLatin1(qtscript_QFont_Stretch_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QFont_Stretch_toScriptValue(QScriptEngine *engine, const QFont::Stretch &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_Stretch_toStringHelper(value));
}

static void qtscript_QFont_Stretch_fromScriptValue(const QScriptValue &value, QFont::Stretch &out)
{
    out = qvariant_cast<QFont::Stretch>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_Stretch(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 9; ++i) {
        if (qtscript_QFont_Stretch_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QFont::Stretch>(arg));
    }
    return context->throwError(QString::fromLatin1("Stretch(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_Stretch_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Stretch value = qscriptvalue_cast<QFont::Stretch>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_Stretch_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Stretch value = qscriptvalue_cast<QFont::Stretch>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_Stretch_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_Stretch_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_Stretch,
        qtscript_QFont_Stretch_valueOf, qtscript_QFont_Stretch_toString);
    qScriptRegisterMetaType<QFont::Stretch>(engine, qtscript_QFont_Stretch_toScriptValue,
        qtscript_QFont_Stretch_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 9; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_Stretch_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_Stretch_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont::Style
//

static const QFont::Style qtscript_QFont_Style_values[] = {
    QFont::StyleNormal
    , QFont::StyleItalic
    , QFont::StyleOblique
};

static const char * const qtscript_QFont_Style_keys[] = {
    "StyleNormal"
    , "StyleItalic"
    , "StyleOblique"
};

static QString qtscript_QFont_Style_toStringHelper(QFont::Style value)
{
    if ((value >= QFont::StyleNormal) && (value <= QFont::StyleOblique))
        return qtscript_QFont_Style_keys[static_cast<int>(value)-static_cast<int>(QFont::StyleNormal)];
    return QString();
}

static QScriptValue qtscript_QFont_Style_toScriptValue(QScriptEngine *engine, const QFont::Style &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFont"));
    return clazz.property(qtscript_QFont_Style_toStringHelper(value));
}

static void qtscript_QFont_Style_fromScriptValue(const QScriptValue &value, QFont::Style &out)
{
    out = qvariant_cast<QFont::Style>(value.toVariant());
}

static QScriptValue qtscript_construct_QFont_Style(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFont::StyleNormal) && (arg <= QFont::StyleOblique))
        return qScriptValueFromValue(engine,  static_cast<QFont::Style>(arg));
    return context->throwError(QString::fromLatin1("Style(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFont_Style_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Style value = qscriptvalue_cast<QFont::Style>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFont_Style_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFont::Style value = qscriptvalue_cast<QFont::Style>(context->thisObject());
    return QScriptValue(engine, qtscript_QFont_Style_toStringHelper(value));
}

static QScriptValue qtscript_create_QFont_Style_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFont_Style,
        qtscript_QFont_Style_valueOf, qtscript_QFont_Style_toString);
    qScriptRegisterMetaType<QFont::Style>(engine, qtscript_QFont_Style_toScriptValue,
        qtscript_QFont_Style_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFont_Style_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFont_Style_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFont
//

static QScriptValue qtscript_QFont_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 59;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFont* _q_self = qscriptvalue_cast<QFont*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFont.%0(): this object is not a QFont")
            .arg(qtscript_QFont_function_names[_id+10]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->bold();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFont::Capitalization _q_result = _q_self->capitalization();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->defaultFamily();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exactMatch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->family();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fixedPitch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->fromString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Qt::HANDLE _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        bool _q_result = _q_self->isCopyOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->italic();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->kerning();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->key();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->lastResortFamily();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->lastResortFont();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->letterSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QFont::SpacingType _q_result = _q_self->letterSpacingType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->overline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pixelSize();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pointSize();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->pointSizeF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->rawMode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->rawName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->resolve();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFont>() == context->argument(0).toVariant().userType())) {
            QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
            QFont _q_result = _q_self->resolve(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            _q_self->resolve(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setBold(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QFont::Capitalization _q_arg0 = qscriptvalue_cast<QFont::Capitalization>(context->argument(0));
        _q_self->setCapitalization(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFamily(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFixedPitch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setItalic(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setKerning(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 2) {
        QFont::SpacingType _q_arg0 = qscriptvalue_cast<QFont::SpacingType>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setLetterSpacing(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setOverline(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPixelSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPointSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPointSizeF(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setRawMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setRawName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setStretch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setStrikeOut(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QFont::Style _q_arg0 = qscriptvalue_cast<QFont::Style>(context->argument(0));
        _q_self->setStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QFont::StyleHint _q_arg0 = qscriptvalue_cast<QFont::StyleHint>(context->argument(0));
        _q_self->setStyleHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QFont::StyleHint _q_arg0 = qscriptvalue_cast<QFont::StyleHint>(context->argument(0));
        QFont::StyleStrategy _q_arg1 = qscriptvalue_cast<QFont::StyleStrategy>(context->argument(1));
        _q_self->setStyleHint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setStyleName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QFont::StyleStrategy _q_arg0 = qscriptvalue_cast<QFont::StyleStrategy>(context->argument(0));
        _q_self->setStyleStrategy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setUnderline(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setWeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWordSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->stretch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->strikeOut();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        QFont::Style _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        QFont::StyleHint _q_result = _q_self->styleHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->styleName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 0) {
        QFont::StyleStrategy _q_result = _q_self->styleStrategy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->underline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 56:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->weight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 57:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->wordSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 58:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFont_throw_ambiguity_error_helper(context,
        qtscript_QFont_function_names[_id+10],
        qtscript_QFont_function_signatures[_id+10]);
}

static QScriptValue qtscript_QFont_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFont(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QFont _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFont>() == context->argument(0).toVariant().userType())) {
            QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
            QFont _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QFont _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QFont>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QPaintDevice*>(context->argument(1))) {
            QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
            QPaintDevice* _q_arg1 = qscriptvalue_cast<QPaintDevice*>(context->argument(1));
            QFont _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            QFont _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QFont _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_arg3 = context->argument(3).toBoolean();
        QFont _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFont::cacheStatistics();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QFont::cleanup();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFont::initialize();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QFont::insertSubstitution(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        QFont::insertSubstitutions(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QFont::removeSubstitution(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QFont::substitute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = QFont::substitutes(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QFont::substitutions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFont_throw_ambiguity_error_helper(context,
        qtscript_QFont_function_names[_id],
        qtscript_QFont_function_signatures[_id]);
}

QScriptValue qtscript_create_QFont_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFont*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFont*)0));
    for (int i = 0; i < 59; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFont_prototype_call, qtscript_QFont_function_lengths[i+10]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFont_function_names[i+10]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QFont>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QFont*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFont_static_call, proto, qtscript_QFont_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFont_static_call,
            qtscript_QFont_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QFont_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("StyleStrategy"),
        qtscript_create_QFont_StyleStrategy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SpacingType"),
        qtscript_create_QFont_SpacingType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleHint"),
        qtscript_create_QFont_StyleHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Weight"),
        qtscript_create_QFont_Weight_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Capitalization"),
        qtscript_create_QFont_Capitalization_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Stretch"),
        qtscript_create_QFont_Stretch_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Style"),
        qtscript_create_QFont_Style_class(engine, ctor));
    return ctor;
}
