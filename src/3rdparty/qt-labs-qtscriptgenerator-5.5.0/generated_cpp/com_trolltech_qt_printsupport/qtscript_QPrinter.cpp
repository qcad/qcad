#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qprinter.h>
#include <QPrinterInfo>
#include <QVariant>
#include <qlist.h>
#include <qpaintengine.h>
#include <qprintengine.h>
#include <qprinter.h>
#include <qrect.h>
#include <qsize.h>

#include "qtscriptshell_QPrinter.h"

static const char * const qtscript_QPrinter_function_names[] = {
    "QPrinter"
    // static
    // prototype
    , "abort"
    , "actualNumCopies"
    , "collateCopies"
    , "colorMode"
    , "copyCount"
    , "creator"
    , "devType"
    , "docName"
    , "doubleSidedPrinting"
    , "duplex"
    , "fontEmbeddingEnabled"
    , "fromPage"
    , "fullPage"
    , "getPageMargins"
    , "isValid"
    , "newPage"
    , "numCopies"
    , "orientation"
    , "outputFileName"
    , "outputFormat"
    , "pageOrder"
    , "pageRect"
    , "paintEngine"
    , "paperName"
    , "paperRect"
    , "paperSize"
    , "paperSource"
    , "printEngine"
    , "printProgram"
    , "printRange"
    , "printerName"
    , "printerState"
    , "resolution"
    , "setCollateCopies"
    , "setColorMode"
    , "setCopyCount"
    , "setCreator"
    , "setDocName"
    , "setDoubleSidedPrinting"
    , "setDuplex"
    , "setFontEmbeddingEnabled"
    , "setFromTo"
    , "setFullPage"
    , "setNumCopies"
    , "setOrientation"
    , "setOutputFileName"
    , "setOutputFormat"
    , "setPageMargins"
    , "setPageOrder"
    , "setPageSizeMM"
    , "setPaperName"
    , "setPaperSize"
    , "setPaperSource"
    , "setPrintProgram"
    , "setPrintRange"
    , "setPrinterName"
    , "setResolution"
    , "setWinPageSize"
    , "supportedResolutions"
    , "supportsMultipleCopies"
    , "toPage"
    , "winPageSize"
    , "toString"
};

static const char * const qtscript_QPrinter_function_signatures[] = {
    "PrinterMode mode\nQPrinterInfo printer, PrinterMode mode"
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
    , ""
    , ""
    , "qreal left, qreal top, qreal right, qreal bottom, Unit unit"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "\nUnit arg__1"
    , ""
    , ""
    , "\nUnit arg__1"
    , "Unit unit"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool collate"
    , "ColorMode arg__1"
    , "int arg__1"
    , "String arg__1"
    , "String arg__1"
    , "bool enable"
    , "DuplexMode duplex"
    , "bool enable"
    , "int fromPage, int toPage"
    , "bool arg__1"
    , "int arg__1"
    , "Orientation arg__1"
    , "String arg__1"
    , "OutputFormat format"
    , "qreal left, qreal top, qreal right, qreal bottom, Unit unit"
    , "PageOrder arg__1"
    , "QSizeF size"
    , "String paperName"
    , "QSizeF paperSize, Unit unit"
    , "PaperSource arg__1"
    , "String arg__1"
    , "PrintRange range"
    , "String arg__1"
    , "int arg__1"
    , "int winPageSize"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QPrinter_function_lengths[] = {
    2
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
    , 0
    , 0
    , 5
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
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
    , 5
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
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPrinter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPrinter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QtScriptShell_QPrinter*)
Q_DECLARE_METATYPE(QPrinter::Orientation)
Q_DECLARE_METATYPE(QPrinter::ColorMode)
Q_DECLARE_METATYPE(QPrinter::PrinterState)
Q_DECLARE_METATYPE(QPrinter::OutputFormat)
Q_DECLARE_METATYPE(QPrinter::PaperSource)
Q_DECLARE_METATYPE(QPrinter::PrintRange)
Q_DECLARE_METATYPE(QPrinter::PageOrder)
Q_DECLARE_METATYPE(QPrinter::Unit)
Q_DECLARE_METATYPE(QPrinter::PrinterMode)
Q_DECLARE_METATYPE(QPrinter::DuplexMode)
Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(QPaintEngine*)
Q_DECLARE_METATYPE(QPrintEngine*)
Q_DECLARE_METATYPE(QList<int >)
Q_DECLARE_METATYPE(QPrinterInfo)
Q_DECLARE_METATYPE(QPrinter::PageSize)

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
// QPrinter::Orientation
//

static const QPrinter::Orientation qtscript_QPrinter_Orientation_values[] = {
    QPrinter::Portrait
    , QPrinter::Landscape
};

static const char * const qtscript_QPrinter_Orientation_keys[] = {
    "Portrait"
    , "Landscape"
};

static QString qtscript_QPrinter_Orientation_toStringHelper(QPrinter::Orientation value)
{
    if ((value >= QPrinter::Portrait) && (value <= QPrinter::Landscape))
        return qtscript_QPrinter_Orientation_keys[static_cast<int>(value)-static_cast<int>(QPrinter::Portrait)];
    return QString();
}

static QScriptValue qtscript_QPrinter_Orientation_toScriptValue(QScriptEngine *engine, const QPrinter::Orientation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_Orientation_toStringHelper(value));
}

static void qtscript_QPrinter_Orientation_fromScriptValue(const QScriptValue &value, QPrinter::Orientation &out)
{
    out = qvariant_cast<QPrinter::Orientation>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_Orientation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::Portrait) && (arg <= QPrinter::Landscape))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::Orientation>(arg));
    return context->throwError(QString::fromLatin1("Orientation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_Orientation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::Orientation value = qscriptvalue_cast<QPrinter::Orientation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_Orientation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::Orientation value = qscriptvalue_cast<QPrinter::Orientation>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_Orientation_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_Orientation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_Orientation,
        qtscript_QPrinter_Orientation_valueOf, qtscript_QPrinter_Orientation_toString);
    qScriptRegisterMetaType<QPrinter::Orientation>(engine, qtscript_QPrinter_Orientation_toScriptValue,
        qtscript_QPrinter_Orientation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_Orientation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_Orientation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::ColorMode
//

static const QPrinter::ColorMode qtscript_QPrinter_ColorMode_values[] = {
    QPrinter::GrayScale
    , QPrinter::Color
};

static const char * const qtscript_QPrinter_ColorMode_keys[] = {
    "GrayScale"
    , "Color"
};

static QString qtscript_QPrinter_ColorMode_toStringHelper(QPrinter::ColorMode value)
{
    if ((value >= QPrinter::GrayScale) && (value <= QPrinter::Color))
        return qtscript_QPrinter_ColorMode_keys[static_cast<int>(value)-static_cast<int>(QPrinter::GrayScale)];
    return QString();
}

static QScriptValue qtscript_QPrinter_ColorMode_toScriptValue(QScriptEngine *engine, const QPrinter::ColorMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_ColorMode_toStringHelper(value));
}

static void qtscript_QPrinter_ColorMode_fromScriptValue(const QScriptValue &value, QPrinter::ColorMode &out)
{
    out = qvariant_cast<QPrinter::ColorMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_ColorMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::GrayScale) && (arg <= QPrinter::Color))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::ColorMode>(arg));
    return context->throwError(QString::fromLatin1("ColorMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_ColorMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::ColorMode value = qscriptvalue_cast<QPrinter::ColorMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_ColorMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::ColorMode value = qscriptvalue_cast<QPrinter::ColorMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_ColorMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_ColorMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_ColorMode,
        qtscript_QPrinter_ColorMode_valueOf, qtscript_QPrinter_ColorMode_toString);
    qScriptRegisterMetaType<QPrinter::ColorMode>(engine, qtscript_QPrinter_ColorMode_toScriptValue,
        qtscript_QPrinter_ColorMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_ColorMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_ColorMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::PrinterState
//

static const QPrinter::PrinterState qtscript_QPrinter_PrinterState_values[] = {
    QPrinter::Idle
    , QPrinter::Active
    , QPrinter::Aborted
    , QPrinter::Error
};

static const char * const qtscript_QPrinter_PrinterState_keys[] = {
    "Idle"
    , "Active"
    , "Aborted"
    , "Error"
};

static QString qtscript_QPrinter_PrinterState_toStringHelper(QPrinter::PrinterState value)
{
    if ((value >= QPrinter::Idle) && (value <= QPrinter::Error))
        return qtscript_QPrinter_PrinterState_keys[static_cast<int>(value)-static_cast<int>(QPrinter::Idle)];
    return QString();
}

static QScriptValue qtscript_QPrinter_PrinterState_toScriptValue(QScriptEngine *engine, const QPrinter::PrinterState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_PrinterState_toStringHelper(value));
}

static void qtscript_QPrinter_PrinterState_fromScriptValue(const QScriptValue &value, QPrinter::PrinterState &out)
{
    out = qvariant_cast<QPrinter::PrinterState>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_PrinterState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::Idle) && (arg <= QPrinter::Error))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::PrinterState>(arg));
    return context->throwError(QString::fromLatin1("PrinterState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_PrinterState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PrinterState value = qscriptvalue_cast<QPrinter::PrinterState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_PrinterState_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PrinterState value = qscriptvalue_cast<QPrinter::PrinterState>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_PrinterState_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_PrinterState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_PrinterState,
        qtscript_QPrinter_PrinterState_valueOf, qtscript_QPrinter_PrinterState_toString);
    qScriptRegisterMetaType<QPrinter::PrinterState>(engine, qtscript_QPrinter_PrinterState_toScriptValue,
        qtscript_QPrinter_PrinterState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_PrinterState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_PrinterState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::OutputFormat
//

static const QPrinter::OutputFormat qtscript_QPrinter_OutputFormat_values[] = {
    QPrinter::NativeFormat
    , QPrinter::PdfFormat
};

static const char * const qtscript_QPrinter_OutputFormat_keys[] = {
    "NativeFormat"
    , "PdfFormat"
};

static QString qtscript_QPrinter_OutputFormat_toStringHelper(QPrinter::OutputFormat value)
{
    if ((value >= QPrinter::NativeFormat) && (value <= QPrinter::PdfFormat))
        return qtscript_QPrinter_OutputFormat_keys[static_cast<int>(value)-static_cast<int>(QPrinter::NativeFormat)];
    return QString();
}

static QScriptValue qtscript_QPrinter_OutputFormat_toScriptValue(QScriptEngine *engine, const QPrinter::OutputFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_OutputFormat_toStringHelper(value));
}

static void qtscript_QPrinter_OutputFormat_fromScriptValue(const QScriptValue &value, QPrinter::OutputFormat &out)
{
    out = qvariant_cast<QPrinter::OutputFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_OutputFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::NativeFormat) && (arg <= QPrinter::PdfFormat))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::OutputFormat>(arg));
    return context->throwError(QString::fromLatin1("OutputFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_OutputFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::OutputFormat value = qscriptvalue_cast<QPrinter::OutputFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_OutputFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::OutputFormat value = qscriptvalue_cast<QPrinter::OutputFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_OutputFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_OutputFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_OutputFormat,
        qtscript_QPrinter_OutputFormat_valueOf, qtscript_QPrinter_OutputFormat_toString);
    qScriptRegisterMetaType<QPrinter::OutputFormat>(engine, qtscript_QPrinter_OutputFormat_toScriptValue,
        qtscript_QPrinter_OutputFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_OutputFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_OutputFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::PaperSource
//

static const QPrinter::PaperSource qtscript_QPrinter_PaperSource_values[] = {
    QPrinter::OnlyOne
    , QPrinter::Lower
    , QPrinter::Middle
    , QPrinter::Manual
    , QPrinter::Envelope
    , QPrinter::EnvelopeManual
    , QPrinter::Auto
    , QPrinter::Tractor
    , QPrinter::SmallFormat
    , QPrinter::LargeFormat
    , QPrinter::LargeCapacity
    , QPrinter::Cassette
    , QPrinter::FormSource
    , QPrinter::MaxPageSource
    , QPrinter::CustomSource
};

static const char * const qtscript_QPrinter_PaperSource_keys[] = {
    "OnlyOne"
    , "Lower"
    , "Middle"
    , "Manual"
    , "Envelope"
    , "EnvelopeManual"
    , "Auto"
    , "Tractor"
    , "SmallFormat"
    , "LargeFormat"
    , "LargeCapacity"
    , "Cassette"
    , "FormSource"
    , "MaxPageSource"
    , "CustomSource"
};

static QString qtscript_QPrinter_PaperSource_toStringHelper(QPrinter::PaperSource value)
{
    if ((value >= QPrinter::OnlyOne) && (value <= QPrinter::CustomSource))
        return qtscript_QPrinter_PaperSource_keys[static_cast<int>(value)-static_cast<int>(QPrinter::OnlyOne)];
    return QString();
}

static QScriptValue qtscript_QPrinter_PaperSource_toScriptValue(QScriptEngine *engine, const QPrinter::PaperSource &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_PaperSource_toStringHelper(value));
}

static void qtscript_QPrinter_PaperSource_fromScriptValue(const QScriptValue &value, QPrinter::PaperSource &out)
{
    out = qvariant_cast<QPrinter::PaperSource>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_PaperSource(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::OnlyOne) && (arg <= QPrinter::CustomSource))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::PaperSource>(arg));
    return context->throwError(QString::fromLatin1("PaperSource(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_PaperSource_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PaperSource value = qscriptvalue_cast<QPrinter::PaperSource>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_PaperSource_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PaperSource value = qscriptvalue_cast<QPrinter::PaperSource>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_PaperSource_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_PaperSource_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_PaperSource,
        qtscript_QPrinter_PaperSource_valueOf, qtscript_QPrinter_PaperSource_toString);
    qScriptRegisterMetaType<QPrinter::PaperSource>(engine, qtscript_QPrinter_PaperSource_toScriptValue,
        qtscript_QPrinter_PaperSource_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_PaperSource_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_PaperSource_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::PrintRange
//

static const QPrinter::PrintRange qtscript_QPrinter_PrintRange_values[] = {
    QPrinter::AllPages
    , QPrinter::Selection
    , QPrinter::PageRange
    , QPrinter::CurrentPage
};

static const char * const qtscript_QPrinter_PrintRange_keys[] = {
    "AllPages"
    , "Selection"
    , "PageRange"
    , "CurrentPage"
};

static QString qtscript_QPrinter_PrintRange_toStringHelper(QPrinter::PrintRange value)
{
    if ((value >= QPrinter::AllPages) && (value <= QPrinter::CurrentPage))
        return qtscript_QPrinter_PrintRange_keys[static_cast<int>(value)-static_cast<int>(QPrinter::AllPages)];
    return QString();
}

static QScriptValue qtscript_QPrinter_PrintRange_toScriptValue(QScriptEngine *engine, const QPrinter::PrintRange &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_PrintRange_toStringHelper(value));
}

static void qtscript_QPrinter_PrintRange_fromScriptValue(const QScriptValue &value, QPrinter::PrintRange &out)
{
    out = qvariant_cast<QPrinter::PrintRange>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_PrintRange(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::AllPages) && (arg <= QPrinter::CurrentPage))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::PrintRange>(arg));
    return context->throwError(QString::fromLatin1("PrintRange(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_PrintRange_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PrintRange value = qscriptvalue_cast<QPrinter::PrintRange>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_PrintRange_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PrintRange value = qscriptvalue_cast<QPrinter::PrintRange>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_PrintRange_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_PrintRange_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_PrintRange,
        qtscript_QPrinter_PrintRange_valueOf, qtscript_QPrinter_PrintRange_toString);
    qScriptRegisterMetaType<QPrinter::PrintRange>(engine, qtscript_QPrinter_PrintRange_toScriptValue,
        qtscript_QPrinter_PrintRange_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_PrintRange_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_PrintRange_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::PageOrder
//

static const QPrinter::PageOrder qtscript_QPrinter_PageOrder_values[] = {
    QPrinter::FirstPageFirst
    , QPrinter::LastPageFirst
};

static const char * const qtscript_QPrinter_PageOrder_keys[] = {
    "FirstPageFirst"
    , "LastPageFirst"
};

static QString qtscript_QPrinter_PageOrder_toStringHelper(QPrinter::PageOrder value)
{
    if ((value >= QPrinter::FirstPageFirst) && (value <= QPrinter::LastPageFirst))
        return qtscript_QPrinter_PageOrder_keys[static_cast<int>(value)-static_cast<int>(QPrinter::FirstPageFirst)];
    return QString();
}

static QScriptValue qtscript_QPrinter_PageOrder_toScriptValue(QScriptEngine *engine, const QPrinter::PageOrder &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_PageOrder_toStringHelper(value));
}

static void qtscript_QPrinter_PageOrder_fromScriptValue(const QScriptValue &value, QPrinter::PageOrder &out)
{
    out = qvariant_cast<QPrinter::PageOrder>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_PageOrder(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::FirstPageFirst) && (arg <= QPrinter::LastPageFirst))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::PageOrder>(arg));
    return context->throwError(QString::fromLatin1("PageOrder(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_PageOrder_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PageOrder value = qscriptvalue_cast<QPrinter::PageOrder>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_PageOrder_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PageOrder value = qscriptvalue_cast<QPrinter::PageOrder>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_PageOrder_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_PageOrder_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_PageOrder,
        qtscript_QPrinter_PageOrder_valueOf, qtscript_QPrinter_PageOrder_toString);
    qScriptRegisterMetaType<QPrinter::PageOrder>(engine, qtscript_QPrinter_PageOrder_toScriptValue,
        qtscript_QPrinter_PageOrder_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_PageOrder_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_PageOrder_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::Unit
//

static const QPrinter::Unit qtscript_QPrinter_Unit_values[] = {
    QPrinter::Millimeter
    , QPrinter::Point
    , QPrinter::Inch
    , QPrinter::Pica
    , QPrinter::Didot
    , QPrinter::Cicero
    , QPrinter::DevicePixel
};

static const char * const qtscript_QPrinter_Unit_keys[] = {
    "Millimeter"
    , "Point"
    , "Inch"
    , "Pica"
    , "Didot"
    , "Cicero"
    , "DevicePixel"
};

static QString qtscript_QPrinter_Unit_toStringHelper(QPrinter::Unit value)
{
    if ((value >= QPrinter::Millimeter) && (value <= QPrinter::DevicePixel))
        return qtscript_QPrinter_Unit_keys[static_cast<int>(value)-static_cast<int>(QPrinter::Millimeter)];
    return QString();
}

static QScriptValue qtscript_QPrinter_Unit_toScriptValue(QScriptEngine *engine, const QPrinter::Unit &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_Unit_toStringHelper(value));
}

static void qtscript_QPrinter_Unit_fromScriptValue(const QScriptValue &value, QPrinter::Unit &out)
{
    out = qvariant_cast<QPrinter::Unit>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_Unit(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::Millimeter) && (arg <= QPrinter::DevicePixel))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::Unit>(arg));
    return context->throwError(QString::fromLatin1("Unit(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_Unit_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::Unit value = qscriptvalue_cast<QPrinter::Unit>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_Unit_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::Unit value = qscriptvalue_cast<QPrinter::Unit>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_Unit_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_Unit_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_Unit,
        qtscript_QPrinter_Unit_valueOf, qtscript_QPrinter_Unit_toString);
    qScriptRegisterMetaType<QPrinter::Unit>(engine, qtscript_QPrinter_Unit_toScriptValue,
        qtscript_QPrinter_Unit_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_Unit_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_Unit_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::PrinterMode
//

static const QPrinter::PrinterMode qtscript_QPrinter_PrinterMode_values[] = {
    QPrinter::ScreenResolution
    , QPrinter::PrinterResolution
    , QPrinter::HighResolution
};

static const char * const qtscript_QPrinter_PrinterMode_keys[] = {
    "ScreenResolution"
    , "PrinterResolution"
    , "HighResolution"
};

static QString qtscript_QPrinter_PrinterMode_toStringHelper(QPrinter::PrinterMode value)
{
    if ((value >= QPrinter::ScreenResolution) && (value <= QPrinter::HighResolution))
        return qtscript_QPrinter_PrinterMode_keys[static_cast<int>(value)-static_cast<int>(QPrinter::ScreenResolution)];
    return QString();
}

static QScriptValue qtscript_QPrinter_PrinterMode_toScriptValue(QScriptEngine *engine, const QPrinter::PrinterMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_PrinterMode_toStringHelper(value));
}

static void qtscript_QPrinter_PrinterMode_fromScriptValue(const QScriptValue &value, QPrinter::PrinterMode &out)
{
    out = qvariant_cast<QPrinter::PrinterMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_PrinterMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::ScreenResolution) && (arg <= QPrinter::HighResolution))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::PrinterMode>(arg));
    return context->throwError(QString::fromLatin1("PrinterMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_PrinterMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PrinterMode value = qscriptvalue_cast<QPrinter::PrinterMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_PrinterMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::PrinterMode value = qscriptvalue_cast<QPrinter::PrinterMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_PrinterMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_PrinterMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_PrinterMode,
        qtscript_QPrinter_PrinterMode_valueOf, qtscript_QPrinter_PrinterMode_toString);
    qScriptRegisterMetaType<QPrinter::PrinterMode>(engine, qtscript_QPrinter_PrinterMode_toScriptValue,
        qtscript_QPrinter_PrinterMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_PrinterMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_PrinterMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter::DuplexMode
//

static const QPrinter::DuplexMode qtscript_QPrinter_DuplexMode_values[] = {
    QPrinter::DuplexNone
    , QPrinter::DuplexAuto
    , QPrinter::DuplexLongSide
    , QPrinter::DuplexShortSide
};

static const char * const qtscript_QPrinter_DuplexMode_keys[] = {
    "DuplexNone"
    , "DuplexAuto"
    , "DuplexLongSide"
    , "DuplexShortSide"
};

static QString qtscript_QPrinter_DuplexMode_toStringHelper(QPrinter::DuplexMode value)
{
    if ((value >= QPrinter::DuplexNone) && (value <= QPrinter::DuplexShortSide))
        return qtscript_QPrinter_DuplexMode_keys[static_cast<int>(value)-static_cast<int>(QPrinter::DuplexNone)];
    return QString();
}

static QScriptValue qtscript_QPrinter_DuplexMode_toScriptValue(QScriptEngine *engine, const QPrinter::DuplexMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrinter"));
    return clazz.property(qtscript_QPrinter_DuplexMode_toStringHelper(value));
}

static void qtscript_QPrinter_DuplexMode_fromScriptValue(const QScriptValue &value, QPrinter::DuplexMode &out)
{
    out = qvariant_cast<QPrinter::DuplexMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrinter_DuplexMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrinter::DuplexNone) && (arg <= QPrinter::DuplexShortSide))
        return qScriptValueFromValue(engine,  static_cast<QPrinter::DuplexMode>(arg));
    return context->throwError(QString::fromLatin1("DuplexMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrinter_DuplexMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::DuplexMode value = qscriptvalue_cast<QPrinter::DuplexMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrinter_DuplexMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrinter::DuplexMode value = qscriptvalue_cast<QPrinter::DuplexMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrinter_DuplexMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrinter_DuplexMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrinter_DuplexMode,
        qtscript_QPrinter_DuplexMode_valueOf, qtscript_QPrinter_DuplexMode_toString);
    qScriptRegisterMetaType<QPrinter::DuplexMode>(engine, qtscript_QPrinter_DuplexMode_toScriptValue,
        qtscript_QPrinter_DuplexMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrinter_DuplexMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrinter_DuplexMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrinter
//

static QScriptValue qtscript_QPrinter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 62;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPrinter* _q_self = qscriptvalue_cast<QPrinter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPrinter.%0(): this object is not a QPrinter")
            .arg(qtscript_QPrinter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->abort();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->actualNumCopies();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->collateCopies();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPrinter::ColorMode _q_result = _q_self->colorMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->copyCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->creator();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->devType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->docName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->doubleSidedPrinting();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QPrinter::DuplexMode _q_result = _q_self->duplex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontEmbeddingEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->fromPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fullPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 5) {
        qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
        qreal* _q_arg1 = qscriptvalue_cast<qreal*>(context->argument(1));
        qreal* _q_arg2 = qscriptvalue_cast<qreal*>(context->argument(2));
        qreal* _q_arg3 = qscriptvalue_cast<qreal*>(context->argument(3));
        QPrinter::Unit _q_arg4 = qscriptvalue_cast<QPrinter::Unit>(context->argument(4));
        _q_self->getPageMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->newPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->numCopies();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QPrinter::Orientation _q_result = _q_self->orientation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->outputFileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QPrinter::OutputFormat _q_result = _q_self->outputFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QPrinter::PageOrder _q_result = _q_self->pageOrder();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->pageRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QPrinter::Unit _q_arg0 = qscriptvalue_cast<QPrinter::Unit>(context->argument(0));
        QRectF _q_result = _q_self->pageRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QPaintEngine* _q_result = _q_self->paintEngine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->paperName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->paperRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QPrinter::Unit _q_arg0 = qscriptvalue_cast<QPrinter::Unit>(context->argument(0));
        QRectF _q_result = _q_self->paperRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QPrinter::Unit _q_arg0 = qscriptvalue_cast<QPrinter::Unit>(context->argument(0));
        QSizeF _q_result = _q_self->paperSize(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QPrinter::PaperSource _q_result = _q_self->paperSource();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QPrintEngine* _q_result = _q_self->printEngine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->printProgram();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QPrinter::PrintRange _q_result = _q_self->printRange();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->printerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QPrinter::PrinterState _q_result = _q_self->printerState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->resolution();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setCollateCopies(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QPrinter::ColorMode _q_arg0 = qscriptvalue_cast<QPrinter::ColorMode>(context->argument(0));
        _q_self->setColorMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setCopyCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setCreator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDocName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setDoubleSidedPrinting(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QPrinter::DuplexMode _q_arg0 = qscriptvalue_cast<QPrinter::DuplexMode>(context->argument(0));
        _q_self->setDuplex(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontEmbeddingEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setFromTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFullPage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setNumCopies(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QPrinter::Orientation _q_arg0 = qscriptvalue_cast<QPrinter::Orientation>(context->argument(0));
        _q_self->setOrientation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setOutputFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        QPrinter::OutputFormat _q_arg0 = qscriptvalue_cast<QPrinter::OutputFormat>(context->argument(0));
        _q_self->setOutputFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPrinter::Unit _q_arg4 = qscriptvalue_cast<QPrinter::Unit>(context->argument(4));
        _q_self->setPageMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        QPrinter::PageOrder _q_arg0 = qscriptvalue_cast<QPrinter::PageOrder>(context->argument(0));
        _q_self->setPageOrder(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setPageSizeMM(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPaperName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    // andrew: begin: fix call with one argument:
    if (context->argumentCount() == 1) {
        QPrinter::PageSize _q_arg0 = qscriptvalue_cast<QPrinter::PageSize>(context->argument(0));
        _q_self->setPaperSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    // andrew: end
    if (context->argumentCount() == 2) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        QPrinter::Unit _q_arg1 = qscriptvalue_cast<QPrinter::Unit>(context->argument(1));
        _q_self->setPaperSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QPrinter::PaperSource _q_arg0 = qscriptvalue_cast<QPrinter::PaperSource>(context->argument(0));
        _q_self->setPaperSource(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPrintProgram(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        QPrinter::PrintRange _q_arg0 = qscriptvalue_cast<QPrinter::PrintRange>(context->argument(0));
        _q_self->setPrintRange(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPrinterName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setResolution(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setWinPageSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        QList<int > _q_result = _q_self->supportedResolutions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 59:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->supportsMultipleCopies();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 60:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->toPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 61:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->winPageSize();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 62: {
    QString result = QString::fromLatin1("QPrinter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrinter_throw_ambiguity_error_helper(context,
        qtscript_QPrinter_function_names[_id+1],
        qtscript_QPrinter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPrinter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPrinter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPrinter* _q_cpp_result = new QtScriptShell_QPrinter();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPrinter*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPrinter::PrinterMode>() == context->argument(0).toVariant().userType())) {
            QPrinter::PrinterMode _q_arg0 = qscriptvalue_cast<QPrinter::PrinterMode>(context->argument(0));
            QtScriptShell_QPrinter* _q_cpp_result = new QtScriptShell_QPrinter(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPrinter*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPrinterInfo>() == context->argument(0).toVariant().userType())) {
            QPrinterInfo _q_arg0 = qscriptvalue_cast<QPrinterInfo>(context->argument(0));
            QtScriptShell_QPrinter* _q_cpp_result = new QtScriptShell_QPrinter(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPrinter*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QPrinterInfo _q_arg0 = qscriptvalue_cast<QPrinterInfo>(context->argument(0));
        QPrinter::PrinterMode _q_arg1 = qscriptvalue_cast<QPrinter::PrinterMode>(context->argument(1));
        QtScriptShell_QPrinter* _q_cpp_result = new QtScriptShell_QPrinter(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPrinter*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrinter_throw_ambiguity_error_helper(context,
        qtscript_QPrinter_function_names[_id],
        qtscript_QPrinter_function_signatures[_id]);
}

QScriptValue qtscript_create_QPrinter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPrinter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPrinter*)0));
    for (int i = 0; i < 63; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPrinter_prototype_call, qtscript_QPrinter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPrinter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPrinter*>(), proto);

    // andrew: begin
    // QPrinter derrived from QPagedPaintDevice:
    QScriptValue dpt = engine->defaultPrototype(qMetaTypeId<QPaintDevice*>());
    if (dpt.isValid()) {
        proto.setPrototype(dpt);
    }
    // andrew: end

    QScriptValue ctor = engine->newFunction(qtscript_QPrinter_static_call, proto, qtscript_QPrinter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Orientation"),
        qtscript_create_QPrinter_Orientation_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ColorMode"),
        qtscript_create_QPrinter_ColorMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PrinterState"),
        qtscript_create_QPrinter_PrinterState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("OutputFormat"),
        qtscript_create_QPrinter_OutputFormat_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PaperSource"),
        qtscript_create_QPrinter_PaperSource_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PrintRange"),
        qtscript_create_QPrinter_PrintRange_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PageOrder"),
        qtscript_create_QPrinter_PageOrder_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Unit"),
        qtscript_create_QPrinter_Unit_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PrinterMode"),
        qtscript_create_QPrinter_PrinterMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DuplexMode"),
        qtscript_create_QPrinter_DuplexMode_class(engine, ctor));
    return ctor;
}
