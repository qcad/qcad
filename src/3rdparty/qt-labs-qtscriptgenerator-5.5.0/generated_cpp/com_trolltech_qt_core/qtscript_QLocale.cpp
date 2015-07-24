#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlocale.h>
#include <QDate>
#include <QVariant>
#include <qdatetime.h>
#include <qlist.h>
#include <qlocale.h>
#include <qstringlist.h>

static const char * const qtscript_QLocale_function_names[] = {
    "QLocale"
    // static
    , "c"
    , "countriesForLanguage"
    , "countryToString"
    , "languageToString"
    , "matchingLocales"
    , "scriptToString"
    , "setDefault"
    , "system"
    // prototype
    , "amText"
    , "bcp47Name"
    , "country"
    , "createSeparatedList"
    , "currencySymbol"
    , "dateFormat"
    , "dateTimeFormat"
    , "dayName"
    , "decimalPoint"
    , "exponential"
    , "firstDayOfWeek"
    , "groupSeparator"
    , "language"
    , "measurementSystem"
    , "monthName"
    , "name"
    , "nativeCountryName"
    , "nativeLanguageName"
    , "negativeSign"
    , "numberOptions"
    , "equals"
    , "percent"
    , "pmText"
    , "positiveSign"
    , "quoteString"
    , "script"
    , "setNumberOptions"
    , "standaloneDayName"
    , "standaloneMonthName"
    , "textDirection"
    , "timeFormat"
    , "toCurrencyString"
    , "toDate"
    , "toDateTime"
    , "toDouble"
    , "toFloat"
    , "toInt"
    , "toLongLong"
    , "toLower"
    , "toShort"
    , "toString"
    , "toTime"
    , "toUInt"
    , "toULongLong"
    , "toUShort"
    , "toUpper"
    , "uiLanguages"
    , "weekdays"
    , "zeroDigit"
};

static const char * const qtscript_QLocale_function_signatures[] = {
    "\nLanguage language, Country country\nLanguage language, Script script, Country country\nQLocale other\nString name"
    // static
    , ""
    , "Language lang"
    , "Country country"
    , "Language language"
    , "Language language, Script script, Country country"
    , "Script script"
    , "QLocale locale"
    , ""
    // prototype
    , ""
    , ""
    , ""
    , "List strl"
    , "CurrencySymbolFormat arg__1"
    , "FormatType format"
    , "FormatType format"
    , "int arg__1, FormatType format"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int arg__1, FormatType format"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QLocale other"
    , ""
    , ""
    , ""
    , "String str, QuotationStyle style\nString str, QuotationStyle style"
    , ""
    , "NumberOptions options"
    , "int arg__1, FormatType format"
    , "int arg__1, FormatType format"
    , ""
    , "FormatType format"
    , "double arg__1, String symbol\nfloat arg__1, String symbol\nint arg__1, String symbol\nqlonglong arg__1, String symbol\nqulonglong arg__1, String symbol\nshort arg__1, String symbol\nuint arg__1, String symbol\nushort arg__1, String symbol"
    , "String string, FormatType arg__2\nString string, String format"
    , "String string, FormatType format\nString string, String format"
    , "String s\nString s, bool ok"
    , "String s\nString s, bool ok"
    , "String s, bool ok\nString s, bool ok"
    , "String s, bool ok\nString s, bool ok"
    , "String str"
    , "String s, bool ok\nString s, bool ok"
    , "QDate date, FormatType format\nQDate date, String formatStr\nQDateTime dateTime, FormatType format\nQDateTime dateTime, String format\nQTime time, FormatType format\nQTime time, String formatStr\ndouble i, char f, int prec\nfloat i, char f, int prec\nint i\nqulonglong i\nshort i"
    , "String string, FormatType arg__2\nString string, String format"
    , "String s, bool ok\nString s, bool ok"
    , "String s, bool ok\nString s, bool ok"
    , "String s, bool ok\nString s, bool ok"
    , "String str"
    , ""
    , ""
    , ""
};

static const int qtscript_QLocale_function_lengths[] = {
    3
    // static
    , 0
    , 1
    , 1
    , 1
    , 3
    , 1
    , 1
    , 0
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 2
    , 2
    , 0
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 2
    , 3
    , 2
    , 2
    , 2
    , 2
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QLocale_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLocale::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QLocale_metaObject()
{
    return &QLocale::staticMetaObject;
}

Q_DECLARE_METATYPE(QLocale*)
Q_DECLARE_METATYPE(QLocale::Script)
Q_DECLARE_METATYPE(QLocale::CurrencySymbolFormat)
Q_DECLARE_METATYPE(QLocale::QuotationStyle)
Q_DECLARE_METATYPE(QLocale::MeasurementSystem)
Q_DECLARE_METATYPE(QLocale::FormatType)
Q_DECLARE_METATYPE(QLocale::Language)
Q_DECLARE_METATYPE(QLocale::NumberOption)
Q_DECLARE_METATYPE(QFlags<QLocale::NumberOption>)
Q_DECLARE_METATYPE(QLocale::Country)
Q_DECLARE_METATYPE(Qt::DayOfWeek)
Q_DECLARE_METATYPE(QStringRef)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QList<Qt::DayOfWeek >)
Q_DECLARE_METATYPE(QList<QLocale::Country >)
Q_DECLARE_METATYPE(QList<QLocale >)


    Q_DECLARE_METATYPE(QScriptValue)
    
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
// QLocale::Script
//

static const QLocale::Script qtscript_QLocale_Script_values[] = {
    QLocale::AnyScript
    , QLocale::ArabicScript
    , QLocale::CyrillicScript
    , QLocale::DeseretScript
    , QLocale::GurmukhiScript
    , QLocale::SimplifiedHanScript
    , QLocale::TraditionalHanScript
    , QLocale::LatinScript
    , QLocale::MongolianScript
    , QLocale::TifinaghScript
    , QLocale::ArmenianScript
    , QLocale::BengaliScript
    , QLocale::CherokeeScript
    , QLocale::DevanagariScript
    , QLocale::EthiopicScript
    , QLocale::GeorgianScript
    , QLocale::GreekScript
    , QLocale::GujaratiScript
    , QLocale::HebrewScript
    , QLocale::JapaneseScript
    , QLocale::KhmerScript
    , QLocale::KannadaScript
    , QLocale::KoreanScript
    , QLocale::LaoScript
    , QLocale::MalayalamScript
    , QLocale::MyanmarScript
    , QLocale::OriyaScript
    , QLocale::TamilScript
    , QLocale::TeluguScript
    , QLocale::ThaanaScript
    , QLocale::ThaiScript
    , QLocale::TibetanScript
    , QLocale::SinhalaScript
    , QLocale::SyriacScript
    , QLocale::YiScript
    , QLocale::VaiScript
    , QLocale::AvestanScript
    , QLocale::BalineseScript
    , QLocale::BamumScript
    , QLocale::BatakScript
    , QLocale::BopomofoScript
    , QLocale::BrahmiScript
    , QLocale::BugineseScript
    , QLocale::BuhidScript
    , QLocale::CanadianAboriginalScript
    , QLocale::CarianScript
    , QLocale::ChakmaScript
    , QLocale::ChamScript
    , QLocale::CopticScript
    , QLocale::CypriotScript
    , QLocale::EgyptianHieroglyphsScript
    , QLocale::FraserScript
    , QLocale::GlagoliticScript
    , QLocale::GothicScript
    , QLocale::HanScript
    , QLocale::HangulScript
    , QLocale::HanunooScript
    , QLocale::ImperialAramaicScript
    , QLocale::InscriptionalPahlaviScript
    , QLocale::InscriptionalParthianScript
    , QLocale::JavaneseScript
    , QLocale::KaithiScript
    , QLocale::KatakanaScript
    , QLocale::KayahLiScript
    , QLocale::KharoshthiScript
    , QLocale::LannaScript
    , QLocale::LepchaScript
    , QLocale::LimbuScript
    , QLocale::LinearBScript
    , QLocale::LycianScript
    , QLocale::LydianScript
    , QLocale::MandaeanScript
    , QLocale::MeiteiMayekScript
    , QLocale::MeroiticScript
    , QLocale::MeroiticCursiveScript
    , QLocale::NkoScript
    , QLocale::NewTaiLueScript
    , QLocale::OghamScript
    , QLocale::OlChikiScript
    , QLocale::OldItalicScript
    , QLocale::OldPersianScript
    , QLocale::OldSouthArabianScript
    , QLocale::OrkhonScript
    , QLocale::OsmanyaScript
    , QLocale::PhagsPaScript
    , QLocale::PhoenicianScript
    , QLocale::PollardPhoneticScript
    , QLocale::RejangScript
    , QLocale::RunicScript
    , QLocale::SamaritanScript
    , QLocale::SaurashtraScript
    , QLocale::SharadaScript
    , QLocale::ShavianScript
    , QLocale::SoraSompengScript
    , QLocale::CuneiformScript
    , QLocale::SundaneseScript
    , QLocale::SylotiNagriScript
    , QLocale::TagalogScript
    , QLocale::TagbanwaScript
    , QLocale::TaiLeScript
    , QLocale::TaiVietScript
    , QLocale::TakriScript
    , QLocale::UgariticScript
    , QLocale::BrailleScript
    , QLocale::HiraganaScript
};

static const char * const qtscript_QLocale_Script_keys[] = {
    "AnyScript"
    , "ArabicScript"
    , "CyrillicScript"
    , "DeseretScript"
    , "GurmukhiScript"
    , "SimplifiedHanScript"
    , "TraditionalHanScript"
    , "LatinScript"
    , "MongolianScript"
    , "TifinaghScript"
    , "ArmenianScript"
    , "BengaliScript"
    , "CherokeeScript"
    , "DevanagariScript"
    , "EthiopicScript"
    , "GeorgianScript"
    , "GreekScript"
    , "GujaratiScript"
    , "HebrewScript"
    , "JapaneseScript"
    , "KhmerScript"
    , "KannadaScript"
    , "KoreanScript"
    , "LaoScript"
    , "MalayalamScript"
    , "MyanmarScript"
    , "OriyaScript"
    , "TamilScript"
    , "TeluguScript"
    , "ThaanaScript"
    , "ThaiScript"
    , "TibetanScript"
    , "SinhalaScript"
    , "SyriacScript"
    , "YiScript"
    , "VaiScript"
    , "AvestanScript"
    , "BalineseScript"
    , "BamumScript"
    , "BatakScript"
    , "BopomofoScript"
    , "BrahmiScript"
    , "BugineseScript"
    , "BuhidScript"
    , "CanadianAboriginalScript"
    , "CarianScript"
    , "ChakmaScript"
    , "ChamScript"
    , "CopticScript"
    , "CypriotScript"
    , "EgyptianHieroglyphsScript"
    , "FraserScript"
    , "GlagoliticScript"
    , "GothicScript"
    , "HanScript"
    , "HangulScript"
    , "HanunooScript"
    , "ImperialAramaicScript"
    , "InscriptionalPahlaviScript"
    , "InscriptionalParthianScript"
    , "JavaneseScript"
    , "KaithiScript"
    , "KatakanaScript"
    , "KayahLiScript"
    , "KharoshthiScript"
    , "LannaScript"
    , "LepchaScript"
    , "LimbuScript"
    , "LinearBScript"
    , "LycianScript"
    , "LydianScript"
    , "MandaeanScript"
    , "MeiteiMayekScript"
    , "MeroiticScript"
    , "MeroiticCursiveScript"
    , "NkoScript"
    , "NewTaiLueScript"
    , "OghamScript"
    , "OlChikiScript"
    , "OldItalicScript"
    , "OldPersianScript"
    , "OldSouthArabianScript"
    , "OrkhonScript"
    , "OsmanyaScript"
    , "PhagsPaScript"
    , "PhoenicianScript"
    , "PollardPhoneticScript"
    , "RejangScript"
    , "RunicScript"
    , "SamaritanScript"
    , "SaurashtraScript"
    , "SharadaScript"
    , "ShavianScript"
    , "SoraSompengScript"
    , "CuneiformScript"
    , "SundaneseScript"
    , "SylotiNagriScript"
    , "TagalogScript"
    , "TagbanwaScript"
    , "TaiLeScript"
    , "TaiVietScript"
    , "TakriScript"
    , "UgariticScript"
    , "BrailleScript"
    , "HiraganaScript"
};

static QString qtscript_QLocale_Script_toStringHelper(QLocale::Script value)
{
    if ((value >= QLocale::AnyScript) && (value <= QLocale::HiraganaScript))
        return qtscript_QLocale_Script_keys[static_cast<int>(value)-static_cast<int>(QLocale::AnyScript)];
    return QString();
}

static QScriptValue qtscript_QLocale_Script_toScriptValue(QScriptEngine *engine, const QLocale::Script &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_Script_toStringHelper(value));
}

static void qtscript_QLocale_Script_fromScriptValue(const QScriptValue &value, QLocale::Script &out)
{
    out = qvariant_cast<QLocale::Script>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_Script(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QLocale::AnyScript) && (arg <= QLocale::HiraganaScript))
        return qScriptValueFromValue(engine,  static_cast<QLocale::Script>(arg));
    return context->throwError(QString::fromLatin1("Script(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_Script_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::Script value = qscriptvalue_cast<QLocale::Script>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_Script_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::Script value = qscriptvalue_cast<QLocale::Script>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_Script_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_Script_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_Script,
        qtscript_QLocale_Script_valueOf, qtscript_QLocale_Script_toString);
    qScriptRegisterMetaType<QLocale::Script>(engine, qtscript_QLocale_Script_toScriptValue,
        qtscript_QLocale_Script_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 105; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_Script_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_Script_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::CurrencySymbolFormat
//

static const QLocale::CurrencySymbolFormat qtscript_QLocale_CurrencySymbolFormat_values[] = {
    QLocale::CurrencyIsoCode
    , QLocale::CurrencySymbol
    , QLocale::CurrencyDisplayName
};

static const char * const qtscript_QLocale_CurrencySymbolFormat_keys[] = {
    "CurrencyIsoCode"
    , "CurrencySymbol"
    , "CurrencyDisplayName"
};

static QString qtscript_QLocale_CurrencySymbolFormat_toStringHelper(QLocale::CurrencySymbolFormat value)
{
    if ((value >= QLocale::CurrencyIsoCode) && (value <= QLocale::CurrencyDisplayName))
        return qtscript_QLocale_CurrencySymbolFormat_keys[static_cast<int>(value)-static_cast<int>(QLocale::CurrencyIsoCode)];
    return QString();
}

static QScriptValue qtscript_QLocale_CurrencySymbolFormat_toScriptValue(QScriptEngine *engine, const QLocale::CurrencySymbolFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_CurrencySymbolFormat_toStringHelper(value));
}

static void qtscript_QLocale_CurrencySymbolFormat_fromScriptValue(const QScriptValue &value, QLocale::CurrencySymbolFormat &out)
{
    out = qvariant_cast<QLocale::CurrencySymbolFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_CurrencySymbolFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QLocale::CurrencyIsoCode) && (arg <= QLocale::CurrencyDisplayName))
        return qScriptValueFromValue(engine,  static_cast<QLocale::CurrencySymbolFormat>(arg));
    return context->throwError(QString::fromLatin1("CurrencySymbolFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_CurrencySymbolFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::CurrencySymbolFormat value = qscriptvalue_cast<QLocale::CurrencySymbolFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_CurrencySymbolFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::CurrencySymbolFormat value = qscriptvalue_cast<QLocale::CurrencySymbolFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_CurrencySymbolFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_CurrencySymbolFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_CurrencySymbolFormat,
        qtscript_QLocale_CurrencySymbolFormat_valueOf, qtscript_QLocale_CurrencySymbolFormat_toString);
    qScriptRegisterMetaType<QLocale::CurrencySymbolFormat>(engine, qtscript_QLocale_CurrencySymbolFormat_toScriptValue,
        qtscript_QLocale_CurrencySymbolFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_CurrencySymbolFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_CurrencySymbolFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::QuotationStyle
//

static const QLocale::QuotationStyle qtscript_QLocale_QuotationStyle_values[] = {
    QLocale::StandardQuotation
    , QLocale::AlternateQuotation
};

static const char * const qtscript_QLocale_QuotationStyle_keys[] = {
    "StandardQuotation"
    , "AlternateQuotation"
};

static QString qtscript_QLocale_QuotationStyle_toStringHelper(QLocale::QuotationStyle value)
{
    if ((value >= QLocale::StandardQuotation) && (value <= QLocale::AlternateQuotation))
        return qtscript_QLocale_QuotationStyle_keys[static_cast<int>(value)-static_cast<int>(QLocale::StandardQuotation)];
    return QString();
}

static QScriptValue qtscript_QLocale_QuotationStyle_toScriptValue(QScriptEngine *engine, const QLocale::QuotationStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_QuotationStyle_toStringHelper(value));
}

static void qtscript_QLocale_QuotationStyle_fromScriptValue(const QScriptValue &value, QLocale::QuotationStyle &out)
{
    out = qvariant_cast<QLocale::QuotationStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_QuotationStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QLocale::StandardQuotation) && (arg <= QLocale::AlternateQuotation))
        return qScriptValueFromValue(engine,  static_cast<QLocale::QuotationStyle>(arg));
    return context->throwError(QString::fromLatin1("QuotationStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_QuotationStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::QuotationStyle value = qscriptvalue_cast<QLocale::QuotationStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_QuotationStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::QuotationStyle value = qscriptvalue_cast<QLocale::QuotationStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_QuotationStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_QuotationStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_QuotationStyle,
        qtscript_QLocale_QuotationStyle_valueOf, qtscript_QLocale_QuotationStyle_toString);
    qScriptRegisterMetaType<QLocale::QuotationStyle>(engine, qtscript_QLocale_QuotationStyle_toScriptValue,
        qtscript_QLocale_QuotationStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_QuotationStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_QuotationStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::MeasurementSystem
//

static const QLocale::MeasurementSystem qtscript_QLocale_MeasurementSystem_values[] = {
    QLocale::MetricSystem
    , QLocale::ImperialUSSystem
    , QLocale::ImperialUKSystem
};

static const char * const qtscript_QLocale_MeasurementSystem_keys[] = {
    "MetricSystem"
    , "ImperialUSSystem"
    , "ImperialUKSystem"
};

static QString qtscript_QLocale_MeasurementSystem_toStringHelper(QLocale::MeasurementSystem value)
{
    const QMetaObject *meta = qtscript_QLocale_metaObject();
    int idx = meta->indexOfEnumerator("MeasurementSystem");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLocale_MeasurementSystem_toScriptValue(QScriptEngine *engine, const QLocale::MeasurementSystem &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_MeasurementSystem_toStringHelper(value));
}

static void qtscript_QLocale_MeasurementSystem_fromScriptValue(const QScriptValue &value, QLocale::MeasurementSystem &out)
{
    out = qvariant_cast<QLocale::MeasurementSystem>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_MeasurementSystem(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLocale_metaObject();
    int idx = meta->indexOfEnumerator("MeasurementSystem");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLocale::MeasurementSystem>(arg));
    return context->throwError(QString::fromLatin1("MeasurementSystem(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_MeasurementSystem_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::MeasurementSystem value = qscriptvalue_cast<QLocale::MeasurementSystem>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_MeasurementSystem_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::MeasurementSystem value = qscriptvalue_cast<QLocale::MeasurementSystem>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_MeasurementSystem_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_MeasurementSystem_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_MeasurementSystem,
        qtscript_QLocale_MeasurementSystem_valueOf, qtscript_QLocale_MeasurementSystem_toString);
    qScriptRegisterMetaType<QLocale::MeasurementSystem>(engine, qtscript_QLocale_MeasurementSystem_toScriptValue,
        qtscript_QLocale_MeasurementSystem_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_MeasurementSystem_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_MeasurementSystem_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::FormatType
//

static const QLocale::FormatType qtscript_QLocale_FormatType_values[] = {
    QLocale::LongFormat
    , QLocale::ShortFormat
    , QLocale::NarrowFormat
};

static const char * const qtscript_QLocale_FormatType_keys[] = {
    "LongFormat"
    , "ShortFormat"
    , "NarrowFormat"
};

static QString qtscript_QLocale_FormatType_toStringHelper(QLocale::FormatType value)
{
    if ((value >= QLocale::LongFormat) && (value <= QLocale::NarrowFormat))
        return qtscript_QLocale_FormatType_keys[static_cast<int>(value)-static_cast<int>(QLocale::LongFormat)];
    return QString();
}

static QScriptValue qtscript_QLocale_FormatType_toScriptValue(QScriptEngine *engine, const QLocale::FormatType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_FormatType_toStringHelper(value));
}

static void qtscript_QLocale_FormatType_fromScriptValue(const QScriptValue &value, QLocale::FormatType &out)
{
    out = qvariant_cast<QLocale::FormatType>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_FormatType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QLocale::LongFormat) && (arg <= QLocale::NarrowFormat))
        return qScriptValueFromValue(engine,  static_cast<QLocale::FormatType>(arg));
    return context->throwError(QString::fromLatin1("FormatType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_FormatType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::FormatType value = qscriptvalue_cast<QLocale::FormatType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_FormatType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::FormatType value = qscriptvalue_cast<QLocale::FormatType>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_FormatType_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_FormatType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_FormatType,
        qtscript_QLocale_FormatType_valueOf, qtscript_QLocale_FormatType_toString);
    qScriptRegisterMetaType<QLocale::FormatType>(engine, qtscript_QLocale_FormatType_toScriptValue,
        qtscript_QLocale_FormatType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_FormatType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_FormatType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::Language
//

static const QLocale::Language qtscript_QLocale_Language_values[] = {
    QLocale::AnyLanguage
    , QLocale::C
    , QLocale::Abkhazian
    , QLocale::Oromo
    , QLocale::Afar
    , QLocale::Afrikaans
    , QLocale::Albanian
    , QLocale::Amharic
    , QLocale::Arabic
    , QLocale::Armenian
    , QLocale::Assamese
    , QLocale::Aymara
    , QLocale::Azerbaijani
    , QLocale::Bashkir
    , QLocale::Basque
    , QLocale::Bengali
    , QLocale::Dzongkha
    , QLocale::Bihari
    , QLocale::Bislama
    , QLocale::Breton
    , QLocale::Bulgarian
    , QLocale::Burmese
    , QLocale::Belarusian
    , QLocale::Khmer
    , QLocale::Catalan
    , QLocale::Chinese
    , QLocale::Corsican
    , QLocale::Croatian
    , QLocale::Czech
    , QLocale::Danish
    , QLocale::Dutch
    , QLocale::English
    , QLocale::Esperanto
    , QLocale::Estonian
    , QLocale::Faroese
    , QLocale::Fijian
    , QLocale::Finnish
    , QLocale::French
    , QLocale::WesternFrisian
    , QLocale::Gaelic
    , QLocale::Galician
    , QLocale::Georgian
    , QLocale::German
    , QLocale::Greek
    , QLocale::Greenlandic
    , QLocale::Guarani
    , QLocale::Gujarati
    , QLocale::Hausa
    , QLocale::Hebrew
    , QLocale::Hindi
    , QLocale::Hungarian
    , QLocale::Icelandic
    , QLocale::Indonesian
    , QLocale::Interlingua
    , QLocale::Interlingue
    , QLocale::Inuktitut
    , QLocale::Inupiak
    , QLocale::Irish
    , QLocale::Italian
    , QLocale::Japanese
    , QLocale::Javanese
    , QLocale::Kannada
    , QLocale::Kashmiri
    , QLocale::Kazakh
    , QLocale::Kinyarwanda
    , QLocale::Kirghiz
    , QLocale::Korean
    , QLocale::Kurdish
    , QLocale::Rundi
    , QLocale::Lao
    , QLocale::Latin
    , QLocale::Latvian
    , QLocale::Lingala
    , QLocale::Lithuanian
    , QLocale::Macedonian
    , QLocale::Malagasy
    , QLocale::Malay
    , QLocale::Malayalam
    , QLocale::Maltese
    , QLocale::Maori
    , QLocale::Marathi
    , QLocale::Marshallese
    , QLocale::Mongolian
    , QLocale::NauruLanguage
    , QLocale::Nepali
    , QLocale::NorwegianBokmal
    , QLocale::Occitan
    , QLocale::Oriya
    , QLocale::Pashto
    , QLocale::Persian
    , QLocale::Polish
    , QLocale::Portuguese
    , QLocale::Punjabi
    , QLocale::Quechua
    , QLocale::Romansh
    , QLocale::Romanian
    , QLocale::Russian
    , QLocale::Samoan
    , QLocale::Sango
    , QLocale::Sanskrit
    , QLocale::Serbian
    , QLocale::Ossetic
    , QLocale::SouthernSotho
    , QLocale::Tswana
    , QLocale::Shona
    , QLocale::Sindhi
    , QLocale::Sinhala
    , QLocale::Swati
    , QLocale::Slovak
    , QLocale::Slovenian
    , QLocale::Somali
    , QLocale::Spanish
    , QLocale::Sundanese
    , QLocale::Swahili
    , QLocale::Swedish
    , QLocale::Sardinian
    , QLocale::Tajik
    , QLocale::Tamil
    , QLocale::Tatar
    , QLocale::Telugu
    , QLocale::Thai
    , QLocale::Tibetan
    , QLocale::Tigrinya
    , QLocale::Tongan
    , QLocale::Tsonga
    , QLocale::Turkish
    , QLocale::Turkmen
    , QLocale::Tahitian
    , QLocale::Uighur
    , QLocale::Ukrainian
    , QLocale::Urdu
    , QLocale::Uzbek
    , QLocale::Vietnamese
    , QLocale::Volapuk
    , QLocale::Welsh
    , QLocale::Wolof
    , QLocale::Xhosa
    , QLocale::Yiddish
    , QLocale::Yoruba
    , QLocale::Zhuang
    , QLocale::Zulu
    , QLocale::NorwegianNynorsk
    , QLocale::Bosnian
    , QLocale::Divehi
    , QLocale::Manx
    , QLocale::Cornish
    , QLocale::Akan
    , QLocale::Konkani
    , QLocale::Ga
    , QLocale::Igbo
    , QLocale::Kamba
    , QLocale::Syriac
    , QLocale::Blin
    , QLocale::Geez
    , QLocale::Koro
    , QLocale::Sidamo
    , QLocale::Atsam
    , QLocale::Tigre
    , QLocale::Jju
    , QLocale::Friulian
    , QLocale::Venda
    , QLocale::Ewe
    , QLocale::Walamo
    , QLocale::Hawaiian
    , QLocale::Tyap
    , QLocale::Nyanja
    , QLocale::Filipino
    , QLocale::SwissGerman
    , QLocale::SichuanYi
    , QLocale::Kpelle
    , QLocale::LowGerman
    , QLocale::SouthNdebele
    , QLocale::NorthernSotho
    , QLocale::NorthernSami
    , QLocale::Taroko
    , QLocale::Gusii
    , QLocale::Taita
    , QLocale::Fulah
    , QLocale::Kikuyu
    , QLocale::Samburu
    , QLocale::Sena
    , QLocale::NorthNdebele
    , QLocale::Rombo
    , QLocale::Tachelhit
    , QLocale::Kabyle
    , QLocale::Nyankole
    , QLocale::Bena
    , QLocale::Vunjo
    , QLocale::Bambara
    , QLocale::Embu
    , QLocale::Cherokee
    , QLocale::Morisyen
    , QLocale::Makonde
    , QLocale::Langi
    , QLocale::Ganda
    , QLocale::Bemba
    , QLocale::Kabuverdianu
    , QLocale::Meru
    , QLocale::Kalenjin
    , QLocale::Nama
    , QLocale::Machame
    , QLocale::Colognian
    , QLocale::Masai
    , QLocale::Soga
    , QLocale::Luyia
    , QLocale::Asu
    , QLocale::Teso
    , QLocale::Saho
    , QLocale::KoyraChiini
    , QLocale::Rwa
    , QLocale::Luo
    , QLocale::Chiga
    , QLocale::CentralMoroccoTamazight
    , QLocale::KoyraboroSenni
    , QLocale::Shambala
    , QLocale::Bodo
    , QLocale::Avaric
    , QLocale::Chamorro
    , QLocale::Chechen
    , QLocale::Church
    , QLocale::Chuvash
    , QLocale::Cree
    , QLocale::Haitian
    , QLocale::Herero
    , QLocale::HiriMotu
    , QLocale::Kanuri
    , QLocale::Komi
    , QLocale::Kongo
    , QLocale::Kwanyama
    , QLocale::Limburgish
    , QLocale::LubaKatanga
    , QLocale::Luxembourgish
    , QLocale::Navaho
    , QLocale::Ndonga
    , QLocale::Ojibwa
    , QLocale::Pali
    , QLocale::Walloon
    , QLocale::Aghem
    , QLocale::Basaa
    , QLocale::Zarma
    , QLocale::Duala
    , QLocale::JolaFonyi
    , QLocale::Ewondo
    , QLocale::Bafia
    , QLocale::MakhuwaMeetto
    , QLocale::Mundang
    , QLocale::Kwasio
    , QLocale::Nuer
    , QLocale::Sakha
    , QLocale::Sangu
    , QLocale::CongoSwahili
    , QLocale::Tasawaq
    , QLocale::Vai
    , QLocale::Walser
    , QLocale::Yangben
    , QLocale::Avestan
    , QLocale::Asturian
    , QLocale::Ngomba
    , QLocale::Kako
    , QLocale::Meta
    , QLocale::Ngiemboon
    , QLocale::Aragonese
    , QLocale::Akkadian
    , QLocale::AncientEgyptian
    , QLocale::AncientGreek
    , QLocale::Aramaic
    , QLocale::Balinese
    , QLocale::Bamun
    , QLocale::BatakToba
    , QLocale::Buginese
    , QLocale::Buhid
    , QLocale::Carian
    , QLocale::Chakma
    , QLocale::ClassicalMandaic
    , QLocale::Coptic
    , QLocale::Dogri
    , QLocale::EasternCham
    , QLocale::EasternKayah
    , QLocale::Etruscan
    , QLocale::Gothic
    , QLocale::Hanunoo
    , QLocale::Ingush
    , QLocale::LargeFloweryMiao
    , QLocale::Lepcha
    , QLocale::Limbu
    , QLocale::Lisu
    , QLocale::Lu
    , QLocale::Lycian
    , QLocale::Lydian
    , QLocale::Mandingo
    , QLocale::Manipuri
    , QLocale::Meroitic
    , QLocale::NorthernThai
    , QLocale::OldIrish
    , QLocale::OldNorse
    , QLocale::OldPersian
    , QLocale::OldTurkish
    , QLocale::Pahlavi
    , QLocale::Parthian
    , QLocale::Phoenician
    , QLocale::PrakritLanguage
    , QLocale::Rejang
    , QLocale::Sabaean
    , QLocale::Samaritan
    , QLocale::Santali
    , QLocale::Saurashtra
    , QLocale::Sora
    , QLocale::Sylheti
    , QLocale::Tagbanwa
    , QLocale::TaiDam
    , QLocale::TaiNua
    , QLocale::Ugaritic
    , QLocale::Akoose
    , QLocale::Lakota
    , QLocale::StandardMoroccanTamazight
};

static const char * const qtscript_QLocale_Language_keys[] = {
    "AnyLanguage"
    , "C"
    , "Abkhazian"
    , "Oromo"
    , "Afar"
    , "Afrikaans"
    , "Albanian"
    , "Amharic"
    , "Arabic"
    , "Armenian"
    , "Assamese"
    , "Aymara"
    , "Azerbaijani"
    , "Bashkir"
    , "Basque"
    , "Bengali"
    , "Dzongkha"
    , "Bihari"
    , "Bislama"
    , "Breton"
    , "Bulgarian"
    , "Burmese"
    , "Belarusian"
    , "Khmer"
    , "Catalan"
    , "Chinese"
    , "Corsican"
    , "Croatian"
    , "Czech"
    , "Danish"
    , "Dutch"
    , "English"
    , "Esperanto"
    , "Estonian"
    , "Faroese"
    , "Fijian"
    , "Finnish"
    , "French"
    , "WesternFrisian"
    , "Gaelic"
    , "Galician"
    , "Georgian"
    , "German"
    , "Greek"
    , "Greenlandic"
    , "Guarani"
    , "Gujarati"
    , "Hausa"
    , "Hebrew"
    , "Hindi"
    , "Hungarian"
    , "Icelandic"
    , "Indonesian"
    , "Interlingua"
    , "Interlingue"
    , "Inuktitut"
    , "Inupiak"
    , "Irish"
    , "Italian"
    , "Japanese"
    , "Javanese"
    , "Kannada"
    , "Kashmiri"
    , "Kazakh"
    , "Kinyarwanda"
    , "Kirghiz"
    , "Korean"
    , "Kurdish"
    , "Rundi"
    , "Lao"
    , "Latin"
    , "Latvian"
    , "Lingala"
    , "Lithuanian"
    , "Macedonian"
    , "Malagasy"
    , "Malay"
    , "Malayalam"
    , "Maltese"
    , "Maori"
    , "Marathi"
    , "Marshallese"
    , "Mongolian"
    , "NauruLanguage"
    , "Nepali"
    , "NorwegianBokmal"
    , "Occitan"
    , "Oriya"
    , "Pashto"
    , "Persian"
    , "Polish"
    , "Portuguese"
    , "Punjabi"
    , "Quechua"
    , "Romansh"
    , "Romanian"
    , "Russian"
    , "Samoan"
    , "Sango"
    , "Sanskrit"
    , "Serbian"
    , "Ossetic"
    , "SouthernSotho"
    , "Tswana"
    , "Shona"
    , "Sindhi"
    , "Sinhala"
    , "Swati"
    , "Slovak"
    , "Slovenian"
    , "Somali"
    , "Spanish"
    , "Sundanese"
    , "Swahili"
    , "Swedish"
    , "Sardinian"
    , "Tajik"
    , "Tamil"
    , "Tatar"
    , "Telugu"
    , "Thai"
    , "Tibetan"
    , "Tigrinya"
    , "Tongan"
    , "Tsonga"
    , "Turkish"
    , "Turkmen"
    , "Tahitian"
    , "Uighur"
    , "Ukrainian"
    , "Urdu"
    , "Uzbek"
    , "Vietnamese"
    , "Volapuk"
    , "Welsh"
    , "Wolof"
    , "Xhosa"
    , "Yiddish"
    , "Yoruba"
    , "Zhuang"
    , "Zulu"
    , "NorwegianNynorsk"
    , "Bosnian"
    , "Divehi"
    , "Manx"
    , "Cornish"
    , "Akan"
    , "Konkani"
    , "Ga"
    , "Igbo"
    , "Kamba"
    , "Syriac"
    , "Blin"
    , "Geez"
    , "Koro"
    , "Sidamo"
    , "Atsam"
    , "Tigre"
    , "Jju"
    , "Friulian"
    , "Venda"
    , "Ewe"
    , "Walamo"
    , "Hawaiian"
    , "Tyap"
    , "Nyanja"
    , "Filipino"
    , "SwissGerman"
    , "SichuanYi"
    , "Kpelle"
    , "LowGerman"
    , "SouthNdebele"
    , "NorthernSotho"
    , "NorthernSami"
    , "Taroko"
    , "Gusii"
    , "Taita"
    , "Fulah"
    , "Kikuyu"
    , "Samburu"
    , "Sena"
    , "NorthNdebele"
    , "Rombo"
    , "Tachelhit"
    , "Kabyle"
    , "Nyankole"
    , "Bena"
    , "Vunjo"
    , "Bambara"
    , "Embu"
    , "Cherokee"
    , "Morisyen"
    , "Makonde"
    , "Langi"
    , "Ganda"
    , "Bemba"
    , "Kabuverdianu"
    , "Meru"
    , "Kalenjin"
    , "Nama"
    , "Machame"
    , "Colognian"
    , "Masai"
    , "Soga"
    , "Luyia"
    , "Asu"
    , "Teso"
    , "Saho"
    , "KoyraChiini"
    , "Rwa"
    , "Luo"
    , "Chiga"
    , "CentralMoroccoTamazight"
    , "KoyraboroSenni"
    , "Shambala"
    , "Bodo"
    , "Avaric"
    , "Chamorro"
    , "Chechen"
    , "Church"
    , "Chuvash"
    , "Cree"
    , "Haitian"
    , "Herero"
    , "HiriMotu"
    , "Kanuri"
    , "Komi"
    , "Kongo"
    , "Kwanyama"
    , "Limburgish"
    , "LubaKatanga"
    , "Luxembourgish"
    , "Navaho"
    , "Ndonga"
    , "Ojibwa"
    , "Pali"
    , "Walloon"
    , "Aghem"
    , "Basaa"
    , "Zarma"
    , "Duala"
    , "JolaFonyi"
    , "Ewondo"
    , "Bafia"
    , "MakhuwaMeetto"
    , "Mundang"
    , "Kwasio"
    , "Nuer"
    , "Sakha"
    , "Sangu"
    , "CongoSwahili"
    , "Tasawaq"
    , "Vai"
    , "Walser"
    , "Yangben"
    , "Avestan"
    , "Asturian"
    , "Ngomba"
    , "Kako"
    , "Meta"
    , "Ngiemboon"
    , "Aragonese"
    , "Akkadian"
    , "AncientEgyptian"
    , "AncientGreek"
    , "Aramaic"
    , "Balinese"
    , "Bamun"
    , "BatakToba"
    , "Buginese"
    , "Buhid"
    , "Carian"
    , "Chakma"
    , "ClassicalMandaic"
    , "Coptic"
    , "Dogri"
    , "EasternCham"
    , "EasternKayah"
    , "Etruscan"
    , "Gothic"
    , "Hanunoo"
    , "Ingush"
    , "LargeFloweryMiao"
    , "Lepcha"
    , "Limbu"
    , "Lisu"
    , "Lu"
    , "Lycian"
    , "Lydian"
    , "Mandingo"
    , "Manipuri"
    , "Meroitic"
    , "NorthernThai"
    , "OldIrish"
    , "OldNorse"
    , "OldPersian"
    , "OldTurkish"
    , "Pahlavi"
    , "Parthian"
    , "Phoenician"
    , "PrakritLanguage"
    , "Rejang"
    , "Sabaean"
    , "Samaritan"
    , "Santali"
    , "Saurashtra"
    , "Sora"
    , "Sylheti"
    , "Tagbanwa"
    , "TaiDam"
    , "TaiNua"
    , "Ugaritic"
    , "Akoose"
    , "Lakota"
    , "StandardMoroccanTamazight"
};

static QString qtscript_QLocale_Language_toStringHelper(QLocale::Language value)
{
    const QMetaObject *meta = qtscript_QLocale_metaObject();
    int idx = meta->indexOfEnumerator("Language");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLocale_Language_toScriptValue(QScriptEngine *engine, const QLocale::Language &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_Language_toStringHelper(value));
}

static void qtscript_QLocale_Language_fromScriptValue(const QScriptValue &value, QLocale::Language &out)
{
    out = qvariant_cast<QLocale::Language>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_Language(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLocale_metaObject();
    int idx = meta->indexOfEnumerator("Language");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLocale::Language>(arg));
    return context->throwError(QString::fromLatin1("Language(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_Language_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::Language value = qscriptvalue_cast<QLocale::Language>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_Language_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::Language value = qscriptvalue_cast<QLocale::Language>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_Language_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_Language_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_Language,
        qtscript_QLocale_Language_valueOf, qtscript_QLocale_Language_toString);
    qScriptRegisterMetaType<QLocale::Language>(engine, qtscript_QLocale_Language_toScriptValue,
        qtscript_QLocale_Language_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 315; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_Language_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_Language_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::NumberOption
//

static const QLocale::NumberOption qtscript_QLocale_NumberOption_values[] = {
    QLocale::OmitGroupSeparator
    , QLocale::RejectGroupSeparator
};

static const char * const qtscript_QLocale_NumberOption_keys[] = {
    "OmitGroupSeparator"
    , "RejectGroupSeparator"
};

static QString qtscript_QLocale_NumberOption_toStringHelper(QLocale::NumberOption value)
{
    if ((value >= QLocale::OmitGroupSeparator) && (value <= QLocale::RejectGroupSeparator))
        return qtscript_QLocale_NumberOption_keys[static_cast<int>(value)-static_cast<int>(QLocale::OmitGroupSeparator)];
    return QString();
}

static QScriptValue qtscript_QLocale_NumberOption_toScriptValue(QScriptEngine *engine, const QLocale::NumberOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_NumberOption_toStringHelper(value));
}

static void qtscript_QLocale_NumberOption_fromScriptValue(const QScriptValue &value, QLocale::NumberOption &out)
{
    out = qvariant_cast<QLocale::NumberOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_NumberOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QLocale::OmitGroupSeparator) && (arg <= QLocale::RejectGroupSeparator))
        return qScriptValueFromValue(engine,  static_cast<QLocale::NumberOption>(arg));
    return context->throwError(QString::fromLatin1("NumberOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_NumberOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::NumberOption value = qscriptvalue_cast<QLocale::NumberOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_NumberOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::NumberOption value = qscriptvalue_cast<QLocale::NumberOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_NumberOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_NumberOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_NumberOption,
        qtscript_QLocale_NumberOption_valueOf, qtscript_QLocale_NumberOption_toString);
    qScriptRegisterMetaType<QLocale::NumberOption>(engine, qtscript_QLocale_NumberOption_toScriptValue,
        qtscript_QLocale_NumberOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_NumberOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_NumberOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale::NumberOptions
//

static QScriptValue qtscript_QLocale_NumberOptions_toScriptValue(QScriptEngine *engine, const QLocale::NumberOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QLocale_NumberOptions_fromScriptValue(const QScriptValue &value, QLocale::NumberOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QLocale::NumberOptions>())
        out = qvariant_cast<QLocale::NumberOptions>(var);
    else if (var.userType() == qMetaTypeId<QLocale::NumberOption>())
        out = qvariant_cast<QLocale::NumberOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QLocale_NumberOptions(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::NumberOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QLocale::NumberOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QLocale::NumberOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("NumberOptions(): argument %0 is not of type NumberOption").arg(i));
            }
            result |= qvariant_cast<QLocale::NumberOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QLocale_NumberOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::NumberOptions value = qscriptvalue_cast<QLocale::NumberOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_NumberOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::NumberOptions value = qscriptvalue_cast<QLocale::NumberOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QLocale_NumberOption_values[i]) == qtscript_QLocale_NumberOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QLocale_NumberOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QLocale_NumberOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QLocale::NumberOptions>() == otherObj.value<QLocale::NumberOptions>())));
}

static QScriptValue qtscript_create_QLocale_NumberOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QLocale_NumberOptions, qtscript_QLocale_NumberOptions_valueOf,
        qtscript_QLocale_NumberOptions_toString, qtscript_QLocale_NumberOptions_equals);
    qScriptRegisterMetaType<QLocale::NumberOptions>(engine, qtscript_QLocale_NumberOptions_toScriptValue,
        qtscript_QLocale_NumberOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QLocale::Country
//

static const QLocale::Country qtscript_QLocale_Country_values[] = {
    QLocale::AnyCountry
    , QLocale::Afghanistan
    , QLocale::Albania
    , QLocale::Algeria
    , QLocale::AmericanSamoa
    , QLocale::Andorra
    , QLocale::Angola
    , QLocale::Anguilla
    , QLocale::Antarctica
    , QLocale::AntiguaAndBarbuda
    , QLocale::Argentina
    , QLocale::Armenia
    , QLocale::Aruba
    , QLocale::Australia
    , QLocale::Austria
    , QLocale::Azerbaijan
    , QLocale::Bahamas
    , QLocale::Bahrain
    , QLocale::Bangladesh
    , QLocale::Barbados
    , QLocale::Belarus
    , QLocale::Belgium
    , QLocale::Belize
    , QLocale::Benin
    , QLocale::Bermuda
    , QLocale::Bhutan
    , QLocale::Bolivia
    , QLocale::BosniaAndHerzegowina
    , QLocale::Botswana
    , QLocale::BouvetIsland
    , QLocale::Brazil
    , QLocale::BritishIndianOceanTerritory
    , QLocale::Brunei
    , QLocale::Bulgaria
    , QLocale::BurkinaFaso
    , QLocale::Burundi
    , QLocale::Cambodia
    , QLocale::Cameroon
    , QLocale::Canada
    , QLocale::CapeVerde
    , QLocale::CaymanIslands
    , QLocale::CentralAfricanRepublic
    , QLocale::Chad
    , QLocale::Chile
    , QLocale::China
    , QLocale::ChristmasIsland
    , QLocale::CocosIslands
    , QLocale::Colombia
    , QLocale::Comoros
    , QLocale::CongoKinshasa
    , QLocale::CongoBrazzaville
    , QLocale::CookIslands
    , QLocale::CostaRica
    , QLocale::IvoryCoast
    , QLocale::Croatia
    , QLocale::Cuba
    , QLocale::Cyprus
    , QLocale::CzechRepublic
    , QLocale::Denmark
    , QLocale::Djibouti
    , QLocale::Dominica
    , QLocale::DominicanRepublic
    , QLocale::EastTimor
    , QLocale::Ecuador
    , QLocale::Egypt
    , QLocale::ElSalvador
    , QLocale::EquatorialGuinea
    , QLocale::Eritrea
    , QLocale::Estonia
    , QLocale::Ethiopia
    , QLocale::FalklandIslands
    , QLocale::FaroeIslands
    , QLocale::Fiji
    , QLocale::Finland
    , QLocale::France
    , QLocale::Guernsey
    , QLocale::FrenchGuiana
    , QLocale::FrenchPolynesia
    , QLocale::FrenchSouthernTerritories
    , QLocale::Gabon
    , QLocale::Gambia
    , QLocale::Georgia
    , QLocale::Germany
    , QLocale::Ghana
    , QLocale::Gibraltar
    , QLocale::Greece
    , QLocale::Greenland
    , QLocale::Grenada
    , QLocale::Guadeloupe
    , QLocale::Guam
    , QLocale::Guatemala
    , QLocale::Guinea
    , QLocale::GuineaBissau
    , QLocale::Guyana
    , QLocale::Haiti
    , QLocale::HeardAndMcDonaldIslands
    , QLocale::Honduras
    , QLocale::HongKong
    , QLocale::Hungary
    , QLocale::Iceland
    , QLocale::India
    , QLocale::Indonesia
    , QLocale::Iran
    , QLocale::Iraq
    , QLocale::Ireland
    , QLocale::Israel
    , QLocale::Italy
    , QLocale::Jamaica
    , QLocale::Japan
    , QLocale::Jordan
    , QLocale::Kazakhstan
    , QLocale::Kenya
    , QLocale::Kiribati
    , QLocale::NorthKorea
    , QLocale::SouthKorea
    , QLocale::Kuwait
    , QLocale::Kyrgyzstan
    , QLocale::Laos
    , QLocale::Latvia
    , QLocale::Lebanon
    , QLocale::Lesotho
    , QLocale::Liberia
    , QLocale::Libya
    , QLocale::Liechtenstein
    , QLocale::Lithuania
    , QLocale::Luxembourg
    , QLocale::Macau
    , QLocale::Macedonia
    , QLocale::Madagascar
    , QLocale::Malawi
    , QLocale::Malaysia
    , QLocale::Maldives
    , QLocale::Mali
    , QLocale::Malta
    , QLocale::MarshallIslands
    , QLocale::Martinique
    , QLocale::Mauritania
    , QLocale::Mauritius
    , QLocale::Mayotte
    , QLocale::Mexico
    , QLocale::Micronesia
    , QLocale::Moldova
    , QLocale::Monaco
    , QLocale::Mongolia
    , QLocale::Montserrat
    , QLocale::Morocco
    , QLocale::Mozambique
    , QLocale::Myanmar
    , QLocale::Namibia
    , QLocale::NauruCountry
    , QLocale::Nepal
    , QLocale::Netherlands
    , QLocale::CuraSao
    , QLocale::NewCaledonia
    , QLocale::NewZealand
    , QLocale::Nicaragua
    , QLocale::Niger
    , QLocale::Nigeria
    , QLocale::Niue
    , QLocale::NorfolkIsland
    , QLocale::NorthernMarianaIslands
    , QLocale::Norway
    , QLocale::Oman
    , QLocale::Pakistan
    , QLocale::Palau
    , QLocale::PalestinianTerritories
    , QLocale::Panama
    , QLocale::PapuaNewGuinea
    , QLocale::Paraguay
    , QLocale::Peru
    , QLocale::Philippines
    , QLocale::Pitcairn
    , QLocale::Poland
    , QLocale::Portugal
    , QLocale::PuertoRico
    , QLocale::Qatar
    , QLocale::Reunion
    , QLocale::Romania
    , QLocale::Russia
    , QLocale::Rwanda
    , QLocale::SaintKittsAndNevis
    , QLocale::SaintLucia
    , QLocale::SaintVincentAndTheGrenadines
    , QLocale::Samoa
    , QLocale::SanMarino
    , QLocale::SaoTomeAndPrincipe
    , QLocale::SaudiArabia
    , QLocale::Senegal
    , QLocale::Seychelles
    , QLocale::SierraLeone
    , QLocale::Singapore
    , QLocale::Slovakia
    , QLocale::Slovenia
    , QLocale::SolomonIslands
    , QLocale::Somalia
    , QLocale::SouthAfrica
    , QLocale::SouthGeorgiaAndTheSouthSandwichIslands
    , QLocale::Spain
    , QLocale::SriLanka
    , QLocale::SaintHelena
    , QLocale::SaintPierreAndMiquelon
    , QLocale::Sudan
    , QLocale::Suriname
    , QLocale::SvalbardAndJanMayenIslands
    , QLocale::Swaziland
    , QLocale::Sweden
    , QLocale::Switzerland
    , QLocale::Syria
    , QLocale::Taiwan
    , QLocale::Tajikistan
    , QLocale::Tanzania
    , QLocale::Thailand
    , QLocale::Togo
    , QLocale::Tokelau
    , QLocale::Tonga
    , QLocale::TrinidadAndTobago
    , QLocale::Tunisia
    , QLocale::Turkey
    , QLocale::Turkmenistan
    , QLocale::TurksAndCaicosIslands
    , QLocale::Tuvalu
    , QLocale::Uganda
    , QLocale::Ukraine
    , QLocale::UnitedArabEmirates
    , QLocale::UnitedKingdom
    , QLocale::UnitedStates
    , QLocale::UnitedStatesMinorOutlyingIslands
    , QLocale::Uruguay
    , QLocale::Uzbekistan
    , QLocale::Vanuatu
    , QLocale::VaticanCityState
    , QLocale::Venezuela
    , QLocale::Vietnam
    , QLocale::BritishVirginIslands
    , QLocale::UnitedStatesVirginIslands
    , QLocale::WallisAndFutunaIslands
    , QLocale::WesternSahara
    , QLocale::Yemen
    , QLocale::CanaryIslands
    , QLocale::Zambia
    , QLocale::Zimbabwe
    , QLocale::ClippertonIsland
    , QLocale::Montenegro
    , QLocale::Serbia
    , QLocale::SaintBarthelemy
    , QLocale::SaintMartin
    , QLocale::LatinAmericaAndTheCaribbean
    , QLocale::AscensionIsland
    , QLocale::AlandIslands
    , QLocale::DiegoGarcia
    , QLocale::CeutaAndMelilla
    , QLocale::IsleOfMan
    , QLocale::Jersey
    , QLocale::TristanDaCunha
    , QLocale::SouthSudan
    , QLocale::Bonaire
    , QLocale::SintMaarten
    , QLocale::Kosovo
};

static const char * const qtscript_QLocale_Country_keys[] = {
    "AnyCountry"
    , "Afghanistan"
    , "Albania"
    , "Algeria"
    , "AmericanSamoa"
    , "Andorra"
    , "Angola"
    , "Anguilla"
    , "Antarctica"
    , "AntiguaAndBarbuda"
    , "Argentina"
    , "Armenia"
    , "Aruba"
    , "Australia"
    , "Austria"
    , "Azerbaijan"
    , "Bahamas"
    , "Bahrain"
    , "Bangladesh"
    , "Barbados"
    , "Belarus"
    , "Belgium"
    , "Belize"
    , "Benin"
    , "Bermuda"
    , "Bhutan"
    , "Bolivia"
    , "BosniaAndHerzegowina"
    , "Botswana"
    , "BouvetIsland"
    , "Brazil"
    , "BritishIndianOceanTerritory"
    , "Brunei"
    , "Bulgaria"
    , "BurkinaFaso"
    , "Burundi"
    , "Cambodia"
    , "Cameroon"
    , "Canada"
    , "CapeVerde"
    , "CaymanIslands"
    , "CentralAfricanRepublic"
    , "Chad"
    , "Chile"
    , "China"
    , "ChristmasIsland"
    , "CocosIslands"
    , "Colombia"
    , "Comoros"
    , "CongoKinshasa"
    , "CongoBrazzaville"
    , "CookIslands"
    , "CostaRica"
    , "IvoryCoast"
    , "Croatia"
    , "Cuba"
    , "Cyprus"
    , "CzechRepublic"
    , "Denmark"
    , "Djibouti"
    , "Dominica"
    , "DominicanRepublic"
    , "EastTimor"
    , "Ecuador"
    , "Egypt"
    , "ElSalvador"
    , "EquatorialGuinea"
    , "Eritrea"
    , "Estonia"
    , "Ethiopia"
    , "FalklandIslands"
    , "FaroeIslands"
    , "Fiji"
    , "Finland"
    , "France"
    , "Guernsey"
    , "FrenchGuiana"
    , "FrenchPolynesia"
    , "FrenchSouthernTerritories"
    , "Gabon"
    , "Gambia"
    , "Georgia"
    , "Germany"
    , "Ghana"
    , "Gibraltar"
    , "Greece"
    , "Greenland"
    , "Grenada"
    , "Guadeloupe"
    , "Guam"
    , "Guatemala"
    , "Guinea"
    , "GuineaBissau"
    , "Guyana"
    , "Haiti"
    , "HeardAndMcDonaldIslands"
    , "Honduras"
    , "HongKong"
    , "Hungary"
    , "Iceland"
    , "India"
    , "Indonesia"
    , "Iran"
    , "Iraq"
    , "Ireland"
    , "Israel"
    , "Italy"
    , "Jamaica"
    , "Japan"
    , "Jordan"
    , "Kazakhstan"
    , "Kenya"
    , "Kiribati"
    , "NorthKorea"
    , "SouthKorea"
    , "Kuwait"
    , "Kyrgyzstan"
    , "Laos"
    , "Latvia"
    , "Lebanon"
    , "Lesotho"
    , "Liberia"
    , "Libya"
    , "Liechtenstein"
    , "Lithuania"
    , "Luxembourg"
    , "Macau"
    , "Macedonia"
    , "Madagascar"
    , "Malawi"
    , "Malaysia"
    , "Maldives"
    , "Mali"
    , "Malta"
    , "MarshallIslands"
    , "Martinique"
    , "Mauritania"
    , "Mauritius"
    , "Mayotte"
    , "Mexico"
    , "Micronesia"
    , "Moldova"
    , "Monaco"
    , "Mongolia"
    , "Montserrat"
    , "Morocco"
    , "Mozambique"
    , "Myanmar"
    , "Namibia"
    , "NauruCountry"
    , "Nepal"
    , "Netherlands"
    , "CuraSao"
    , "NewCaledonia"
    , "NewZealand"
    , "Nicaragua"
    , "Niger"
    , "Nigeria"
    , "Niue"
    , "NorfolkIsland"
    , "NorthernMarianaIslands"
    , "Norway"
    , "Oman"
    , "Pakistan"
    , "Palau"
    , "PalestinianTerritories"
    , "Panama"
    , "PapuaNewGuinea"
    , "Paraguay"
    , "Peru"
    , "Philippines"
    , "Pitcairn"
    , "Poland"
    , "Portugal"
    , "PuertoRico"
    , "Qatar"
    , "Reunion"
    , "Romania"
    , "Russia"
    , "Rwanda"
    , "SaintKittsAndNevis"
    , "SaintLucia"
    , "SaintVincentAndTheGrenadines"
    , "Samoa"
    , "SanMarino"
    , "SaoTomeAndPrincipe"
    , "SaudiArabia"
    , "Senegal"
    , "Seychelles"
    , "SierraLeone"
    , "Singapore"
    , "Slovakia"
    , "Slovenia"
    , "SolomonIslands"
    , "Somalia"
    , "SouthAfrica"
    , "SouthGeorgiaAndTheSouthSandwichIslands"
    , "Spain"
    , "SriLanka"
    , "SaintHelena"
    , "SaintPierreAndMiquelon"
    , "Sudan"
    , "Suriname"
    , "SvalbardAndJanMayenIslands"
    , "Swaziland"
    , "Sweden"
    , "Switzerland"
    , "Syria"
    , "Taiwan"
    , "Tajikistan"
    , "Tanzania"
    , "Thailand"
    , "Togo"
    , "Tokelau"
    , "Tonga"
    , "TrinidadAndTobago"
    , "Tunisia"
    , "Turkey"
    , "Turkmenistan"
    , "TurksAndCaicosIslands"
    , "Tuvalu"
    , "Uganda"
    , "Ukraine"
    , "UnitedArabEmirates"
    , "UnitedKingdom"
    , "UnitedStates"
    , "UnitedStatesMinorOutlyingIslands"
    , "Uruguay"
    , "Uzbekistan"
    , "Vanuatu"
    , "VaticanCityState"
    , "Venezuela"
    , "Vietnam"
    , "BritishVirginIslands"
    , "UnitedStatesVirginIslands"
    , "WallisAndFutunaIslands"
    , "WesternSahara"
    , "Yemen"
    , "CanaryIslands"
    , "Zambia"
    , "Zimbabwe"
    , "ClippertonIsland"
    , "Montenegro"
    , "Serbia"
    , "SaintBarthelemy"
    , "SaintMartin"
    , "LatinAmericaAndTheCaribbean"
    , "AscensionIsland"
    , "AlandIslands"
    , "DiegoGarcia"
    , "CeutaAndMelilla"
    , "IsleOfMan"
    , "Jersey"
    , "TristanDaCunha"
    , "SouthSudan"
    , "Bonaire"
    , "SintMaarten"
    , "Kosovo"
};

static QString qtscript_QLocale_Country_toStringHelper(QLocale::Country value)
{
    const QMetaObject *meta = qtscript_QLocale_metaObject();
    int idx = meta->indexOfEnumerator("Country");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLocale_Country_toScriptValue(QScriptEngine *engine, const QLocale::Country &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLocale"));
    return clazz.property(qtscript_QLocale_Country_toStringHelper(value));
}

static void qtscript_QLocale_Country_fromScriptValue(const QScriptValue &value, QLocale::Country &out)
{
    out = qvariant_cast<QLocale::Country>(value.toVariant());
}

static QScriptValue qtscript_construct_QLocale_Country(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLocale_metaObject();
    int idx = meta->indexOfEnumerator("Country");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLocale::Country>(arg));
    return context->throwError(QString::fromLatin1("Country(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLocale_Country_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::Country value = qscriptvalue_cast<QLocale::Country>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLocale_Country_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLocale::Country value = qscriptvalue_cast<QLocale::Country>(context->thisObject());
    return QScriptValue(engine, qtscript_QLocale_Country_toStringHelper(value));
}

static QScriptValue qtscript_create_QLocale_Country_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLocale_Country,
        qtscript_QLocale_Country_valueOf, qtscript_QLocale_Country_toString);
    qScriptRegisterMetaType<QLocale::Country>(engine, qtscript_QLocale_Country_toScriptValue,
        qtscript_QLocale_Country_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 258; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLocale_Country_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLocale_Country_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLocale
//

static QScriptValue qtscript_QLocale_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 49;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QLocale* _q_self = qscriptvalue_cast<QLocale*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLocale.%0(): this object is not a QLocale")
            .arg(qtscript_QLocale_function_names[_id+9]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->amText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->bcp47Name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QLocale::Country _q_result = _q_self->country();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QString _q_result = _q_self->createSeparatedList(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->currencySymbol();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QLocale::CurrencySymbolFormat _q_arg0 = qscriptvalue_cast<QLocale::CurrencySymbolFormat>(context->argument(0));
        QString _q_result = _q_self->currencySymbol(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->dateFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QLocale::FormatType _q_arg0 = qscriptvalue_cast<QLocale::FormatType>(context->argument(0));
        QString _q_result = _q_self->dateFormat(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->dateTimeFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QLocale::FormatType _q_arg0 = qscriptvalue_cast<QLocale::FormatType>(context->argument(0));
        QString _q_result = _q_self->dateTimeFormat(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->dayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
        QString _q_result = _q_self->dayName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->decimalPoint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->exponential();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        Qt::DayOfWeek _q_result = _q_self->firstDayOfWeek();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->groupSeparator();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QLocale::Language _q_result = _q_self->language();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QLocale::MeasurementSystem _q_result = _q_self->measurementSystem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->monthName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
        QString _q_result = _q_self->monthName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->nativeCountryName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->nativeLanguageName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->negativeSign();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QFlags<QLocale::NumberOption> _q_result = _q_self->numberOptions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->percent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->pmText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->positiveSign();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_result = _q_self->quoteString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            QString _q_result = _q_self->quoteString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QLocale::QuotationStyle>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QLocale::QuotationStyle _q_arg1 = qscriptvalue_cast<QLocale::QuotationStyle>(context->argument(1));
            QString _q_result = _q_self->quoteString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QLocale::QuotationStyle>() == context->argument(1).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            QLocale::QuotationStyle _q_arg1 = qscriptvalue_cast<QLocale::QuotationStyle>(context->argument(1));
            QString _q_result = _q_self->quoteString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QLocale::Script _q_result = _q_self->script();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QFlags<QLocale::NumberOption> _q_arg0 = qscriptvalue_cast<QFlags<QLocale::NumberOption> >(context->argument(0));
        _q_self->setNumberOptions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->standaloneDayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
        QString _q_result = _q_self->standaloneDayName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->standaloneMonthName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
        QString _q_result = _q_self->standaloneMonthName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        Qt::LayoutDirection _q_result = _q_self->textDirection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->timeFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QLocale::FormatType _q_arg0 = qscriptvalue_cast<QLocale::FormatType>(context->argument(0));
        QString _q_result = _q_self->timeFormat(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isNumber()) {
            double _q_arg0 = context->argument(0).toNumber();
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qlonglong>() == context->argument(0).toVariant().userType())) {
            qlonglong _q_arg0 = qscriptvalue_cast<qlonglong>(context->argument(0));
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qulonglong>() == context->argument(0).toVariant().userType())) {
            qulonglong _q_arg0 = qscriptvalue_cast<qulonglong>(context->argument(0));
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            short _q_arg0 = qscriptvalue_cast<short>(context->argument(0));
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<ushort>() == context->argument(0).toVariant().userType())) {
            ushort _q_arg0 = qscriptvalue_cast<ushort>(context->argument(0));
            QString _q_result = _q_self->toCurrencyString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            double _q_arg0 = context->argument(0).toNumber();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qlonglong>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            qlonglong _q_arg0 = qscriptvalue_cast<qlonglong>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qulonglong>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            qulonglong _q_arg0 = qscriptvalue_cast<qulonglong>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            short _q_arg0 = qscriptvalue_cast<short>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<ushort>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            ushort _q_arg0 = qscriptvalue_cast<ushort>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toCurrencyString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDate _q_result = _q_self->toDate(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QLocale::FormatType>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
            QDate _q_result = _q_self->toDate(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QDate _q_result = _q_self->toDate(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDateTime _q_result = _q_self->toDateTime(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QLocale::FormatType>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
            QDateTime _q_result = _q_self->toDateTime(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QDateTime _q_result = _q_self->toDateTime(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg1 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                      double _q_result = _q_self->toDouble(_q_arg0, _q_arg1);
            
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            double _q_result = _q_self->toDouble(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
        bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
        double _q_result = _q_self->toDouble(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg1 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                      float _q_result = _q_self->toFloat(_q_arg0, _q_arg1);
            
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            float _q_result = _q_self->toFloat(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
        bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
        float _q_result = _q_self->toFloat(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_result = _q_self->toInt(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            int _q_result = _q_self->toInt(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            int _q_result = _q_self->toInt(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            int _q_result = _q_self->toInt(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            qlonglong _q_result = _q_self->toLongLong(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            qlonglong _q_result = _q_self->toLongLong(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            qlonglong _q_result = _q_self->toLongLong(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            qlonglong _q_result = _q_self->toLongLong(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->toLower(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            short _q_result = _q_self->toShort(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            short _q_result = _q_self->toShort(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            short _q_result = _q_self->toShort(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            short _q_result = _q_self->toShort(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QDate>() == context->argument(0).toVariant().userType())) {
            QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())) {
            QDateTime _q_arg0 = context->argument(0).toDateTime();
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTime>() == context->argument(0).toVariant().userType())) {
            QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            double _q_arg0 = context->argument(0).toNumber();
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<qulonglong>() == context->argument(0).toVariant().userType())) {
            qulonglong _q_arg0 = qscriptvalue_cast<qulonglong>(context->argument(0));
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            short _q_arg0 = qscriptvalue_cast<short>(context->argument(0));
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QDate>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QLocale::FormatType>() == context->argument(1).toVariant().userType())) {
            QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
            QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QDate>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QLocale::FormatType>() == context->argument(1).toVariant().userType())) {
            QDateTime _q_arg0 = context->argument(0).toDateTime();
            QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QDateTime _q_arg0 = context->argument(0).toDateTime();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTime>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QLocale::FormatType>() == context->argument(1).toVariant().userType())) {
            QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
            QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTime>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<char>() == context->argument(1).toVariant().userType())) {
            double _q_arg0 = context->argument(0).toNumber();
            char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<char>() == context->argument(1).toVariant().userType())) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isNumber()
            && (qMetaTypeId<char>() == context->argument(1).toVariant().userType())
            && context->argument(2).isNumber()) {
            double _q_arg0 = context->argument(0).toNumber();
            char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<char>() == context->argument(1).toVariant().userType())
            && context->argument(2).isNumber()) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            QString _q_result = _q_self->toString(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QTime _q_result = _q_self->toTime(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QLocale::FormatType>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QLocale::FormatType _q_arg1 = qscriptvalue_cast<QLocale::FormatType>(context->argument(1));
            QTime _q_result = _q_self->toTime(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QTime _q_result = _q_self->toTime(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            uint _q_result = _q_self->toUInt(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            uint _q_result = _q_self->toUInt(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            uint _q_result = _q_self->toUInt(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            uint _q_result = _q_self->toUInt(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            qulonglong _q_result = _q_self->toULongLong(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            qulonglong _q_result = _q_self->toULongLong(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            qulonglong _q_result = _q_self->toULongLong(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            qulonglong _q_result = _q_self->toULongLong(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            ushort _q_result = _q_self->toUShort(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            ushort _q_result = _q_self->toUShort(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            ushort _q_result = _q_self->toUShort(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QStringRef>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<bool*>(context->argument(1))) {
            QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
            bool* _q_arg1 = qscriptvalue_cast<bool*>(context->argument(1));
            ushort _q_result = _q_self->toUShort(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->toUpper(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->uiLanguages();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QList<Qt::DayOfWeek > _q_result = _q_self->weekdays();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->zeroDigit();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocale_throw_ambiguity_error_helper(context,
        qtscript_QLocale_function_names[_id+9],
        qtscript_QLocale_function_signatures[_id+9]);
}

static QScriptValue qtscript_QLocale_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLocale(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QLocale _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QLocale::Language>() == context->argument(0).toVariant().userType())) {
            QLocale::Language _q_arg0 = qscriptvalue_cast<QLocale::Language>(context->argument(0));
            QLocale _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QLocale>() == context->argument(0).toVariant().userType())) {
            QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
            QLocale _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QLocale _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QLocale::Language _q_arg0 = qscriptvalue_cast<QLocale::Language>(context->argument(0));
        QLocale::Country _q_arg1 = qscriptvalue_cast<QLocale::Country>(context->argument(1));
        QLocale _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QLocale::Language _q_arg0 = qscriptvalue_cast<QLocale::Language>(context->argument(0));
        QLocale::Script _q_arg1 = qscriptvalue_cast<QLocale::Script>(context->argument(1));
        QLocale::Country _q_arg2 = qscriptvalue_cast<QLocale::Country>(context->argument(2));
        QLocale _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QLocale _q_result = QLocale::c();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QLocale::Language _q_arg0 = qscriptvalue_cast<QLocale::Language>(context->argument(0));
        QList<QLocale::Country > _q_result = QLocale::countriesForLanguage(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QLocale::Country _q_arg0 = qscriptvalue_cast<QLocale::Country>(context->argument(0));
        QString _q_result = QLocale::countryToString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QLocale::Language _q_arg0 = qscriptvalue_cast<QLocale::Language>(context->argument(0));
        QString _q_result = QLocale::languageToString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QLocale::Language _q_arg0 = qscriptvalue_cast<QLocale::Language>(context->argument(0));
        QLocale::Script _q_arg1 = qscriptvalue_cast<QLocale::Script>(context->argument(1));
        QLocale::Country _q_arg2 = qscriptvalue_cast<QLocale::Country>(context->argument(2));
        QList<QLocale > _q_result = QLocale::matchingLocales(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QLocale::Script _q_arg0 = qscriptvalue_cast<QLocale::Script>(context->argument(0));
        QString _q_result = QLocale::scriptToString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
        QLocale::setDefault(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QLocale _q_result = QLocale::system();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLocale_throw_ambiguity_error_helper(context,
        qtscript_QLocale_function_names[_id],
        qtscript_QLocale_function_signatures[_id]);
}

QScriptValue qtscript_create_QLocale_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLocale*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLocale*)0));
    for (int i = 0; i < 49; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocale_prototype_call, qtscript_QLocale_function_lengths[i+9]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLocale_function_names[i+9]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QLocale>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QLocale*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLocale_static_call, proto, qtscript_QLocale_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocale_static_call,
            qtscript_QLocale_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLocale_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Script"),
        qtscript_create_QLocale_Script_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CurrencySymbolFormat"),
        qtscript_create_QLocale_CurrencySymbolFormat_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("QuotationStyle"),
        qtscript_create_QLocale_QuotationStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MeasurementSystem"),
        qtscript_create_QLocale_MeasurementSystem_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FormatType"),
        qtscript_create_QLocale_FormatType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Language"),
        qtscript_create_QLocale_Language_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NumberOption"),
        qtscript_create_QLocale_NumberOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NumberOptions"),
        qtscript_create_QLocale_NumberOptions_class(engine));
    ctor.setProperty(QString::fromLatin1("Country"),
        qtscript_create_QLocale_Country_class(engine, ctor));
    return ctor;
}
