#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessible.h>
#include <QVariant>
#include <qaccessible.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>

#include "qtscriptshell_QAccessibleInterfaceEx.h"

static const char * const qtscript_QAccessibleInterfaceEx_function_names[] = {
    "QAccessibleInterfaceEx"
    // static
    // prototype
    , "invokeMethodEx"
    , "virtual_hook"
    , "toString"
};

static const char * const qtscript_QAccessibleInterfaceEx_function_signatures[] = {
    ""
    // static
    // prototype
    , "Method method, int child, List params"
    , "Object data"
""
};

static const int qtscript_QAccessibleInterfaceEx_function_lengths[] = {
    0
    // static
    // prototype
    , 3
    , 1
    , 0
};

static QScriptValue qtscript_QAccessibleInterfaceEx_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleInterfaceEx::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleInterfaceEx*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessibleInterfaceEx*)
Q_DECLARE_METATYPE(QAccessible::Method)
Q_DECLARE_METATYPE(QAccessibleInterface*)

//
// QAccessibleInterfaceEx
//

static QScriptValue qtscript_QAccessibleInterfaceEx_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAccessibleInterfaceEx* _q_self = qscriptvalue_cast<QAccessibleInterfaceEx*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleInterfaceEx.%0(): this object is not a QAccessibleInterfaceEx")
            .arg(qtscript_QAccessibleInterfaceEx_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QAccessible::Method _q_arg0 = qscriptvalue_cast<QAccessible::Method>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QList<QVariant> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QVariant _q_result = _q_self->invokeMethodEx(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        QVariant _q_result = _q_self->virtual_hook(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QAccessibleInterfaceEx");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleInterfaceEx_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleInterfaceEx_function_names[_id+1],
        qtscript_QAccessibleInterfaceEx_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleInterfaceEx_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleInterfaceEx(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAccessibleInterfaceEx* _q_cpp_result = new QtScriptShell_QAccessibleInterfaceEx();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleInterfaceEx*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleInterfaceEx_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleInterfaceEx_function_names[_id],
        qtscript_QAccessibleInterfaceEx_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleInterfaceEx_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleInterfaceEx*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleInterfaceEx*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAccessibleInterface*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessibleInterfaceEx_prototype_call, qtscript_QAccessibleInterfaceEx_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAccessibleInterfaceEx_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleInterfaceEx*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleInterfaceEx_static_call, proto, qtscript_QAccessibleInterfaceEx_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
