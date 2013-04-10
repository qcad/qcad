#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextlayout.h>
#include <QTextLayout>
#include <QVariant>
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>

static const char * const qtscript_QTextLine_function_names[] = {
    "QTextLine"
    // static
    // prototype
    , "ascent"
    , "cursorToX"
    , "descent"
    , "draw"
    , "height"
    , "horizontalAdvance"
    , "isValid"
    , "leading"
    , "leadingIncluded"
    , "lineNumber"
    , "naturalTextRect"
    , "naturalTextWidth"
    , "position"
    , "rect"
    , "setLeadingIncluded"
    , "setLineWidth"
    , "setNumColumns"
    , "setPosition"
    , "textLength"
    , "textStart"
    , "width"
    , "x"
    , "xToCursor"
    , "y"
    , "toString"
};

static const char * const qtscript_QTextLine_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "int cursorPos, Edge edge"
    , ""
    , "QPainter p, QPointF point, QTextLayout_FormatRange selection"
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
    , "bool included"
    , "qreal width"
    , "int columns\nint columns, qreal alignmentWidth"
    , "QPointF pos"
    , ""
    , ""
    , ""
    , ""
    , "qreal x, CursorPosition arg__2"
    , ""
""
};

static const int qtscript_QTextLine_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 2
    , 0
    , 3
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
    , 2
    , 1
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QTextLine_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextLine::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextLine)
Q_DECLARE_METATYPE(QTextLine*)
Q_DECLARE_METATYPE(QTextLine::Edge)
Q_DECLARE_METATYPE(QTextLine::CursorPosition)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QTextLayout::FormatRange*)

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
// QTextLine::Edge
//

static const QTextLine::Edge qtscript_QTextLine_Edge_values[] = {
    QTextLine::Leading
    , QTextLine::Trailing
};

static const char * const qtscript_QTextLine_Edge_keys[] = {
    "Leading"
    , "Trailing"
};

static QString qtscript_QTextLine_Edge_toStringHelper(QTextLine::Edge value)
{
    if ((value >= QTextLine::Leading) && (value <= QTextLine::Trailing))
        return qtscript_QTextLine_Edge_keys[static_cast<int>(value)-static_cast<int>(QTextLine::Leading)];
    return QString();
}

static QScriptValue qtscript_QTextLine_Edge_toScriptValue(QScriptEngine *engine, const QTextLine::Edge &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextLine"));
    return clazz.property(qtscript_QTextLine_Edge_toStringHelper(value));
}

static void qtscript_QTextLine_Edge_fromScriptValue(const QScriptValue &value, QTextLine::Edge &out)
{
    out = qvariant_cast<QTextLine::Edge>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextLine_Edge(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextLine::Leading) && (arg <= QTextLine::Trailing))
        return qScriptValueFromValue(engine,  static_cast<QTextLine::Edge>(arg));
    return context->throwError(QString::fromLatin1("Edge(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextLine_Edge_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextLine::Edge value = qscriptvalue_cast<QTextLine::Edge>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextLine_Edge_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextLine::Edge value = qscriptvalue_cast<QTextLine::Edge>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextLine_Edge_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextLine_Edge_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextLine_Edge,
        qtscript_QTextLine_Edge_valueOf, qtscript_QTextLine_Edge_toString);
    qScriptRegisterMetaType<QTextLine::Edge>(engine, qtscript_QTextLine_Edge_toScriptValue,
        qtscript_QTextLine_Edge_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextLine_Edge_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextLine_Edge_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextLine::CursorPosition
//

static const QTextLine::CursorPosition qtscript_QTextLine_CursorPosition_values[] = {
    QTextLine::CursorBetweenCharacters
    , QTextLine::CursorOnCharacter
};

static const char * const qtscript_QTextLine_CursorPosition_keys[] = {
    "CursorBetweenCharacters"
    , "CursorOnCharacter"
};

static QString qtscript_QTextLine_CursorPosition_toStringHelper(QTextLine::CursorPosition value)
{
    if ((value >= QTextLine::CursorBetweenCharacters) && (value <= QTextLine::CursorOnCharacter))
        return qtscript_QTextLine_CursorPosition_keys[static_cast<int>(value)-static_cast<int>(QTextLine::CursorBetweenCharacters)];
    return QString();
}

static QScriptValue qtscript_QTextLine_CursorPosition_toScriptValue(QScriptEngine *engine, const QTextLine::CursorPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextLine"));
    return clazz.property(qtscript_QTextLine_CursorPosition_toStringHelper(value));
}

static void qtscript_QTextLine_CursorPosition_fromScriptValue(const QScriptValue &value, QTextLine::CursorPosition &out)
{
    out = qvariant_cast<QTextLine::CursorPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextLine_CursorPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextLine::CursorBetweenCharacters) && (arg <= QTextLine::CursorOnCharacter))
        return qScriptValueFromValue(engine,  static_cast<QTextLine::CursorPosition>(arg));
    return context->throwError(QString::fromLatin1("CursorPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextLine_CursorPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextLine::CursorPosition value = qscriptvalue_cast<QTextLine::CursorPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextLine_CursorPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextLine::CursorPosition value = qscriptvalue_cast<QTextLine::CursorPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextLine_CursorPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextLine_CursorPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextLine_CursorPosition,
        qtscript_QTextLine_CursorPosition_valueOf, qtscript_QTextLine_CursorPosition_toString);
    qScriptRegisterMetaType<QTextLine::CursorPosition>(engine, qtscript_QTextLine_CursorPosition_toScriptValue,
        qtscript_QTextLine_CursorPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextLine_CursorPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextLine_CursorPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextLine
//

static QScriptValue qtscript_QTextLine_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextLine* _q_self = qscriptvalue_cast<QTextLine*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextLine.%0(): this object is not a QTextLine")
            .arg(qtscript_QTextLine_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->ascent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->cursorToX(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextLine::Edge _q_arg1 = qscriptvalue_cast<QTextLine::Edge>(context->argument(1));
        qreal _q_result = _q_self->cursorToX(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->descent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        _q_self->draw(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QTextLayout::FormatRange* _q_arg2 = qscriptvalue_cast<QTextLayout::FormatRange*>(context->argument(2));
        _q_self->draw(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->horizontalAdvance();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->leading();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->leadingIncluded();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lineNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->naturalTextRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->naturalTextWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->position();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->rect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setLeadingIncluded(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setLineWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setNumColumns(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setNumColumns(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPosition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->textLength();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->textStart();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->x();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        int _q_result = _q_self->xToCursor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QTextLine::CursorPosition _q_arg1 = qscriptvalue_cast<QTextLine::CursorPosition>(context->argument(1));
        int _q_result = _q_self->xToCursor(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->y();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24: {
    QString result = QString::fromLatin1("QTextLine");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextLine_throw_ambiguity_error_helper(context,
        qtscript_QTextLine_function_names[_id+1],
        qtscript_QTextLine_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextLine_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextLine(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextLine _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextLine_throw_ambiguity_error_helper(context,
        qtscript_QTextLine_function_names[_id],
        qtscript_QTextLine_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextLine_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextLine*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextLine*)0));
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextLine_prototype_call, qtscript_QTextLine_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextLine_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextLine>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextLine*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextLine_static_call, proto, qtscript_QTextLine_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Edge"),
        qtscript_create_QTextLine_Edge_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CursorPosition"),
        qtscript_create_QTextLine_CursorPosition_class(engine, ctor));
    return ctor;
}
