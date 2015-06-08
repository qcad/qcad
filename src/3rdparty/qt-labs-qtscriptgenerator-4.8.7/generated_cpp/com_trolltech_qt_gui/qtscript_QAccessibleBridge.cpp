#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessiblebridge.h>
#include <QVariant>
#include <qaccessible.h>

#include "qtscriptshell_QAccessibleBridge.h"

static const char * const qtscript_QAccessibleBridge_function_names[] = {
    "QAccessibleBridge"
    // static
    // prototype
    , "notifyAccessibilityUpdate"
    , "setRootObject"
    , "toString"
};

static const char * const qtscript_QAccessibleBridge_function_signatures[] = {
    ""
    // static
    // prototype
    , "int arg__1, QAccessibleInterface arg__2, int arg__3"
    , "QAccessibleInterface arg__1"
""
};

static const int qtscript_QAccessibleBridge_function_lengths[] = {
    0
    // static
    // prototype
    , 3
    , 1
    , 0
};

static QScriptValue qtscript_QAccessibleBridge_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleBridge::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleBridge*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessibleBridge*)
Q_DECLARE_METATYPE(QAccessibleInterface*)

//
// QAccessibleBridge
//

static QScriptValue qtscript_QAccessibleBridge_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAccessibleBridge* _q_self = qscriptvalue_cast<QAccessibleBridge*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleBridge.%0(): this object is not a QAccessibleBridge")
            .arg(qtscript_QAccessibleBridge_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QAccessibleInterface* _q_arg1 = qscriptvalue_cast<QAccessibleInterface*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->notifyAccessibilityUpdate(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QAccessibleInterface* _q_arg0 = qscriptvalue_cast<QAccessibleInterface*>(context->argument(0));
        _q_self->setRootObject(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QAccessibleBridge");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleBridge_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleBridge_function_names[_id+1],
        qtscript_QAccessibleBridge_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleBridge_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleBridge(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAccessibleBridge* _q_cpp_result = new QtScriptShell_QAccessibleBridge();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleBridge*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleBridge_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleBridge_function_names[_id],
        qtscript_QAccessibleBridge_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleBridge_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleBridge*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleBridge*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessibleBridge_prototype_call, qtscript_QAccessibleBridge_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAccessibleBridge_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleBridge*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleBridge_static_call, proto, qtscript_QAccessibleBridge_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
