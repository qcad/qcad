#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtexttable.h>
#include <QTextCursor>
#include <QTextFrame>
#include <QVariant>
#include <qtextcursor.h>
#include <qtextformat.h>
#include <qtexttable.h>

static const char * const qtscript_QTextTableCell_function_names[] = {
    "QTextTableCell"
    // static
    // prototype
    , "begin"
    , "column"
    , "columnSpan"
    , "end"
    , "firstCursorPosition"
    , "firstPosition"
    , "format"
    , "isValid"
    , "lastCursorPosition"
    , "lastPosition"
    , "equals"
    , "row"
    , "rowSpan"
    , "setFormat"
    , "tableCellFormatIndex"
    , "toString"
};

static const char * const qtscript_QTextTableCell_function_signatures[] = {
    "\nQTextTableCell o"
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
    , "QTextTableCell other"
    , ""
    , ""
    , "QTextCharFormat format"
    , ""
""
};

static const int qtscript_QTextTableCell_function_lengths[] = {
    1
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
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextTableCell_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextTableCell::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextTableCell)
Q_DECLARE_METATYPE(QTextTableCell*)
Q_DECLARE_METATYPE(QTextFrame::iterator)
Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QTextCharFormat)

//
// QTextTableCell
//

static QScriptValue qtscript_QTextTableCell_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 15;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextTableCell* _q_self = qscriptvalue_cast<QTextTableCell*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextTableCell.%0(): this object is not a QTextTableCell")
            .arg(qtscript_QTextTableCell_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextFrame::iterator _q_result = _q_self->begin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->column();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnSpan();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QTextFrame::iterator _q_result = _q_self->end();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->firstCursorPosition();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->firstPosition();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->lastCursorPosition();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lastPosition();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QTextTableCell _q_arg0 = qscriptvalue_cast<QTextTableCell>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->row();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowSpan();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->tableCellFormatIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15: {
    QString result = QString::fromLatin1("QTextTableCell");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTableCell_throw_ambiguity_error_helper(context,
        qtscript_QTextTableCell_function_names[_id+1],
        qtscript_QTextTableCell_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextTableCell_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextTableCell(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextTableCell _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QTextTableCell _q_arg0 = qscriptvalue_cast<QTextTableCell>(context->argument(0));
        QTextTableCell _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTableCell_throw_ambiguity_error_helper(context,
        qtscript_QTextTableCell_function_names[_id],
        qtscript_QTextTableCell_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextTableCell_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextTableCell*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextTableCell*)0));
    for (int i = 0; i < 16; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextTableCell_prototype_call, qtscript_QTextTableCell_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextTableCell_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextTableCell>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextTableCell*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextTableCell_static_call, proto, qtscript_QTextTableCell_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
