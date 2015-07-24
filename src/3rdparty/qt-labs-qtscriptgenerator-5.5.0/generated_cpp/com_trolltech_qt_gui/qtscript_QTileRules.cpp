#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdrawutil.h>
#include <QVariant>

#include "qtscriptshell_QTileRules.h"

static const char * const qtscript_QTileRules_function_names[] = {
    "QTileRules"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QTileRules_function_signatures[] = {
    "TileRule horizontalRule, TileRule verticalRule\nTileRule rule"
    // static
    // prototype
""
};

static const int qtscript_QTileRules_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QTileRules_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTileRules::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTileRules)
Q_DECLARE_METATYPE(QTileRules*)
Q_DECLARE_METATYPE(QtScriptShell_QTileRules)
Q_DECLARE_METATYPE(QtScriptShell_QTileRules*)
Q_DECLARE_METATYPE(Qt::TileRule)

//
// QTileRules
//

static QScriptValue qtscript_QTileRules_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTileRules* _q_self = qscriptvalue_cast<QTileRules*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTileRules.%0(): this object is not a QTileRules")
            .arg(qtscript_QTileRules_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QTileRules");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTileRules_throw_ambiguity_error_helper(context,
        qtscript_QTileRules_function_names[_id+1],
        qtscript_QTileRules_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTileRules_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTileRules(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTileRules _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTileRules)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        Qt::TileRule _q_arg0 = qscriptvalue_cast<Qt::TileRule>(context->argument(0));
        QtScriptShell_QTileRules _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTileRules)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        Qt::TileRule _q_arg0 = qscriptvalue_cast<Qt::TileRule>(context->argument(0));
        Qt::TileRule _q_arg1 = qscriptvalue_cast<Qt::TileRule>(context->argument(1));
        QtScriptShell_QTileRules _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTileRules)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTileRules_throw_ambiguity_error_helper(context,
        qtscript_QTileRules_function_names[_id],
        qtscript_QTileRules_function_signatures[_id]);
}

QScriptValue qtscript_create_QTileRules_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTileRules*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTileRules*)0));

    engine->setDefaultPrototype(qMetaTypeId<QTileRules>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTileRules*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTileRules_static_call, proto, qtscript_QTileRules_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
