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
#include <qfont.h>
#include <qpen.h>
#include <qstringlist.h>
#include <qtextformat.h>
#include <qvector.h>

#include "qtscriptshell_QTextCharFormat.h"

static const char * const qtscript_QTextCharFormat_function_names[] = {
    "QTextCharFormat"
    // static
    // prototype
    , "anchorHref"
    , "anchorNames"
    , "font"
    , "fontCapitalization"
    , "fontFamily"
    , "fontFixedPitch"
    , "fontItalic"
    , "fontKerning"
    , "fontLetterSpacing"
    , "fontOverline"
    , "fontPointSize"
    , "fontStrikeOut"
    , "fontStyleHint"
    , "fontStyleStrategy"
    , "fontUnderline"
    , "fontWeight"
    , "fontWordSpacing"
    , "isAnchor"
    , "setAnchor"
    , "setAnchorHref"
    , "setAnchorNames"
    , "setFont"
    , "setFontCapitalization"
    , "setFontFamily"
    , "setFontFixedPitch"
    , "setFontItalic"
    , "setFontKerning"
    , "setFontLetterSpacing"
    , "setFontOverline"
    , "setFontPointSize"
    , "setFontStrikeOut"
    , "setFontStyleHint"
    , "setFontStyleStrategy"
    , "setFontUnderline"
    , "setFontWeight"
    , "setFontWordSpacing"
    , "setTableCellColumnSpan"
    , "setTableCellRowSpan"
    , "setTextOutline"
    , "setToolTip"
    , "setUnderlineColor"
    , "setUnderlineStyle"
    , "setVerticalAlignment"
    , "tableCellColumnSpan"
    , "tableCellRowSpan"
    , "textOutline"
    , "toolTip"
    , "underlineColor"
    , "underlineStyle"
    , "verticalAlignment"
    , "toString"
};

static const char * const qtscript_QTextCharFormat_function_signatures[] = {
    ""
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
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool anchor"
    , "String value"
    , "List names"
    , "QFont font"
    , "Capitalization capitalization"
    , "String family"
    , "bool fixedPitch"
    , "bool italic"
    , "bool enable"
    , "qreal spacing"
    , "bool overline"
    , "qreal size"
    , "bool strikeOut"
    , "StyleHint hint, StyleStrategy strategy"
    , "StyleStrategy strategy"
    , "bool underline"
    , "int weight"
    , "qreal spacing"
    , "int tableCellColumnSpan"
    , "int tableCellRowSpan"
    , "QPen pen"
    , "String tip"
    , "QColor color"
    , "UnderlineStyle style"
    , "VerticalAlignment alignment"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTextCharFormat_function_lengths[] = {
    0
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
};

static QScriptValue qtscript_QTextCharFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextCharFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextCharFormat)
Q_DECLARE_METATYPE(QTextCharFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextCharFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextCharFormat*)
Q_DECLARE_METATYPE(QTextCharFormat::VerticalAlignment)
Q_DECLARE_METATYPE(QTextCharFormat::UnderlineStyle)
Q_DECLARE_METATYPE(QFont::Capitalization)
Q_DECLARE_METATYPE(QFont::StyleHint)
Q_DECLARE_METATYPE(QFont::StyleStrategy)
Q_DECLARE_METATYPE(QTextFormat*)

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
// QTextCharFormat::VerticalAlignment
//

static const QTextCharFormat::VerticalAlignment qtscript_QTextCharFormat_VerticalAlignment_values[] = {
    QTextCharFormat::AlignNormal
    , QTextCharFormat::AlignSuperScript
    , QTextCharFormat::AlignSubScript
    , QTextCharFormat::AlignMiddle
    , QTextCharFormat::AlignTop
    , QTextCharFormat::AlignBottom
    , QTextCharFormat::AlignBaseline
};

static const char * const qtscript_QTextCharFormat_VerticalAlignment_keys[] = {
    "AlignNormal"
    , "AlignSuperScript"
    , "AlignSubScript"
    , "AlignMiddle"
    , "AlignTop"
    , "AlignBottom"
    , "AlignBaseline"
};

static QString qtscript_QTextCharFormat_VerticalAlignment_toStringHelper(QTextCharFormat::VerticalAlignment value)
{
    if ((value >= QTextCharFormat::AlignNormal) && (value <= QTextCharFormat::AlignBaseline))
        return qtscript_QTextCharFormat_VerticalAlignment_keys[static_cast<int>(value)-static_cast<int>(QTextCharFormat::AlignNormal)];
    return QString();
}

static QScriptValue qtscript_QTextCharFormat_VerticalAlignment_toScriptValue(QScriptEngine *engine, const QTextCharFormat::VerticalAlignment &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextCharFormat"));
    return clazz.property(qtscript_QTextCharFormat_VerticalAlignment_toStringHelper(value));
}

static void qtscript_QTextCharFormat_VerticalAlignment_fromScriptValue(const QScriptValue &value, QTextCharFormat::VerticalAlignment &out)
{
    out = qvariant_cast<QTextCharFormat::VerticalAlignment>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextCharFormat_VerticalAlignment(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextCharFormat::AlignNormal) && (arg <= QTextCharFormat::AlignBaseline))
        return qScriptValueFromValue(engine,  static_cast<QTextCharFormat::VerticalAlignment>(arg));
    return context->throwError(QString::fromLatin1("VerticalAlignment(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextCharFormat_VerticalAlignment_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCharFormat::VerticalAlignment value = qscriptvalue_cast<QTextCharFormat::VerticalAlignment>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCharFormat_VerticalAlignment_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCharFormat::VerticalAlignment value = qscriptvalue_cast<QTextCharFormat::VerticalAlignment>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextCharFormat_VerticalAlignment_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextCharFormat_VerticalAlignment_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextCharFormat_VerticalAlignment,
        qtscript_QTextCharFormat_VerticalAlignment_valueOf, qtscript_QTextCharFormat_VerticalAlignment_toString);
    qScriptRegisterMetaType<QTextCharFormat::VerticalAlignment>(engine, qtscript_QTextCharFormat_VerticalAlignment_toScriptValue,
        qtscript_QTextCharFormat_VerticalAlignment_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextCharFormat_VerticalAlignment_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextCharFormat_VerticalAlignment_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextCharFormat::UnderlineStyle
//

static const QTextCharFormat::UnderlineStyle qtscript_QTextCharFormat_UnderlineStyle_values[] = {
    QTextCharFormat::NoUnderline
    , QTextCharFormat::SingleUnderline
    , QTextCharFormat::DashUnderline
    , QTextCharFormat::DotLine
    , QTextCharFormat::DashDotLine
    , QTextCharFormat::DashDotDotLine
    , QTextCharFormat::WaveUnderline
    , QTextCharFormat::SpellCheckUnderline
};

static const char * const qtscript_QTextCharFormat_UnderlineStyle_keys[] = {
    "NoUnderline"
    , "SingleUnderline"
    , "DashUnderline"
    , "DotLine"
    , "DashDotLine"
    , "DashDotDotLine"
    , "WaveUnderline"
    , "SpellCheckUnderline"
};

static QString qtscript_QTextCharFormat_UnderlineStyle_toStringHelper(QTextCharFormat::UnderlineStyle value)
{
    if ((value >= QTextCharFormat::NoUnderline) && (value <= QTextCharFormat::SpellCheckUnderline))
        return qtscript_QTextCharFormat_UnderlineStyle_keys[static_cast<int>(value)-static_cast<int>(QTextCharFormat::NoUnderline)];
    return QString();
}

static QScriptValue qtscript_QTextCharFormat_UnderlineStyle_toScriptValue(QScriptEngine *engine, const QTextCharFormat::UnderlineStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextCharFormat"));
    return clazz.property(qtscript_QTextCharFormat_UnderlineStyle_toStringHelper(value));
}

static void qtscript_QTextCharFormat_UnderlineStyle_fromScriptValue(const QScriptValue &value, QTextCharFormat::UnderlineStyle &out)
{
    out = qvariant_cast<QTextCharFormat::UnderlineStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextCharFormat_UnderlineStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextCharFormat::NoUnderline) && (arg <= QTextCharFormat::SpellCheckUnderline))
        return qScriptValueFromValue(engine,  static_cast<QTextCharFormat::UnderlineStyle>(arg));
    return context->throwError(QString::fromLatin1("UnderlineStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextCharFormat_UnderlineStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCharFormat::UnderlineStyle value = qscriptvalue_cast<QTextCharFormat::UnderlineStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCharFormat_UnderlineStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCharFormat::UnderlineStyle value = qscriptvalue_cast<QTextCharFormat::UnderlineStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextCharFormat_UnderlineStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextCharFormat_UnderlineStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextCharFormat_UnderlineStyle,
        qtscript_QTextCharFormat_UnderlineStyle_valueOf, qtscript_QTextCharFormat_UnderlineStyle_toString);
    qScriptRegisterMetaType<QTextCharFormat::UnderlineStyle>(engine, qtscript_QTextCharFormat_UnderlineStyle_toScriptValue,
        qtscript_QTextCharFormat_UnderlineStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextCharFormat_UnderlineStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextCharFormat_UnderlineStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextCharFormat
//

static QScriptValue qtscript_QTextCharFormat_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 50;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextCharFormat* _q_self = qscriptvalue_cast<QTextCharFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextCharFormat.%0(): this object is not a QTextCharFormat")
            .arg(qtscript_QTextCharFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->anchorHref();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->anchorNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFont::Capitalization _q_result = _q_self->fontCapitalization();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fontFamily();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontFixedPitch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontItalic();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontKerning();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->fontLetterSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontOverline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->fontPointSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontStrikeOut();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QFont::StyleHint _q_result = _q_self->fontStyleHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QFont::StyleStrategy _q_result = _q_self->fontStyleStrategy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontUnderline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->fontWeight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->fontWordSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAnchor();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAnchor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setAnchorHref(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setAnchorNames(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QFont::Capitalization _q_arg0 = qscriptvalue_cast<QFont::Capitalization>(context->argument(0));
        _q_self->setFontCapitalization(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFontFamily(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontFixedPitch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontItalic(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontKerning(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setFontLetterSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontOverline(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setFontPointSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontStrikeOut(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QFont::StyleHint _q_arg0 = qscriptvalue_cast<QFont::StyleHint>(context->argument(0));
        _q_self->setFontStyleHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QFont::StyleHint _q_arg0 = qscriptvalue_cast<QFont::StyleHint>(context->argument(0));
        QFont::StyleStrategy _q_arg1 = qscriptvalue_cast<QFont::StyleStrategy>(context->argument(1));
        _q_self->setFontStyleHint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QFont::StyleStrategy _q_arg0 = qscriptvalue_cast<QFont::StyleStrategy>(context->argument(0));
        _q_self->setFontStyleStrategy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFontUnderline(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setFontWeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setFontWordSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTableCellColumnSpan(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTableCellRowSpan(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QPen _q_arg0 = qscriptvalue_cast<QPen>(context->argument(0));
        _q_self->setTextOutline(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setToolTip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->setUnderlineColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QTextCharFormat::UnderlineStyle _q_arg0 = qscriptvalue_cast<QTextCharFormat::UnderlineStyle>(context->argument(0));
        _q_self->setUnderlineStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QTextCharFormat::VerticalAlignment _q_arg0 = qscriptvalue_cast<QTextCharFormat::VerticalAlignment>(context->argument(0));
        _q_self->setVerticalAlignment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->tableCellColumnSpan();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->tableCellRowSpan();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 0) {
        QPen _q_result = _q_self->textOutline();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toolTip();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->underlineColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QTextCharFormat::UnderlineStyle _q_result = _q_self->underlineStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QTextCharFormat::VerticalAlignment _q_result = _q_self->verticalAlignment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50: {
    QString result = QString::fromLatin1("QTextCharFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextCharFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextCharFormat_function_names[_id+1],
        qtscript_QTextCharFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextCharFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextCharFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextCharFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextCharFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextCharFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextCharFormat_function_names[_id],
        qtscript_QTextCharFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextCharFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextCharFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextCharFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextFormat*>()));
    for (int i = 0; i < 51; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextCharFormat_prototype_call, qtscript_QTextCharFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextCharFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextCharFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextCharFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextCharFormat_static_call, proto, qtscript_QTextCharFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("VerticalAlignment"),
        qtscript_create_QTextCharFormat_VerticalAlignment_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("UnderlineStyle"),
        qtscript_create_QTextCharFormat_UnderlineStyle_class(engine, ctor));
    return ctor;
}
