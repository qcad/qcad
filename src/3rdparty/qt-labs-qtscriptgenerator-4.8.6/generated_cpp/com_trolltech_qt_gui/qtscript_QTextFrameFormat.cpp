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
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#include "qtscriptshell_QTextFrameFormat.h"

static const char * const qtscript_QTextFrameFormat_function_names[] = {
    "QTextFrameFormat"
    // static
    // prototype
    , "border"
    , "borderBrush"
    , "borderStyle"
    , "bottomMargin"
    , "height"
    , "leftMargin"
    , "margin"
    , "padding"
    , "pageBreakPolicy"
    , "position"
    , "rightMargin"
    , "setBorder"
    , "setBorderBrush"
    , "setBorderStyle"
    , "setBottomMargin"
    , "setHeight"
    , "setLeftMargin"
    , "setMargin"
    , "setPadding"
    , "setPageBreakPolicy"
    , "setPosition"
    , "setRightMargin"
    , "setTopMargin"
    , "setWidth"
    , "topMargin"
    , "width"
    , "toString"
};

static const char * const qtscript_QTextFrameFormat_function_signatures[] = {
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
    , "qreal border"
    , "QBrush brush"
    , "BorderStyle style"
    , "qreal margin"
    , "QTextLength height\nqreal height"
    , "qreal margin"
    , "qreal margin"
    , "qreal padding"
    , "PageBreakFlags flags"
    , "Position f"
    , "qreal margin"
    , "qreal margin"
    , "QTextLength length\nqreal width"
    , ""
    , ""
""
};

static const int qtscript_QTextFrameFormat_function_lengths[] = {
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
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextFrameFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextFrameFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextFrameFormat)
Q_DECLARE_METATYPE(QTextFrameFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextFrameFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextFrameFormat*)
Q_DECLARE_METATYPE(QTextFrameFormat::Position)
Q_DECLARE_METATYPE(QTextFrameFormat::BorderStyle)
Q_DECLARE_METATYPE(QFlags<QTextFormat::PageBreakFlag>)
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
// QTextFrameFormat::Position
//

static const QTextFrameFormat::Position qtscript_QTextFrameFormat_Position_values[] = {
    QTextFrameFormat::InFlow
    , QTextFrameFormat::FloatLeft
    , QTextFrameFormat::FloatRight
};

static const char * const qtscript_QTextFrameFormat_Position_keys[] = {
    "InFlow"
    , "FloatLeft"
    , "FloatRight"
};

static QString qtscript_QTextFrameFormat_Position_toStringHelper(QTextFrameFormat::Position value)
{
    if ((value >= QTextFrameFormat::InFlow) && (value <= QTextFrameFormat::FloatRight))
        return qtscript_QTextFrameFormat_Position_keys[static_cast<int>(value)-static_cast<int>(QTextFrameFormat::InFlow)];
    return QString();
}

static QScriptValue qtscript_QTextFrameFormat_Position_toScriptValue(QScriptEngine *engine, const QTextFrameFormat::Position &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextFrameFormat"));
    return clazz.property(qtscript_QTextFrameFormat_Position_toStringHelper(value));
}

static void qtscript_QTextFrameFormat_Position_fromScriptValue(const QScriptValue &value, QTextFrameFormat::Position &out)
{
    out = qvariant_cast<QTextFrameFormat::Position>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextFrameFormat_Position(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextFrameFormat::InFlow) && (arg <= QTextFrameFormat::FloatRight))
        return qScriptValueFromValue(engine,  static_cast<QTextFrameFormat::Position>(arg));
    return context->throwError(QString::fromLatin1("Position(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextFrameFormat_Position_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFrameFormat::Position value = qscriptvalue_cast<QTextFrameFormat::Position>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFrameFormat_Position_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFrameFormat::Position value = qscriptvalue_cast<QTextFrameFormat::Position>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextFrameFormat_Position_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextFrameFormat_Position_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextFrameFormat_Position,
        qtscript_QTextFrameFormat_Position_valueOf, qtscript_QTextFrameFormat_Position_toString);
    qScriptRegisterMetaType<QTextFrameFormat::Position>(engine, qtscript_QTextFrameFormat_Position_toScriptValue,
        qtscript_QTextFrameFormat_Position_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextFrameFormat_Position_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextFrameFormat_Position_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextFrameFormat::BorderStyle
//

static const QTextFrameFormat::BorderStyle qtscript_QTextFrameFormat_BorderStyle_values[] = {
    QTextFrameFormat::BorderStyle_None
    , QTextFrameFormat::BorderStyle_Dotted
    , QTextFrameFormat::BorderStyle_Dashed
    , QTextFrameFormat::BorderStyle_Solid
    , QTextFrameFormat::BorderStyle_Double
    , QTextFrameFormat::BorderStyle_DotDash
    , QTextFrameFormat::BorderStyle_DotDotDash
    , QTextFrameFormat::BorderStyle_Groove
    , QTextFrameFormat::BorderStyle_Ridge
    , QTextFrameFormat::BorderStyle_Inset
    , QTextFrameFormat::BorderStyle_Outset
};

static const char * const qtscript_QTextFrameFormat_BorderStyle_keys[] = {
    "BorderStyle_None"
    , "BorderStyle_Dotted"
    , "BorderStyle_Dashed"
    , "BorderStyle_Solid"
    , "BorderStyle_Double"
    , "BorderStyle_DotDash"
    , "BorderStyle_DotDotDash"
    , "BorderStyle_Groove"
    , "BorderStyle_Ridge"
    , "BorderStyle_Inset"
    , "BorderStyle_Outset"
};

static QString qtscript_QTextFrameFormat_BorderStyle_toStringHelper(QTextFrameFormat::BorderStyle value)
{
    if ((value >= QTextFrameFormat::BorderStyle_None) && (value <= QTextFrameFormat::BorderStyle_Outset))
        return qtscript_QTextFrameFormat_BorderStyle_keys[static_cast<int>(value)-static_cast<int>(QTextFrameFormat::BorderStyle_None)];
    return QString();
}

static QScriptValue qtscript_QTextFrameFormat_BorderStyle_toScriptValue(QScriptEngine *engine, const QTextFrameFormat::BorderStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextFrameFormat"));
    return clazz.property(qtscript_QTextFrameFormat_BorderStyle_toStringHelper(value));
}

static void qtscript_QTextFrameFormat_BorderStyle_fromScriptValue(const QScriptValue &value, QTextFrameFormat::BorderStyle &out)
{
    out = qvariant_cast<QTextFrameFormat::BorderStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextFrameFormat_BorderStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextFrameFormat::BorderStyle_None) && (arg <= QTextFrameFormat::BorderStyle_Outset))
        return qScriptValueFromValue(engine,  static_cast<QTextFrameFormat::BorderStyle>(arg));
    return context->throwError(QString::fromLatin1("BorderStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextFrameFormat_BorderStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextFrameFormat::BorderStyle value = qscriptvalue_cast<QTextFrameFormat::BorderStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextFrameFormat_BorderStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextFrameFormat::BorderStyle value = qscriptvalue_cast<QTextFrameFormat::BorderStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextFrameFormat_BorderStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextFrameFormat_BorderStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextFrameFormat_BorderStyle,
        qtscript_QTextFrameFormat_BorderStyle_valueOf, qtscript_QTextFrameFormat_BorderStyle_toString);
    qScriptRegisterMetaType<QTextFrameFormat::BorderStyle>(engine, qtscript_QTextFrameFormat_BorderStyle_toScriptValue,
        qtscript_QTextFrameFormat_BorderStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextFrameFormat_BorderStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextFrameFormat_BorderStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextFrameFormat
//

static QScriptValue qtscript_QTextFrameFormat_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 26;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextFrameFormat* _q_self = qscriptvalue_cast<QTextFrameFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextFrameFormat.%0(): this object is not a QTextFrameFormat")
            .arg(qtscript_QTextFrameFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->border();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->borderBrush();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextFrameFormat::BorderStyle _q_result = _q_self->borderStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->bottomMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextLength _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->leftMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->margin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->padding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QFlags<QTextFormat::PageBreakFlag> _q_result = _q_self->pageBreakPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QTextFrameFormat::Position _q_result = _q_self->position();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->rightMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBorder(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBorderBrush(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QTextFrameFormat::BorderStyle _q_arg0 = qscriptvalue_cast<QTextFrameFormat::BorderStyle>(context->argument(0));
        _q_self->setBorderStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBottomMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextLength>() == context->argument(0).toVariant().userType())) {
            QTextLength _q_arg0 = qscriptvalue_cast<QTextLength>(context->argument(0));
            _q_self->setHeight(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<qreal>() == context->argument(0).toVariant().userType())) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            _q_self->setHeight(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setLeftMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QFlags<QTextFormat::PageBreakFlag> _q_arg0 = qscriptvalue_cast<QFlags<QTextFormat::PageBreakFlag> >(context->argument(0));
        _q_self->setPageBreakPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QTextFrameFormat::Position _q_arg0 = qscriptvalue_cast<QTextFrameFormat::Position>(context->argument(0));
        _q_self->setPosition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRightMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setTopMargin(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextLength>() == context->argument(0).toVariant().userType())) {
            QTextLength _q_arg0 = qscriptvalue_cast<QTextLength>(context->argument(0));
            _q_self->setWidth(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<qreal>() == context->argument(0).toVariant().userType())) {
            qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
            _q_self->setWidth(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->topMargin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QTextLength _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26: {
    QString result = QString::fromLatin1("QTextFrameFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFrameFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextFrameFormat_function_names[_id+1],
        qtscript_QTextFrameFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextFrameFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextFrameFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextFrameFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextFrameFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFrameFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextFrameFormat_function_names[_id],
        qtscript_QTextFrameFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextFrameFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextFrameFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextFrameFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextFormat*>()));
    for (int i = 0; i < 27; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextFrameFormat_prototype_call, qtscript_QTextFrameFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextFrameFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextFrameFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextFrameFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextFrameFormat_static_call, proto, qtscript_QTextFrameFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Position"),
        qtscript_create_QTextFrameFormat_Position_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BorderStyle"),
        qtscript_create_QTextFrameFormat_BorderStyle_class(engine, ctor));
    return ctor;
}
