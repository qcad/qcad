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

#include "qtscriptshell_QTextTableFormat.h"

static const char * const qtscript_QTextTableFormat_function_names[] = {
    "QTextTableFormat"
    // static
    // prototype
    , "alignment"
    , "cellPadding"
    , "cellSpacing"
    , "clearColumnWidthConstraints"
    , "columnWidthConstraints"
    , "columns"
    , "headerRowCount"
    , "setAlignment"
    , "setCellPadding"
    , "setCellSpacing"
    , "setColumnWidthConstraints"
    , "setColumns"
    , "setHeaderRowCount"
    , "toString"
};

static const char * const qtscript_QTextTableFormat_function_signatures[] = {
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
    , "Alignment alignment"
    , "qreal padding"
    , "qreal spacing"
    , "List constraints"
    , "int columns"
    , "int count"
""
};

static const int qtscript_QTextTableFormat_function_lengths[] = {
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
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTextTableFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextTableFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextTableFormat)
Q_DECLARE_METATYPE(QTextTableFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextTableFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextTableFormat*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QVector<QTextLength>)
Q_DECLARE_METATYPE(QTextFrameFormat*)

//
// QTextTableFormat
//

static QScriptValue qtscript_QTextTableFormat_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextTableFormat* _q_self = qscriptvalue_cast<QTextTableFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextTableFormat.%0(): this object is not a QTextTableFormat")
            .arg(qtscript_QTextTableFormat_function_names[_id+1]));
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
        qreal _q_result = _q_self->cellPadding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->cellSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clearColumnWidthConstraints();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QVector<QTextLength> _q_result = _q_self->columnWidthConstraints();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columns();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->headerRowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QFlags<Qt::AlignmentFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(0));
        _q_self->setAlignment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setCellPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setCellSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QVector<QTextLength> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setColumnWidthConstraints(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setColumns(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setHeaderRowCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QTextTableFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTableFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextTableFormat_function_names[_id+1],
        qtscript_QTextTableFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextTableFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextTableFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextTableFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextTableFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTableFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextTableFormat_function_names[_id],
        qtscript_QTextTableFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextTableFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextTableFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextTableFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextFrameFormat*>()));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextTableFormat_prototype_call, qtscript_QTextTableFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextTableFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextTableFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextTableFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextTableFormat_static_call, proto, qtscript_QTextTableFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
