#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextformat.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qlist.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#include "qtscriptshell_QTextBlockFormat.h"

static const char * const qtscript_QTextBlockFormat_function_names[] = {
    "QTextBlockFormat"
    // static
    // prototype
    , "alignment"
    , "bottomMargin"
    , "indent"
    , "leftMargin"
    , "lineHeight"
    , "lineHeightType"
    , "nonBreakableLines"
    , "pageBreakPolicy"
    , "rightMargin"
    , "setAlignment"
    , "setBottomMargin"
    , "setIndent"
    , "setLeftMargin"
    , "setLineHeight"
    , "setNonBreakableLines"
    , "setPageBreakPolicy"
    , "setRightMargin"
    , "setTabPositions"
    , "setTextIndent"
    , "setTopMargin"
    , "tabPositions"
    , "textIndent"
    , "topMargin"
    , "toString"
};

static const char * const qtscript_QTextBlockFormat_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "\nqreal scriptLineHeight, qreal scaling"
    , ""
    , ""
    , ""
    , ""
    , "Alignment alignment"
    , "qreal margin"
    , "int indent"
    , "qreal margin"
    , "qreal height, int heightType"
    , "bool b"
    , "PageBreakFlags flags"
    , "qreal margin"
    , "List tabs"
    , "qreal aindent"
    , "qreal margin"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTextBlockFormat_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
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
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextBlockFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextBlockFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextBlockFormat)
Q_DECLARE_METATYPE(QTextBlockFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextBlockFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextBlockFormat*)
Q_DECLARE_METATYPE(QTextBlockFormat::LineHeightTypes)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QFlags<QTextFormat::PageBreakFlag>)
Q_DECLARE_METATYPE(QList<QTextOption::Tab >)
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
// QTextBlockFormat::LineHeightTypes
//

static const QTextBlockFormat::LineHeightTypes qtscript_QTextBlockFormat_LineHeightTypes_values[] = {
    QTextBlockFormat::SingleHeight
    , QTextBlockFormat::ProportionalHeight
    , QTextBlockFormat::FixedHeight
    , QTextBlockFormat::MinimumHeight
    , QTextBlockFormat::LineDistanceHeight
};

static const char * const qtscript_QTextBlockFormat_LineHeightTypes_keys[] = {
    "SingleHeight"
    , "ProportionalHeight"
    , "FixedHeight"
    , "MinimumHeight"
    , "LineDistanceHeight"
};

static QString qtscript_QTextBlockFormat_LineHeightTypes_toStringHelper(QTextBlockFormat::LineHeightTypes value)
{
    if ((value >= QTextBlockFormat::SingleHeight) && (value <= QTextBlockFormat::LineDistanceHeight))
        return qtscript_QTextBlockFormat_LineHeightTypes_keys[static_cast<int>(value)-static_cast<int>(QTextBlockFormat::SingleHeight)];
    return QString();
}

static QScriptValue qtscript_QTextBlockFormat_LineHeightTypes_toScriptValue(QScriptEngine *engine, const QTextBlockFormat::LineHeightTypes &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextBlockFormat"));
    return clazz.property(qtscript_QTextBlockFormat_LineHeightTypes_toStringHelper(value));
}

static void qtscript_QTextBlockFormat_LineHeightTypes_fromScriptValue(const QScriptValue &value, QTextBlockFormat::LineHeightTypes &out)
{
    out = qvariant_cast<QTextBlockFormat::LineHeightTypes>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextBlockFormat_LineHeightTypes(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextBlockFormat::SingleHeight) && (arg <= QTextBlockFormat::LineDistanceHeight))
        return qScriptValueFromValue(engine,  static_cast<QTextBlockFormat::LineHeightTypes>(arg));
    return context->throwError(QString::fromLatin1("LineHeightTypes(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextBlockFormat_LineHeightTypes_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextBlockFormat::LineHeightTypes value = qscriptvalue_cast<QTextBlockFormat::LineHeightTypes>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextBlockFormat_LineHeightTypes_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextBlockFormat::LineHeightTypes value = qscriptvalue_cast<QTextBlockFormat::LineHeightTypes>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextBlockFormat_LineHeightTypes_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextBlockFormat_LineHeightTypes_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextBlockFormat_LineHeightTypes,
        qtscript_QTextBlockFormat_LineHeightTypes_valueOf, qtscript_QTextBlockFormat_LineHeightTypes_toString);
    qScriptRegisterMetaType<QTextBlockFormat::LineHeightTypes>(engine, qtscript_QTextBlockFormat_LineHeightTypes_toScriptValue,
        qtscript_QTextBlockFormat_LineHeightTypes_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextBlockFormat_LineHeightTypes_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextBlockFormat_LineHeightTypes_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextBlockFormat
//

static QScriptValue qtscript_QTextBlockFormat_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 23;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextBlockFormat* _q_self = qscriptvalue_cast<QTextBlockFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextBlockFormat.%0(): this object is not a QTextBlockFormat")
            .arg(qtscript_QTextBlockFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::AlignmentFlag> _q_result = _q_self->alignment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->bottomMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->indent();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->leftMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->lineHeight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_result = _q_self->lineHeight(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lineHeightType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->nonBreakableLines();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QFlags<QTextFormat::PageBreakFlag> _q_result = _q_self->pageBreakPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->rightMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QFlags<Qt::AlignmentFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(0));
        _q_self->setAlignment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBottomMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIndent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setLeftMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setLineHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setNonBreakableLines(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QFlags<QTextFormat::PageBreakFlag> _q_arg0 = qscriptvalue_cast<QFlags<QTextFormat::PageBreakFlag> >(context->argument(0));
        _q_self->setPageBreakPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRightMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QList<QTextOption::Tab> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setTabPositions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setTextIndent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setTopMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QList<QTextOption::Tab > _q_result = _q_self->tabPositions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->textIndent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->topMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23: {
    QString result = QString::fromLatin1("QTextBlockFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBlockFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextBlockFormat_function_names[_id+1],
        qtscript_QTextBlockFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextBlockFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextBlockFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextBlockFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextBlockFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBlockFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextBlockFormat_function_names[_id],
        qtscript_QTextBlockFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextBlockFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextBlockFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextBlockFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextFormat*>()));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextBlockFormat_prototype_call, qtscript_QTextBlockFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextBlockFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextBlockFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextBlockFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextBlockFormat_static_call, proto, qtscript_QTextBlockFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("LineHeightTypes"),
        qtscript_create_QTextBlockFormat_LineHeightTypes_class(engine, ctor));
    return ctor;
}
