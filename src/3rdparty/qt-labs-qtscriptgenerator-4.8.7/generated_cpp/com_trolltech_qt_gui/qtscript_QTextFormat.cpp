#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextformat.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

static const char * const qtscript_QTextFormat_function_names[] = {
    "QTextFormat"
    // static
    // prototype
    , "background"
    , "boolProperty"
    , "brushProperty"
    , "clearBackground"
    , "clearForeground"
    , "clearProperty"
    , "colorProperty"
    , "doubleProperty"
    , "foreground"
    , "hasProperty"
    , "intProperty"
    , "isBlockFormat"
    , "isCharFormat"
    , "isFrameFormat"
    , "isImageFormat"
    , "isListFormat"
    , "isTableCellFormat"
    , "isTableFormat"
    , "isValid"
    , "layoutDirection"
    , "lengthProperty"
    , "lengthVectorProperty"
    , "merge"
    , "objectIndex"
    , "objectType"
    , "equals"
    , "penProperty"
    , "properties"
    , "property"
    , "propertyCount"
    , "readFrom"
    , "setBackground"
    , "setForeground"
    , "setLayoutDirection"
    , "setLengthVectorProperty"
    , "setObjectIndex"
    , "setObjectType"
    , "setProperty"
    , "stringProperty"
    , "toBlockFormat"
    , "toCharFormat"
    , "toFrameFormat"
    , "toImageFormat"
    , "toListFormat"
    , "toTableCellFormat"
    , "toTableFormat"
    , "type"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QTextFormat_function_signatures[] = {
    "\nQTextFormat rhs\nint type"
    // static
    // prototype
    , ""
    , "int propertyId"
    , "int propertyId"
    , ""
    , ""
    , "int propertyId"
    , "int propertyId"
    , "int propertyId"
    , ""
    , "int propertyId"
    , "int propertyId"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int propertyId"
    , "int propertyId"
    , "QTextFormat other"
    , ""
    , ""
    , "QTextFormat rhs"
    , "int propertyId"
    , ""
    , "int propertyId"
    , ""
    , "QDataStream arg__1"
    , "QBrush brush"
    , "QBrush brush"
    , "LayoutDirection direction"
    , "int propertyId, List lengths"
    , "int object"
    , "int type"
    , "int propertyId, Object value"
    , "int propertyId"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
""
};

static const int qtscript_QTextFormat_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
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
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTextFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QTextFormat_metaObject()
{
    return &QTextFormat::staticMetaObject;
}

Q_DECLARE_METATYPE(QTextFormat*)
Q_DECLARE_METATYPE(QTextFormat::Property)
Q_DECLARE_METATYPE(QTextFormat::FormatType)
Q_DECLARE_METATYPE(QTextFormat::ObjectTypes)
Q_DECLARE_METATYPE(QTextFormat::PageBreakFlag)
Q_DECLARE_METATYPE(QFlags<QTextFormat::PageBreakFlag>)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(QVector<QTextLength>)
template <> \
struct QMetaTypeId< QMap<int,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QMap<int,QVariant> >("QMap<int,QVariant>"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QTextBlockFormat)
Q_DECLARE_METATYPE(QTextCharFormat)
Q_DECLARE_METATYPE(QTextFrameFormat)
Q_DECLARE_METATYPE(QTextImageFormat)
Q_DECLARE_METATYPE(QTextListFormat)
Q_DECLARE_METATYPE(QTextTableCellFormat)
Q_DECLARE_METATYPE(QTextTableFormat)

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
// QTextFormat::Property
//

static const QTextFormat::Property qtscript_QTextFormat_Property_values[] = {
    QTextFormat::ObjectIndex
    , QTextFormat::CssFloat
    , QTextFormat::LayoutDirection
    , QTextFormat::OutlinePen
    , QTextFormat::BackgroundBrush
    , QTextFormat::ForegroundBrush
    , QTextFormat::BackgroundImageUrl
    , QTextFormat::BlockAlignment
    , QTextFormat::BlockTopMargin
    , QTextFormat::BlockBottomMargin
    , QTextFormat::BlockLeftMargin
    , QTextFormat::BlockRightMargin
    , QTextFormat::TextIndent
    , QTextFormat::TabPositions
    , QTextFormat::BlockIndent
    , QTextFormat::LineHeight
    , QTextFormat::LineHeightType
    , QTextFormat::BlockNonBreakableLines
    , QTextFormat::BlockTrailingHorizontalRulerWidth
    , QTextFormat::FirstFontProperty
    , QTextFormat::FontLetterSpacing
    , QTextFormat::FontWordSpacing
    , QTextFormat::FontStyleHint
    , QTextFormat::FontStyleStrategy
    , QTextFormat::FontKerning
    , QTextFormat::FontHintingPreference
    , QTextFormat::FontFamily
    , QTextFormat::FontPointSize
    , QTextFormat::FontSizeAdjustment
    , QTextFormat::FontWeight
    , QTextFormat::FontItalic
    , QTextFormat::FontUnderline
    , QTextFormat::FontOverline
    , QTextFormat::FontStrikeOut
    , QTextFormat::FontFixedPitch
    , QTextFormat::FontPixelSize
    , QTextFormat::TextUnderlineColor
    , QTextFormat::TextVerticalAlignment
    , QTextFormat::TextOutline
    , QTextFormat::TextUnderlineStyle
    , QTextFormat::TextToolTip
    , QTextFormat::IsAnchor
    , QTextFormat::AnchorHref
    , QTextFormat::AnchorName
    , QTextFormat::ObjectType
    , QTextFormat::ListStyle
    , QTextFormat::ListIndent
    , QTextFormat::ListNumberPrefix
    , QTextFormat::ListNumberSuffix
    , QTextFormat::FrameBorder
    , QTextFormat::FrameMargin
    , QTextFormat::FramePadding
    , QTextFormat::FrameWidth
    , QTextFormat::FrameHeight
    , QTextFormat::FrameTopMargin
    , QTextFormat::FrameBottomMargin
    , QTextFormat::FrameLeftMargin
    , QTextFormat::FrameRightMargin
    , QTextFormat::FrameBorderBrush
    , QTextFormat::FrameBorderStyle
    , QTextFormat::TableColumns
    , QTextFormat::TableColumnWidthConstraints
    , QTextFormat::TableCellSpacing
    , QTextFormat::TableCellPadding
    , QTextFormat::TableHeaderRowCount
    , QTextFormat::TableCellRowSpan
    , QTextFormat::TableCellColumnSpan
    , QTextFormat::TableCellTopPadding
    , QTextFormat::TableCellBottomPadding
    , QTextFormat::TableCellLeftPadding
    , QTextFormat::TableCellRightPadding
    , QTextFormat::ImageName
    , QTextFormat::ImageWidth
    , QTextFormat::ImageHeight
    , QTextFormat::FullWidthSelection
    , QTextFormat::PageBreakPolicy
    , QTextFormat::UserProperty
};

static const char * const qtscript_QTextFormat_Property_keys[] = {
    "ObjectIndex"
    , "CssFloat"
    , "LayoutDirection"
    , "OutlinePen"
    , "BackgroundBrush"
    , "ForegroundBrush"
    , "BackgroundImageUrl"
    , "BlockAlignment"
    , "BlockTopMargin"
    , "BlockBottomMargin"
    , "BlockLeftMargin"
    , "BlockRightMargin"
    , "TextIndent"
    , "TabPositions"
    , "BlockIndent"
    , "LineHeight"
    , "LineHeightType"
    , "BlockNonBreakableLines"
    , "BlockTrailingHorizontalRulerWidth"
    , "FirstFontProperty"
    , "FontLetterSpacing"
    , "FontWordSpacing"
    , "FontStyleHint"
    , "FontStyleStrategy"
    , "FontKerning"
    , "FontHintingPreference"
    , "FontFamily"
    , "FontPointSize"
    , "FontSizeAdjustment"
    , "FontWeight"
    , "FontItalic"
    , "FontUnderline"
    , "FontOverline"
    , "FontStrikeOut"
    , "FontFixedPitch"
    , "FontPixelSize"
    , "TextUnderlineColor"
    , "TextVerticalAlignment"
    , "TextOutline"
    , "TextUnderlineStyle"
    , "TextToolTip"
    , "IsAnchor"
    , "AnchorHref"
    , "AnchorName"
    , "ObjectType"
    , "ListStyle"
    , "ListIndent"
    , "ListNumberPrefix"
    , "ListNumberSuffix"
    , "FrameBorder"
    , "FrameMargin"
    , "FramePadding"
    , "FrameWidth"
    , "FrameHeight"
    , "FrameTopMargin"
    , "FrameBottomMargin"
    , "FrameLeftMargin"
    , "FrameRightMargin"
    , "FrameBorderBrush"
    , "FrameBorderStyle"
    , "TableColumns"
    , "TableColumnWidthConstraints"
    , "TableCellSpacing"
    , "TableCellPadding"
    , "TableHeaderRowCount"
    , "TableCellRowSpan"
    , "TableCellColumnSpan"
    , "TableCellTopPadding"
    , "TableCellBottomPadding"
    , "TableCellLeftPadding"
    , "TableCellRightPadding"
    , "ImageName"
    , "ImageWidth"
    , "ImageHeight"
    , "FullWidthSelection"
    , "PageBreakPolicy"
    , "UserProperty"
};

static QString qtscript_QTextFormat_Property_toStringHelper(QTextFormat::Property value)
{
    const QMetaObject *meta = qtscript_QTextFormat_metaObject();
    int idx = meta->indexOfEnumerator("Property");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTextFormat_Property_toScriptValue(QScriptEngine *engine, const QTextFormat::Property &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextFormat"));
    return clazz.property(qtscript_QTextFormat_Property_toStringHelper(value));
}

static void qtscript_QTextFormat_Property_fromScriptValue(const QScriptValue &value, QTextFormat::Property &out)
{
    out = qvariant_cast<QTextFormat::Property>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextFormat_Property(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTextFormat_metaObject();
    int idx = meta->indexOfEnumerator("Property");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTextFormat::Property>(arg));
    return context->throwError(QString::fromLatin1("Property(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextFormat_Property_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::Property value = qscriptvalue_cast<QTextFormat::Property>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFormat_Property_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::Property value = qscriptvalue_cast<QTextFormat::Property>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextFormat_Property_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextFormat_Property_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextFormat_Property,
        qtscript_QTextFormat_Property_valueOf, qtscript_QTextFormat_Property_toString);
    qScriptRegisterMetaType<QTextFormat::Property>(engine, qtscript_QTextFormat_Property_toScriptValue,
        qtscript_QTextFormat_Property_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 77; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextFormat_Property_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextFormat_Property_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextFormat::FormatType
//

static const QTextFormat::FormatType qtscript_QTextFormat_FormatType_values[] = {
    QTextFormat::InvalidFormat
    , QTextFormat::BlockFormat
    , QTextFormat::CharFormat
    , QTextFormat::ListFormat
    , QTextFormat::TableFormat
    , QTextFormat::FrameFormat
    , QTextFormat::UserFormat
};

static const char * const qtscript_QTextFormat_FormatType_keys[] = {
    "InvalidFormat"
    , "BlockFormat"
    , "CharFormat"
    , "ListFormat"
    , "TableFormat"
    , "FrameFormat"
    , "UserFormat"
};

static QString qtscript_QTextFormat_FormatType_toStringHelper(QTextFormat::FormatType value)
{
    const QMetaObject *meta = qtscript_QTextFormat_metaObject();
    int idx = meta->indexOfEnumerator("FormatType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTextFormat_FormatType_toScriptValue(QScriptEngine *engine, const QTextFormat::FormatType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextFormat"));
    return clazz.property(qtscript_QTextFormat_FormatType_toStringHelper(value));
}

static void qtscript_QTextFormat_FormatType_fromScriptValue(const QScriptValue &value, QTextFormat::FormatType &out)
{
    out = qvariant_cast<QTextFormat::FormatType>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextFormat_FormatType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTextFormat_metaObject();
    int idx = meta->indexOfEnumerator("FormatType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTextFormat::FormatType>(arg));
    return context->throwError(QString::fromLatin1("FormatType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextFormat_FormatType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::FormatType value = qscriptvalue_cast<QTextFormat::FormatType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFormat_FormatType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::FormatType value = qscriptvalue_cast<QTextFormat::FormatType>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextFormat_FormatType_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextFormat_FormatType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextFormat_FormatType,
        qtscript_QTextFormat_FormatType_valueOf, qtscript_QTextFormat_FormatType_toString);
    qScriptRegisterMetaType<QTextFormat::FormatType>(engine, qtscript_QTextFormat_FormatType_toScriptValue,
        qtscript_QTextFormat_FormatType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextFormat_FormatType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextFormat_FormatType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextFormat::ObjectTypes
//

static const QTextFormat::ObjectTypes qtscript_QTextFormat_ObjectTypes_values[] = {
    QTextFormat::NoObject
    , QTextFormat::ImageObject
    , QTextFormat::TableObject
    , QTextFormat::TableCellObject
    , QTextFormat::UserObject
};

static const char * const qtscript_QTextFormat_ObjectTypes_keys[] = {
    "NoObject"
    , "ImageObject"
    , "TableObject"
    , "TableCellObject"
    , "UserObject"
};

static QString qtscript_QTextFormat_ObjectTypes_toStringHelper(QTextFormat::ObjectTypes value)
{
    const QMetaObject *meta = qtscript_QTextFormat_metaObject();
    int idx = meta->indexOfEnumerator("ObjectTypes");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTextFormat_ObjectTypes_toScriptValue(QScriptEngine *engine, const QTextFormat::ObjectTypes &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextFormat"));
    return clazz.property(qtscript_QTextFormat_ObjectTypes_toStringHelper(value));
}

static void qtscript_QTextFormat_ObjectTypes_fromScriptValue(const QScriptValue &value, QTextFormat::ObjectTypes &out)
{
    out = qvariant_cast<QTextFormat::ObjectTypes>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextFormat_ObjectTypes(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTextFormat_metaObject();
    int idx = meta->indexOfEnumerator("ObjectTypes");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTextFormat::ObjectTypes>(arg));
    return context->throwError(QString::fromLatin1("ObjectTypes(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextFormat_ObjectTypes_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::ObjectTypes value = qscriptvalue_cast<QTextFormat::ObjectTypes>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFormat_ObjectTypes_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::ObjectTypes value = qscriptvalue_cast<QTextFormat::ObjectTypes>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextFormat_ObjectTypes_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextFormat_ObjectTypes_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextFormat_ObjectTypes,
        qtscript_QTextFormat_ObjectTypes_valueOf, qtscript_QTextFormat_ObjectTypes_toString);
    qScriptRegisterMetaType<QTextFormat::ObjectTypes>(engine, qtscript_QTextFormat_ObjectTypes_toScriptValue,
        qtscript_QTextFormat_ObjectTypes_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextFormat_ObjectTypes_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextFormat_ObjectTypes_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextFormat::PageBreakFlag
//

static const QTextFormat::PageBreakFlag qtscript_QTextFormat_PageBreakFlag_values[] = {
    QTextFormat::PageBreak_Auto
    , QTextFormat::PageBreak_AlwaysBefore
    , QTextFormat::PageBreak_AlwaysAfter
};

static const char * const qtscript_QTextFormat_PageBreakFlag_keys[] = {
    "PageBreak_Auto"
    , "PageBreak_AlwaysBefore"
    , "PageBreak_AlwaysAfter"
};

static QString qtscript_QTextFormat_PageBreakFlag_toStringHelper(QTextFormat::PageBreakFlag value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QTextFormat_PageBreakFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QTextFormat_PageBreakFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTextFormat_PageBreakFlag_toScriptValue(QScriptEngine *engine, const QTextFormat::PageBreakFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextFormat"));
    return clazz.property(qtscript_QTextFormat_PageBreakFlag_toStringHelper(value));
}

static void qtscript_QTextFormat_PageBreakFlag_fromScriptValue(const QScriptValue &value, QTextFormat::PageBreakFlag &out)
{
    out = qvariant_cast<QTextFormat::PageBreakFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextFormat_PageBreakFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QTextFormat_PageBreakFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTextFormat::PageBreakFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("PageBreakFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextFormat_PageBreakFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::PageBreakFlag value = qscriptvalue_cast<QTextFormat::PageBreakFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFormat_PageBreakFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::PageBreakFlag value = qscriptvalue_cast<QTextFormat::PageBreakFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextFormat_PageBreakFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextFormat_PageBreakFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextFormat_PageBreakFlag,
        qtscript_QTextFormat_PageBreakFlag_valueOf, qtscript_QTextFormat_PageBreakFlag_toString);
    qScriptRegisterMetaType<QTextFormat::PageBreakFlag>(engine, qtscript_QTextFormat_PageBreakFlag_toScriptValue,
        qtscript_QTextFormat_PageBreakFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextFormat_PageBreakFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextFormat_PageBreakFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextFormat::PageBreakFlags
//

static QScriptValue qtscript_QTextFormat_PageBreakFlags_toScriptValue(QScriptEngine *engine, const QTextFormat::PageBreakFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QTextFormat_PageBreakFlags_fromScriptValue(const QScriptValue &value, QTextFormat::PageBreakFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QTextFormat::PageBreakFlags>())
        out = qvariant_cast<QTextFormat::PageBreakFlags>(var);
    else if (var.userType() == qMetaTypeId<QTextFormat::PageBreakFlag>())
        out = qvariant_cast<QTextFormat::PageBreakFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QTextFormat_PageBreakFlags(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::PageBreakFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QTextFormat::PageBreakFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QTextFormat::PageBreakFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("PageBreakFlags(): argument %0 is not of type PageBreakFlag").arg(i));
            }
            result |= qvariant_cast<QTextFormat::PageBreakFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QTextFormat_PageBreakFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::PageBreakFlags value = qscriptvalue_cast<QTextFormat::PageBreakFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFormat_PageBreakFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFormat::PageBreakFlags value = qscriptvalue_cast<QTextFormat::PageBreakFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QTextFormat_PageBreakFlag_values[i]) == qtscript_QTextFormat_PageBreakFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QTextFormat_PageBreakFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QTextFormat_PageBreakFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QTextFormat::PageBreakFlags>() == otherObj.value<QTextFormat::PageBreakFlags>())));
}

static QScriptValue qtscript_create_QTextFormat_PageBreakFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QTextFormat_PageBreakFlags, qtscript_QTextFormat_PageBreakFlags_valueOf,
        qtscript_QTextFormat_PageBreakFlags_toString, qtscript_QTextFormat_PageBreakFlags_equals);
    qScriptRegisterMetaType<QTextFormat::PageBreakFlags>(engine, qtscript_QTextFormat_PageBreakFlags_toScriptValue,
        qtscript_QTextFormat_PageBreakFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QTextFormat
//

static QScriptValue qtscript_QTextFormat_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 48;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextFormat* _q_self = qscriptvalue_cast<QTextFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextFormat.%0(): this object is not a QTextFormat")
            .arg(qtscript_QTextFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->background();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->boolProperty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QBrush _q_result = _q_self->brushProperty(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clearBackground();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->clearForeground();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->clearProperty(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QColor _q_result = _q_self->colorProperty(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->doubleProperty(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->foreground();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->hasProperty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->intProperty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isBlockFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCharFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFrameFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isImageFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isListFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTableCellFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTableFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        Qt::LayoutDirection _q_result = _q_self->layoutDirection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextLength _q_result = _q_self->lengthProperty(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector<QTextLength> _q_result = _q_self->lengthVectorProperty(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QTextFormat _q_arg0 = qscriptvalue_cast<QTextFormat>(context->argument(0));
        _q_self->merge(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->objectIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->objectType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QTextFormat _q_arg0 = qscriptvalue_cast<QTextFormat>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPen _q_result = _q_self->penProperty(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QMap<int,QVariant> _q_result = _q_self->properties();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->property(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->propertyCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBackground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setForeground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        Qt::LayoutDirection _q_arg0 = qscriptvalue_cast<Qt::LayoutDirection>(context->argument(0));
        _q_self->setLayoutDirection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector<QTextLength> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->setProperty(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setObjectIndex(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setObjectType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setProperty(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->stringProperty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 0) {
        QTextBlockFormat _q_result = _q_self->toBlockFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->toCharFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QTextFrameFormat _q_result = _q_self->toFrameFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        QTextImageFormat _q_result = _q_self->toImageFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        QTextListFormat _q_result = _q_self->toListFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        QTextTableCellFormat _q_result = _q_self->toTableCellFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 0) {
        QTextTableFormat _q_result = _q_self->toTableFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->type();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 48: {
    QString result = QString::fromLatin1("QTextFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextFormat_function_names[_id+1],
        qtscript_QTextFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextFormat(): Did you forget to construct with 'new'?"));
    }

    if ((context->argumentCount() == 1) && (qMetaTypeId<QTextFormat>() == context->argument(0).toVariant().userType())) {
        QTextFormat _q_arg0 = qscriptvalue_cast<QTextFormat>(context->argument(0));
        QTextFormat _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    
    if (context->argumentCount() == 0) {
        QTextFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextFormat>() == context->argument(0).toVariant().userType())) {
            QTextFormat _q_arg0 = qscriptvalue_cast<QTextFormat>(context->argument(0));
            QTextFormat _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QTextFormat _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextFormat_function_names[_id],
        qtscript_QTextFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextFormat*)0));
    for (int i = 0; i < 49; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextFormat_prototype_call, qtscript_QTextFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextFormat_static_call, proto, qtscript_QTextFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Property"),
        qtscript_create_QTextFormat_Property_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FormatType"),
        qtscript_create_QTextFormat_FormatType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ObjectTypes"),
        qtscript_create_QTextFormat_ObjectTypes_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PageBreakFlag"),
        qtscript_create_QTextFormat_PageBreakFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PageBreakFlags"),
        qtscript_create_QTextFormat_PageBreakFlags_class(engine));
    return ctor;
}
