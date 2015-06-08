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

#include "qtscriptshell_QTextTableCellFormat.h"

static const char * const qtscript_QTextTableCellFormat_function_names[] = {
    "QTextTableCellFormat"
    // static
    // prototype
    , "bottomPadding"
    , "leftPadding"
    , "rightPadding"
    , "setBottomPadding"
    , "setLeftPadding"
    , "setPadding"
    , "setRightPadding"
    , "setTopPadding"
    , "topPadding"
    , "toString"
};

static const char * const qtscript_QTextTableCellFormat_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , "qreal padding"
    , "qreal padding"
    , "qreal padding"
    , "qreal padding"
    , "qreal padding"
    , ""
""
};

static const int qtscript_QTextTableCellFormat_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextTableCellFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextTableCellFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextTableCellFormat)
Q_DECLARE_METATYPE(QTextTableCellFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextTableCellFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextTableCellFormat*)
Q_DECLARE_METATYPE(QTextCharFormat*)

//
// QTextTableCellFormat
//

static QScriptValue qtscript_QTextTableCellFormat_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextTableCellFormat* _q_self = qscriptvalue_cast<QTextTableCellFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextTableCellFormat.%0(): this object is not a QTextTableCellFormat")
            .arg(qtscript_QTextTableCellFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->bottomPadding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->leftPadding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->rightPadding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBottomPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setLeftPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRightPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setTopPadding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->topPadding();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QTextTableCellFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTableCellFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextTableCellFormat_function_names[_id+1],
        qtscript_QTextTableCellFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextTableCellFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextTableCellFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextTableCellFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextTableCellFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTableCellFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextTableCellFormat_function_names[_id],
        qtscript_QTextTableCellFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextTableCellFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextTableCellFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextTableCellFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextCharFormat*>()));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextTableCellFormat_prototype_call, qtscript_QTextTableCellFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextTableCellFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextTableCellFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextTableCellFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextTableCellFormat_static_call, proto, qtscript_QTextTableCellFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
