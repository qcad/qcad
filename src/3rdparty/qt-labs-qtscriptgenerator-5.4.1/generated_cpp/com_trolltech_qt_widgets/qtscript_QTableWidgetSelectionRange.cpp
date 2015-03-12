#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtablewidget.h>
#include <QVariant>
#include <qtablewidget.h>

static const char * const qtscript_QTableWidgetSelectionRange_function_names[] = {
    "QTableWidgetSelectionRange"
    // static
    // prototype
    , "bottomRow"
    , "columnCount"
    , "leftColumn"
    , "rightColumn"
    , "rowCount"
    , "topRow"
    , "toString"
};

static const char * const qtscript_QTableWidgetSelectionRange_function_signatures[] = {
    "\nQTableWidgetSelectionRange other\nint top, int left, int bottom, int right"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTableWidgetSelectionRange_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTableWidgetSelectionRange_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTableWidgetSelectionRange::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTableWidgetSelectionRange)
Q_DECLARE_METATYPE(QTableWidgetSelectionRange*)

//
// QTableWidgetSelectionRange
//

static QScriptValue qtscript_QTableWidgetSelectionRange_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTableWidgetSelectionRange* _q_self = qscriptvalue_cast<QTableWidgetSelectionRange*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTableWidgetSelectionRange.%0(): this object is not a QTableWidgetSelectionRange")
            .arg(qtscript_QTableWidgetSelectionRange_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->bottomRow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->leftColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rightColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->topRow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QTableWidgetSelectionRange");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableWidgetSelectionRange_throw_ambiguity_error_helper(context,
        qtscript_QTableWidgetSelectionRange_function_names[_id+1],
        qtscript_QTableWidgetSelectionRange_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTableWidgetSelectionRange_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTableWidgetSelectionRange(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTableWidgetSelectionRange _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QTableWidgetSelectionRange _q_arg0 = qscriptvalue_cast<QTableWidgetSelectionRange>(context->argument(0));
        QTableWidgetSelectionRange _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QTableWidgetSelectionRange _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableWidgetSelectionRange_throw_ambiguity_error_helper(context,
        qtscript_QTableWidgetSelectionRange_function_names[_id],
        qtscript_QTableWidgetSelectionRange_function_signatures[_id]);
}

QScriptValue qtscript_create_QTableWidgetSelectionRange_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTableWidgetSelectionRange*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTableWidgetSelectionRange*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTableWidgetSelectionRange_prototype_call, qtscript_QTableWidgetSelectionRange_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTableWidgetSelectionRange_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTableWidgetSelectionRange>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTableWidgetSelectionRange*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTableWidgetSelectionRange_static_call, proto, qtscript_QTableWidgetSelectionRange_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
