#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextlayout.h>
#include <QTextLayout>
#include <QTextOption>
#include <QVariant>
#include <qfont.h>
#include <qlist.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>
#include <qtextlayout.h>
#include <qtextobject.h>
#include <qvector.h>

static const char * const qtscript_QTextLayout_function_names[] = {
    "QTextLayout"
    // static
    // prototype
    , "additionalFormats"
    , "beginLayout"
    , "boundingRect"
    , "cacheEnabled"
    , "clearAdditionalFormats"
    , "clearLayout"
    , "createLine"
    , "draw"
    , "drawCursor"
    , "endLayout"
    , "font"
    , "isValidCursorPosition"
    , "lineAt"
    , "lineCount"
    , "lineForTextPosition"
    , "maximumWidth"
    , "minimumWidth"
    , "nextCursorPosition"
    , "position"
    , "preeditAreaPosition"
    , "preeditAreaText"
    , "previousCursorPosition"
    , "setAdditionalFormats"
    , "setCacheEnabled"
    , "setFlags"
    , "setFont"
    , "setPosition"
    , "setPreeditArea"
    , "setText"
    , "setTextOption"
    , "text"
    , "textOption"
    , "toString"
};

static const char * const qtscript_QTextLayout_function_signatures[] = {
    "\nString text\nString text, QFont font, QPaintDevice paintdevice\nQTextBlock b"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QPainter p, QPointF pos, List selections, QRectF clip"
    , "QPainter p, QPointF pos, int cursorPosition\nQPainter p, QPointF pos, int cursorPosition, int width"
    , ""
    , ""
    , "int pos"
    , "int i"
    , ""
    , "int pos"
    , ""
    , ""
    , "int oldPos, CursorMode mode"
    , ""
    , ""
    , ""
    , "int oldPos, CursorMode mode"
    , "List overrides"
    , "bool enable"
    , "int flags"
    , "QFont f"
    , "QPointF p"
    , "int position, String text"
    , "String string"
    , "QTextOption option"
    , ""
    , ""
""
};

static const int qtscript_QTextLayout_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 4
    , 4
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextLayout*)
Q_DECLARE_METATYPE(QTextLayout::CursorMode)
Q_DECLARE_METATYPE(QTextLayout::FormatRange)
Q_DECLARE_METATYPE(QList<QTextLayout::FormatRange>)
Q_DECLARE_METATYPE(QTextLine)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QVector<QTextLayout::FormatRange>)
Q_DECLARE_METATYPE(QTextOption)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QTextBlock)

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
// QTextLayout::CursorMode
//

static const QTextLayout::CursorMode qtscript_QTextLayout_CursorMode_values[] = {
    QTextLayout::SkipCharacters
    , QTextLayout::SkipWords
};

static const char * const qtscript_QTextLayout_CursorMode_keys[] = {
    "SkipCharacters"
    , "SkipWords"
};

static QString qtscript_QTextLayout_CursorMode_toStringHelper(QTextLayout::CursorMode value)
{
    if ((value >= QTextLayout::SkipCharacters) && (value <= QTextLayout::SkipWords))
        return qtscript_QTextLayout_CursorMode_keys[static_cast<int>(value)-static_cast<int>(QTextLayout::SkipCharacters)];
    return QString();
}

static QScriptValue qtscript_QTextLayout_CursorMode_toScriptValue(QScriptEngine *engine, const QTextLayout::CursorMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextLayout"));
    return clazz.property(qtscript_QTextLayout_CursorMode_toStringHelper(value));
}

static void qtscript_QTextLayout_CursorMode_fromScriptValue(const QScriptValue &value, QTextLayout::CursorMode &out)
{
    out = qvariant_cast<QTextLayout::CursorMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextLayout_CursorMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextLayout::SkipCharacters) && (arg <= QTextLayout::SkipWords))
        return qScriptValueFromValue(engine,  static_cast<QTextLayout::CursorMode>(arg));
    return context->throwError(QString::fromLatin1("CursorMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextLayout_CursorMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextLayout::CursorMode value = qscriptvalue_cast<QTextLayout::CursorMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextLayout_CursorMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextLayout::CursorMode value = qscriptvalue_cast<QTextLayout::CursorMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextLayout_CursorMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextLayout_CursorMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextLayout_CursorMode,
        qtscript_QTextLayout_CursorMode_valueOf, qtscript_QTextLayout_CursorMode_toString);
    qScriptRegisterMetaType<QTextLayout::CursorMode>(engine, qtscript_QTextLayout_CursorMode_toScriptValue,
        qtscript_QTextLayout_CursorMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextLayout_CursorMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextLayout_CursorMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextLayout
//

static QScriptValue qtscript_QTextLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 32;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextLayout* _q_self = qscriptvalue_cast<QTextLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextLayout.%0(): this object is not a QTextLayout")
            .arg(qtscript_QTextLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QTextLayout::FormatRange> _q_result = _q_self->additionalFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->beginLayout();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->cacheEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->clearAdditionalFormats();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->clearLayout();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QTextLine _q_result = _q_self->createLine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QVector<QTextLayout::FormatRange> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        _q_self->draw(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QVector<QTextLayout::FormatRange> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QRectF _q_arg3 = qscriptvalue_cast<QRectF>(context->argument(3));
        _q_self->draw(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->drawCursor(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->drawCursor(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->endLayout();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isValidCursorPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextLine _q_result = _q_self->lineAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lineCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextLine _q_result = _q_self->lineForTextPosition(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->maximumWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->minimumWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->nextCursorPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextLayout::CursorMode _q_arg1 = qscriptvalue_cast<QTextLayout::CursorMode>(context->argument(1));
        int _q_result = _q_self->nextCursorPosition(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->position();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->preeditAreaPosition();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->preeditAreaText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->previousCursorPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextLayout::CursorMode _q_arg1 = qscriptvalue_cast<QTextLayout::CursorMode>(context->argument(1));
        int _q_result = _q_self->previousCursorPosition(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QList<QTextLayout::FormatRange> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setAdditionalFormats(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setCacheEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPosition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setPreeditArea(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QTextOption _q_arg0 = qscriptvalue_cast<QTextOption>(context->argument(0));
        _q_self->setTextOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QTextOption _q_result = _q_self->textOption();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32: {
    QString result = QString::fromLatin1("QTextLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextLayout_throw_ambiguity_error_helper(context,
        qtscript_QTextLayout_function_names[_id+1],
        qtscript_QTextLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextLayout* _q_cpp_result = new QTextLayout();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QTextLayout* _q_cpp_result = new QTextLayout(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QTextBlock>() == context->argument(0).toVariant().userType())) {
            QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
            QTextLayout* _q_cpp_result = new QTextLayout(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        QTextLayout* _q_cpp_result = new QTextLayout(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        QPaintDevice* _q_arg2 = qscriptvalue_cast<QPaintDevice*>(context->argument(2));
        QTextLayout* _q_cpp_result = new QTextLayout(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextLayout_throw_ambiguity_error_helper(context,
        qtscript_QTextLayout_function_names[_id],
        qtscript_QTextLayout_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextLayout*)0));
    for (int i = 0; i < 33; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextLayout_prototype_call, qtscript_QTextLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextLayout*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextLayout_static_call, proto, qtscript_QTextLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("CursorMode"),
        qtscript_create_QTextLayout_CursorMode_class(engine, ctor));
    return ctor;
}
